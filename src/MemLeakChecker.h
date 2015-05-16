#pragma onece
#ifdef MEMCHEK
#include <mcheck.h>  // mtrace用のヘッダ

class MemLeakChecker
{
	MemLeakChecker()
	{
		// チェック開始
		mtrace();		
	}
	~
	MemLeakChecker()
	{
		// チェック終了
		mtrace();		
	}
};
#endif