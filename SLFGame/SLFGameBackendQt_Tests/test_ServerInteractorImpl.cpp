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
	MOCK_METHOD(void, ReceiveID, (int), (override));
	MOCK_METHOD(void, UpdateLobby, (const LobbySettings&), (override));
	MOCK_METHOD(void, SetLobbyCode, (const LobbyCode&), (override));
	MOCK_METHOD(void, UpdateGameState, (const STATE&), (override));
	MOCK_METHOD(void, ChatMessageReceived, (const ChatMessage&), (override));
	MOCK_METHOD(void, ReceiveCategories, (const std::vector<std::string>&), (override));
	MOCK_METHOD(void, ReveiveAllAnswers, (const std::vector<std::vector<std::string>>&), (override));
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

TEST_F(TestServerInteractor, OnMsgPlayerName_PlayerName_BroadcastToAll)
{
	HandleGameSettings hgs{};
	hgs.ls.categories = "Stadt,Land,Fluss,Name,Tier,Beruf";
	hgs.ls.playerNames = { {0, "Elysium"} };
	hgs.ls.rounds = 5;
	hgs.ls.timeout = "bis Ende";
	auto expected = serializer.Serialize(hgs);
	EXPECT_CALL(fakeServer, Broadcast(expected));

	Playername name{"Elysium"};
	msgHandler.onPlayername(name);
}

TEST_F(TestServerInteractor, OnMsgHandleGameSettings_HandleGameSettings_BroadcastToAll)
{
	HandleGameSettings br{};
	br.ls.categories = "Stadt,Land,Fluss,Name,Tier,Beruf";
	br.ls.playerNames = { {0, "Elysium"} };
	br.ls.rounds = 5;
	br.ls.timeout = "bis Ende";
	auto expected = serializer.Serialize(br);
	EXPECT_CALL(fakeServer, Broadcast(expected));

	HandleGameSettings re{};
	re.ls.categories = "Stadt,Land,Fluss,Name,Tier,Beruf";
	re.ls.playerNames = { {0, "Elysium"} };
	re.ls.rounds = 5;
	re.ls.timeout = "bis Ende";
	msgHandler.onHandleGameSettings(re);
}

//void OnMsgHandleGameSettings(const HandleGameSettings&);
//void OnChatMessage(const ChatMessage&);
//void OnPlayerAnswers(const PlayerAnswers&);
//void OnGameState(const GameState&);