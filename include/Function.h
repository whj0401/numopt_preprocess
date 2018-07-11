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
    
    public:
        string func_name;
        SgFunctionDeclaration *decl;
        VariableTable input_parameters;
        shared_ptr<Code_Tree_Node> root;
    
        Function(const string &_func_name, SgFunctionDeclaration *_decl);

//        VariableTable collect_all_var_tbl();
        
        string to_string() const;
        
        string to_code() const;
        
        void to_klee_code_functions();
    };
    
}
#endif //CODE_ANALYSE_FUNCTION_H
