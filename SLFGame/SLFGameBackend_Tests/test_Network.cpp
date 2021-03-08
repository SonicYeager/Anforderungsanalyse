#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/GameInteractor.h"
#include "../SLFGameBackend/RandomGenerator.h"
#include "../SLFGameBackend/GameStatsOperations.h"
#include "../SLFGameBackend/Network.h"
#include "../SLFGameBackend/SLFParser.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/UI.h"
#include "../SLFGameBackend/Client.h"
#include "../SLFGameBackend/Host.h"
#include "../SLFGameBackend/GameStatsSerializer.h"
#include "../SLFGameBackend/NetworkHandler.h"

#include <future>

using namespace ::testing;

class FakeUI : public UI
{
public:
	MOCK_METHOD(void, PrepareLobby,			(const GameStats&), (override));
	MOCK_METHOD(void, PrepareGame,			(const GameStats&), (override));
	MOCK_METHOD(void, PrepareOverview,		(const GameStats&), (override));
	MOCK_METHOD(void, PrepareFinalScores,	(const GameStats&), (override));
	MOCK_METHOD(void, UpdateGameStats,		(const GameStats&), (override));
};

class TestGameInteractor : public Test
{
public:
	TestGameInteractor() :
		gameInteractorHost{ &RandomLetterGenerator, &gameStatsOperations, &game, &parser, &clientLogic, &hostLogic, &serializer, &netHandler },
		gameInteractorClient{ &RandomLetterGenerator, &gameStatsOperations, &game, &parser, &clientLogic, &hostLogic, &serializer, &netHandler }
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
	RandomGenerator RandomLetterGenerator{};
	Network HostNet{};
	Network ClietnNet{};
	GameStatsOperations gameStatsOperations{};
	GameStats gameStats{};
	PlayerStats playerStats{};
	SLFParser parser;
	Client clientLogic{ &ClietnNet };
	Host hostLogic{ &HostNet };
	GameStatsSerializer serializer{};
	NetworkHandler netHandler{};
	GameInteractor gameInteractorHost;
	GameInteractor gameInteractorClient;
};

TEST_F(TestGameInteractor, Enjoy)
{
	FakeUI fui{};
	gameInteractorHost.onPrepareLobby = [&fui](const GameStats& stats) {fui.PrepareGame(stats); };
	gameInteractorClient.onPrepareLobby = [&fui](const GameStats& stats) {fui.PrepareGame(stats); };
	gameInteractorHost.HostLobby("Sahrah Connor");
	gameInteractorClient.JoinLobby("192.168.0.80", "T-3000");
}