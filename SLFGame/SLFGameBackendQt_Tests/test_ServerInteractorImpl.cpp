#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/ServerInteractorImpl.h"
#include "../SLFGameBackend/ServerSource.h"
#include "../SLFGameBackend/UI.h"
#include "../SLFGameBackend/GameStatsSerializer.h"
#include "../SLFGameBackend/MessageHandler.h"

using namespace ::testing;

class FakeUI : public UI
{
public:
	MOCK_METHOD(void, PrepareGame, (const GameStats&), (override));
	MOCK_METHOD(void, PrepareOverview, (const GameStats&), (override));
	MOCK_METHOD(void, PrepareFinalScores, (const GameStats&), (override));
	MOCK_METHOD(void, ReceiveID, (int), (override));
	MOCK_METHOD(void, UpdateLobby, (const LobbySettings&), (override));
	MOCK_METHOD(void, SetLobbyCode, (const LobbyCode&), (override));
	MOCK_METHOD(void, UpdateGameState, (const STATE&), (override));
};

class FakeServer : public ServerSource
{
public:
	MOCK_METHOD(std::string,GenerateLobbyCode,	(),							(override));
	MOCK_METHOD(LobbyCode,	StartServer,		(),							(override));
	MOCK_METHOD(void,		WriteTo,			(const ByteStream&, int),	(override));
	MOCK_METHOD(void,		Broadcast,			(const ByteStream&),		(override));
};

class TestServerInteractor : public Test
{
public:
	TestServerInteractor() :
		gameInteractor{ &fakeServer, &serializer, &msgHandler }
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

	::testing::NiceMock<FakeServer> fakeServer{};
	GameStats gameStats{};
	PlayerStats playerStats{};
	GameStatsSerializer serializer{};
	MessageHandler msgHandler{};
	ServerInteractorImpl gameInteractor;
};

TEST_F(TestServerInteractor, StartServer_StartServer_CallStartServer)
{
	EXPECT_CALL(fakeServer, StartServer());

	gameInteractor.StartServer();
}