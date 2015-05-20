%{

#include "Calc.h"
#include "numberBase.h"
#include "args.h"
#include "sum.h"
#include "function.h"
#include "exmath.h"
#include "variable.h"
#include "memory.h"
#include "print.h"
#include <vector>
#include <string>
#include <limits.h>

#include <FlexLexer.h>

FlexLexer* lexer;
bool isFileInputMode = false;//ファイル入力があるか
bool isBinaryInput = false;//その時点の計算に2進数表記があるか
bool isHexInput = false;
bool isFuncReadMode = false;
int yyparse();
int yylex()
{
  if(const char* text = lexer->YYText())
  {
    if(to_String(text) != "\n")
    {
      WriteInput(to_String(text));
    }
  }
  return lexer->yylex();
}

void yyerror(const char *s)
{
  PrintErrorln(s);
}


void showFormula(double value)
{  
  bool error = false;
  if(std::isinf(value))//オーバーフロー
  {
    PrintErrorln("ERROR: Overflow");
    error = true;
  }
  if(std::isnan(value))//数値でない
  {
    PrintErrorln("Not a Number");
    error = true;
  }


  if(!error)
  {
    if(isBinaryInput)
    {
      Println(uIntToBinStr((unsigned int)value)+"("+to_String((unsigned int)value)+")");
    }
    else if(isHexInput)
    {
      Println(uIntToHexStr((unsigned int)value)+"("+to_String((unsigned int)value)+")");
    }
    else if(ceil(value)!=floor(value) || value > INT_MAX)
    {
      Println(value);
    }
    else
    {
      Println((int)value);
    }
  }

  isBinaryInput=false;
  isHexInput = false;
}


int main(int argc, char *argv[])
{
    Clac mainCalc;
    mainCalc.run();
}
%}

%union 
{
  double number;
  char string[255];
  double (*fp)(double);//1引数double型の数学関数用
  double (*fpp)(double,double);//2引数double型の数学関数用
  void (*fpv)(void);//引数のないvoid型の関数
  double (*fpvec)(void);//可変引数の関数用、引数は全てargs.cのvecotrに追加されていく。
  void (*fpc)(char*);
  char expr[255];//ユーザー定義の式の文字列
}

%token  <number> CONSTANT
%token  <string> CHARACTER
%token  <fp> FUNCTION
%token  <fpp> FUNCTION2
%token  <fpv> FUNCTION0
%token  <fpvec> FUNCTION_var
%token  <fpc> FUNCTION_user
%token  <expr> FUNCTION_TEXT
%token  '+'
%token  '('
%token  ')'

%type <number> lines expression formula term primary function args
%type <string> character

%%
lines
  : /* empty */ {/* empty */}
  | lines '\n' {PrintNextLine();}
  | lines expression '\n' {PrintNextLine();}
  | error '\n'       { yyerrok;PrintNextLine(); }
expression
  : formula { showFormula($1);update_ans($1);pushMemory($1); }
  | character { show_variable($1); }
  | character '=' formula { update_variable($1, $3); }
  | FUNCTION0 { $1();}
  | FUNCTION_user '(' character ')'{$1($3);clearArgs();/*変数なしのファイル*/}
  | FUNCTION_user '(' character'('args')' ')'{$1($3);  clearArgs();/*変数ｘがあるファイル*/}
  | '#'  character'('character')'FUNCTION_TEXT {makeFunc($2,$6); clearArgs();/*# a(x) $(x-1)*(x-3)$のような定義*/}
formula
  : term
  | '-'term  { $$ = (!isBinaryInput) ? -1*$2 : complement($2) ;}
  | formula '+' term  { $$ = $1 + $3; }
  | formula '-' term  { $$ = $1 - $3; }
term
  : primary
  | term '*' primary { $$ = $1 * $3; }
  | term '/' primary { $$ = $1 / $3; if($3==0)PrintErrorln("ERROR: Can't divide by 0");}
  | term '%' primary { $$ = fmod($1,$3); }
  | term '^' primary { $$ = pow($1,$3); }
  | term '<''<' primary { $$ = leftShift($1,$4); if(32<=$4||$$ < $1)PrintErrorln("ERROR: Over Flow");}
  | term '>''>' primary { $$ = rightShift($1,$4); if($4< 0||31<=$4 )PrintErrorln("ERROR: Out of Shift Range"); }
primary
  : CONSTANT 
  | function { $$ = $1; }
  | character { if(get_value($1)){ $$ = *get_value($1);}else{$$ = NAN;}}
  | '(' formula ')'  { $$ = $2; }
function
  : FUNCTION '(' formula ')'{ $$ = $1($3); }
  | FUNCTION2 '(' formula','formula')'{ $$ = $1($3,$5); }
  | FUNCTION_var '(' args ')'{ $$ = $1(); clearArgs();/* argsで引数を全てpushArgした後、それらは関数内で参照する */}
  | character'('args')'{readFunc($1);  clearArgs();$$=get_value("ans") ? *get_value("ans"):1;/*ユーザー定義の関数(変数ｘがあるファイル)*/}
args/* $$ = NANは使われないため特に意味はない */
  : formula   { pushArg($1);$$ = NAN;}
  | formula ',' args  { pushArg($1);$$ = NAN; }
character
  : CHARACTER
%%
