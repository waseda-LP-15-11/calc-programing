#pragma once
#include "Writer.h"
#include <memory>
#include <iostream>
#include <sstream>

//calc.y以外でもprint.hをincludeすればWriteとWritelnが使える
static Writer writer("result.txt");
template<typename Type>void Write(const Type value)
{
	writer.write(value);
}
template<typename Type>void Writeln(const Type value)
{
	writer.writeln(value);
}

void WriteNextLine();

template<typename Type>void Print(const Type value,bool write  = true)
{
	std::cout << value;
	if(write)
	{
		writer.write(value);
	}
}
template<typename Type>void Println(const Type value,bool write  = true)
{
	std::cout << value << std::endl;
	if(write)
	{
		writer.writeln(value);
	}
}

template<typename Type>void PrintErrorln(const Type value,bool write  = true)
{
	std::cerr << value << std::endl;
	if(write)
	{
		writer.writeln(value);
	}
}

template <typename T> std::string to_string(const T& t)
{
    std::ostringstream os; os<<t; return os.str();
}
