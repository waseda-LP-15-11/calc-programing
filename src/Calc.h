#pragma once
//#define MEMCHEK //メモリリークのチェックをする場合有効化
#include <fstream>
#include <iostream>
#include <FlexLexer.h>
#include "MemLeakChecker.h"
#include "print.h"
#include <stdio.h>
extern bool isFileInputMode;
extern FlexLexer* lexer;
int yyparse();
class Clac
{
  public:
  Clac()
  {
      //Println("ClacConstr",false);
    #ifdef MEMCHEK
    MemLeakChecker checker;
    #endif

    m_lexer = new yyFlexLexer();

    lexer = m_lexer;
      //Println("ClacConstrfinis",false);
  }

  Clac(const char* filename)
  {
      //Println("ClacConstrS",false);
    #ifdef MEMCHEK
    MemLeakChecker checker;
    #endif

    m_preLexer = lexer;//グローバルなlexerを一旦保存

    m_ifs.open(filename);
    if(!m_ifs.fail())
    {
        //Println("suceess",false);
      m_lexer = new yyFlexLexer(&m_ifs);
        //Println("newFinish",false);
      isFileInputMode = true;
    }
    else
    {
      //PrintlnErrorln("FAIL_OPEN_FILE");
      m_lexer = new yyFlexLexer();
      isFileInputMode = false;
    }
       //Println("newFinish",false);
    lexer = m_lexer;
      //Println("ClacConstrfinisS",false);
  }

  void run()
  {
      //Println("Clacrun",false);
    Print(">> ");
    yyparse();
      //Println("Clacrunfini",false);
  }

  void doFunc()
  {
      //Println("dofunc",false);
    Print(">> ");
    yyparse();
      //Println("dofuncfin",false);
  }

  ~Clac()
  {
    //Println("calcDest",false);
    lexer = m_preLexer;
    remove("temp");
    //delete m_lexer;
  }
//private:
  FlexLexer* m_lexer;
  std::ifstream m_ifs;
  FlexLexer* m_preLexer;
};