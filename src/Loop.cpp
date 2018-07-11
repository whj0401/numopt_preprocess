//
// Created by whj on 6/13/18.
//

#include <set>
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
}