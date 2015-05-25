#pragma once
#include "Writer.h"
#include <memory>
#include <iostream>
#include <sstream>

extern Writer writer;
extern bool isFileInputMode;
extern bool isFuncReadMode;
void PrintNextLine();

void ClearInputOutput();
void WriteInput(const std::string& value);
void WriteOutput(const std::string& value);


template <typename T> std::string to_String(const T& t)
{
    std::ostringstream os; os<<t; return os.str();
}

template<typename Type>void Print(const Type value,bool writable  = true)
{
	if(!isFileInputMode)
	{
		std::cout << value;
	}
	if(writable)
	{
		WriteOutput(to_String(value));
	}
}

template<typename Type>void Println(const Type value,bool writable  = true)
{
	Print(value,writable);
	if(!isFileInputMode)
	{
		std::cout << std::endl;
	}
}

template<typename Type>void PrintErrorln(const Type value)
{
	if(!isFileInputMode)
	{
		std::cerr << value << std::endl;
	}
	WriteOutput(to_String(value));
}

void dispFunc(void);