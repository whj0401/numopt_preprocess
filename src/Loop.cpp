//
// Created by whj on 6/13/18.
//

#include <set>
#include <fstream>
#include "Loop.h"
#include "debug.h"
#include "common.h"

namespace le
{
    volatile size_t loop_index = 0;
    
    size_t get_loop_index()
    {
        loop_index++;
        return loop_index;
    }
    
    Loop::Loop()
    {
        root = make_shared<Code_Tree_Node>();
        ID = get_loop_index();
    }
    
    void Loop::initial_out_loop_variables(const VariableTable &vars)
    {
        out_loop_vars = vars;
        root->initial_make_symbolics(out_loop_vars);
    }
    
    void Loop::init_for_statement(SgForStatement *for_stmt)
    {
        // TODO
    }
    
    void Loop::init_while_statement(SgWhileStmt *while_stmt)
    {
        SgStatement *test_stmt = while_stmt->get_condition();
        SgExpression *condition = nullptr;
        if (auto expr_stmt = dynamic_cast<SgExprStatement *>(test_stmt))
        {
            condition = expr_stmt->get_expression();
        }
        // while condition expression must not be NULL
        assert(condition != nullptr);
        root->initial_if_else_branch(condition);
        root->else_node->set_broke();
        // traverse the block of this while_stmt
        SgStatement *body_stmt = while_stmt->get_body();
        root->handle_statement(body_stmt);
    }
    
    string Loop::get_loop_func_name() const
    {
        stringstream ss;
        ss << "loop" << ID;
        return ss.str();
    }
    
    void Loop::write_loop_correspond_main_func(stringstream &ss) const
    {
        string tab = generate_tab(1);
        ss << "int main()" << endl;
        ss << "{" << endl;
        ss << out_loop_vars.to_declaration_code(1);
        ss << tab << "loop" << ID << out_loop_vars.to_variables_reference_list() << ";" << endl;
        ss << tab << "return 0;" << endl;
        ss << "}" << endl;
    }
    
    void Loop::to_klee_code_functions() const
    {
        stringstream ss;
        ofstream out(klee_output_dir + get_loop_func_name() + source_code_file_postfix);
        ss << klee_code_file_includes << endl;
        ss << "void " << get_loop_func_name() << out_loop_vars.to_parameterlist() << endl;
        root->write_code_to_ss(ss, 0);
        this->write_loop_correspond_main_func(ss);
        out << ss.str();
        out.close();
        
        set<shared_ptr<Code_Tree_Node>> nodes;
        set<shared_ptr<Loop>> loops;
        root->get_all_nodes_need_to_be_printed(nodes, loops);
        for (auto &n : nodes)
        {
            ofstream node_out(klee_output_dir + n->get_node_func_name() + source_code_file_postfix);
            ss.clear();
            ss << klee_code_file_includes << endl;
            n->write_node_function_to_ss(ss);
            n->write_node_correspond_main_func(ss);
            node_out << ss.str();
            node_out.close();
        }
        for (auto &l : loops)
        {
            l->to_klee_code_functions();
        }
    }
    
    VariableTable Loop::get_variables_declared_in_loop() const
    {
        return root->get_all_declared_variables();
    }
    
    void Loop::write_simple_json_file() const
    {
        stringstream ss;
        ofstream simple_json(klee_output_dir + get_loop_func_name() + ".json");
        string tab = generate_tab(1);
        VariableTable tmp = get_variables_declared_in_loop();
        tmp = tmp + forloop_initializer;
        ss << "{" << endl;
        ss << tab << "\"type\": " << "\"loop\"," << endl;
        ss << tab << "\"variables\": " << tmp.to_string() << "," << endl;
        ss << tab << "\"initializer\": {";
        size_t size = forloop_initializer.T.size();
        // TODO forloop initializer, not implemented
//        size_t count = 1;
//        for (auto &v : forloop_initializer.T)
//        {
//            ss << "\"" << v.second.var_name << "\"";
//            if (count < size)
//            {
//                ss << ", ";
//            }
//            ++count;
//        }
        ss << "}," << endl;
        ss << tab << "\"loop_body\": []" << endl;
        ss << "}" << endl;
        simple_json << ss.str();
        simple_json.close();
    }
    
    string Loop::to_string() const
    {
        stringstream ss;
        ss << "void loop" << ID << out_loop_vars.to_parameterlist() << endl;
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
}