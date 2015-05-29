%option noyywrap
%option c++
%{
#include <stdlib.h>
#include "calc.hpp"
#include "calc.tab.h"
#include "exmath.h"
#include "sum.h"
#include "numberBase.h"
#include "numberBase.h"
#include "print.h"

extern bool isBinInput;
extern bool isHexInput;
void dispVar(void);
void dispMem(void);
void dispFunc(void);
double getMem(double index);
void restart();
%}

letter  [a-zA-Z_'"']
digit        [0-9]
hexleter	 [a-fA-F]
string		 {letter}({digit}|{letter})* 
white_blank  [ \t]
other        .|\n

%%
<<EOF>>			{ yylval.fpv = restart; return FUNCTION0; }
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
toBin			{ yylval.character = create_character(yytext); isBinInput=true; return FUNCTION;}

sum				{ yylval.character = create_character(yytext); return FUNCTION_var;}
ave				{ yylval.character = create_character(yytext); return FUNCTION_var;}

geomean			{ yylval.character = create_character(yytext); return FUNCTION_var;}

mem				{ yylval.character = create_character(yytext); return FUNCTION;}

memory			{ yylval.fpv = dispMem; return FUNCTION0;}

variable		{ yylval.fpv = dispVar; return FUNCTION0;}

function		{ yylval.fpv = dispFunc; return FUNCTION0;}

0(b|B)(0|(1|0)+)	{ 
	Expression *expression = alloc_expression(NUM_EXPRESSION);
	expression->u.num_value = binToUInt(yytext);
	isBinInput=true;
	yylval.expression = expression;
	return NUM_LITERAL;
}

0(x|X)(0|({digit}|{hexleter})+)	{
	Expression *expression = alloc_expression(NUM_EXPRESSION);
	expression->u.num_value = hexToUInt(yytext);
	isHexInput=true;
	yylval.expression = expression;
	return NUM_LITERAL;
}

{digit}+(\.{digit}+)?   {
    Expression *expression = alloc_expression(NUM_EXPRESSION);
    sscanf(yytext, "%lf", &expression->u.num_value);
    yylval.expression = expression;
    return NUM_LITERAL;
}
{letter}({digit}|{letter})* 		{ yylval.character = create_character(yytext); return CHARACTER;}
{other}          	{ return (int)yytext[0]; } 
