typedef struct Expression_tag Expression;

typedef enum {
    FALSE = 0,
    TRUE = 1
} Boolean;
typedef enum {
    INT_VALUE,
    DOUBLE_VALUE
} ValueType;

typedef struct {
    ValueType type;
    union {
        int int_value;
        double double_value;
    } u;
} Value;

typedef enum {
    BOOLEAN_EXPRESSION = 1,
    INT_EXPRESSION,
    ADD_EXPRESSION
} ExpressionType;

typedef struct {
    Expression *left;
    Expression *right;
} BinaryExpression;
struct Expression_tag {
    ExpressionType type;
    int line_number;
    union {
        Boolean boolean_value;
        int     int_value;
        double  doule_value;
        BinaryExpression    binary_expression;
    } u;
};

// create.cpp
Expression* alloc_expression(ExpressionType type);
Expression* create_binary_expression(ExpressionType type, Expression *left, Expression *right);

//eval.cpp

void calc_eval_expression(Expression *expression);
static Value eval_expression(Expression *expr);
Value eval_int_expression(int int_value);
static int eval_binary_int(ExpressionType type, int left, int right);
Value eval_binary_expression(ExpressionType type, Expression *left, Expression *right);