//
// Created by whj on 7/10/18.
//

#include "Code_Tree_Node.h"
#include "common.h"

namespace le
{
    const string enter_block = "{";
    const string leave_block = "}";
    
    bool Code_Tree_Node::is_leaf_node() const
    {
        return (if_node == nullptr && else_node == nullptr && next_tree_root == nullptr);
    }
    
    vector<shared_ptr<Code_Tree_Node>> Code_Tree_Node::get_all_leaves_ptr()
    {
        vector<shared_ptr<Code_Tree_Node>> ret;
        vector<shared_ptr<Code_Tree_Node>> stack;
        stack.push_back(shared_from_this());
        while (!stack.empty())
        {
            if (stack.back()->is_leaf_node())
            {
                ret.push_back(stack.back());
                stack.pop_back();
            }
            else
            {
                auto tmp = stack.back();
                stack.pop_back();
                if (tmp->if_node != nullptr)
                {
                    stack.push_back(tmp->if_node);
                }
                if (tmp->else_node != nullptr)
                {
                    stack.push_back(tmp->else_node);
                }
                if (tmp->next_tree_root != nullptr)
                {
                    stack.push_back(tmp->next_tree_root);
                }
            }
        }
        return ret;
    }
    
    Code_Tree_Node::Code_Tree_Node() :
            has_returned(false),
            has_broken(false),
            has_continued(false),
            if_node(nullptr),
            else_node(nullptr),
            condition(nullptr),
            next_tree_root(nullptr),
            loop(nullptr)
    {}
    
    void Code_Tree_Node::add_stmt(const SgStatement *stmt)
    {
        if (!can_add_stmt()) return;
        if (next_tree_root != nullptr)
        {
            next_tree_root->add_stmt(stmt);
        }
        else if (condition != nullptr)
        {
            if_node->add_stmt(stmt);
            else_node->add_stmt(stmt);
        }
        else
        {
            code_lines.push_back(stmt->unparseToString());
        }
    }
    
    void Code_Tree_Node::add_str(const string &str)
    {
        if (!can_add_stmt()) return;
        if (next_tree_root != nullptr)
        {
            next_tree_root->add_str(str);
        }
        else if (condition != nullptr)
        {
            if_node->add_str(str);
            else_node->add_str(str);
        }
        else
        {
            code_lines.push_back(str);
        }
    }
    
    void Code_Tree_Node::set_returned()
    {
        if (!can_add_stmt()) return;
        if (next_tree_root != nullptr)
        {
            next_tree_root->set_returned();
        }
        else if (condition != nullptr)
        {
            if_node->set_returned();
            else_node->set_returned();
        }
        else
        {
            has_returned = true;
        }
    }
    
    void Code_Tree_Node::handle_block_statement(SgBasicBlock *block)
    {
        SgStatementPtrList &stmt_list = block->get_statements();
        for (auto s : stmt_list)
        {
            handle_statement(s);
        }
    }
    
    void Code_Tree_Node::handle_statement(SgStatement *stmt)
    {
        if (auto s = dynamic_cast<SgBasicBlock *>(stmt))
        {
            handle_block_statement(s);
        }
//        else if (auto s = dynamic_cast<SgForStatement *>(stmt))
//        {
//            handle_for_statement(s);
//        }
//        else if (auto s = dynamic_cast<SgWhileStmt *>(stmt))
//        {
//            handle_while_statement(s);
//        }
//        else if (auto s = dynamic_cast<SgDoWhileStmt *>(stmt))
//        {
//            handle_dowhile_statement(s);
//        }
        else if (auto s = dynamic_cast<SgIfStmt *>(stmt))
        {
            handle_if_statement(s);
        }
        else if (auto s = dynamic_cast<SgReturnStmt *>(stmt))
        {
            handle_return_statement(s);
        }
        else
        {
            add_stmt(stmt);
        }
    }
    
    void Code_Tree_Node::handle_return_statement(SgReturnStmt *return_stmt)
    {
        add_stmt(return_stmt);
        set_returned();
    }
    
    void Code_Tree_Node::handle_if_statement(SgIfStmt *if_stmt)
    {
        if (!can_add_stmt()) return;
        SgStatement *condition_stmt = if_stmt->get_conditional();
        if (auto *expr_stmt = dynamic_cast<SgExprStatement *>(condition_stmt))
        {
            SgExpression *condition = expr_stmt->get_expression();
            auto leaf_nodes = this->get_all_leaves_ptr();
            for (auto ptr : leaf_nodes)
            {
                // ignore returned branch
                if (!ptr->can_add_stmt()) continue;
                
                ptr->condition = condition;
                ptr->if_node = make_shared<Code_Tree_Node>();
                ptr->else_node = make_shared<Code_Tree_Node>();
                
                string true_stmt = string("if(") + condition->unparseToString() + ")";
                
                auto true_body = dynamic_cast<SgBasicBlock *>(if_stmt->get_true_body());
                auto false_body = dynamic_cast<SgBasicBlock *>(if_stmt->get_false_body());
                auto else_if_body = dynamic_cast<SgIfStmt *>(if_stmt->get_false_body());
                
                if (true_body != nullptr)
                {
                    ptr->if_node->handle_block_statement(true_body);
                }
                
                if (else_if_body != nullptr)
                {
                    ptr->else_node->handle_statement(else_if_body);
                }
                else if (false_body != nullptr)
                {
                    ptr->else_node->handle_block_statement(false_body);
                }
            }
        }
    }
    
    void Code_Tree_Node::write_code_to_ss(stringstream &ss, unsigned int tab_num) const
    {
        string tab1 = generate_tab(tab_num);
        ss << tab1 << enter_block << endl;
        string tab2 = generate_tab(tab_num + 1);
        for (const auto &stmt : code_lines)
        {
            ss << tab2 << stmt << endl;
        }
        if (condition != nullptr)
        {
            ss << tab2 << "if(" << condition->unparseToString() << ")" << endl;
            if_node->write_code_to_ss(ss, tab_num + 1);
            ss << tab2 << "else" << endl;
            else_node->write_code_to_ss(ss, tab_num + 1);
        }
        ss << tab1 << leave_block << endl;
    }
    
    Code_Tree_Node::~Code_Tree_Node()
    {
    
    }
    
}