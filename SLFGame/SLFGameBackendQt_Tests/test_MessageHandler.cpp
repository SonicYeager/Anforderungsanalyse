#pragma once
#include "gmock/gmock.h"
#include "../SLFGameBackend/MessageHandler.h"

using namespace Messages;

class FakeClass
{
public:
	/*int HandleGameStatsCalled(const HandleGameStats& hgs) {	return 1; }*/
	int PlayernameCalled(const Playername& hgs) { return 2; }
	int PlayerIDCalled(const PlayerID& hgs) { return 3; }
	int PlayerAnswersCalled(const PlayerAnswers& hgs) { return 4; }
	int HandleGameSettingsCalled(const HandleGameSettings& hgs) { return 5; }
	int GameStateCalled(const GameState& hgs) { return 6; }
	int ChatMessageCalled(const ChatMessage& hgs) { return 7; }
	int AllAnswersCalled(const AllAnswers& hgs) { return 8; }
	int RoundSetupCalled(const RoundSetup& hgs) { return 9; }
	int AnswerIndexCalled(const AnswerIndex& hgs) { return 10; }
	int FinalScoresCalled(const FinalScores& fs) { return 11; }
};

//TEST(MessageHandlerTest, RightEventCalled_onHandleGameStats)
//{
//	MessageHandler msgHandler;
//	FakeClass fc{};
//	Message hgs = HandleGameStats();
//	int result = 0;
//
//	msgHandler.onHandleGameStats = [&fc, &result](const HandleGameStats& msg) {result = fc.HandleGameStatsCalled(msg); };
//	msgHandler.handleMessage(hgs);
//
//	EXPECT_EQ(1, result);
//}

TEST(MessageHandlerTest, handleMessage_onPlayername)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = Playername();
	int result = 0;

	msgHandler.onPlayername = [&fc, &result](const Playername& msg) {result = fc.PlayernameCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(2, result);
}


TEST(MessageHandlerTest, handleMessage_onPlayerID)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = PlayerID();
	int result = 0;

	msgHandler.onPlayerID = [&fc, &result](const PlayerID& msg) {result = fc.PlayerIDCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(3, result);
}

TEST(MessageHandlerTest, handleMessage_onPlayerAnswers)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = PlayerAnswers();
	int result = 0;

	msgHandler.onPlayerAnswers = [&fc, &result](const PlayerAnswers& msg) {result = fc.PlayerAnswersCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(4, result);
}

TEST(MessageHandlerTest, handleMessage_onHandleGameSettings)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = HandleGameSettings();
	int result = 0;

	msgHandler.onHandleGameSettings = [&fc, &result](const HandleGameSettings& msg) {result = fc.HandleGameSettingsCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(5, result);
}

TEST(MessageHandlerTest, handleMessage_onGameState)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = GameState();
	int result = 0;

	msgHandler.onGameState = [&fc, &result](const GameState& msg) {result = fc.GameStateCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(6, result);
}

TEST(MessageHandlerTest, handleMessage_onChatMessage)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = ChatMessage();
	int result = 0;

	msgHandler.onChatMessage = [&fc, &result](const ChatMessage& msg) {result = fc.ChatMessageCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(7, result);
}

TEST(MessageHandlerTest, handleMessage_onAllAnswers)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = AllAnswers();
	int result = 0;

	msgHandler.onAllAnswers = [&fc, &result](const AllAnswers& msg) {result = fc.AllAnswersCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(8, result);
}

TEST(MessageHandlerTest, handleMessage_onRoundSetup)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = RoundSetup();
	int result = 0;

	msgHandler.onRoundSetup = [&fc, &result](const RoundSetup& msg) {result = fc.RoundSetupCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(9, result);
}

TEST(MessageHandlerTest, handleMessage_onAnswerIndex)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = AnswerIndex();
	int result = 0;

	msgHandler.onAnswerIndex = [&fc, &result](const AnswerIndex& msg) {result = fc.AnswerIndexCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(10, result);
}

TEST(MessageHandlerTest, RightEventCalled_onFinalScores)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = FinalScores();
	int result = 0;

	msgHandler.onFinalScores = [&fc, &result](const FinalScores& msg) {result = fc.FinalScoresCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(11, result);
}