#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/GameInteractor.h"
#include "../SLFGameBackend/RandomGenRessource.h"
#include "../SLFGameBackend/GameStatsOperations.h"

using namespace ::testing;

class FakeRandomLetterGenerator : public RandomGenRessource
{
public:
	Letter GenerateLetter() override
	{
		auto res = numCalls == 1 ? Letter{ 'B' } : Letter{ 'C' };
		++numCalls;
		return res;
	}
private:
	int numCalls = 0;
};

class TestGameInteractor : public Test
{
public:
	TestGameInteractor() :
		gi{&frlg, &gsop}
	{}
protected:
	virtual void SetUp()
	{
		Test::SetUp();
	}
	virtual void TearDown()
	{
		Test::TearDown();
	}

	FakeRandomLetterGenerator frlg{};
	GameStatsOperations gsop{};
	GameInteractor gi;
	GameStats gs{};
	PlayerStats ps{};
};

TEST_F(TestGameInteractor, PrepareNextRound_EmptyGameStatsEmptyPlayerStats_Round1LetterC)
{
	auto actual = gi.PrepareNextRound(gs, ps);

	EXPECT_EQ(actual.first.GetCurrentLetter().letter, 'C');
	EXPECT_EQ(actual.first.GetCurrentRound(), 1);
}

TEST_F(TestGameInteractor, PrepareNextRound_GameStatsFilledWithUsedLetterNoCurrentLetterPlayerStats_LetterB)
{
	Letters usedLetters{ {{'A'},{'C'}} };
	gs.SetUsedLetters(usedLetters);

	auto actual = gi.PrepareNextRound(gs, ps);

	EXPECT_EQ(actual.first.GetCurrentLetter().letter, 'B');
}

TEST_F(TestGameInteractor, PrepareNextRound_GameStatsCurrentLetterBPlayerStats_LetterBIsTransferedToUsedLetters)
{
	gs.SetCurrentLetter(Letter{'B'});

	auto actual = gi.PrepareNextRound(gs, ps);

	EXPECT_EQ(actual.first.GetUsedLetters().letters[0].letter, 'B');
}