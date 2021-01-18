#include<assert.h>
#include "RomanConvert.h"

int main() {
	auto val3 = RomanToDecimal("MCDXCII");
	assert(val3 == 1492);
	val3 = RomanToDecimal("MDCCCLVI");
	assert(val3 == 1856);
	val3 = RomanToDecimal("I");
	assert(val3 == 1);
	val3 = RomanToDecimal("II");
	assert(val3 == 2);
	val3 = RomanToDecimal("IV");
	assert(val3 == 4);
	val3 = RomanToDecimal("V");
	assert(val3 == 5);
	val3 = RomanToDecimal("IX");
	assert(val3 == 9);
	val3 = RomanToDecimal("XLII");
	assert(val3 == 42);
	val3 = RomanToDecimal("XCIX");
	assert(val3 == 99);
	val3 = RomanToDecimal("MMXIII");
	assert(val3 == 2013);


	auto val = DecimalToRoman(1492);
	assert(val == "MCDXCII");
	auto val2 = DecimalToRoman(1856);
	assert(val2 == "MDCCCLVI");
	auto val5 = DecimalToRoman(1000);
	assert(val5 == "M");
}