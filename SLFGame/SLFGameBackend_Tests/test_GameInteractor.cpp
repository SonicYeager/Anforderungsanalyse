#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/GameInteractor.h"
#include "../SLFGameBackend/RandomGenRessource.h"
#include "../SLFGameBackend/GameStatsOperations.h"
#include "../SLFGameBackend/NetworkSource.h"
#include "../SLFGameBackend/SLFParser.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/UI.h"

using namespace ::testing;

class FakeUI : public UI
{
public:
	MOCK_METHOD(void, Init, (const GameStats&), (override));
	MOCK_METHOD(void, PrepareGame, (const GameStats&), (override));
	MOCK_METHOD(void, PrepareOverview, (const GameStats&), (override));
	MOCK_METHOD(void, PrepareFinalScores, (const GameStats&), (override));
};

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
	// Geerbt über NetworkSource
	void StartServer() override
	{
	}
	void ConnectToServer(const std::string&) override
	{
	}
private:
	int numCalls = 0;

};

class TestGameInteractor : public Test
{
public:
	TestGameInteractor() :
		gameInteractor{&fakeRandomLetterGenerator, &gameStatsOperations, &game, &fakeNetworkSource, &parser}
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

	Game game{};
	FakeRandomLetterGenerator fakeRandomLetterGenerator{};
	FakeNetworkSource fakeNetworkSource{};
	GameStatsOperations gameStatsOperations{};
	GameInteractor gameInteractor;
	GameStats gameStats{};
	PlayerStats playerStats{};
	SLFParser parser;
};

//TEST_F(TestGameInteractor, PrepareLobby_EmptyLobbyCode_StandartGameStatsPlayerStats)
//{
//	auto actual = gameInteractor.PrepareLobby();
//
//	EXPECT_EQ(actual.second.GetAnswers().size(), 0);
//	EXPECT_EQ(actual.second.GetPoints(), 0);
//
//	Categories cat{ {"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"} };
//	EXPECT_EQ(actual.first.GetCategories(), cat);
//	EXPECT_EQ(actual.first.GetCurrentLetter(), Letter{});
//	EXPECT_EQ(actual.first.GetUsedLetters().letters.size(), 0);
//	EXPECT_EQ(actual.first.GetCurrentRound(), 0);
//	EXPECT_EQ(actual.first.GetMaxRound(), 5);
//	EXPECT_EQ(actual.first.GetLobbyCode(), "CODE");
//}

TEST_F(TestGameInteractor, PrepareGame_StandartCatsRound0NoTimer_ReturnGameStatsAndPlayerStatsFilledWithStdCatsRound0NoTimer)
{
	GameStats actualGS;

	gameInteractor.onPrepareGame = [&actualGS](GameStats gs) 
	{
		actualGS = gs;
	};

	gameInteractor.PrepareGame("Stadt,Land,Fluss,Name,Tier,Beruf", "", "0");

	Categories cat{ {"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"} };
	EXPECT_EQ(actualGS.GetCategories(), cat);
	EXPECT_EQ(actualGS.GetTimeout(), "");
	EXPECT_EQ(actualGS.GetCurrentRound(), 1);
}

TEST_F(TestGameInteractor, PrepareOverview_AnswersBremenBulgarienBrahmaputra_ReturnPlayerStatsFilledWithBremenBulgarienBrahmaputra)
{
	GameStats actualGS;
	PlayerStats ps;
	int playerID = 0;
	ps.SetPlayerID(playerID);
	actualGS.AddPlayer(ps);

	gameInteractor.onPrepareOverview = [&actualGS](GameStats gs)
	{
		actualGS = gs;
	};

	gameInteractor.PrepareOverview({ {"Bremen"}, {"Bulgarien"}, {"Brahmaputra"} }, playerID);

	std::vector<std::string> expected{ {"Bremen"}, {"Bulgarien"}, {"Brahmaputra"} };
	EXPECT_EQ(actualGS.GetPlayerStats(playerID).GetAnswers(), expected);
}

TEST_F(TestGameInteractor, EndRound_LastRoundThreeEvaluations_CallPrepareFinalScoresWithCalculatedScores)
{
	GameStats expectedGS;
	expectedGS.SetCurrentRound(1);
	PlayerStats ps;
	expectedGS.AddPlayer(ps);
	expectedGS.GetPlayerStats(0).SetPoints(40);
	::testing::StrictMock<FakeUI> fui;
	gameInteractor.onGameOver = [&fui](GameStats gs) {fui.PrepareFinalScores(gs); };
	std::vector<DECISION> dec{UNIQUE, UNIQUE, SOLO};

	EXPECT_CALL(fui, PrepareFinalScores(expectedGS));

	gameInteractor.EndRound(dec, 0);
}

TEST_F(TestGameInteractor, EndRound_FirstRoundThreeEvaluations_CallPrepareGameWithScoresAndUsedLetters)
{
	GameStats expectedGS;
	expectedGS.SetCurrentRound(1);
	expectedGS.SetCurrentLetter({'C'});
	expectedGS.SetMaxRounds(2);
	expectedGS.SetUsedLetters({ {{'C'} } });
	PlayerStats ps;
	ps.SetPoints(40);
	expectedGS.AddPlayer(ps);
	::testing::StrictMock<FakeUI> fui;
	gameInteractor.onPrepareNextRound = [&fui](GameStats gs) {fui.PrepareGame(gs); };
	std::vector<DECISION> dec{ UNIQUE, UNIQUE, SOLO };
	gameInteractor.m_GameStats.SetMaxRounds(2);

	EXPECT_CALL(fui, PrepareGame(expectedGS));

	gameInteractor.EndRound(dec, 0);
}