//
// Created by whj on 6/11/18.
//

#ifndef CODE_ANALYSE_LOOP_H
#define CODE_ANALYSE_LOOP_H

#include <set>
#include "Variable.h"
#include "Code_Tree_Node.h"

namespace le
{
    using namespace std;
    
    enum LoopType
    {
        FOR,
        WHILE,
        DOWHILE
    };
    
    class Code_Tree_Node;
    
    class Loop : public enable_shared_from_this<Loop>
    {
    public:
        size_t ID;
        VariableTable out_loop_vars;
        VariableTable lval_vars;
        shared_ptr<Code_Tree_Node> root;
        
        Loop();
        
        void initial_out_loop_variables(const VariableTable &vars);
        
        void init_for_statement(SgForStatement *for_stmt);
        
        void init_while_statement(SgWhileStmt *while_stmt);
        
        string to_string() const;
    };
    
}

#endif //CODE_ANALYSE_LOOP_H