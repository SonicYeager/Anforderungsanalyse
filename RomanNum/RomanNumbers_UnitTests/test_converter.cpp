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

TEST(TestConverter, ConvertArabicNumber_5_ReturnV)
{
	auto actual = ConvertArabicNumber(5);

	EXPECT_EQ(actual, "V");
}

TEST(TestConverter, ConvertRomanNumber_V_Return5)
{
	auto actual = ConvertRomanNumber("V");

	EXPECT_EQ(actual, "5");
}

TEST(TestConverter, ConvertArabicNumber_9_ReturnIX)
{
	auto actual = ConvertArabicNumber(9);

	EXPECT_EQ(actual, "IX");
}

TEST(TestConverter, ConvertRomanNumber_IX_Return9)
{
	auto actual = ConvertRomanNumber("IX");

	EXPECT_EQ(actual, "9");
}

TEST(TestConverter, ConvertArabicNumber_10_ReturnX)
{
	auto actual = ConvertArabicNumber(10);

	EXPECT_EQ(actual, "X");
}

TEST(TestConverter, ConvertRomanNumber_X_Return10)
{
	auto actual = ConvertRomanNumber("X");

	EXPECT_EQ(actual, "10");
}

TEST(TestConverter, ConvertArabicNumber_40_ReturnXL)
{
	auto actual = ConvertArabicNumber(40);

	EXPECT_EQ(actual, "XL");
}

TEST(TestConverter, ConvertRomanNumber_XL_Return40)
{
	auto actual = ConvertRomanNumber("XL");

	EXPECT_EQ(actual, "40");
}

TEST(TestConverter, ConvertArabicNumber_50_ReturnL)
{
	auto actual = ConvertArabicNumber(50);

	EXPECT_EQ(actual, "L");
}

TEST(TestConverter, ConvertRomanNumber_L_Return50)
{
	auto actual = ConvertRomanNumber("L");

	EXPECT_EQ(actual, "50");
}

TEST(TestConverter, ConvertArabicNumber_90_ReturnXC)
{
	auto actual = ConvertArabicNumber(90);

	EXPECT_EQ(actual, "XC");
}

TEST(TestConverter, ConvertRomanNumber_XC_Return90)
{
	auto actual = ConvertRomanNumber("XC");

	EXPECT_EQ(actual, "90");
}

TEST(TestConverter, ConvertArabicNumber_100_ReturnC)
{
	auto actual = ConvertArabicNumber(100);

	EXPECT_EQ(actual, "C");
}

TEST(TestConverter, ConvertRomanNumber_C_Return100)
{
	auto actual = ConvertRomanNumber("C");

	EXPECT_EQ(actual, "100");
}

TEST(TestConverter, ConvertArabicNumber_400_ReturnCD)
{
	auto actual = ConvertArabicNumber(400);

	EXPECT_EQ(actual, "CD");
}

TEST(TestConverter, ConvertRomanNumber_CD_Return400)
{
	auto actual = ConvertRomanNumber("CD");

	EXPECT_EQ(actual, "400");
}

TEST(TestConverter, ConvertArabicNumber_500_ReturnD)
{
	auto actual = ConvertArabicNumber(500);

	EXPECT_EQ(actual, "D");
}

TEST(TestConverter, ConvertRomanNumber_D_Return500)
{
	auto actual = ConvertRomanNumber("D");

	EXPECT_EQ(actual, "500");
}

TEST(TestConverter, ConvertArabicNumber_900_ReturnCM)
{
	auto actual = ConvertArabicNumber(900);

	EXPECT_EQ(actual, "CM");
}

TEST(TestConverter, ConvertRomanNumber_CM_Return900)
{
	auto actual = ConvertRomanNumber("CM");

	EXPECT_EQ(actual, "900");
}

TEST(TestConverter, ConvertArabicNumber_1000_ReturnM)
{
	auto actual = ConvertArabicNumber(1000);

	EXPECT_EQ(actual, "M");
}

TEST(TestConverter, ConvertRomanNumber_D_Return1000)
{
	auto actual = ConvertRomanNumber("M");

	EXPECT_EQ(actual, "1000");
}