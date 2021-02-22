#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/GameInteractor.h"
#include "../SLFGameBackend/RandomGenRessource.h"
#include "../SLFGameBackend/GameStatsOperations.h"
#include "../SLFGameBackend/NetworkSource.h"
#include "../SLFGameBackendQt/Parser.h"

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

class FakeNetworkSource : public NetworkSource
{
public:
	std::string GenerateLobbyCode() override
	{
		return "CODE";
	}
private:
	int numCalls = 0;
};

class TestGameInteractor : public Test
{
public:
	TestGameInteractor() :
		gi{&frlg, &gsop, &fns, &p}
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
	FakeNetworkSource fns{};
	GameStatsOperations gsop{};
	GameInteractor gi;
	GameStats gs{};
	PlayerStats ps{};
	Parser p;
};

//TEST_F(TestGameInteractor, PrepareNextRound_EmptyGameStatsEmptyPlayerStats_Round1LetterC)
//{
//	auto actual = gi.PrepareGame(gs, ps);
//
//	EXPECT_EQ(actual.first.GetCurrentLetter().letter, 'C');
//	EXPECT_EQ(actual.first.GetCurrentRound(), 1);
//}
//
//TEST_F(TestGameInteractor, PrepareNextRound_GameStatsFilledWithUsedLetterNoCurrentLetterPlayerStats_LetterB)
//{
//	Letters usedLetters{ {{'A'},{'C'}} };
//	gs.SetUsedLetters(usedLetters);
//
//	auto actual = gi.PrepareGame(gs, ps);
//
//	EXPECT_EQ(actual.first.GetCurrentLetter().letter, 'B');
//}
//
//TEST_F(TestGameInteractor, PrepareNextRound_GameStatsCurrentLetterBPlayerStats_LetterBIsTransferedToUsedLetters)
//{
//	gs.SetCurrentLetter(Letter{'B'});
//
//	auto actual = gi.PrepareGame(gs, ps);
//
//	EXPECT_EQ(actual.first.GetUsedLetters().letters[0].letter, 'B');
//}

TEST_F(TestGameInteractor, PrepareLobby_EmptyLobbyCode_StandartGameStatsPlayerStats)
{
	auto actual = gi.PrepareLobby();

	EXPECT_EQ(actual.second.GetAnswers().size(), 0);
	EXPECT_EQ(actual.second.GetPoints(), 0);

	Categories cat{ {"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"} };
	EXPECT_EQ(actual.first.GetCategories(), cat);
	EXPECT_EQ(actual.first.GetCurrentLetter(), Letter{});
	EXPECT_EQ(actual.first.GetUsedLetters().letters.size(), 0);
	EXPECT_EQ(actual.first.GetCurrentRound(), 0);
	EXPECT_EQ(actual.first.GetMaxRound(), 5);
	EXPECT_EQ(actual.first.GetLobbyCode(), "CODE");
}

TEST_F(TestGameInteractor, PrepareGame_StandartCatsRound0NoTimer_ReturnGameStatsAndPlayerStatsFilledWithStdCatsRound0NoTimer)
{
	auto actual = gi.PrepareGame("Stadt,Land,Fluss,Name,Tier,Beruf", "", "0");

	Categories cat{ {"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"} };
	EXPECT_EQ(actual.first.GetCategories(), cat);
	EXPECT_EQ(actual.first.GetTimeout(), "");
	EXPECT_EQ(actual.first.GetCurrentRound(), 1);
}