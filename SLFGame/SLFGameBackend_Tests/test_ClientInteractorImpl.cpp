#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/ClientInteractorImpl.h"
#include "../SLFGameBackend/RandomGenRessource.h"
#include "../SLFGameBackend/GameStatsOperations.h"
#include "../SLFGameBackend/ClientSource.h"
#include "../SLFGameBackend/SLFParser.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/UI.h"
#include "../SLFGameBackend/GameStatsSerializer.h"
#include "../SLFGameBackend/MessageHandler.h"

using namespace ::testing;

class FakeUI : public UI
{
public:
	MOCK_METHOD(void, PrepareGame,			(const GameStats&),		(override));
	MOCK_METHOD(void, PrepareOverview,		(const GameStats&),		(override));
	MOCK_METHOD(void, PrepareFinalScores,	(const GameStats&),		(override));
	MOCK_METHOD(void, ReceiveID,			(int),					(override));
	MOCK_METHOD(void, UpdateLobby,			(const LobbySettings&),	(override));
	MOCK_METHOD(void, SetLobbyCode,			(const LobbyCode&),		(override));
	MOCK_METHOD(void, UpdateGameState,		(const STATE&),			(override));
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

class FakeClient : public ClientSource
{
public:
	MOCK_METHOD(std::string,	GenerateLobbyCode,	(),					(override));
	MOCK_METHOD(void,			ConnectToServer,	(const LobbyCode&),	(override));
	MOCK_METHOD(void,			WriteToHost,		(const ByteStream&),(override));
};

class TestClientInteractor : public Test
{
public:
	TestClientInteractor() :
		gameInteractor{&fakeRandomLetterGenerator, &gameStatsOperations, &game, &parser, &fakeServer, &serializer, &msgHandler}
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
	::testing::NiceMock<FakeClient> fakeServer{};
	GameStatsOperations gameStatsOperations{};
	GameStats gameStats{};
	PlayerStats playerStats{};
	SLFParser parser;
	GameStatsSerializer serializer{};
	MessageHandler msgHandler{};
	ClientInteractorImpl gameInteractor;
};

//TEST_F(TestClientInteractor, PrepareLobby_EmptyLobbyCode_StandartGameStatsPlayerStats)
//{
//	auto actual = gameInteractor.PrepareLobby();
//
//	EXPECT_EQ(actual.second.answers.size(), 0);
//	EXPECT_EQ(actual.second.points, 0);
//
//	Categories cat{ {"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"} };
//	EXPECT_EQ(actual.first.categories, cat);
//	EXPECT_EQ(actual.first.currentLetter, Letter{});
//	EXPECT_EQ(actual.first.lettersUsed.size(), 0);
//	EXPECT_EQ(actual.first.currentRound, 0);
//	EXPECT_EQ(actual.first.maxRounds, 5);
//	EXPECT_EQ(actual.first.lobbyCode, "");
//}

TEST_F(TestClientInteractor, PrepareGame_StandartCatsRound0NoTimer_ReturnGameStatsAndPlayerStatsFilledWithStdCatsRound0NoTimer)
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

TEST_F(TestClientInteractor, PrepareOverview_AnswersBremenBulgarienBrahmaputra_ReturnPlayerStatsFilledWithBremenBulgarienBrahmaputra)
{
	GameStats actualGS;
	PlayerStats actualPS;
	gameInteractor.onPrepareOverview = [&actualGS, &actualPS](GameStats gs)
	{
		actualGS = gs;
		actualPS = gs.players[0];
	};

	gameInteractor.m_GameStats.players.push_back({ "Name", {}, {} });
	gameInteractor.PrepareOverview({ {"Bremen"}, {"Bulgarien"}, {"Brahmaputra"} });

	std::vector<std::string> expected{ {"Bremen"}, {"Bulgarien"}, {"Brahmaputra"} };
	EXPECT_EQ(actualPS.answers, expected);
}

TEST_F(TestClientInteractor, EndRound_LastRoundThreeEvaluations_CallPrepareFinalScoresWithCalculatedScores)
{
	GameStats expectedGS;
	expectedGS.currentRound = 1;
	expectedGS.maxRounds = 0;
	PlayerStats expectedPS;
	expectedPS.points = 40;
	expectedGS.players.push_back(expectedPS);
	::testing::StrictMock<FakeUI> fui;
	gameInteractor.onGameOver = [&fui](GameStats gs) 
		{fui.PrepareFinalScores(gs); };
	std::vector<DECISION> dec{ DECISION::UNIQUE, DECISION::UNIQUE, DECISION::SOLO};

	EXPECT_CALL(fui, PrepareFinalScores(expectedGS));

	gameInteractor.m_GameStats.players.push_back({ "", 0, {} });
	gameInteractor.m_GameStats.maxRounds = 0;
	gameInteractor.EndRound(dec);
}

TEST_F(TestClientInteractor, EndRound_FirstRoundThreeEvaluations_CallPrepareGameWithScoresAndUsedLetters)
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
	gameInteractor.onPrepareNextRound = [&fui](GameStats gs) {fui.PrepareGame(gs); };
	std::vector<DECISION> dec{ DECISION::UNIQUE, DECISION::UNIQUE, DECISION::SOLO };
	gameInteractor.m_GameStats.maxRounds = 2;

	EXPECT_CALL(fui, PrepareGame(expectedGS));

	gameInteractor.m_GameStats.players.push_back({ "", 0, {} });
	gameInteractor.EndRound(dec);
}

TEST_F(TestClientInteractor, HostLobby_StartServer_CallStartServer)
{
	FakeUI fui{};
	bool started = false;
	gameInteractor.onPrepareLobby = [&fui](const GameStats& stats) {fui.PrepareGame(stats); };
	gameInteractor.onSetLobbyCode = [&fui](const std::string& id) {fui.SetLobbyCode(id); };
	gameInteractor.onStartServer = [&started]() { started = true; };

	gameInteractor.HostLobby("T-3000");

	EXPECT_TRUE(started);
}

TEST_F(TestClientInteractor, JoinLobby_ConnectToServer_CallConnectToServer)
{
	EXPECT_CALL(fakeServer, ConnectToServer("CODE"));
	FakeUI fui{};
	gameInteractor.onPrepareLobby = [&fui](const GameStats& stats) {fui.PrepareGame(stats); };
	gameInteractor.onSetLobbyCode = [&fui](const std::string& id) {fui.SetLobbyCode(id); };
	gameInteractor.JoinLobby("CODE", "T-3000");
}

TEST_F(TestClientInteractor, JoinLobby_WriteToHost_CallConnectToServer)
{
	EXPECT_CALL(fakeServer, WriteToHost(ByteStream{ '\0', '\0', '\0', '\x1', '\0', '\0', '\0', '\f', '\0', 'T', '\0', '-','\0', '3','\0', '0','\0', '0','\0', '0'}));
	FakeUI fui{};
	gameInteractor.onPrepareLobby = [&fui](const GameStats& stats) {fui.PrepareGame(stats); };
	gameInteractor.onSetLobbyCode = [&fui](const std::string& id) {fui.SetLobbyCode(id); };

	gameInteractor.JoinLobby("CODE", "T-3000");
}