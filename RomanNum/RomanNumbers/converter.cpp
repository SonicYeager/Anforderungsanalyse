#include "converter.h"
#include "converter.h"
#include "../RomanNumConverter/RomanConvert.h"

std::string ConvertArabicNumber(int num)
{
	return DecimalToRoman(num);
}

std::string ConvertRomanNumber(const std::string& num)
{
	return std::to_string(RomanToDecimal(num));
}
