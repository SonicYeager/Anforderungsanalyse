#pragma once
#include "gmock/gmock.h"
#include "../SLFGameBackend/MessageHandler.h"

class FakeClass
{
public:
	/*int HandleGameStatsCalled(const HandleGameStats& hgs) {	return 1; }*/
	int PlayernameCalled(const Playername& hgs) { return 2; }
	int PlayerIDCalled(const PlayerID& hgs) { return 3; }
	int PlayerAnswersCalled(const PlayerAnswers& hgs) { return 4; }
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

TEST(MessageHandlerTest, RightEventCalled_onPlayername)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = Playername();
	int result = 0;

	msgHandler.onPlayername = [&fc, &result](const Playername& msg) {result = fc.PlayernameCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(2, result);
}

//TEST(MessageHandlerTest, RightEventCalled_onPlayername)
//{
//	MessageHandler msgHandler;
//	FakeClass fc{};
//	Message hgs = Playername();
//	int result = 0;
//
//	msgHandler.onPlayername = [&fc, &result](const Playername& msg) {result = fc.PlayernameCalled(msg); };
//	msgHandler.handleMessage(hgs);
//
//	EXPECT_EQ(2, result);
//}

TEST(MessageHandlerTest, RightEventCalled_onPlayerID)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = PlayerID();
	int result = 0;

	msgHandler.onPlayerID = [&fc, &result](const PlayerID& msg) {result = fc.PlayerIDCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(3, result);
}

TEST(MessageHandlerTest, RightEventCalled_onPlayerAnswers)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = PlayerAnswers();
	int result = 0;

	msgHandler.onPlayerAnswers = [&fc, &result](const PlayerAnswers& msg) {result = fc.PlayerAnswersCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(4, result);
}