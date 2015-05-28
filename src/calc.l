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

(pi|π)2			{ yylval.character = strdup(yytext); return CHARACTER; }
2(pi|π)			{ yylval.character = strdup(yytext); return CHARACTER; }
pi|π			{ yylval.character = strdup(yytext); return CHARACTER; }

asinh			{ yylval.character = strdup(yytext); return FUNCTION;}
acosh			{ yylval.character = strdup(yytext); return FUNCTION;}
atanh 			{ yylval.character = strdup(yytext); return FUNCTION;}

sinh			{ yylval.character = strdup(yytext); return FUNCTION;}
cosh			{ yylval.character = strdup(yytext); return FUNCTION;}
tanh 			{ yylval.character = strdup(yytext); return FUNCTION;}

sin 			{ yylval.character = strdup(yytext); return FUNCTION; }
cos 			{ yylval.character = strdup(yytext); return FUNCTION; }
tan 			{ yylval.character = strdup(yytext); return FUNCTION; }

asin 			{ yylval.character = strdup(yytext); return FUNCTION;}
acos 			{ yylval.character = strdup(yytext); return FUNCTION;}
atan 			{ yylval.character = strdup(yytext); return FUNCTION;}

e				{ yylval.character = strdup(yytext); return CHARACTER; }
exp				{ yylval.character = strdup(yytext); return FUNCTION;}
exp2			{ yylval.character = strdup(yytext); return FUNCTION;}
log2			{ yylval.character = strdup(yytext); return FUNCTION;}
log10			{ yylval.character = strdup(yytext); return FUNCTION;}
log|ln			{ yylval.character = strdup(yytext); return FUNCTION;}

abs				{ yylval.character = strdup(yytext); return FUNCTION;}

sqrt|√			{ yylval.character = strdup(yytext); return FUNCTION;}
cbrt			{ yylval.character = strdup(yytext); return FUNCTION;}

round|rint		{ yylval.character = strdup(yytext); return FUNCTION;}
floor			{ yylval.character = strdup(yytext); return FUNCTION;}
ceil			{ yylval.character = strdup(yytext); return FUNCTION;}

Radians			{ yylval.character = strdup(yytext); return FUNCTION;}
Degrees			{ yylval.character = strdup(yytext); return FUNCTION;}

toHex			{ yylval.character = strdup(yytext); isHexInput=true; return FUNCTION;}
toBin			{ yylval.character = strdup(yytext); isBinInput=true; return FUNCTION;}

sum				{ yylval.character = strdup(yytext); return FUNCTION_var;}
ave				{ yylval.character = strdup(yytext); return FUNCTION_var;}

geomean			{ yylval.character = strdup(yytext); return FUNCTION_var;}

mem				{ yylval.character = strdup(yytext); return FUNCTION;}

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
{letter}({digit}|{letter})* 		{ yylval.character = strdup(yytext); return CHARACTER;}
{other}          	{ return (int)yytext[0]; } 
