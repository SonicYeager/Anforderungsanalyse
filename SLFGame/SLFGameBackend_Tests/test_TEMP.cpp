#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/ServerInteractorImpl.h"
#include "../SLFGameBackend/ClientInteractorImpl.h"
#include "../SLFGameBackend/RandomGenerator.h"
#include "../SLFGameBackend/GameStatsOperations.h"
#include "../SLFGameBackend/Client.h"
#include "../SLFGameBackend/Server.h"
#include "../SLFGameBackend/SLFParser.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/UI.h"
#include "../SLFGameBackend/GameStatsSerializer.h"
#include "../SLFGameBackend/MessageHandler.h"

using namespace ::testing;

class FakeUI : public UI
{
public:
	MOCK_METHOD(void, PrepareLobby, (const GameStats&), (override));
	MOCK_METHOD(void, PrepareGame, (const GameStats&), (override));
	MOCK_METHOD(void, PrepareOverview, (const GameStats&), (override));
	MOCK_METHOD(void, PrepareFinalScores, (const GameStats&), (override));
	MOCK_METHOD(void, UpdateGameStats, (const GameStats&), (override));
};

class Testy : public Test
{
public:
	Testy() :
		clientInteractor{ &RandomLetterGenerator, &gameStatsOperations, &game, &parser, &client, &serializer, &msgHandler },
		serverInteractor{ &server, &serializer, &msgHandler},
		clientInteractorII{ &RandomLetterGenerator, &gameStatsOperations, &game, &parser, &clientII, &serializer, &msgHandler },
		serverInteractorII{ &serverII, &serializer, &msgHandler }
	{
		clientInteractor.onStartServer = [this] {serverInteractor.StartServer(); };
		clientInteractorII.onStartServer = [this] {serverInteractorII.StartServer(); };

		clientInteractor.onPrepareLobby = [this](const GameStats& gs) { ui.PrepareLobby(gs); };
		clientInteractor.onUpdateLobby = [this](const GameStats& gs) { ui.UpdateGameStats(gs); };
		clientInteractor.onReceivedID = [this](int i) { auto some = i; };

		clientInteractorII.onPrepareLobby = [this](const GameStats& gs) { ui.PrepareLobby(gs); };
		clientInteractorII.onUpdateLobby = [this](const GameStats& gs) { ui.UpdateGameStats(gs); };
		clientInteractorII.onReceivedID = [this](int i) { auto some = i; };
	}
protected:
	virtual void SetUp()
	{
		Test::SetUp();
	}
	virtual void TearDown()
	{
		Test::TearDown();
	}

	FakeUI ui{};
	Game game{};
	RandomGenerator RandomLetterGenerator{};
	Client client{};
	Server server{};
	Client clientII{};
	Server serverII{};
	GameStatsOperations gameStatsOperations{};
	SLFParser parser;
	GameStatsSerializer serializer{};
	MessageHandler msgHandler{};
	ClientInteractorImpl clientInteractor;
	ServerInteractorImpl serverInteractor;
	ClientInteractorImpl clientInteractorII;
	ServerInteractorImpl serverInteractorII;
};

TEST_F(Testy, DeepDebuggedBugs)
{
	clientInteractor.HostLobby("Vision");
	clientInteractorII.JoinLobby("192.168.0.80", "Wanda Maximov");
	EXPECT_TRUE(false);
}