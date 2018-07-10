//
// Created by whj on 6/11/18.
//

#ifndef CODE_ANALYSE_LOOP_H
#define CODE_ANALYSE_LOOP_H

#include "Variable.h"

namespace le
{
    using namespace std;
    
    enum LoopType
    {
        FOR,
        WHILE,
        DOWHILE
    };
    
    
    class Loop
    {
    public:
        size_t ID;
        VariableTable out_loop_vars;
        VariableTable lval_vars;
        
    };
    
}

#endif //CODE_ANALYSE_LOOP_H
