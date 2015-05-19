%option noyywrap
%option c++
%{
#include <stdlib.h>
#include "calc.hpp"
#include "calc.tab.h"
#include "exmath.h"
#include "sum.h"
#include "numberBase.h"

using namespace std;
double getMem(double);
void dispMem(void);
void dispFunc(void);
void dispVar(void);
extern bool isBinaryInput;
extern bool isHexInput;
%}

letter  [a-zA-Z_'"']
digit        [0-9]
hexleter	 [a-fA-F]
string		 {letter}({digit}|{letter})* 
white_blank  [ \t]
other        .|\n

%%
"exit" { exit(0); }
{white_blank}+
{digit}+   {
    Expression *expression = alloc_expression(INT_EXPRESSION);
    sscanf(yytext, "%d", &expression->u.int_value);
    yylval.expression = expression;
    return INT_LITERAL;
}
{letter}({digit}|{letter})* 		{ yylval.character = create_character(yytext); return CHARACTER;}
{other}          	{ return (int)yytext[0]; } 
