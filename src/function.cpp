#include "function.h"
#include "Calc.h"
#include "print.h"
#include "args.h"
#include <fstream>
#include <vector>

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

		//引数の取得
		std::vector<double> args = getArgs();
		clearArgs();//sumなどの関数が記述されていると引数が交じるため一旦リセット
		//全行の読み出し
		while(ifs >> str)
		{
			//引数がなければ置換しない
			if(!args.empty())
			{
				//引数があれば関数なので$$を削除する
				str.replace((int)str.find("$"), 1, "");
				str.replace((int)str.rfind("$"), 1, "");
				
				std::string::size_type pos = 0;
				std::string from = "x";
				std::string to = to_String(args[0]);
		    	while(pos = str.find(from, pos), pos != std::string::npos) 
		    	{
		        	str.replace(pos, from.length(), to);
		       	 	pos += to.length();
		    	}	
	    	}
			ofs << str << std::endl;
		}
	}
	Clac calc("temp");
  	calc.doFunc();
}

void makeFunc(char* funcName,char* funcText)
{
	const char* filename = std::string(to_String(funcName)+".txt").c_str();

	std::ofstream ofs(filename);
	ofs << funcText;
}