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

"#" { return DEFINE; }

(pi|π)2			{ yylval.character = create_character(yytext); return CHARACTER; }
2(pi|π)			{ yylval.character = create_character(yytext); return CHARACTER; }
pi|π			{ yylval.character = create_character(yytext); return CHARACTER; }

asinh			{ yylval.character = create_character(yytext); return FUNCTION;}
acosh			{ yylval.character = create_character(yytext); return FUNCTION;}
atanh 			{ yylval.character = create_character(yytext); return FUNCTION;}

sinh			{ yylval.character = create_character(yytext); return FUNCTION;}
cosh			{ yylval.character = create_character(yytext); return FUNCTION;}
tanh 			{ yylval.character = create_character(yytext); return FUNCTION;}

sin 			{ yylval.character = create_character(yytext); return FUNCTION; }
cos 			{ yylval.character = create_character(yytext); return FUNCTION; }
tan 			{ yylval.character = create_character(yytext); return FUNCTION; }

asin 			{ yylval.character = create_character(yytext); return FUNCTION;}
acos 			{ yylval.character = create_character(yytext); return FUNCTION;}
atan 			{ yylval.character = create_character(yytext); return FUNCTION;}

e				{ yylval.character = create_character(yytext); return CHARACTER; }
exp				{ yylval.character = create_character(yytext); return FUNCTION;}
exp2			{ yylval.character = create_character(yytext); return FUNCTION;}
log2			{ yylval.character = create_character(yytext); return FUNCTION;}
log10			{ yylval.character = create_character(yytext); return FUNCTION;}
log|ln			{ yylval.character = create_character(yytext); return FUNCTION;}

abs				{ yylval.character = create_character(yytext); return FUNCTION;}

sqrt|√			{ yylval.character = create_character(yytext); return FUNCTION;}
cbrt			{ yylval.character = create_character(yytext); return FUNCTION;}

round|rint		{ yylval.character = create_character(yytext); return FUNCTION;}
floor			{ yylval.character = create_character(yytext); return FUNCTION;}
ceil			{ yylval.character = create_character(yytext); return FUNCTION;}

Radians			{ yylval.character = create_character(yytext); return FUNCTION;}
Degrees			{ yylval.character = create_character(yytext); return FUNCTION;}

toHex			{ yylval.character = create_character(yytext); isHexInput=true; return FUNCTION;}
toBin			{ yylval.character = create_character(yytext); isBinaryInput=true; return FUNCTION;}

sum				{ yylval.character = create_character(yytext); return FUNCTION_var;}
ave				{ yylval.character = create_character(yytext); return FUNCTION_var;}

geomean			{ yylval.character = create_character(yytext); return FUNCTION_var;}

{digit}+(\.{digit}+)?   {
    Expression *expression = alloc_expression(NUM_EXPRESSION);
    sscanf(yytext, "%lf", &expression->u.num_value);
    yylval.expression = expression;
    return NUM_LITERAL;
}
{letter}({digit}|{letter})* 		{ yylval.character = create_character(yytext); return CHARACTER;}
{other}          	{ return (int)yytext[0]; } 
