#include "numberBase.h"
#include "print.h"

unsigned int binToUInt(const std::string &str)
{
    unsigned int value = 0;
    for(unsigned int i=2;i<str.length();++i)
    {
    	value = value * 2 + (str[i] - '0');
    }
    return value;
}

unsigned int binToUInt(const char *ptr)
{
    return binToUInt(to_String(ptr));
}

std::string uIntToBinStr(unsigned int value)
{
    if(value==0)
        return std::string("0");
    std::string str;
    while( value != 0 ) 
    {
        str.insert(str.begin(), '0'+ ((value & 1) == 1));
        value >>= 1;
    }
    return str;
}