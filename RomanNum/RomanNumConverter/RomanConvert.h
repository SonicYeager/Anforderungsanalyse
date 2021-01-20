#pragma once
#include <string>

//#ifdef ROMANNUMCONVERTER_EXPORTS
//#define ROMANNUMCONVERTER_API __declspec(dllexport)
//#else
//#define ROMANNUMCONVERTER_API __declspec(dllimport)
//#endif

std::string DecimalToRoman(int dec);
int RomanToDecimal(const std::string&);