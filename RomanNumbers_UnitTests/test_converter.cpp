#include "gmock/gmock.h"
#include "../RomanNumbers/converter.h"

TEST(TestConverter, ConvertArabicNumber_1_ReturnI)
{
	auto actual = ConvertArabicNumber(1);

	EXPECT_EQ(actual, "I");
}

TEST(TestConverter, ConvertRomanNumber_I_Return1)
{
	auto actual = ConvertRomanNumber("I");

	EXPECT_EQ(actual, "1");
}

TEST(TestConverter, ConvertArabicNumber_4_ReturnIV)
{
	auto actual = ConvertArabicNumber(4);

	EXPECT_EQ(actual, "IV");
}

TEST(TestConverter, ConvertRomanNumber_IV_Return4)
{
	auto actual = ConvertRomanNumber("IV");

	EXPECT_EQ(actual, "4");
}

