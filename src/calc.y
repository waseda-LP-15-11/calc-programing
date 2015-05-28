%{
//#define MEMCHEK //メモリリークのチェックをする場合有効化
#include "numberBase.h"
#include "args.h"
#include "sum.h"
#include "MemLeakChecker.h"
#include "exmath.h"
#include "memory.h"
#include "print.h"
#include <vector>
#include <string>
#include <limits.h>
#include <fstream>
#include <iostream>
#include <FlexLexer.h>

#include "calc.hpp"

std::unique_ptr<FlexLexer> lexer = nullptr;
bool isFileInputMode = false;//ファイル入力があるか
bool isBinInput = false;//その時点の計算に2進数表記があるか
bool isHexInput = false;
int yyparse();
int yylex()
{
  int yylexValue = lexer->yylex();
  if(const char* text = lexer->YYText())
  {
    if(to_String(text) != "\n")
    {
      WriteInput(to_String(text));
    }
  }
  return yylexValue;
}

void yyerror(const char *s)
{
  PrintErrorln(s);
}

int main(int argc, char *argv[])
{
#ifdef MEMCHEK
  MemLeakChecker checker;
#endif

  std::ifstream ifs;

  if(argc >= 2)
  {
    ifs.open(argv[1]);
    if(!ifs.fail())
    {
      lexer = std::make_unique<yyFlexLexer>(&ifs);
      isFileInputMode = true;
      goto OPEN_SUCCESS;
    }
    else
    {
      PrintErrorln("FAIL_OPEN_FILE");
    }
  }

  //失敗した場合||入力がない場合はここでnew
  lexer = std::make_unique<yyFlexLexer>();

OPEN_SUCCESS:
  defineAllDefaultFunction();

  Print(">> ",false);
  yyparse();
}
%}

%union 
{
  double number;
  char *character;
  double (*fp)(double);//1引数double型の数学関数用
  double (*fpp)(double,double);//2引数double型の数学関数用
  void (*fpv)(void);//引数のないvoid型の関数
  double (*fpvec)(void);//可変引数の関数用、引数は全てargs.cのvecotrに追加されていく。
  Expression *expression;
  ParameterList *parameter_list;

}
%token <expression> NUM_LITERAL
%token  <number> CONSTANT
%token  <character> CHARACTER
%token  <character> FUNCTION
%token  <character> FUNCTION_var
%token  <fpp> FUNCTION2
%token  <fpv> FUNCTION0
%token  '+'
%token  '('
%token  ')'
%token  DEFINE;

%type <parameter_list> func_parameter_list
%type <number> lines
%type <expression> expression formula term primary func_expression_list args
%type <fpv> system_func
%%
lines
  : /* empty */ {/* empty */}
  | lines '\n' {PrintNextLine();}
  | lines expression '\n' {calc_eval_expression($2); PrintNextLine();}
  | error '\n'       { yyerrok;PrintNextLine(); }
  | lines function_definition
  | lines system_func
function_definition
  : DEFINE CHARACTER '(' func_parameter_list ')' '=' func_expression_list { function_define($2, $4, $7); }
func_parameter_list
  : CHARACTER { $$ = create_parameter($1); }
  | func_parameter_list ',' CHARACTER { $$ = chain_parameter($1, $3); }
func_expression_list
  : expression { $$ = create_expression_list($1); }
  | func_expression_list ',' expression { $$ = chain_expression_list($1, $3); }
expression
  : formula
  | CHARACTER '=' expression { $$ = create_assign_expression($1, $3); }
formula
  : term
  | '-' term { $$ = create_minus_expression($2); }
  | formula '+' term  { $$ = create_binary_expression(ADD_EXPRESSION, $1, $3); }
  | formula '-' term  { $$ = create_binary_expression(SUB_EXPRESSION, $1, $3); }
term
  : primary
  | term '*' primary { $$ = create_binary_expression(MUL_EXPRESSION, $1,$3); }
  | term '/' primary { $$ = create_binary_expression(DIV_EXPRESSION, $1,$3); }
  | term '%' primary { $$ = create_binary_expression(MOD_EXPRESSION, $1,$3); }
  | term '^' primary { $$ = create_binary_expression(POW_EXPRESSION, $1,$3); }
  | term '<''<' primary { $$ = create_binary_expression(LS_EXPRESSION, $1, $4);}
  | term '>''>' primary { $$ = create_binary_expression(RS_EXPRESSION, $1, $4);}
primary
  : NUM_LITERAL
  | '(' formula ')'  { $$ = $2; }
  | CHARACTER '(' func_expression_list ')' { $$ = create_function_call_expression($1, $3); }
  | CHARACTER { $$ = create_character_expression($1); }
  | FUNCTION '(' func_expression_list ')' { $$ = create_function_call_expression($1, $3); }
  | FUNCTION_var '(' args ')' { $$ = create_function_var_call_expression($1);}
args
  : formula   { pushArg($1);}
  | formula ',' args  { pushArg($1); }
system_func
  : FUNCTION0 {$1();}
%%
