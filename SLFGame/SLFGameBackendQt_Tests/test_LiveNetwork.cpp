#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/ServerInteractorImpl.h"
#include "../SLFGameBackend/ClientInteractorImpl.h"
#include "../SLFGameBackend/Server.h"
#include "../SLFGameBackend/Client.h"
#include "../SLFGameBackend/UI.h"
#include "../SLFGameBackend/GameStatsSerializer.h"
#include "../SLFGameBackend/MessageHandler.h"
#include "../SLFGameBackend/SLFParser.h"
#include "../SLFGameBackend/Game.h"
#include "../SLFGameBackend/RandomGenerator.h"
#include "../SLFGameBackend/GameStatsOperations.h"

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
		serverInteractor{ &server, &serializers, &msgHandlers, &randgen, &gsops, &games, &parsers },
		clientInteractor{ &randgen, &client, &serializerc, &msgHandlerc }
	{
		clientInteractor.onAllAnswers = [this](const std::vector<std::vector<std::string>>& ans) {fui.ReveiveAllAnswers(ans); };
		clientInteractor.onChatMessage = [this](const ChatMessage& ans) {fui.ChatMessageReceived(ans); };
		clientInteractor.onGameState = [this](const STATE& ans) {fui.UpdateGameState(ans); };
		clientInteractor.onReceivedID = [this](const int& ans) {fui.ReceiveID(ans); };
		clientInteractor.onUpdateLobbySettings = [this](const LobbySettings& ans) {fui.UpdateLobby(ans); };
		clientInteractor.onSetLobbyCode = [this](const LobbyCode& ans) {fui.SetLobbyCode(ans); };
		clientInteractor.onRoundData = [this](const RoundData& ans) {fui.ReceiveRoundData(ans); };

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
	SLFParser parsers{};
	Game games{};
	GameStatsOperations gsops{};


	Client client{};
	GameStatsSerializer serializerc{};
	MessageHandler msgHandlerc{};
	SLFParser parserc{};
	FakeRandomGenerator randgen{};


	ClientInteractorImpl clientInteractor;
	ServerInteractorImpl serverInteractor;

	FakeUI fui{};
};

//clientCreator would be handy

TEST_F(Testy, JustEnjoy)
{
	clientInteractor.HostLobby("Jeager");
	auto check = 0;
}