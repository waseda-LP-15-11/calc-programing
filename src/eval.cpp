//
// Created by Keigo Ogawa on 5/19/15.
// 流れ: 枝を一つづつ再帰的に評価→数値を計算して返す→最終的に一つの数値を出力
//

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "calc.hpp"
#include "exmath.h"
#include "variable.h"
#include "numberBase.h"
#include "sum.h"
#include "args.h"
#include "memory.h"

extern bool isBinInput;//calc.y
extern bool isHexInput;//calc.y

//
// 計算関数
//

// 左辺、右辺ともにdouble型の式の計算
static double calc_binary_int(ExpressionType type, double left, double right) {
    double result;
    switch (type) {
        case ADD_EXPRESSION:
            result = left + right;
            break;
        case SUB_EXPRESSION:
            result = left - right;
            break;
        case MUL_EXPRESSION:
            result = left * right;
            break;
        case DIV_EXPRESSION:
            result = left / right;
            break;
        case MOD_EXPRESSION:
            result = (int)left % (int)right;
            break;
        case POW_EXPRESSION:
            result = pow(left, right);
            break;
        case LS_EXPRESSION:
            result = leftShift(left, right);
            if(32 <= right || result < left) {
                PrintErrorln("ERROR: Over Flow") ;
                result = 0;
            }
            break;
        case RS_EXPRESSION:
            result = rightShift(left, right);
            if(right < 0||31<= right ) {
                PrintErrorln("ERROR: Out of Shift Range");
                result = 0;
            }
            break;
        default:
            PrintErrorln("ERROR: at calc_binary_int");
    }
    return result;
}

//
// 枝評価関数
//

// 変数の枝を評価
// 今のところ、ローカルな変数とグローバルな変数は区別していない
static Value eval_char_expression(Expression *expr) {
    Value v;
    Value *var;

    // 変数を探す
    var = search_local_variable(expr->u.character);
    if(var != nullptr) {
        // 変数があったらそれを返す
        v = *var;
    } else {
        // TODO: 変数がなかった場合,エラーを表示
//        var = search_global_variable(expr->u.character);
        if(var != nullptr) {
            v = *var;
        } else {
         // TODO: error handling
        }
    }
    return v;
}

// 変数作成枝の評価
static Value eval_assign_expression(char *chara, Expression *expr) {
    Value v;
    Value *left;

    // 右辺の構文木を評価
    v = eval_expression(expr);

    // 左辺の変数があるかどうか探す
    left = search_local_variable(chara);
//    if (left == NULL) {
//        left = search_global_variable(chara);
//    }
    if (left != nullptr) {
        // 変数がすでにあったら更新
        *left = v;
    } else {
        // なかったら作成
        add_variable(chara, &v);
    }

    return v;

}

static Value eval_expression_list_expression(Expression *expression, Expression *next) {
    Value v;
    v = eval_expression(expression);
    if (next) {
        v = eval_expression(next);
    }
    return v;
}

static Value eval_function_call_expression(char *character, Expression *arg) {
    Value result;
    Expression *arg_p;
    ParameterList *param_p;
    FunctionDefinition *func;

    func = search_function(character);
    if (func == nullptr) {
        PrintErrorln("error function not found");
        return result;
    }
    for (arg_p = arg, param_p = func->parameter; arg_p; arg_p = arg_p->u.expression_list.next, param_p = param_p->next) {
        Value arg_val;
        if (param_p == nullptr) {
            // error many arg
        }
        arg_val = eval_expression(arg_p->u.expression_list.expression);
        add_variable(param_p->name, &arg_val);
    }
    if (param_p) {
        // error few arg
    }
    result = eval_expression(func->expression_list);
    //dispose var
    return result;
}

static Value eval_function_var_call_expression(char *name) {
    Value result;
    result.type = NUM_VALUE;
    if (!strcmp(name, "sum")) { result.u.num_value = sum(); }
    if (!strcmp(name, "ave")) { result.u.num_value = ave(); }
    if (!strcmp(name, "geomean")) { result.u.num_value = geometricMean(); }
    return result;
}

static Value eval_math_expression(char *math_name, Expression *arg) {
    Value result;
    result.type = NUM_VALUE;
    Value arg_p = eval_expression(arg);

    if (!strcmp(math_name, "sin"))     { result.u.num_value = sin(arg_p.u.num_value); }
    if (!strcmp(math_name, "cos"))     { result.u.num_value = cos(arg_p.u.num_value); }
    if (!strcmp(math_name, "tan"))     { result.u.num_value = tan(arg_p.u.num_value); }
    if (!strcmp(math_name, "sinh"))    { result.u.num_value = sinh(arg_p.u.num_value); }
    if (!strcmp(math_name, "cosh"))    { result.u.num_value = cosh(arg_p.u.num_value); }
    if (!strcmp(math_name, "tanh"))    { result.u.num_value = tanh(arg_p.u.num_value); }
    if (!strcmp(math_name, "asin"))    { result.u.num_value = asin(arg_p.u.num_value); }
    if (!strcmp(math_name, "acos"))    { result.u.num_value = acos(arg_p.u.num_value); }
    if (!strcmp(math_name, "atan"))    { result.u.num_value = atan(arg_p.u.num_value); }
    if (!strcmp(math_name, "asinh"))   { result.u.num_value = asinh(arg_p.u.num_value); }
    if (!strcmp(math_name, "acosh"))   { result.u.num_value = acosh(arg_p.u.num_value); }
    if (!strcmp(math_name, "atanh"))   { result.u.num_value = atanh(arg_p.u.num_value); }
    if (!strcmp(math_name, "exp"))     { result.u.num_value = exp(arg_p.u.num_value); }
    if (!strcmp(math_name, "log2"))    { result.u.num_value = log2(arg_p.u.num_value); }
    if (!strcmp(math_name, "log10"))   { result.u.num_value = log10(arg_p.u.num_value); }
    if (!strcmp(math_name, "log"))     { result.u.num_value = log(arg_p.u.num_value); }
    if (!strcmp(math_name, "ln"))      { result.u.num_value = log(arg_p.u.num_value); }
    if (!strcmp(math_name, "abs"))     { result.u.num_value = abs(arg_p.u.num_value); }
    if (!strcmp(math_name, "sqrt"))    { result.u.num_value = sqrt(arg_p.u.num_value); }
    if (!strcmp(math_name, "cbrt"))    { result.u.num_value = cbrt(arg_p.u.num_value); }
    if (!strcmp(math_name, "round"))   { result.u.num_value = round(arg_p.u.num_value); }
    if (!strcmp(math_name, "rint"))    { result.u.num_value = rint(arg_p.u.num_value); }
    if (!strcmp(math_name, "floor"))   { result.u.num_value = floor(arg_p.u.num_value); }
    if (!strcmp(math_name, "ceil"))    { result.u.num_value = ceil(arg_p.u.num_value); }
    if (!strcmp(math_name, "Radians")) { result.u.num_value = Radians(arg_p.u.num_value); }
    if (!strcmp(math_name, "Degrees")) { result.u.num_value = Degrees(arg_p.u.num_value); }
    if (!strcmp(math_name, "toBin"))   {
        result.type = BIN_VALUE;
        result.u.num_value = toBin(arg_p.u.num_value);
    }
    if (!strcmp(math_name, "toHex"))   {
        result.type = HEX_VALUE;
        result.u.num_value = toHex(arg_p.u.num_value);
    }
    return result;

}

// 右辺と左辺があるタイプの枝を評価
Value eval_binary_expression(ExpressionType type, Expression *left, Expression *right) {
    Value left_val;
    Value right_val;
    Value result;
    // 両辺の枝を評価
    left_val = eval_expression(left);
    right_val = eval_expression(right);

    result.type = NUM_VALUE;
    result.u.num_value = calc_binary_int(type, left_val.u.num_value, right_val.u.num_value);

    return result;
}

//
// 値評価関数
//

// int型の値を評価
Value eval_num_expression(double num_value) {
    Value v;
    v.type = NUM_VALUE;
    v.u.num_value = num_value;
    return v;
}

Value eval_minus_expression(Expression *ope) {
    Value ope_val;
    Value result;
    ope_val = eval_expression(ope);
    if (ope_val.type == NUM_VALUE) {
        result.type = NUM_VALUE;
        result.u.num_value = -(ope_val.u.num_value);
    }
    return result;
}
// 解析木の評価をする
Value eval_expression(Expression *expr) {
    Value v;
    switch(expr->type) {
        case NUM_EXPRESSION:
            v = eval_num_expression(expr->u.num_value);
            break;
        case CHAR_EXPRESSION:
            v = eval_char_expression(expr);
            break;
        case EXPRESSION_LIST_EXPRESSION:
            v = eval_expression_list_expression(expr->u.expression_list.expression, expr->u.expression_list.next);
            break;
        case ASSIGN_EXPRESSION:
            v = eval_assign_expression(expr->u.assignExpression.variable, expr->u.assignExpression.operand);
            break;
        case MINUS_EXPRESSION:
            v = eval_minus_expression(expr->u.minus_expression);
            break;
        case ADD_EXPRESSION:
        case SUB_EXPRESSION:
        case MUL_EXPRESSION:
        case DIV_EXPRESSION:
        case MOD_EXPRESSION:
        case POW_EXPRESSION:
        case EQ_EXPRESSION:
        case LS_EXPRESSION:
        case RS_EXPRESSION:
            v = eval_binary_expression(expr->type, expr->u.binary_expression.left, expr->u.binary_expression.right);
            break;
        case MATH_EXPRESSION:
            v = eval_math_expression(expr->u.function_call_expression.character, expr->u.function_call_expression.arg );
            break;
        case FUNCTION_CALL_EXPRESSION:
            v = eval_function_call_expression(expr->u.function_call_expression.character, expr->u.function_call_expression.arg);
            break;
        case FUNCTION_VAR_CALL_EXPRESSION:
            v = eval_function_var_call_expression(expr->u.function_call_expression.character);
            clearArgs();
            break;
        default:
            Println("Expression error");
    }
    return v;
}


// 入力された解析木全体の評価をする。そして、最終的な出力をする。
void calc_eval_expression(Expression *expression) 
{
    Value v = eval_expression(expression);
    const auto uIntValue = to_String((unsigned int)v.u.num_value);
    if (v.type == HEX_VALUE || isHexInput) 
    {
        Println(uIntToHexStr((unsigned int)v.u.num_value)+"("+uIntValue+")");
    } 
    else if (v.type == BIN_VALUE || isBinInput) 
    {
        Println(uIntToBinStr((unsigned int)v.u.num_value)+"("+uIntValue+")");
    } 
    else if (v.type == NUM_VALUE) 
    {
        if (v.u.num_value / (int)(v.u.num_value) == 1) 
        {
            Println((int)(v.u.num_value));
        } 
        else 
        {
            Println(v.u.num_value);
        }
    } 
    else 
    {
        Println("<void>");
    }
  pushMemory(v.u.num_value);
  isBinInput=false;
  isHexInput = false;
}