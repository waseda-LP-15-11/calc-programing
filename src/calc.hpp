#ifndef CALC_HPP_INCLUDED
#define CALC_HPP_INCLUDED
#include "print.h"
#include <map>
using namespace std;
typedef struct Expression_tag Expression;

//
// 数値定義
// 各数値の属性、値の定義
//

// 数値の属性
typedef enum {
    INT_VALUE,
    DOUBLE_VALUE
} ValueType;

// 数値
// 数値は、属性と値をもつ
typedef struct {
    ValueType type;
    union {
        int int_value;
        double double_value;
    } u;
} Value;

//
// 枝定義
// 各枝の属性、値の定義
//

// 枝の属性
typedef enum {
    BOOLEAN_EXPRESSION = 1,
    INT_EXPRESSION,
    ADD_EXPRESSION,
    SUB_EXPRESSION,
    MUL_EXPRESSION,
    DIV_EXPRESSION,
    MOD_EXPRESSION,
    POW_EXPRESSION,
    CHAR_EXPRESSION,
    EQ_EXPRESSION,
    ASSIGN_EXPRESSION
} ExpressionType;

// Booleanの枝の値
typedef enum {
    FALSE = 0,
    TRUE = 1
} Boolean;

// 右辺と左辺がある枝の値
typedef struct {
    Expression *left;
    Expression *right;
} BinaryExpression;

// 変数を割り当てる枝の値
typedef struct {
    char *variable;         // 変数名
    Expression *operand;    // 割り当てる式
} AssignExpression;

// 枝
// 枝は、属性と値をもつ
struct Expression_tag {
    ExpressionType type;
    int line_number;    //未実装
    union {
        Boolean boolean_value;
        int     int_value;
        double  doule_value;
        BinaryExpression    binary_expression;
        char *character;
        AssignExpression    assignExpression;
    } u;
};

// 変数の保存場所
static map<string,Value> Variables;

// create.cpp
Expression* alloc_expression(ExpressionType type);
Expression* create_binary_expression(ExpressionType type, Expression *left, Expression *right);
Expression * create_character_expression(char *chara);
Expression * create_assign_expression(char *variable, Expression *operand);
char * create_character(char *chara);

//eval.cpp
void calc_eval_expression(Expression *expression);
static Value eval_expression(Expression *expr);
Value eval_int_expression(int int_value);
static int calc_binary_int(ExpressionType type, int left, int right);
Value eval_binary_expression(ExpressionType type, Expression *left, Expression *right);

#endif