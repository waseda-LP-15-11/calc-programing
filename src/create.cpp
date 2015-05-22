//
// Created by Keigo Ogawa on 5/19/15.
// ここで枝の作成を行う。
// 流れ: メモリ確保→枝作成
// 各枝の定義はcalc.hppで行う。
//
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "calc.hpp"

FunctionDefinition *search_function(char *name) {
    FunctionDefinition *pos;
    for(pos = function_list_top; pos; pos = pos->next) {
        if (!strcmp(pos->name, name)) {
            break;
        }
    }
    return pos;
}

void function_define(char *character, ParameterList *parameter_list, Expression *expression_list) {
    FunctionDefinition *f;
    if (search_function(character)) {
        return;
    }
    f = new FunctionDefinition;
    f->name = character;
    f->parameter = parameter_list;
    f->expression_list = expression_list;
    f->next = function_list_top;
    function_list_top = f;
}

ParameterList *create_parameter(char *character) {
    ParameterList *p;
    p = new ParameterList;
    p->name = character;
    p->next = NULL;
    return p;
}

ParameterList *chain_parameter(ParameterList *list, char *character) {
    ParameterList *add;
    add = create_parameter(character);

    ParameterList *pos;
    for (pos = list; pos->next; pos = pos->next);
    pos->next = add;
    return list;
}

// expression(=解析木の枝)のメモリ確保
Expression* alloc_expression(ExpressionType type) {
    Expression *exp;
    exp = new Expression;
    exp->type = type;
    return exp;
}

Expression *create_expression_list(Expression *expression) {
    Expression *exp;
    exp = alloc_expression(EXPRESSION_LIST_EXPRESSION);
    exp->u.expression_list.expression = expression;
    exp->u.expression_list.next = NULL;
    return exp;
}

Expression *chain_expression_list(Expression *list, Expression *add) {
    Expression *exp;
    Expression *pos;
    exp = alloc_expression(EXPRESSION_LIST_EXPRESSION);
    exp->u.expression_list.expression = add;
    exp->u.expression_list.next = NULL;
    for (pos = list; pos->u.expression_list.next; pos->u.expression_list.next);
    pos->u.expression_list.next = exp;
    return list;
}

// 右辺と左辺があるタイプの枝を作成
Expression* create_binary_expression(ExpressionType type, Expression *left, Expression *right) {
    Expression *exp;
    exp = alloc_expression(type);
    exp->u.binary_expression.left = left;
    exp->u.binary_expression.right = right;
    return exp;
}

static Expression convert_value_to_expression(Value *v) {
    Expression exp;
    if (v->type == NUM_VALUE) {
        exp.type = NUM_EXPRESSION;
        exp.u.num_value = v->u.num_value;
    }
    return exp;
}

Expression *create_minus_expression(Expression *ope) {
    if (ope->type == NUM_EXPRESSION) {
        Value v;
        v = eval_minus_expression(ope);
        *ope = convert_value_to_expression(&v);
        return ope;
    } else {
        Expression *exp;
        exp = alloc_expression(MINUS_EXPRESSION);
        exp->u.minus_expression = ope;
        return exp;
    }
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

Expression *create_math_expression(char* math_name ) {
    Expression *exp;
    char *arg = (char*)"x";
    Expression *name_expr = create_character_expression(math_name);
    Expression *arg_expr = create_character_expression(arg);
    exp = alloc_expression(MATH_EXPRESSION);
    exp->u.function_call_expression.character = math_name;
    exp->u.function_call_expression.arg = arg_expr;
    return exp;
}

Expression *create_function_call_expression(char *func_name, Expression *arg) {
    Expression *exp;
    exp = alloc_expression(FUNCTION_CALL_EXPRESSION);
    exp->u.function_call_expression.character = func_name;
    exp->u.function_call_expression.arg = arg;
    return exp;
}

// 変数作成
// TODO: これは枝作成機能ではないので違うところに移動したい

char *create_character(char *chara) {
#if 0
    char *new_chara;
    new_chara = (char*)malloc(strlen(chara) + 1);
    strcpy(new_chara, chara);
    return new_chara;
#else
    //create_characterで渡されたcharaはtempCharactersに全て追加されていく
    //できれば一つの計算ごとに.clearしたい。
    static std::vector<std::string> tempCharacters;
    tempCharacters.push_back(chara);
    return const_cast<char *>(tempCharacters.back().c_str());
#endif
}