%{
//#define MEMCHEK //メモリリークのチェックをする場合有効化
#include "MemLeakChecker.h"
#include "exmath.h"
#include "variable.h"
#include "memory.h"
#include "print.h"
#include <vector>
#include <string>
#include <limits.h>
#include <fstream>
#include <iostream>
#include <FlexLexer.h>


std::unique_ptr<FlexLexer> lexer = nullptr;
bool isFileInputMode = false;

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
    if(ceil(value)!=floor(value) || value > INT_MAX)
    {
      Println(value);
    }
    else 
    {
      Println((int)value);
    }
  }
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

  Print(">> ",false);
  yyparse();
}

%}

%union 
{
  double number;
  char string[255];
  double (*fp)(double);//double型の数学関数用
  double (*fpp)(double,double);//double型の数学関数用
  void (*fpv)(void);//void型の関数
}

%token  <number> CONSTANT
%token  <string> CHARACTER
%token  <fp> FUNCTION
%token  <fpp> FUNCTION2
%token  <fpv> FUNCTION3
%token  '+'
%token  '('
%token  ')'

%type <number> lines expression formula term primary
%type <string> character

%%
lines
  : /* empty */ {/* empty */}
  | lines '\n' {PrintNextLine();}
  | lines expression '\n' {PrintNextLine();update_ans($2);pushMemory($2);}
  | error '\n'       { yyerrok;PrintNextLine(); }
expression
  : formula { showFormula($1); }
  | character { show_variable($1); }
  | character '=' formula { update_variable($1, $3); }
formula
  : term
  | '-'term  { $$ = -1*$2; }
  | formula '+' term  { $$ = $1 + $3; }
  | formula '-' term  { $$ = $1 - $3; }
term
  : primary
  | term '*' primary { $$ = $1 * $3; }
  | term '/' primary { $$ = $1 / $3; if($3==0)PrintErrorln("ERROR: Can't divide by 0");}
  | term '%' primary { $$ = fmod($1,$3); }
  | term '^' primary { $$ = pow($1,$3); }
primary
  : CONSTANT 
  | FUNCTION '(' formula ')'{ $$ = $1($3); }
  | FUNCTION2 '(' formula','formula')'{ $$ = $1($3,$5); }
  | FUNCTION3 { $1(); }
  | character { if(get_value($1)){ $$ = *get_value($1);}else{$$ = nan(NULL);}}
  | '(' formula ')'  { $$ = $2; }
character
  : CHARACTER
%%


