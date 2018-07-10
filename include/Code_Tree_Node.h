//
// Created by whj on 7/10/18.
//

#ifndef CODE_ANALYSE_CODE_TREE_NODE_H
#define CODE_ANALYSE_CODE_TREE_NODE_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "rose.h"
#include "Loop.h"

namespace le
{
    using namespace std;
    
    class Code_Tree_Node : public enable_shared_from_this<Code_Tree_Node>
    {
        vector<shared_ptr<Code_Tree_Node>> get_all_leaves_ptr();
        
        bool is_leaf_node() const;
    
    public:
        vector<string> code_lines;
        bool has_returned;
        bool has_broken;
        bool has_continued;
        shared_ptr<Code_Tree_Node> if_node;
        shared_ptr<Code_Tree_Node> else_node;
        shared_ptr<Code_Tree_Node> next_tree_root;
        shared_ptr<Loop> loop;
//        Code_Tree_Node* if_node;
//        Code_Tree_Node* else_node;
        SgExpression *condition;
//        Code_Tree_Node* next_tree_root;
//        Loop* loop;
        
        Code_Tree_Node();
        
        void add_stmt(const SgStatement *stmt);
        
        void add_str(const string &str);
        
        void add_loop(const SgStatement *stmt);
        
        void set_returned();
        
        void handle_statement(SgStatement *stmt);
        
        void handle_block_statement(SgBasicBlock *block);
        
        void handle_if_statement(SgIfStmt *if_stmt);
        
        void handle_return_statement(SgReturnStmt *return_stmt);
        
        void write_code_to_ss(stringstream &ss, unsigned int tab_num) const;
        
        bool can_add_stmt() const
        { return !has_returned && !has_broken && !has_continued; }
        
        ~Code_Tree_Node();
    };
}

#endif //CODE_ANALYSE_CODE_TREE_NODE_H
