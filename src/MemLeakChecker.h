#pragma onece
#ifdef MEMCHEK
#include <mcheck.h>  // mtrace用のヘッダ

class MemLeakChecker
{
public:
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
