//
// Created by whj on 6/13/18.
//


#include "common.h"

namespace le
{
    const std::string TAB = "    ";
    
    std::map<VariantT, std::string> operator_str_map;
    
    void init_operator_str_map()
    {
        operator_str_map[V_SgEqualityOp] = "==";
        operator_str_map[V_SgLessThanOp] = "<";
        operator_str_map[V_SgGreaterThanOp] = ">";
        operator_str_map[V_SgNotEqualOp] = "!=";
        operator_str_map[V_SgLessOrEqualOp] = "<=";
        operator_str_map[V_SgGreaterOrEqualOp] = ">=";
        operator_str_map[V_SgAddOp] = "+";
        operator_str_map[V_SgSubtractOp] = "-";
        operator_str_map[V_SgMultiplyOp] = "*";
        operator_str_map[V_SgDivideOp] = "/";
        operator_str_map[V_SgIntegerDivideOp] = "/";
        operator_str_map[V_SgModOp] = "%";
        operator_str_map[V_SgAndOp] = "&&";
        operator_str_map[V_SgOrOp] = "||";
        operator_str_map[V_SgBitXorOp] = "^";
        operator_str_map[V_SgBitAndOp] = "&";
        operator_str_map[V_SgBitOrOp] = "|";
        operator_str_map[V_SgCommaOpExp] = ",";
        operator_str_map[V_SgLshiftOp] = "<<";
        operator_str_map[V_SgRshiftOp] = ">>";
        operator_str_map[V_SgNotOp] = "!";
        operator_str_map[V_SgAssignOp] = "=";
        operator_str_map[V_SgPointerDerefExp] = "*";
        operator_str_map[V_SgAddressOfOp] = "&";
        operator_str_map[V_SgPlusAssignOp] = "+=";
        operator_str_map[V_SgMinusAssignOp] = "-=";
        operator_str_map[V_SgAndAssignOp] = "&&=";
        operator_str_map[V_SgIorAssignOp] = "||=";
        operator_str_map[V_SgMultAssignOp] = "*=";
        operator_str_map[V_SgDivAssignOp] = "/=";
        operator_str_map[V_SgModAssignOp] = "%=";
        operator_str_map[V_SgXorAssignOp] = "^=";
        operator_str_map[V_SgLshiftAssignOp] = "<<=";
    }
    
    std::string get_operator_str(VariantT type)
    {
        auto op = operator_str_map.find(type);
        assert(op != operator_str_map.end());
        return op->second;
    }
    
    SgVarRefExp *get_func_call_lhs(SgFunctionCallExp *func_call)
    {
        auto suc_list = func_call->get_traversalSuccessorContainer();
        for (auto n : suc_list)
        {
            if (auto dot_exp = dynamic_cast<SgDotExp *>(n))
            {
                SgExpression *left = dot_exp->get_lhs_operand();
                return dynamic_cast<SgVarRefExp *>(left);
            }
        }
        return nullptr;
    }
    
    bool write_stream_to_file(std::string out_file, std::stringstream &ss)
    {
        std::ofstream out;
        out.open(out_file, std::ofstream::out);
        if (out)
        {
            out << ss.str();
            out.close();
            return true;
        }
        return false;
    }
    
    void expression_to_string_with_value_map(std::stringstream &ss, const SgExpression *expr,
                                             const std::map<std::string, std::string> &val_map)
    {
        if (auto func_call = dynamic_cast<const SgFunctionCallExp *>(expr))
        {
            ss << func_call->unparseToString();
        }
        else if (auto binary_op = dynamic_cast<const SgBinaryOp *>(expr))
        {
            SgExpression *left = binary_op->get_lhs_operand_i();
            SgExpression *right = binary_op->get_rhs_operand_i();
            expression_to_string_with_value_map(ss, left, val_map);
            ss << get_operator_str(binary_op->variantT());
            expression_to_string_with_value_map(ss, right, val_map);
        }
        else if (auto unary_op = dynamic_cast<const SgUnaryOp *>(expr))
        {
            if (auto cast_exp = dynamic_cast<const SgCastExp *>(unary_op))
            {
                ss << cast_exp->get_type()->unparseToString() << "(";
            }
            else
            {
                ss << get_operator_str(unary_op->variantT());
            }
            expression_to_string_with_value_map(ss, unary_op->get_operand(), val_map);
            if (auto cast_exp = dynamic_cast<const SgCastExp *>(unary_op))
            {
                ss << ")";
            }
        }
        else if (auto var_ref = dynamic_cast<const SgVarRefExp *>(expr))
        {
            std::string var_name = var_ref->get_symbol()->get_name().getString();
            if (val_map.find(var_name) != val_map.end())
            {
                ss << "(" << val_map.find(var_name)->second << ")";
            }
            else
            {
                ss << var_name;
            }
        }
        else if (auto value_exp = dynamic_cast<const SgValueExp *>(expr))
        {
            ss << value_exp->get_constant_folded_value_as_string();
        }
    }
    
    std::string
    expression_to_string_with_value_map(const SgExpression *expr, const std::map<std::string, std::string> &val_map)
    {
        std::stringstream ss;
        expression_to_string_with_value_map(ss, expr, val_map);
        return ss.str();
    }
    
    bool is_empty_block(SgBasicBlock *block)
    {
        if (block == nullptr) return true;
        SgStatementPtrList &stmt_list = block->get_statements();
        return stmt_list.empty();
    }
}