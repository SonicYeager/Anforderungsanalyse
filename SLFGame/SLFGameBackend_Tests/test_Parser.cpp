#include "gmock/gmock.h"
#include "../SLFGameBackendQt/Parser.h"
#include "../SLFGameBackend/DataTypes.h"

TEST(TestParser, ParseCategories_StandartCats_ReturnCategoriesStandart)
{
	Parser p;
	auto actual = p.ParseCategories("Stadt,Land,Fluss,Name,Tier,Beruf");

	Categories expected{ {"Stadt" }, {"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"} };
	EXPECT_EQ(actual, expected);
}

TEST(TestParser, ParseRoundCount_Round0_Return0)
{
	Parser p;
	auto actual = p.ParseRoundCount("0");

	EXPECT_EQ(actual, 0);
}

TEST(TestParser, ParseRoundCount_Round12_Return12)
{
	Parser p;
	auto actual = p.ParseRoundCount("12");

	EXPECT_EQ(actual, 12);
}