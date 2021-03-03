#include "gmock/gmock.h"
#include "../SLFGameBackend/RandomGenerator.h"

TEST(TestRandomGenerator, GenerateUnusedLetter_AllUsedExceptZ_ReturnZ)
{
	RandomGenerator rg{};
	Letters used{ {
		{{'A'}},
		{{'B'}},
		{{'C'}},
		{{'D'}},
		{{'E'}},
		{{'F'}},
		{{'G'}},
		{{'H'}},
		{{'I'}},
		{{'J'}},
		{{'K'}},
		{{'L'}},
		{{'M'}},
		{{'N'}},
		{{'O'}},
		{{'P'}},
		{{'Q'}},
		{{'R'}},
		{{'S'}},
		{{'T'}},
		{{'U'}},
		{{'V'}},
		{{'W'}},
		{{'X'}},
		{{'Y'}}
		} };
	auto val = rg.GenerateUnusedLetter(used);
	Letter z{ 'Z' };
	EXPECT_EQ(val, z);
}

TEST(TestRandomGenerator, fGenerateUnusedLetter_AllUsedExceptVWXY_ReturnOneOfVWXY)
{
	RandomGenerator rg{};
	Letters used{ {
		{{'A'}},
		{{'B'}},
		{{'C'}},
		{{'D'}},
		{{'E'}},
		{{'F'}},
		{{'G'}},
		{{'H'}},
		{{'I'}},
		{{'J'}},
		{{'K'}},
		{{'L'}},
		{{'M'}},
		{{'N'}},
		{{'O'}},
		{{'P'}},
		{{'Q'}},
		{{'R'}},
		{{'S'}},
		{{'T'}},
		{{'U'}}
		}};

	auto val = rg.GenerateUnusedLetter(used);

	EXPECT_THAT(val.letter, ::testing::AnyOfArray({'V', 'W', 'X', 'Y', 'Z'}));
}