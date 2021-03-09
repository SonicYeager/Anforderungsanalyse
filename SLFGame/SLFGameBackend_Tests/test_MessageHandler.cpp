#pragma once
#include "gmock/gmock.h"
#include "../SLFGameBackend/MessageHandler.h"

class FakeClass
{
public:
	int HandleGameStatsCalled(const HandleGameStats& hgs)
	{
		return 1;
	}
	int AddNewPlayerCalled(const AddNewPlayer& hgs)
	{
		return 2;
	}
	int PlayernameCalled(const Playername& hgs)
	{
		return 3;
	}
};

TEST(MessageHandlerTest, RightEventCalled_onHandleGameStats)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = HandleGameStats();
	int result = 0;

	msgHandler.onHandleGameStats = [&fc, &result](const HandleGameStats& msg) {result = fc.HandleGameStatsCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(1, result);
}

TEST(MessageHandlerTest, RightEventCalled_onAddNewPlayer)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = AddNewPlayer();
	int result = 0;

	msgHandler.onAddNewPlayer = [&fc, &result](const AddNewPlayer& msg) {result = fc.AddNewPlayerCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(2, result);
}

TEST(MessageHandlerTest, RightEventCalled_onPlayername)
{
	MessageHandler msgHandler;
	FakeClass fc{};
	Message hgs = Playername();
	int result = 0;

	msgHandler.onPlayername = [&fc, &result](const Playername& msg) {result = fc.PlayernameCalled(msg); };
	msgHandler.handleMessage(hgs);

	EXPECT_EQ(3, result);
}