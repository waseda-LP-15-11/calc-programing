//
// Created by Keigo Ogawa on 5/19/15.
//

#include <stddef.h>
#include <stdio.h>
#include "calc.hpp"
#include "exmath.h"

Value eval_int_expression(int int_value) {
    Value v;
    v.type = INT_VALUE;
    v.u.int_value = int_value;
    return v;
}

static int eval_binary_int(ExpressionType type, int left, int right) {
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

Value eval_binary_expression(ExpressionType type, Expression *left, Expression *right) {
    Value left_val;
    Value right_val;
    Value result;
    left_val = eval_expression(left);
    right_val = eval_expression(right);

    if(left_val.type == INT_VALUE && right_val.type == INT_VALUE) {
        result.type = INT_VALUE;
        result.u.int_value = eval_binary_int(type, left_val.u.int_value, right_val.u.int_value);
    }

    return result;
}

static Value eval_expression(Expression *expr) {
    Value v;
    switch(expr->type) {
        case INT_EXPRESSION:
            v = eval_int_expression(expr->u.int_value);
            break;
        case ADD_EXPRESSION:
        case SUB_EXPRESSION:
        case MUL_EXPRESSION:
        case DIV_EXPRESSION:
        case MOD_EXPRESSION:
        case POW_EXPRESSION:
            v = eval_binary_expression(expr->type, expr->u.binary_expression.left, expr->u.binary_expression.right);
            break;
    }
    return v;
}


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