//
// Created by Keigo Ogawa on 5/19/15.
// ここで枝の作成を行う。
// 流れ: メモリ確保→枝作成
// 各枝の定義はcalc.hppで行う。
//
#include <stdlib.h>
#include <string.h>
#include "calc.hpp"

// expression(=解析木の枝)のメモリ確保
Expression* alloc_expression(ExpressionType type) {
    Expression *exp;
    exp = (Expression*)malloc(sizeof *exp);
    exp->type = type;
    return exp;
}

// 右辺と左辺があるタイプの枝を作成
Expression* create_binary_expression(ExpressionType type, Expression *left, Expression *right) {
    Expression *exp;
    exp = alloc_expression(type);
    exp->u.binary_expression.left = left;
    exp->u.binary_expression.right = right;
    return exp;
}

// 変数の枝作成
Expression *create_character_expression(char *chara) {
    Expression *exp;
    exp = alloc_expression(CHAR_EXPRESSION);
    exp->u.character = chara;
    return exp;
}

// 変数に割り当てる枝作成(a=1としたときの=を挟んだ両辺の関係)
Expression *create_assign_expression(char *variable, Expression *operand) {
    Expression *exp;
    exp = alloc_expression(ASSIGN_EXPRESSION);
    exp->u.assignExpression.variable = variable;
    exp->u.assignExpression.operand = operand;

    return exp;
}

// 変数作成
// TODO: これは枝作成機能ではないので違うところに移動したい
char *create_character(char *chara) {
    char *new_chara;
    new_chara = (char*)malloc(strlen(chara) + 1);
    strcpy(new_chara, chara);
    return new_chara;
}
