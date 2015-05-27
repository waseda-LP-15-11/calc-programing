#include "function.h"
#include "Calc.h"
#include "print.h"
#include "args.h"
#include <fstream>
#include <vector>
void readFile(char* fileName)
{
	{
		const char* filename = std::string(to_String(fileName)+".txt").c_str();
		std::ifstream ifs(filename);
		if(ifs.fail())
		{
			PrintErrorln("CANNOT OPEN");
			return;
		}

		std::ofstream ofs("temp");
		std::string str;

		//全行の読み出し
		while(ifs >> str)
		{
			ofs << str << std::endl;
		}
	}
	ClearInputOutput();
	Clac calc("temp");
  	calc.doFunc();
}
double readFunc(char* funcName)
{
	{
		const char* filename = std::string(to_String(funcName)+".txt").c_str();
		std::ifstream ifs(filename);
		if(ifs.fail())
		{
			PrintErrorln("the func is undefined");
			return 0;
		}

		std::ofstream ofs("temp0");
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
				//引数があれば関数なので$  $を削除する
				if((int)str.find("$") != -1)
				{
					str.replace((int)str.find("$"), 1, "");
					if((int)str.find("$") != -1)
					{
						str.replace((int)str.rfind("$"), 1, "");
					}
				}

				
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
	double ret = system("calc.exe temp0");
	std::ifstream ifs("temp1");
	std::string str;
	ifs >> str;
	return atof(str.c_str());
}

void makeFunc(char* funcName,char* funcText)
{
	const char* filename = std::string(to_String(funcName)+".txt").c_str();

	std::ofstream ofs(filename);
	ofs << funcText;
}