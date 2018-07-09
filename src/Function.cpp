//
// Created by whj on 6/11/18.
//

#include <sstream>
#include <Path.h>
#include "Function.h"
#include "debug.h"

namespace le
{
    using namespace std;
    
    void Function::add_input_parameter(const le::Variable &v)
    {
        var_tbl.add_variable(v);
        input_parameters.add_variable(v);
    }
    
    void Function::add_input_parameterlist()
    {
        SgFunctionParameterList *params = decl->get_parameterList();
        for (SgInitializedName *param : params->get_args())
        {
            std::string name = param->get_name().getString();
            SgType *type = param->get_type();
            Variable v(name, type);
            add_input_parameter(v);
        }
    }
    
    Function Function::copy_with_no_end_path()
    {
        Function new_func = *this;
        new_func.paths = this->paths.copy_no_end();
        return new_func;
    }
    
    void Function::merge(const le::Function &f)
    {
        paths.merge(f.paths);
    }
    
    void Function::handle_statement(SgStatement *stmt)
    {
//        print_whole_node(stmt);
        if (stmt == nullptr) return;
        if (auto s = dynamic_cast<SgBasicBlock *>(stmt))
        {
            handle_block_statement(s);
        }
        else if (auto s = dynamic_cast<SgForStatement *>(stmt))
        {
            handle_for_statement(s);
        }
        else if (auto s = dynamic_cast<SgWhileStmt *>(stmt))
        {
            handle_while_statement(s);
        }
        else if (auto s = dynamic_cast<SgDoWhileStmt *>(stmt))
        {
            handle_dowhile_statement(s);
        }
        else if (auto s = dynamic_cast<SgIfStmt *>(stmt))
        {
            handle_if_statement(s);
        }
        else if (auto s = dynamic_cast<SgSwitchStatement *>(stmt))
        {
            // TODO
            handle_switch_statement(s);
        }
        else if (auto s = dynamic_cast<SgReturnStmt *>(stmt))
        {
            handle_return_statement(s);
        }
        else if (auto s = dynamic_cast<SgVariableDeclaration *>(stmt))
        {
            handle_var_declaration(s);
        }
        else if (auto s = dynamic_cast<SgExprStatement *>(stmt))
        {
            handle_expr_statement(s);
        }
        else
        {
            print_err_statement(stmt);
        }
    }
    
    void Function::handle_block_statement(SgBasicBlock *block)
    {
        SgStatementPtrList &stmt_list = block->get_statements();
        paths.enter_new_block();
        for (auto s : stmt_list)
        {
            handle_statement(s);
        }
        paths.leave_cur_block();
    }
    
    void Function::handle_for_statement(SgForStatement *for_stmt)
    {
        paths.add_str(for_stmt->unparseToString());
    }
    
    void Function::handle_while_statement(SgWhileStmt *while_stmt)
    {
        paths.add_str(while_stmt->unparseToString());
    }
    
    void Function::handle_dowhile_statement(SgDoWhileStmt *dowhile_stmt)
    {
        paths.add_str(dowhile_stmt->unparseToString());
    }
    
    void Function::handle_if_statement(SgIfStmt *if_stmt)
    {
        SgStatement *condition_stmt = if_stmt->get_conditional();
        if (auto *expr_stmt = dynamic_cast<SgExprStatement *>(condition_stmt))
        {
            SgExpression *condition = expr_stmt->get_expression();
            handle_expression(condition);
            Function new_func = this->copy_with_no_end_path();
            
            auto true_body = dynamic_cast<SgBasicBlock *>(if_stmt->get_true_body());
            auto false_body = dynamic_cast<SgBasicBlock *>(if_stmt->get_false_body());
            if (!is_empty_block(true_body))
            {
                string true_stmt = string("if(") + condition->unparseToString() + ")";
                this->paths.add_str(true_stmt);
                this->handle_block_statement(true_body);
            }
            
            if (!is_empty_block(false_body))
            {
                string false_stmt = string("if(!(") + condition->unparseToString() + "))";
                new_func.paths.add_str(false_stmt);
                new_func.handle_block_statement(false_body);
            }
            
            merge(new_func);
        }
    }
    
    void Function::handle_switch_statement(SgSwitchStatement *switch_stmt)
    {
        // TODO
    }
    
    void Function::handle_var_declaration(SgVariableDeclaration *decl)
    {
        paths.add_stmt(decl);
//        SgInitializedNamePtrList &list = decl->get_variables();
//        for (SgInitializedName *n : list)
//        {
//            SgType *type = n->get_type();
//            string var_name = n->get_name();
//            // check type must be iRRAM::REAL, do no process on basic type now!
////            if(type->get_mangled() != REAL_MANGLED)
////                return;
//            if(auto initializer = dynamic_cast<SgConstructorInitializer*>(n->get_initptr()))
//            {
//                // for iRRAM::REAL type, initializer with constructor, rather than SgAssignInitializer
//                // REAL constructor with 1 parameter
//                SgExprListExp* list_exp = initializer->get_args();
//                if(list_exp->get_expressions().empty())
//                {
//                    Variable var(var_name, type, nullptr);
//                    add_variable(var);
//                }
//                else
//                {
//                    Variable var(var_name, type, list_exp->get_expressions()[0]);
//                    add_variable(var);
//                }
//            }
//            else if(auto initializer = dynamic_cast<SgAssignInitializer *>(n->get_initptr()))
//            {
//                // basic type initializer
//                Variable var(var_name, type, initializer->get_operand());
//                add_variable(var);
//            }
//            else
//            {
//                Variable var(var_name, type);
//                add_variable(var);
//            }
//        }
    }
    
    void Function::handle_expression(SgExpression *expr)
    {
//        if(auto func_call = dynamic_cast<SgFunctionCallExp*>(expr))
//        {
//            string func_decl_str = func_call->getAssociatedFunctionDeclaration()->unparseToString();
//            if (find_in_member_func_set(func_decl_str))
//            {
//                SgExpressionPtrList expr_list = get_func_parameters(func_call);
//                SgMemberFunctionRefExp *ref_exp = get_member_func_refExp(func_call);
//                if (ref_exp->unparseToString() == "=")
//                {// now only has assign value operator= in member function set
//                    SgExpression *caller = get_member_func_caller(func_call);
//                    add_procedure(caller->unparseToString(), expr_list[0]);
//                    handle_expression(expr_list[0]);
//                }
//            }
//        }
//        else
//        {
//            if (auto assign_op = dynamic_cast<SgAssignOp *>(expr))
//            {
//                SgExpression *ref = assign_op->get_lhs_operand();
//                SgExpression *value = assign_op->get_rhs_operand();
//                add_procedure(ref->unparseToString(), value);
//                handle_expression(value);
//            }
//            else if (auto compound_op = dynamic_cast<SgCompoundAssignOp *>(expr))
//            {
//                SgExpression *ref = compound_op->get_lhs_operand();
//                add_procedure(ref->unparseToString(), expr);
//                handle_expression(compound_op->get_rhs_operand());
//            }
//            else if (auto pp_op = dynamic_cast<SgPlusPlusOp *>(expr))
//            {
//                SgExpression *ref = pp_op->get_operand_i();
//                add_procedure(ref->unparseToString(), expr);
//                handle_expression(ref);
//            }
//            else if (auto mm_op = dynamic_cast<SgMinusMinusOp *>(expr))
//            {
//                SgExpression *ref = pp_op->get_operand_i();
//                add_procedure(ref->unparseToString(), expr);
//                handle_expression(ref);
//            }
//        }
    }
    
    void Function::handle_expr_statement(SgExprStatement *expr_s)
    {
//        print_whole_node(expr_s);
        SgExpression *expr = expr_s->get_expression();
        handle_expression(expr);
        paths.add_stmt(expr_s);
    }
    
    void Function::handle_return_statement(SgReturnStmt *return_stmt)
    {
        SgExpression *expr = return_stmt->get_expression();
        paths.add_stmt(return_stmt);
        // must place after the add_stmt function
        paths.set_return();
    }
    
    Function::Function(const std::string &_func_name, SgFunctionDeclaration *_decl, CodeCreater *_pool) :
            func_name(_func_name), decl(_decl), _in_pool(_pool)
    {
        if (decl == nullptr)
        {
            return;
        }
        add_input_parameterlist();
        
        SgFunctionDefinition *func_def = decl->get_definition();
        if (func_def == nullptr)
        {
            print_warning_function_no_definition(decl);
            return;
        }
        SgBasicBlock *func_body = func_def->get_body();
        handle_block_statement(func_body);
    }
    
    string Function::to_string() const
    {
        stringstream ss;
        ss << "\"function_name\": " << "\"" << func_name << "\"" << endl;
        ss << "\"variables\": " << var_tbl.to_string() << endl;
        ss << "\"input_variables\": " << input_parameters.to_string() << endl;
        ss << "\"paths\": [" << endl;
//        for (const auto &p : path_list)
//        {
//            ss << p.to_string(1);
//        }
        ss << "]" << endl;
        return ss.str();
    }
    
    string Function::to_code() const
    {
//        stringstream ss;
//        ss << "\"function_name\": " << "\"" << func_name << "\"" << endl;
//        ss << "\"variables\": " << var_tbl.to_string() << endl;
//        ss << "\"input_variables\": " << input_parameters.to_string() << endl;
//        ss << "\"paths\": [" << endl;
//        for (const auto &p : path_list)
//        {
//            ss << p.to_code(1);
//        }
//        ss << "]" << endl;
//        return ss.str();
        return paths.to_string();
    }
    
    void Function::to_klee_code_functions()
    {
//        for (auto &p : path_list)
//        {
//            p.to_klee_code_functions(input_parameters);
//        }
    }
    
}