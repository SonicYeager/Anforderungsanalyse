#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/GameInteractor.h"
#include "../SLFGameBackend/RandomGenRessource.h"
#include "../SLFGameBackend/GameStatsOperations.h"
#include "../SLFGameBackend/NetworkSource.h"
#include "../SLFGameBackend/SLFParser.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/UI.h"
#include "../SLFGameBackend/Client.h"
#include "../SLFGameBackend/Host.h"

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
	MOCK_METHOD(LobbyCode,	StartServer,		(),							(override));
	MOCK_METHOD(void,		ConnectToServer,	(const LobbyCode&),			(override));
	MOCK_METHOD(void,		WriteTo,			(const ByteStream&, int),	(override));
	MOCK_METHOD(void,		WriteToHost,		(const ByteStream&),		(override));
	MOCK_METHOD(void,		Broadcast,			(const ByteStream&),		(override));
	MOCK_METHOD(ByteStream,	ReceiveData,		(),							(override));
	MOCK_METHOD(ByteStream,	ReceiveData,		(int),						(override));
private:
	int numCalls = 0;
};

class TestGameInteractor : public Test
{
public:
	TestGameInteractor() :
		gameInteractor{&fakeRandomLetterGenerator, &gameStatsOperations, &game, &fakeNetworkSource, &parser, &clientLogic, &hostLogic}
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
	Client clientLogic{&fakeNetworkSource};
	Host hostLogic{&fakeNetworkSource};
};

TEST_F(TestGameInteractor, PrepareLobby_EmptyLobbyCode_StandartGameStatsPlayerStats)
{
	auto actual = gameInteractor.PrepareLobby();

	EXPECT_EQ(actual.second.answers.size(), 0);
	EXPECT_EQ(actual.second.points, 0);

	Categories cat{ {"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"} };
	EXPECT_EQ(actual.first.categories, cat);
	EXPECT_EQ(actual.first.currentLetter, Letter{});
	EXPECT_EQ(actual.first.lettersUsed.size(), 0);
	EXPECT_EQ(actual.first.currentRound, 0);
	EXPECT_EQ(actual.first.maxRounds, 5);
	EXPECT_EQ(actual.first.lobbyCode, "");
}

TEST_F(TestGameInteractor, PrepareGame_StandartCatsRound0NoTimer_ReturnGameStatsAndPlayerStatsFilledWithStdCatsRound0NoTimer)
{
	GameStats actualGS;
	gameInteractor.onPrepareGame = [&actualGS](GameStats gs) 
	{
		actualGS = gs;
	};

	gameInteractor.PrepareGame("Stadt,Land,Fluss,Name,Tier,Beruf", "", "0");

	Categories cat{ {"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"} };
	EXPECT_EQ(actualGS.categories, cat);
	EXPECT_EQ(actualGS.timeout, "");
	EXPECT_EQ(actualGS.currentRound, 1);
}

TEST_F(TestGameInteractor, PrepareOverview_AnswersBremenBulgarienBrahmaputra_ReturnPlayerStatsFilledWithBremenBulgarienBrahmaputra)
{
	GameStats actualGS;
	PlayerStats actualPS;
	gameInteractor.onPrepareOverview = [&actualGS, &actualPS](GameStats gs)
	{
		actualGS = gs;
		actualPS = gs.players[0];
	};

	gameInteractor.m_GameStats.players.push_back({ "Name", 0, {}, {} });
	gameInteractor.PrepareOverview({ {"Bremen"}, {"Bulgarien"}, {"Brahmaputra"} });

	std::vector<std::string> expected{ {"Bremen"}, {"Bulgarien"}, {"Brahmaputra"} };
	EXPECT_EQ(actualPS.answers, expected);
}

TEST_F(TestGameInteractor, EndRound_LastRoundThreeEvaluations_CallPrepareFinalScoresWithCalculatedScores)
{
	GameStats expectedGS;
	expectedGS.currentRound = 1;
	PlayerStats expectedPS;
	expectedPS.points = 40;
	expectedGS.players.push_back(expectedPS);
	::testing::StrictMock<FakeUI> fui;
	gameInteractor.onGameOver = [&fui](GameStats gs) 
		{fui.PrepareFinalScores(gs, gs.players[0]); };
	std::vector<DECISION> dec{ DECISION::UNIQUE, DECISION::UNIQUE, DECISION::SOLO};

	EXPECT_CALL(fui, PrepareFinalScores(expectedGS, expectedPS));

	gameInteractor.m_GameStats.players.push_back({ "", 0, 0, {} });
	gameInteractor.EndRound(dec);
}

TEST_F(TestGameInteractor, EndRound_FirstRoundThreeEvaluations_CallPrepareGameWithScoresAndUsedLetters)
{
	GameStats expectedGS;
	expectedGS.currentRound = 1;
	expectedGS.currentLetter = {'C'};
	expectedGS.maxRounds = 2;
	expectedGS.lettersUsed = {{'C'}};
	PlayerStats expectedPS;
	expectedPS.points = 40;
	expectedGS.players.push_back(expectedPS);
	::testing::StrictMock<FakeUI> fui;
	gameInteractor.onPrepareNextRound = [&fui](GameStats gs) {fui.PrepareGame(gs, gs.players[0]); };
	std::vector<DECISION> dec{ DECISION::UNIQUE, DECISION::UNIQUE, DECISION::SOLO };
	gameInteractor.m_GameStats.maxRounds = 2;

	EXPECT_CALL(fui, PrepareGame(expectedGS, expectedPS));

	gameInteractor.m_GameStats.players.push_back({ "", 0, 0, {} });
	gameInteractor.EndRound(dec);
}

TEST_F(TestGameInteractor, HostLobby_StatsAreCreated_GameStatsShouldBeFilledWithPlayer0AndBasicSettings)
{
	GameStats expectedgs{};
	expectedgs.maxRounds = 5;
	expectedgs.categories = { {{"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"}} };
	expectedgs.lobbyCode = "";
	PlayerStats expectedps{};
	expectedps.playerName = "Johnny";
	expectedps.playerID = 0;
	expectedgs.players.push_back(expectedps);
	GameStats actualGS;
	PlayerStats actualPS;
	gameInteractor.onPrepareLobby = [&actualGS, &actualPS](GameStats gs)
	{
		actualGS = gs;
		actualPS = gs.players[0];
	};

	gameInteractor.HostLobby("Johnny");
	EXPECT_EQ(expectedgs.maxRounds, actualGS.maxRounds);
	EXPECT_EQ(expectedgs.categories, actualGS.categories);
	EXPECT_EQ(expectedgs.lobbyCode, actualGS.lobbyCode);
	EXPECT_EQ(expectedgs.players[0].playerName, expectedps.playerName);
	EXPECT_EQ(expectedgs.players[0].playerID, expectedps.playerID);
}