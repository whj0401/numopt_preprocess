//
// Created by whj on 6/11/18.
//

#include <sstream>
#include <fstream>
#include "Function.h"
#include "debug.h"

namespace le
{
    using namespace std;
    
    void Function::add_input_parameter(const le::Variable &v)
    {
        input_parameters.add_variable(v);
    }
    
    void Function::add_input_parameterlist()
    {
        SgFunctionParameterList *params = decl->get_parameterList();
        for (SgInitializedName *param : params->get_args())
        {
            std::string name = param->get_name().getString();
            SgType *type = param->get_type();
            Variable v(name, type);
            add_input_parameter(v);
        }
    }
    
    VariableTable Function::get_variables_declared_in_function() const
    {
        return root->get_all_declared_variables();
    }
    
    Function::Function(const std::string &_func_name, SgFunctionDeclaration *_decl, const string &_program_name) :
            func_name(_func_name), decl(_decl), program_name(_program_name)
    {
        if (decl == nullptr)
        {
            return;
        }
        add_input_parameterlist();
        SgFunctionDefinition *func_def = decl->get_definition();
        if (func_def == nullptr)
        {
            print_warning_function_no_definition(decl);
            return;
        }
        SgBasicBlock *func_body = func_def->get_body();
//        handle_block_statement(func_body);
        root = make_shared<Code_Tree_Node>();
        root->initial_make_symbolics(input_parameters);
        root->handle_block_statement(func_body);
    }
    
    string Function::to_string() const
    {
        stringstream ss;
        ss << "void " << func_name << input_parameters.to_parameterlist() << endl;
        root->write_code_to_ss(ss, 0);
    
        set<shared_ptr<Code_Tree_Node>> nodes;
        set<shared_ptr<Loop>> loops;
        root->get_all_nodes_need_to_be_printed(nodes, loops);
        for (auto &n : nodes)
        {
            n->write_node_function_to_ss(ss);
        }
        for (auto &l : loops)
        {
            ss << l->to_string() << endl;
        }
        return ss.str();
    }
    
    string Function::to_code() const
    {
        return "";
    }
    
    void Function::write_function_correspond_main_func(stringstream &ss) const
    {
        string tab = generate_tab(1);
        ss << "int main()" << endl;
        ss << "{" << endl;
        ss << input_parameters.to_declaration_code(1);
        ss << tab << func_name << input_parameters.to_variables_reference_list() << ";" << endl;
        ss << tab << "return 0;" << endl;
        ss << "}" << endl;
    }
    
    void Function::to_klee_code_functions() const
    {
        stringstream ss;
        ofstream out(klee_output_dir + func_name + source_code_file_postfix);
        ss << klee_code_file_includes << endl;
        ss << "void " << func_name << input_parameters.to_parameterlist() << endl;
        root->write_code_to_ss(ss, 0);
        this->write_function_correspond_main_func(ss);
        out << ss.str();
        out.close();
    
        set<shared_ptr<Code_Tree_Node>> nodes;
        set<shared_ptr<Loop>> loops;
        root->get_all_nodes_need_to_be_printed(nodes, loops);
        for (auto &n : nodes)
        {
            ofstream node_out(klee_output_dir + n->get_node_func_name() + source_code_file_postfix);
            stringstream node_ss;
            node_ss << klee_code_file_includes << endl;
            n->write_node_function_to_ss(node_ss);
            n->write_node_correspond_main_func(node_ss);
            node_out << node_ss.str();
            node_out.close();
        }
        for (auto &l : loops)
        {
            l->to_klee_code_functions();
        }
    }
    
    void Function::write_simple_json_file() const
    {
        stringstream ss;
        ofstream simple_json(klee_output_dir + func_name + ".json");
        string tab = generate_tab(1);
        VariableTable tmp = get_variables_declared_in_function() + input_parameters;
        ss << "{" << endl;
        ss << tab << "\"program_name\": " << "\"" << program_name << "\"," << endl;
        ss << tab << "\"function_name\": " << "\"" << func_name << "\"," << endl;
        ss << tab << "\"variables\": " << tmp.to_string() << "," << endl;
        ss << tab << "\"input_variables\": [";
        size_t size = input_parameters.T.size();
        size_t count = 1;
        for (auto &v : input_parameters.T)
        {
            ss << "\"" << v.second.var_name << "\"";
            if (count < size)
            {
                ss << ", ";
            }
            ++count;
        }
        ss << "]," << endl;
        ss << tab << "\"return\": " << "\"__return__\"," << endl;
        ss << tab << "\"paths\": []" << endl;
        ss << "}" << endl;
        simple_json << ss.str();
        simple_json.close();
    }
    
}