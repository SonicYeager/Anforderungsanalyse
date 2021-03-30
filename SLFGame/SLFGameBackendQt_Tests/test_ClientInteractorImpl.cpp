#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SLFGameBackend/ClientInteractorImpl.h"
#include "../SLFGameBackend/RandomGenRessource.h"
#include "../SLFGameBackend/ClientSource.h"
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

inline bool operator==(const Index& left, const Index& right)
{
	return left.answerIDX == right.answerIDX &&
		left.categoryIDX == right.categoryIDX &&
		left.voterIDX == right.voterIDX;
}


class FakeUI : public UI
{
public:
	MOCK_METHOD(void, ReceiveID,			(int),											(override));
	MOCK_METHOD(void, UpdateLobby,			(const LobbySettings&),							(override));
	MOCK_METHOD(void, SetLobbyCode,			(const LobbyCode&),								(override));
	MOCK_METHOD(void, UpdateGameState,		(const STATE&),									(override));
	MOCK_METHOD(void, ChatMessageReceived,	(const ChatMessage&),							(override));
	MOCK_METHOD(void, ReveiveAllAnswers,	(const std::vector<std::vector<std::string>>&),	(override));
	MOCK_METHOD(void, ReceiveRoundData,		(const RoundData&),								(override));
	MOCK_METHOD(void, ReceiveVoteChange,	(const Index&),									(override));
	MOCK_METHOD(void, ReceiveFinalScores,	(const Scores&),								(override));
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
	MOCK_METHOD(std::string,	GenerateLobbyCode,		(),					(override));
	MOCK_METHOD(void,			ConnectToServer,		(const LobbyCode&),	(override));
	MOCK_METHOD(void,			WriteToHost,			(const ByteStream&),(override));
	MOCK_METHOD(void,			DisconnectFromServer,	(),					(override));
};

class TestClientInteractor : public Test
{
public:
	TestClientInteractor() :
		clientInteractor{&fakeServer, &serializer, &msgHandler}
	{
		clientInteractor.onAllAnswers = [this](const std::vector<std::vector<std::string>>& ans) {fui.ReveiveAllAnswers(ans); };
		clientInteractor.onChatMessage = [this](const ChatMessage& ans) {fui.ChatMessageReceived(ans); };
		clientInteractor.onGameState = [this](const STATE& ans) {fui.UpdateGameState(ans); };
		clientInteractor.onReceivedID = [this](const int& ans) {fui.ReceiveID(ans); };
		clientInteractor.onUpdateLobbySettings = [this](const LobbySettings& ans) {fui.UpdateLobby(ans); };
		clientInteractor.onVoteChange = [this](const Index& ans) {fui.ReceiveVoteChange(ans); };
		clientInteractor.onFinalScores = [this](const Scores& scores) {fui.ReceiveFinalScores(scores); };
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

	::testing::NiceMock<FakeClient> fakeServer{};
	GameStatsSerializer serializer{};
	MessageHandler msgHandler{};
	ClientInteractorImpl clientInteractor;
	::NiceMock<FakeUI> fui;
};

TEST_F(TestClientInteractor, HostLobby_StartServer_CallStartServer)
{
	FakeUI fui{};
	bool started = false;
	clientInteractor.onSetLobbyCode = [&fui](const std::string& id) {fui.SetLobbyCode(id); };
	clientInteractor.onStartServer = [&started]() { started = true; };

	clientInteractor.HostLobby("T-3000");

	EXPECT_TRUE(started);
}

TEST_F(TestClientInteractor, JoinLobby_ConnectToServer_CallConnectToServer)
{
	EXPECT_CALL(fakeServer, ConnectToServer("CODE"));
	FakeUI fui{};
	clientInteractor.onSetLobbyCode = [&fui](const std::string& id) {fui.SetLobbyCode(id); };
	clientInteractor.JoinLobby("CODE", "T-3000");
}

//TEST_F(TestClientInteractor, JoinLobby_WriteToHost_CallConnectToServer)
//{
//	EXPECT_CALL(fakeServer, WriteToHost(ByteStream{ '\0', '\0', '\0', '\x1', '\0', '\0', '\0', '\f', '\0', 'T', '\0', '-','\0', '3','\0', '0','\0', '0','\0', '0'}));
//	FakeUI fui{};
//	clientInteractor.onSetLobbyCode = [&fui](const std::string& id) {fui.SetLobbyCode(id); };
//
//	clientInteractor.JoinLobby("CODE", "T-3000");
//}

TEST_F(TestClientInteractor, OnMsgID_ID_CallReceiveID)
{
	EXPECT_CALL(fui, ReceiveID(10));

	PlayerID re{};
	re.id = 10;
	msgHandler.onPlayerID(re);
}

TEST_F(TestClientInteractor, OnMsgHandleGameSettings_HandleGameSettings_CallUpdateLobbyAndUpdateGameState)
{
	LobbySettings ls;
	ls.categories = { "Baum,Auto,NCC" };
	ls.rounds = "10";
	ls.timeout = "10";
	ls.playerNames = { {0, "DU"} };
	EXPECT_CALL(fui, UpdateLobby(ls));

	HandleGameSettings re{};
	re.ls.categories = {"Baum,Auto,NCC"};
	re.ls.rounds = "10";
	re.ls.timeout = "10";
	re.ls.playerNames = { {0, "DU"} };
	msgHandler.onHandleGameSettings(re);
}

//TEST_F(TestClientInteractor, OnMsgGameState_GameState_CallUpdateGameState)
//{
//	EXPECT_CALL(fui, UpdateGameState(STATE::INTERVENTION));	
//	clientInteractor.m_customCategoryString = "Junge,Why" ;
//
//	GameState re{};
//	re.state = STATE::INTERVENTION;
//	msgHandler.onGameState(re);
//}

TEST_F(TestClientInteractor, OnAllAnswers_AllAnswers_CallReceiveAllAnswersAndUpdateGameState)
{
	AllAnswers answ{};
	answ.ans = { {"Wolverine", "Magneto"} };
	EXPECT_CALL(fui, ReveiveAllAnswers(answ.ans));
	EXPECT_CALL(fui, UpdateGameState(STATE::OVERVIEW));

	AllAnswers ans;
	ans.ans = { {"Wolverine", "Magneto"} };
	msgHandler.onAllAnswers(ans);
}

TEST_F(TestClientInteractor, LobbyChanged_ChangedCategories_CallWriteToHost)
{
	HandleGameSettings gs{ {"NewCat", "NewTimeout", "NewRound"} };
	auto ser = serializer.Serialize(gs);
	EXPECT_CALL(fakeServer, WriteToHost(ser));

	clientInteractor.LobbyChanged("NewCat", "NewTimeout", "NewRound");
}

TEST_F(TestClientInteractor, ChatMessageReceived_ChatMessage_CallWriteToHost)
{
	ChatMessage cm{ "Mel", "1034 Cars long" };
	auto ser = serializer.Serialize(cm);
	EXPECT_CALL(fakeServer, WriteToHost(ser));

	clientInteractor.ChatMessageReceived("Mel", "1034 Cars long");
}

TEST_F(TestClientInteractor, StateChangeTriggered_ChatMessage_CallWriteToHost)
{
	GameState cm = {STATE::LOBBY};
	auto ser = serializer.Serialize(cm);
	EXPECT_CALL(fakeServer, WriteToHost(ser));

	clientInteractor.StateChangeTriggered(STATE::LOBBY);
}

TEST_F(TestClientInteractor, AnswersReceived_Answers_CallWriteToHost)
{
	PlayerAnswers cm{};
	cm.answers.push_back("Yeah");
	cm.answers.push_back("Boi");
	auto ser = serializer.Serialize(cm);
	EXPECT_CALL(fakeServer, WriteToHost(ser));

	clientInteractor.AnswersReceived({ "Yeah", "Boi" });
}

TEST_F(TestClientInteractor, OnChatMessage_ChatMessage_CallOnChatMessage)
{
	clientInteractor.onChatMessage = [this](const ChatMessage& msg) {fui.ChatMessageReceived(msg); };
	ChatMessage msg{"Sender", "Text"};
	EXPECT_CALL(fui, ChatMessageReceived(_));

	clientInteractor.OnChatMessage({ "Sender", "Text" });
}

TEST_F(TestClientInteractor, OnRoundSetup_RoundSetup_CallUpdateGameStateAndOnRoundSetup)
{
	clientInteractor.onRoundData = [this](const RoundData& msg) {fui.ReceiveRoundData(msg); };
	clientInteractor.onGameState = [this](const STATE& msg) {fui.UpdateGameState(msg); };

	RoundData data{ {"some", "cats"}, "C", "bis Stop", 0, 5, 20 };
	EXPECT_CALL(fui, ReceiveRoundData(data));
	EXPECT_CALL(fui, UpdateGameState(STATE::INGAME));

	clientInteractor.OnRoundSetup({ { {"some", "cats"}, "C", "bis Stop", 0, 5, 20 } });
}

TEST_F(TestClientInteractor, ChangeVoteStateTriggered_VoteChanged_CallWriteToHost)
{
	AnswerIndex cm{ {1,1,1} };
	auto ser = serializer.Serialize(cm);
	EXPECT_CALL(fakeServer, WriteToHost(ser));

	clientInteractor.ChangeVoteStateTriggered(1,1,1);
}

TEST_F(TestClientInteractor, OnAnswerIndex_AnswerIndex_CallonVoteChange)
{
	Index data{ 1,1,1 };
	EXPECT_CALL(fui, ReceiveVoteChange(data));

	clientInteractor.OnAnswerIndex(AnswerIndex{ data });
}

TEST_F(TestClientInteractor, OnAnswerIndex_FinalScores_CallonFinalScores)
{
	Scores data{ {0,10} };
	EXPECT_CALL(fui, ReceiveFinalScores(data));

	clientInteractor.OnFinalScores(FinalScores{ data });
}