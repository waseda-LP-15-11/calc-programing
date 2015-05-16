#include "print.h"
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
