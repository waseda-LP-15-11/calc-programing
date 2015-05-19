//
// Created by Keigo Ogawa on 5/19/15.
//
#include <stdlib.h>
#include "calc.hpp"

Expression* alloc_expression(ExpressionType type) {
    Expression *exp;
    exp = (Expression*)malloc(sizeof *exp);
    exp->type = type;
    return exp;
}

Expression* create_binary_expression(ExpressionType type, Expression *left, Expression *right) {
    Expression *exp;
    exp = alloc_expression(type);
    exp->u.binary_expression.left = left;
    exp->u.binary_expression.right = right;
    return exp;
}
