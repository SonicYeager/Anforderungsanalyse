#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/GameInteractor.h"
#include "../SLFGameBackend/RandomGenRessource.h"
#include "../SLFGameBackend/GameStatsOperations.h"
#include "../SLFGameBackend/NetworkSource.h"
#include "../SLFGameBackend/SLFParser.h"

#include "../SLFGameBackend/RandomGenerator.h"

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
	Letter GenerateUnusedLetter(const Letters& filter) override
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
	SLFParser p;
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
	GameStats actualGS;
	PlayerStats actualPS;
	gi.onPrepareNextRound = [&actualGS, &actualPS](GameStats gs, PlayerStats ps) 
	{
		actualGS = gs;
		actualPS = ps;
	};

	gi.PrepareGame("Stadt,Land,Fluss,Name,Tier,Beruf", "", "0");

	Categories cat{ {"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"} };
	EXPECT_EQ(actualGS.GetCategories(), cat);
	EXPECT_EQ(actualGS.GetTimeout(), "");
	EXPECT_EQ(actualGS.GetCurrentRound(), 1);
}

TEST_F(TestGameInteractor, PrepareOverview_AnswersBremenBulgarienBrahmaputra_ReturnPlayerStatsFilledWithBremenBulgarienBrahmaputra)
{
	GameStats actualGS;
	PlayerStats actualPS;
	gi.onPrepareOverview = [&actualGS, &actualPS](GameStats gs, PlayerStats ps)
	{
		actualGS = gs;
		actualPS = ps;
	};

	gi.PrepareOverview({ {"Bremen"}, {"Bulgarien"}, {"Brahmaputra"} });

	std::vector<std::string> expected{ {"Bremen"}, {"Bulgarien"}, {"Brahmaputra"} };
	EXPECT_EQ(actualPS.GetAnswers(), expected);
}