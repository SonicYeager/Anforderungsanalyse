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
	MOCK_METHOD(void, Init, (const GameStats&, const PlayerStats&), (override));
	MOCK_METHOD(void, PrepareGame, (const GameStats&, const PlayerStats&), (override));
	MOCK_METHOD(void, PrepareOverview, (const GameStats&, const PlayerStats&), (override));
	MOCK_METHOD(void, PrepareFinalScores, (const GameStats&, const PlayerStats&), (override));
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

TEST_F(TestGameInteractor, PrepareLobby_EmptyLobbyCode_StandartGameStatsPlayerStats)
{
	auto actual = gameInteractor.PrepareLobby();

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
	gameInteractor.onPrepareGame = [&actualGS, &actualPS](GameStats gs, PlayerStats playerStats) 
	{
		actualGS = gs;
		actualPS = playerStats;
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
	PlayerStats actualPS;
	gameInteractor.onPrepareOverview = [&actualGS, &actualPS](GameStats gs, PlayerStats playerStats)
	{
		actualGS = gs;
		actualPS = playerStats;
	};

	gameInteractor.PrepareOverview({ {"Bremen"}, {"Bulgarien"}, {"Brahmaputra"} });

	std::vector<std::string> expected{ {"Bremen"}, {"Bulgarien"}, {"Brahmaputra"} };
	EXPECT_EQ(actualPS.GetAnswers(), expected);
}

TEST_F(TestGameInteractor, EndRound_LastRoundThreeEvaluations_CallPrepareFinalScoresWithCalculatedScores)
{
	GameStats expectedGS;
	expectedGS.SetCurrentRound(1);
	PlayerStats expectedPS;
	expectedPS.SetPoints(40);
	::testing::StrictMock<FakeUI> fui;
	gameInteractor.onGameOver = [&fui](GameStats gs, PlayerStats playerStats) {fui.PrepareFinalScores(gs, playerStats); };
	std::vector<int> dec{2, 2, 1};

	EXPECT_CALL(fui, PrepareFinalScores(expectedGS, expectedPS));

	gameInteractor.EndRound(dec);
}

TEST_F(TestGameInteractor, EndRound_FirstRoundThreeEvaluations_CallPrepareGameWithScoresAndUsedLetters)
{
	GameStats expectedGS;
	expectedGS.SetCurrentRound(1);
	expectedGS.SetCurrentLetter({'C'});
	expectedGS.SetMaxRounds(2);
	expectedGS.SetUsedLetters({ {{'C'} } });
	PlayerStats expectedPS;
	expectedPS.SetPoints(40);
	::testing::StrictMock<FakeUI> fui;
	gameInteractor.onPrepareNextRound = [&fui](GameStats gs, PlayerStats playerStats) {fui.PrepareGame(gs, playerStats); };
	std::vector<int> dec{ 2, 2, 1 };
	gameInteractor.m_GameStats.SetMaxRounds(2);

	EXPECT_CALL(fui, PrepareGame(expectedGS, expectedPS));

	gameInteractor.EndRound(dec);
}