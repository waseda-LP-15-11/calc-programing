#include "function.h"
#include "Calc.h"
#include "print.h"
#include <fstream>

void readFunc(char* funcName)
{
	{
		const char* filename = std::string(to_String(funcName)+".txt").c_str();
		std::ifstream ifs(filename);
		if(ifs.fail())
		{
			PrintErrorln("the func is undefined");
			return;
		}
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