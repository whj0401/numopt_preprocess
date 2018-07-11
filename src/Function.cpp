//
// Created by whj on 6/11/18.
//

#include <sstream>
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
    
    Function::Function(const std::string &_func_name, SgFunctionDeclaration *_decl) :
            func_name(_func_name), decl(_decl)
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
            ss << "void node" << n->ID << n->input_vars.to_parameterlist() << endl;
            n->write_code_to_ss(ss, 0);
            ss << endl;
        }
        for (auto &l : loops)
        {
            ss << l->to_string() << endl;
        }
        return ss.str();
    }
    
    string Function::to_code() const
    {
//        stringstream ss;
//        ss << "\"function_name\": " << "\"" << func_name << "\"" << endl;
//        ss << "\"variables\": " << var_tbl.to_string() << endl;
//        ss << "\"input_variables\": " << input_parameters.to_string() << endl;
//        ss << "\"paths\": [" << endl;
//        for (const auto &p : path_list)
//        {
//            ss << p.to_code(1);
//        }
//        ss << "]" << endl;
//        return ss.str();
        return "";
    }
    
    void Function::to_klee_code_functions()
    {
//        for (auto &p : path_list)
//        {
//            p.to_klee_code_functions(input_parameters);
//        }
    }
    
}