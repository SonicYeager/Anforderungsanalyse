#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/ServerInteractorImpl.h"
#include "../SLFGameBackend/ServerSource.h"
#include "../SLFGameBackend/UI.h"
#include "../SLFGameBackend/GameStatsSerializer.h"
#include "../SLFGameBackend/MessageHandler.h"

using namespace ::testing;

inline bool operator==(const LobbySettings& left, const LobbySettings& right)
{
	return left.timeout == right.timeout &&
		left.categories == right.categories &&
		left.playerNames == right.playerNames &&
		left.rounds == right.rounds;
}

inline bool operator==(const ChatMessage& left, const ChatMessage& right)
{
	return left.sender == right.sender &&
		left.text == right.text;
}

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
	hgs.ls.rounds = "5";
	hgs.ls.timeout = "bis Stop";
	hgs.ls.playerNames.emplace(0, "Elysium");
	auto expected = serializer.Serialize(hgs);
	EXPECT_CALL(fakeServer, Broadcast(expected));

	Playername name{"Elysium"};
	msgHandler.onPlayername(name);
}

TEST_F(TestServerInteractor, OnMsgHandleGameSettings_HandleGameSettings_BroadcastToAll)
{
	HandleGameSettings br{};
	br.ls.categories = "Stadt,Land,Fluss,Name,Tier,Beruf";
	br.ls.rounds = "10";
	br.ls.timeout = "20";
	auto expected = serializer.Serialize(br);
	EXPECT_CALL(fakeServer, Broadcast(expected));

	HandleGameSettings re{};
	re.ls.categories = "Stadt,Land,Fluss,Name,Tier,Beruf";
	re.ls.rounds = "10";
	re.ls.timeout = "20";
	msgHandler.onHandleGameSettings(re);
}

TEST_F(TestServerInteractor, OnChatMessage_ChatMsg_BroadcastToAll)
{
	ChatMessage br{};
	br.sender = "Mar-Vell";
	br.text = "True-Lies is a Hit!";
	auto expected = serializer.Serialize(br);
	EXPECT_CALL(fakeServer, Broadcast(expected));

	ChatMessage re{};
	re.sender = "Mar-Vell";
	re.text = "True-Lies is a Hit!";
	msgHandler.onChatMessage(re);
}

TEST_F(TestServerInteractor, OnPlayerAnswers_PlayerAnswer_BroadcastToAll)
{
	AllAnswers br{};
	br.ans = { {"Kaminar", "KVN", "Keplar"} };
	auto expected = serializer.Serialize(br);
	EXPECT_CALL(fakeServer, Broadcast(expected));

	PlayerAnswers re{};
	re.answers = {"Kaminar", "KVN", "Keplar"};
	msgHandler.onPlayerAnswers(re);
}

TEST_F(TestServerInteractor, OnGameState_GameState_BroadcastToAll)
{
	GameState br{};
	br.state = STATE::INTERVENTION;
	auto expected = serializer.Serialize(br);
	EXPECT_CALL(fakeServer, Broadcast(expected));

	GameState re{};
	re.state = STATE::INTERVENTION;
	msgHandler.onGameState(re);
}