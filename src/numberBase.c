#include "numberBase.h"
#include "print.h"
#include <limits>

unsigned int binToUInt(const std::string &str)
{
    unsigned int value = 0;
    //0b表記の場合は2文字目から読み始める
    unsigned int i=0;
    if(str[1]=='b' || str[1]=='B')
    {
        i=2;
    }
    for(;i<str.length();++i)
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
    return "0b"+str;
}
unsigned int complement(unsigned int value)
{
    std::string binStrMAX = uIntToBinStr(std::numeric_limits<unsigned int>::max());
    std::string binStr = uIntToBinStr(value);
    for(unsigned int i = binStr.length() - 1 ; 2 <= i; --i)
    {
        if(binStr[i] == '1')
        {
            auto offset = binStrMAX.length() - binStr.length();

            binStrMAX[i+offset] = '0';
        }
    }
    return binToUInt(binStrMAX)+1 ;
}


unsigned int hexToUInt(const std::string &str)
{
    unsigned int value = 0;
    //0x表記の場合は2文字目から読み始める
    unsigned int i=0;
    if(str[1]=='x' || str[1]=='X')
    {
        i=2;
    }
    for(;i<str.length();++i)
    {
        char ch = str[i];
        unsigned int v;
        if( '0' <=ch && ch <= '9' )
            v = ch - '0';
        else if('A'<= ch && ch <= 'F' )
            v = ch - 'A' + 10;
        else if( 'a' <=ch && ch <= 'f' )
            v = ch - 'a' + 10;

        value = value * 16 + v;
    }
    return value;
}

unsigned int hexToUInt(const char *ptr)
{
    return hexToUInt(to_String(ptr));
}

std::string uIntToHexStr(unsigned int value, bool lower)
{
    if(value==0)
        return std::string("0");
    std::string str;
    const char hc = lower ? 'a' : 'A';
    while( value != 0 )
    {
        int d = value & 15;
        str.insert(str.begin(), d + (( d < 10 ) ? '0' : hc - 10));
        value >>= 4;
    }
    return "0x"+str;
}

double toBin(double value)
{
    return 0 < value ? value : (double)complement(-value);
}
double toHex(double value)
{
    return 0 < value ? value : (double)complement(-value);
}