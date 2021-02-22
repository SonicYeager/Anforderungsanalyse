#include "gmock/gmock.h"
#include "../SLFGameBackendQt/SLFParser.h"
#include "../SLFGameBackend/DataTypes.h"

TEST(TestSLFParser, ParseCategories_StandartCats_ReturnCategoriesStandart)
{
	SLFParser p;
	auto actual = p.ParseCategories("Stadt,Land,Fluss,Name,Tier,Beruf");

	Categories expected{ {"Stadt" }, {"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"} };
	EXPECT_EQ(actual, expected);
}

TEST(TestSLFParser, ParseRoundCount_Round0_Return0)
{
	SLFParser p;
	auto actual = p.ParseRoundCount("0");

	EXPECT_EQ(actual, 0);
}

TEST(TestSLFParser, ParseRoundCount_Round12_Return12)
{
	SLFParser p;
	auto actual = p.ParseRoundCount("12");

	EXPECT_EQ(actual, 12);
}