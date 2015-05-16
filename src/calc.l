%option noyywrap
%option c++
%{
#include <stdlib.h>
#include "calc.tab.h"
#include "exmath.h"
using namespace std;
double getMem(double);
void dispFunc(void);
%}

letter  [a-zA-Z_'"']
digit        [0-9]
string		 {letter}({digit}|{letter})* 
white_blank  [ \t]
other        .|\n

%%
"exit" { exit(0); }
{white_blank}+

(pi|π)2			{ yylval.number = M_PI_2; return CONSTANT; }
2(pi|π)			{ yylval.number = 2*M_PI; return CONSTANT; }
pi|π			{ yylval.number = M_PI; return CONSTANT; }
asinh			{ yylval.fp = asinh; return FUNCTION;}
acosh			{ yylval.fp = acosh; return FUNCTION;}
atanh 			{ yylval.fp = atanh; return FUNCTION;}

sinh			{ yylval.fp = sinh; return FUNCTION;}
cosh			{ yylval.fp = cosh; return FUNCTION;}
tanh 			{ yylval.fp = tanh; return FUNCTION;}

sin 			{ yylval.fp = sin; return FUNCTION; }
cos 			{ yylval.fp = cos; return FUNCTION; }
tan 			{ yylval.fp = tan; return FUNCTION; }

asin 			{ yylval.fp = asin; return FUNCTION;}
acos 			{ yylval.fp = acos; return FUNCTION;}
atan 			{ yylval.fp = atan; return FUNCTION;}

e				{ yylval.number = M_E; return CONSTANT; }
exp				{ yylval.fp = exp; return FUNCTION;}
exp2			{ yylval.fp = exp2; return FUNCTION;}
log2			{ yylval.fp = log2; return FUNCTION;}
log10			{ yylval.fp = log10; return FUNCTION;}
log|ln			{ yylval.fp = log; return FUNCTION;}

abs				{ yylval.fp = fabs; return FUNCTION;}

sqrt|√			{ yylval.fp = sqrt; return FUNCTION;}
cbrt			{ yylval.fp = cbrt; return FUNCTION;}

round|rint		{ yylval.fp = round; return FUNCTION;}
floor			{ yylval.fp = floor; return FUNCTION;}
ceil			{ yylval.fp = ceil; return FUNCTION;}

Radians			{ yylval.fp = Radians; return FUNCTION;}
Degrees			{ yylval.fp = Degrees; return FUNCTION;}

hypot			{ yylval.fpp = hypot; return FUNCTION2;}

dim				{ yylval.fpp = fdim; return FUNCTION2;}
			
mem				{ yylval.fp = getMem; return FUNCTION;}

function 		{ yylval.fpv = dispFunc; return FUNCTION3;}

{digit}+(\.{digit}+)?   { yylval.number = atof(yytext); return CONSTANT; }
{letter}({digit}|{letter})* 		{ strcpy(yylval.string, yytext); return CHARACTER; }
{other}          	{ return (int)yytext[0]; } 
