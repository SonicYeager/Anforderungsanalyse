#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/UI.h"
#include "../SLFGameBackend/GameStatsSerializer.h"
#include "../SLFGameBackend/MessageHandler.h"
#include "../SLFGameBackend/ClientInteractorImpl.h"
#include "../SLFGameBackend/ServerInteractorImpl.h"
#include "../SLFGameBackend/GameInteractorImpl.h"
#include "../SLFGameBackend/RandomGenerator.h"
#include "../SLFGameBackend/GameStatsOperations.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/SLFParser.h"

#include <QtCore/QCoreApplication>

using namespace ::testing;

inline bool operator==(const LobbySettings& left, const LobbySettings& right)
{
	return left.timeout == right.timeout &&
		left.categories == right.categories &&
		left.playerNames == right.playerNames &&
		left.rounds == right.rounds;
}

inline bool operator==(const RoundData& left, const RoundData& right)
{
	return left.categories == right.categories &&
		left.currentRound == right.currentRound &&
		left.letter == right.letter &&
		left.maxRounds == right.maxRounds &&
		left.points == right.points &&
		left.roundTime == right.roundTime;
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
	MOCK_METHOD(std::string, GenerateLobbyCode, (), (override));
	MOCK_METHOD(void, ConnectToServer, (const LobbyCode&), (override));
	MOCK_METHOD(void, WriteToHost, (const ByteStream&), (override));
	MOCK_METHOD(void, DisconnectFromServer, (), (override));
};

class FakeServer : public ServerSource
{
public:
	MOCK_METHOD(std::string, GenerateLobbyCode, (), (override));
	MOCK_METHOD(LobbyCode, StartServer, (), (override));
	MOCK_METHOD(void, WriteTo, (const ByteStream&, int), (override));
	MOCK_METHOD(void, Broadcast, (const ByteStream&), (override));
};

class TestGameInteractor : public Test
{
public:
	TestGameInteractor() :
		clientInteractor{ &fakeClient, &serializerc, &msgHandlerc },
		serverInteractor{ &fakeServer, &serializers, &msgHandlers },
		gameInteractor{ &game, &randgen, &gsops, &serverInteractor }
	{
		//a.exec();
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
	::StrictMock<FakeUI> fui;

	::testing::NiceMock<FakeClient> fakeClient{};
	GameStatsSerializer serializerc{};
	MessageHandler msgHandlerc{};
	ClientInteractorImpl clientInteractor;

	::testing::NiceMock<FakeServer> fakeServer{};
	GameStatsSerializer serializers{};
	MessageHandler msgHandlers{};
	ServerInteractorImpl serverInteractor;
	
	Game game{};
	RandomGenerator randgen{};
	GameStatsOperations gsops{};
	GameInteractorImpl gameInteractor;

	std::string strargv{"empty"};
	int argc = 0;
	char** argv{};
	QCoreApplication a{argc, argv};
};

TEST_F(TestGameInteractor, OnMsgPlayerName_PlayerName_CallBroadcastAndAdd)
{
	HandleGameSettings hgs{};
	hgs.ls.categories = "Stadt,Land,Fluss,Name,Tier,Beruf";
	hgs.ls.rounds = "5";
	hgs.ls.timeout = "bis Stop";
	hgs.ls.playerNames.emplace(0, "Elysium");
	auto expected = serializers.Serialize(hgs);
	EXPECT_CALL(fakeServer, Broadcast(expected));

	PlayerStats name{};
	name.playerName = "Elysium";
	name.answers = {};
	name.points = 0;
	gameInteractor.AddPlayer(0, name);
}
//
TEST_F(TestGameInteractor, OnMsgHandleGameSettings_HandleGameSettings_BroadcastToAll)
{
	HandleGameSettings br{};
	br.ls.categories = "Stadt,Land,Fluss,Name,Tier,Beruf";
	br.ls.rounds = "10";
	br.ls.timeout = "20";
	auto expected = serializers.Serialize(br);
	EXPECT_CALL(fakeServer, Broadcast(expected));

	gameInteractor.SetGameSettings(br.ls);
}

TEST_F(TestGameInteractor, OnPlayerAnswers_PlayerAnswer_BroadcastToAll)
{
	AllAnswers br{};
	br.ans = { {"Kaminar", "KVN", "Keplar"} };
	auto expected = serializers.Serialize(br);
	EXPECT_CALL(fakeServer, Broadcast(expected));

	gameInteractor.AddAnswers(0, { "Kaminar", "KVN", "Keplar" });
}

TEST_F(TestGameInteractor, OnGameState_GameStateANSWERREQUEST_BroadcastToAll)
{
	GameState msg;
	msg.state = STATE::ANSWERREQUEST;
	auto expected = serializers.Serialize(msg);
	EXPECT_CALL(fakeServer, Broadcast(expected));

	gameInteractor.ChangeGameState(STATE::ANSWERREQUEST);
}

TEST_F(TestGameInteractor, OnGameState_SetupRound_WriteToAll)
{
	PlayerStats playerPeter;
	playerPeter.points = 10;
	gameInteractor.m_GameStats.players.emplace(0, playerPeter);
	GameState msg;
	msg.state = STATE::SETUPROUND;
	RoundSetup roundSetup;
	roundSetup.data.maxRounds = 5;
	roundSetup.data.currentRound = 1;
	roundSetup.data.roundTime = "bis Stop";
	roundSetup.data.categories = { "Stadt", "Land", "Fluss", "Name", "Tier", "Beruf" };
	roundSetup.data.points = 10;
	roundSetup.data.letter = "A";
	auto expected = serializers.Serialize(roundSetup);
	EXPECT_CALL(fakeServer, WriteTo(/*expected, 0*/_,_));

	gameInteractor.ChangeGameState(STATE::SETUPROUND);
}
