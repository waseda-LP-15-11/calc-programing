#include "function.h"
#include "Calc.h"
#include <fstream>

void readFunc(void)
{
	{
		std::ifstream ifs("a(x).txt");
		std::ofstream ofs("temp");
		std::string str;
		//全行の読み出し
		while(ifs >> str)
		{
			std::string::size_type pos = 0;
			std::string from = "x";
			std::string to = "3";
	    	while(pos = str.find(from, pos), pos != std::string::npos) 
	    	{
	        	str.replace(pos, from.length(), to);
	       	 	pos += to.length();
	    	}	
			ofs << str << std::endl;
		}
	}
	Clac calc("temp");
  	calc.doFunc();
}