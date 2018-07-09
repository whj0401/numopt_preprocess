//
// Created by whj on 6/13/18.
//

#ifndef CODE_ANALYSE_COMMON_H
#define CODE_ANALYSE_COMMON_H

#include <string>
#include <sstream>
#include <fstream>
#include "rose.h"

namespace le
{
    extern const std::string TAB;
    
    extern std::map<VariantT, std::string> operator_str_map;
    
    void init_operator_str_map();
    
    inline std::string generate_tab(unsigned int tab_num)
    {
        std::stringstream ss;
        for (int i = 0; i < tab_num; ++i) ss << TAB;
        return ss.str();
    }
    
    template<class T>
    T *clone(SgNode * node)
    {
        if (node == nullptr) return nullptr;
        SgTreeCopy copy;
        return dynamic_cast<T *>(copy.copyAst(dynamic_cast<SgNode *>(node)));
    }
    
    SgVarRefExp *get_func_call_lhs(SgFunctionCallExp *func_call);
    
    inline bool isAtomStatement(const SgStatement *stmt)
    {
        return dynamic_cast<const SgForStatement *>(stmt) ||
               dynamic_cast<const SgWhileStmt *>(stmt) ||
               dynamic_cast<const SgDoWhileStmt *>(stmt) ||
               dynamic_cast<const SgIfStmt *>(stmt) ||
               dynamic_cast<const SgSwitchStatement *>(stmt);
    }
    
    bool write_stream_to_file(std::string out_file, std::stringstream &ss);
    
    std::string
    expression_to_string_with_value_map(const SgExpression *expr, const std::map<std::string, std::string> &val_map);
    
    bool is_empty_block(SgBasicBlock *block);
}

#endif //CODE_ANALYSE_COMMON_H
