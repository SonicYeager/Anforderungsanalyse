#pragma once

#include <string>

#ifdef ROMANNUMCONVERTER_EXPORTS
#define ROMANNUMCONVERTER_API __declspec(dllexport)
#else
#define ROMANNUMCONVERTER_API __declspec(dllimport)
#endif

std::string ROMANNUMCONVERTER_API DecimalToRoman(int dec);
int ROMANNUMCONVERTER_API RomanToDecimal(std::string);