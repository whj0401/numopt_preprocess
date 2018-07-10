//
// Created by whj on 6/11/18.
//

#ifndef CODE_ANALYSE_FUNCTION_H
#define CODE_ANALYSE_FUNCTION_H

#include <iostream>
#include <vector>
#include <string>
#include "common.h"
#include "Variable.h"
#include "Path.h"
#include "CodeCreater.h"
#include "Code_Tree_Node.h"

namespace le
{
    
    using namespace std;
    
    bool isAtomStatement(const SgStatement *stmt);
    
    class Function
    {
    private:
        void add_input_parameter(const Variable &v);
        
        void add_input_parameterlist();
        
        Function copy_with_no_end_path();
        
        void merge(const Function &f);
        
        void handle_expression(SgExpression *expr);
        
        void handle_statement(SgStatement *stmt);
        
        void handle_block_statement(SgBasicBlock *block);
        
        void handle_for_statement(SgForStatement *for_stmt);
        
        void handle_while_statement(SgWhileStmt *while_stmt);
        
        void handle_dowhile_statement(SgDoWhileStmt *dowhile_stmt);
        
        void handle_if_statement(SgIfStmt *if_stmt);
        
        void handle_switch_statement(SgSwitchStatement *switch_stmt);
        
        void handle_return_statement(SgReturnStmt *return_stmt);
        
        void handle_var_declaration(SgVariableDeclaration *decl);
        
        void handle_expr_statement(SgExprStatement *expr_s);
    
    public:
        string func_name;
        CodeCreater *_in_pool;
        SgFunctionDeclaration *decl;
        VariableTable var_tbl;
        VariableTable input_parameters;
        Paths *paths;
        shared_ptr<Code_Tree_Node> root;
        
        Function(const string &_func_name, SgFunctionDeclaration *_decl, CodeCreater *_pool = &paths_pool);

//        VariableTable collect_all_var_tbl();
        
        string to_string() const;
        
        string to_code() const;
        
        void to_klee_code_functions();
    };
    
}
#endif //CODE_ANALYSE_FUNCTION_H
