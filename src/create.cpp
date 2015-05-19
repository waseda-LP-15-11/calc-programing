//
// Created by Keigo Ogawa on 5/19/15.
//
#include <stdlib.h>
#include <string.h>
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


Expression *create_character_expression(char *chara) {
    Expression *exp;
    exp = alloc_expression(CHAR_EXPRESSION);
    exp->u.character = chara;
    return exp;
}


Expression *create_assign_expression(char *variable, Expression *operand) {
    Expression *exp;
    exp = alloc_expression(ASSIGN_EXPRESSION);
    exp->u.assignExpression.variable = variable;
    exp->u.assignExpression.operand = operand;

    return exp;
}


char *create_character(char *chara) {
    char *new_chara;
    new_chara = (char*)malloc(strlen(chara) + 1);
    strcpy(new_chara, chara);
    return new_chara;
}
