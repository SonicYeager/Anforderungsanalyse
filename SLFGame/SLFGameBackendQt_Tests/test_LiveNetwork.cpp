#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/ServerInteractorImpl.h"
#include "../SLFGameBackend/ClientInteractorImpl.h"
#include "../SLFGameBackend/GameInteractorImpl.h"
#include "../SLFGameBackend/Server.h"
#include "../SLFGameBackend/Client.h"
#include "../SLFGameBackend/UI.h"
#include "../SLFGameBackend/GameStatsSerializer.h"
#include "../SLFGameBackend/MessageHandler.h"
#include "../SLFGameBackend/SLFParser.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/RandomGenerator.h"
#include "../SLFGameBackend/GameStatsOperations.h"

#include <chrono>

using namespace ::testing;
using namespace std::chrono_literals;

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

class FakeRandomGenerator : public RandomGenerator
{
	Letter GenerateUnusedLetter(const Letters&) override
	{
		return 'A';
	};
};
class Testy : public Test
{
public:
	Testy() :
		serverInteractor{ &server, &serializers, &msgHandlers},
		clientInteractor{ &client, &serializerc, &msgHandlerc },
		gameInteractor{ &games, &randgen, &gsops, &clientInteractor, &serverInteractor }
	{
		gameInteractor.onAllAnswers = [this](const std::vector<std::vector<std::string>>& ans) {fui.ReveiveAllAnswers(ans); };
		gameInteractor.onChatMessage = [this](const ChatMessage& ans) {fui.ChatMessageReceived(ans); };
		gameInteractor.onGameState = [this](const STATE& ans) {fui.UpdateGameState(ans); };
		gameInteractor.onReceivedID = [this](const int& ans) {fui.ReceiveID(ans); };
		gameInteractor.onUpdateLobbySettings = [this](const LobbySettings& ans) {fui.UpdateLobby(ans); };
		gameInteractor.onSetLobbyCode = [this](const LobbyCode& ans) {fui.SetLobbyCode(ans); };
		gameInteractor.onRoundData = [this](const RoundData& ans) {fui.ReceiveRoundData(ans); };

		clientInteractor.onStartServer = [this]() { serverInteractor.StartServer(); };
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

	Server server{};
	GameStatsSerializer serializers{};
	MessageHandler msgHandlers{};


	Client client{};
	GameStatsSerializer serializerc{};
	MessageHandler msgHandlerc{};
	SLFParser parserc{};

	SLFParser parsers{};
	Game games{};
	GameStatsOperations gsops{};
	FakeRandomGenerator randgen{};

	ClientInteractorImpl clientInteractor;
	ServerInteractorImpl serverInteractor;
	GameInteractorImpl gameInteractor;

	FakeUI fui{};
};

//clientCreator would be handy

TEST_F(Testy, JustEnjoy)
{
	EXPECT_CALL(fui, ReceiveID(0));	
	EXPECT_CALL(fui, SetLobbyCode(std::string("192.168.0.80")));

	gameInteractor.HostLobby("Jeager");
	gameInteractor.
	auto check = 0;
	std::this_thread::sleep_for(1000ms);
}