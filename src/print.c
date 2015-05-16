#include "print.h"
#include <fstream>
#include <locale>
Writer writer("result.txt");

void WriteInput(const std::string& value)
{
	writer.writeInput(value);
}
void WriteOutput(const std::string& value)
{
	writer.writeOutput(value);
}

void PrintNextLine()
{	
	if(isFileInputMode)
	{
		writer.writeCout();
	}
	writer.writeOneLine();
	Print(">> ",false);
}

void dispFunc(void)
{
	std::ifstream ifs("func.txt");
	if(!ifs.fail())
	{
		std::string text;
		while (getline(ifs, text))
    	{
        	Println(text,false);
    	}
	}
	else
	{
		PrintErrorln("FAIL_OPEN_FILE");
	}
}