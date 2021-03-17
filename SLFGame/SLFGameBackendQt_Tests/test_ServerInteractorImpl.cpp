#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/ServerInteractorImpl.h"
#include "../SLFGameBackend/ServerSource.h"
#include "../SLFGameBackend/UI.h"
#include "../SLFGameBackend/GameStatsSerializer.h"
#include "../SLFGameBackend/MessageHandler.h"
#include "../SLFGameBackend/SLFParser.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/RandomGenerator.h"
#include "../SLFGameBackend/GameStatsOperations.h"
#include "../SLFGameBackend/GameInteractor.h"

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
	MOCK_METHOD(void, ReveiveAllAnswers, (const std::vector<std::vector<std::string>>&), (override));
	MOCK_METHOD(void, ReceiveRoundData, (const RoundData&), (override));
};

class FakeServer : public ServerSource
{
public:
	MOCK_METHOD(std::string,GenerateLobbyCode,	(),							(override));
	MOCK_METHOD(LobbyCode,	StartServer,		(),							(override));
	MOCK_METHOD(void,		WriteTo,			(const ByteStream&, int),	(override));
	MOCK_METHOD(void,		Broadcast,			(const ByteStream&),		(override));
};

class FakeRandomGenerator : public RandomGenerator
{
	Letter GenerateUnusedLetter(const Letters&) override
	{
		return 'A';
	};
};

class FakeGameInteractor : public GameInteractor
{
public:
	MOCK_METHOD(void, RemovePlayer,		(const int&),							(override));
	MOCK_METHOD(void, AddAnswers,		(int, const std::vector<std::string>&),	(override));
	MOCK_METHOD(void, AddPlayer,		(int, const PlayerStats&),				(override));
	MOCK_METHOD(void, SetGameSettings,	(const LobbySettings&),					(override));
	MOCK_METHOD(void, ChangeGameState,	(const STATE&),							(override));
	MOCK_METHOD(void, SetLobbyCode,		(const LobbyCode&),						(override));
};

class TestServerInteractor : public Test
{
public:
	TestServerInteractor() :
		gameInteractor{ &fakeServer, &serializer, &msgHandler }
	{
		gameInteractor.onAddAnswers			= [this](int id, const std::vector<std::string>& msg) {fakeGI.AddAnswers(id, msg); };
		gameInteractor.onRemovePlayer		= [this](int id) {fakeGI.RemovePlayer(id); };
		gameInteractor.onAddPlayer			= [this](int id, const PlayerStats& msg) {fakeGI.AddPlayer(id, msg); };
		gameInteractor.onSetGameSettings	= [this](const LobbySettings& msg) {fakeGI.SetGameSettings(msg); };
		gameInteractor.onChangeGameState	= [this](const STATE& msg) {fakeGI.ChangeGameState(msg); };
		gameInteractor.onSetLobbyCode		= [this](const LobbyCode& msg = "") {fakeGI.SetLobbyCode(msg); };
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

	::testing::StrictMock<FakeGameInteractor> fakeGI{};
	::testing::NiceMock<FakeServer> fakeServer{};
	GameStatsSerializer serializer{};
	MessageHandler msgHandler{};
	ServerInteractorImpl gameInteractor;
};

TEST_F(TestServerInteractor, StartServer_StartServer_CallStartServer)
{
	EXPECT_CALL(fakeServer, StartServer());
	EXPECT_CALL(fakeGI, SetLobbyCode(_));

	gameInteractor.StartServer();
}

//TEST_F(TestServerInteractor, Broadcast_WriteToOnAllSockets_CallWriteTo)
//{
//	EXPECT_CALL(fakeServer, StartServer());
//
//	gameInteractor.StartServer();
//}

//TEST_F(TestServerInteractor, WriteTo_WriteTo_CallWriteTo)
//{
//	EXPECT_CALL(fakeServer, StartServer());
//
//	gameInteractor.StartServer();
//}

TEST_F(TestServerInteractor, OnMsgPlayerName_PlayerName_BroadcastToAll)
{
	EXPECT_CALL(fakeGI, AddPlayer(_, _));

	Playername name{"Elysium"};
	msgHandler.onPlayername(name);
}

TEST_F(TestServerInteractor, OnMsgHandleGameSettings_HandleGameSettings_BroadcastToAll)
{
	EXPECT_CALL(fakeGI, SetGameSettings(_));

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
	EXPECT_CALL(fakeGI, AddAnswers(_, _));

	PlayerAnswers re{};
	re.answers = {"Kaminar", "KVN", "Keplar"};
	msgHandler.onPlayerAnswers(re);
}

TEST_F(TestServerInteractor, OnGameState_GameStateANSWERREQUEST_BroadcastToAll)
{
	GameState msg;
	msg.state = STATE::ANSWERREQUEST;
	EXPECT_CALL(fakeGI, ChangeGameState(_));

	msgHandler.onGameState(msg);
}

//TEST_F(TestServerInteractor, OnGameState_SetupRound_WriteToAll)
//{
//	PlayerStats playerPeter;
//	playerPeter.points = 10;
//	gameInteractor.m_GameStats.players.emplace(0, playerPeter);
//	GameState msg;
//	msg.state = STATE::SETUPROUND;
//	RoundSetup roundSetup;
//	roundSetup.data.maxRounds = 5;
//	roundSetup.data.currentRound = 1;
//	roundSetup.data.roundTime = "bis Stop";
//	roundSetup.data.categories = { "Stadt", "Land", "Fluss", "Name", "Tier", "Beruf" };
//	roundSetup.data.points = 10;
//	roundSetup.data.letter = "A";
//	auto expected = serializer.Serialize(roundSetup);
//	EXPECT_CALL(fakeServer, WriteTo(expected, 0));
//	msgHandler.onGameState(msg);
//}
