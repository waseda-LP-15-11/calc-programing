#include "print.h"
#include "calc.hpp"
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
	// std::ifstream ifs("func.txt");
	// if(!ifs.fail())
	// {
	// 	std::string text;
	// 	while (getline(ifs, text))
 //    	{
 //        	Println(text,false);
 //    	}
	// }
	// else
	// {
	// 	PrintErrorln("FAIL_OPEN_FILE");
	// }
std::cout <<"Defined Function"<<std::endl;
std::cout <<"	"<<std::endl;
std::cout <<"	"<<std::endl;
std::cout <<"sin(rad)	cos(rad)	tan(rad)	"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"asin(rad)	acos(rad)	atan(rad) 	"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"sinh(rad)	cosh(rad)	tanh(rad) "<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"asinh(rad) acosh(rad) atanh(rad)	"<<std::endl;
std::cout <<"	"<<std::endl;

std::cout <<"exp(x) 		exp2(x)"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"log2(x) 	log(x) ln(x)"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"log10(x) 	"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"abs(x)"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"sqrt(x) 	cbrt(x) 	"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"round(x)	rint(x) "<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"floor(x)	ceil(x) 	"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"Radians(deg)"<<std::endl;
std::cout <<"Degrees(rad)"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"hypot(x,y) 	= sqrt(x^2+y^2)"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"dim(a,b) 	= (a>b)?a-b:0"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"sum(a,b,c,...)	"<<std::endl;
std::cout <<"ave(a,b,c,...)	"<<std::endl;
std::cout <<"geomean(a,b,c,...)	"<<std::endl;
std::cout <<"			"<<std::endl;
std::cout <<"mem(index)	Calculation results"<<std::endl;
std::cout <<"memory		ALL Calculation results"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"variable	ALL Defined variables"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"toBin(x)	binary representation"<<std::endl;
std::cout <<""<<std::endl;
std::cout <<"toHex(x)	hexadecimal representation"<<std::endl;
std::cout <<"	"<<std::endl;
}