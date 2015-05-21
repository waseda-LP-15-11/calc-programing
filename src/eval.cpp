//
// Created by Keigo Ogawa on 5/19/15.
// 流れ: 枝を一つづつ再帰的に評価→数値を計算して返す→最終的に一つの数値を出力
//

#include <stddef.h>
#include <stdio.h>
#include "calc.hpp"
#include "exmath.h"
#include "variable.h"

//
// 計算関数
//

// 左辺、右辺ともにint型の式の計算
static int calc_binary_int(ExpressionType type, int left, int right) {
    int result;
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
            result = left % right;
            break;
        case POW_EXPRESSION:
            result = pow(left, right);
            break;
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
    if(var != NULL) {
        // 変数があったらそれを返す
        v = *var;
    } else {
        // TODO: 変数がなかった場合,エラーを表示
//        var = search_global_variable(expr->u.character);
        if(var != NULL) {
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
    if (left != NULL) {
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
    if (func == NULL) {
        //error;
    }
    for (arg_p = arg, param_p = func->parameter; arg_p; arg_p = arg_p->u.expression_list.next, param_p = param_p->next) {
        Value arg_val;
        if (param_p == NULL) {
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
// 右辺と左辺があるタイプの枝を評価
Value eval_binary_expression(ExpressionType type, Expression *left, Expression *right) {
    Value left_val;
    Value right_val;
    Value result;
    // 両辺の枝を評価
    left_val = eval_expression(left);
    right_val = eval_expression(right);

    // 両辺のタイプによって、計算する方法を変える
    // int & int -> int
    if(left_val.type == INT_VALUE && right_val.type == INT_VALUE) {
        result.type = INT_VALUE;
        result.u.int_value = calc_binary_int(type, left_val.u.int_value, right_val.u.int_value);
    } else {
        // TODO: double & double -> double
        // TODO: double & int -> double
    }

    return result;
}

//
// 値評価関数
//

// int型の値を評価
Value eval_int_expression(int int_value) {
    Value v;
    v.type = INT_VALUE;
    v.u.int_value = int_value;
    return v;
}

// 解析木の評価をする
static Value eval_expression(Expression *expr) {
    Value v;
    switch(expr->type) {
        case INT_EXPRESSION:
            v = eval_int_expression(expr->u.int_value);
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
        case ADD_EXPRESSION:
        case SUB_EXPRESSION:
        case MUL_EXPRESSION:
        case DIV_EXPRESSION:
        case MOD_EXPRESSION:
        case POW_EXPRESSION:
        case EQ_EXPRESSION:
            v = eval_binary_expression(expr->type, expr->u.binary_expression.left, expr->u.binary_expression.right);
            break;
        case FUNCTION_CALL_EXPRESSION:
            v = eval_function_call_expression(expr->u.function_call_expression.character, expr->u.function_call_expression.arg);
            break;
    }
    return v;
}



// 入力された解析木全体の評価をする。そして、最終的な出力をする。
void calc_eval_expression(Expression *expression) {
    Value v;
    v = eval_expression(expression);
    if (v.type == INT_VALUE) {
        printf(">>%d\n", v.u.int_value);
    } else if (v.type == DOUBLE_VALUE) {
        printf(">>%f\n", v.u.double_value);
    } else {
        printf("<void>\n");
    }
}