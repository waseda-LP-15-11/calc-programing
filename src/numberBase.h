#pragma once
#include <string>
unsigned int binToUInt(const std::string &str);
unsigned int binToUInt(const char *str);
std::string uIntToBinStr(unsigned int value);
unsigned int complement(unsigned int value);

unsigned int hexToUInt(const std::string &str);
unsigned int hexToUInt(const char *ptr);
std::string uIntToHexStr(unsigned int val, bool lower = false);

//0より大きいかチェックして返すだけの関数
double toBin(double value);
double toHex(double value);
