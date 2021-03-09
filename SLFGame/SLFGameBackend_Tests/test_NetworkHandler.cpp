#pragma once
#include "gmock/gmock.h"
#include "../SLFGameBackend/NetworkHandler.h"

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

TEST(NetworkHandlerTest, RightEventCalled_onHandleGameStats)
{
	NetworkHandler netHandler;
	FakeClass fc{};
	Message hgs = HandleGameStats();
	int result = 0;

	netHandler.onHandleGameStats = [&fc, &result](const HandleGameStats& msg) {result = fc.HandleGameStatsCalled(msg); };
	netHandler.handleMessage(hgs);

	EXPECT_EQ(1, result);
}

TEST(NetworkHandlerTest, RightEventCalled_onAddNewPlayer)
{
	NetworkHandler netHandler;
	FakeClass fc{};
	Message hgs = AddNewPlayer();
	int result = 0;

	netHandler.onAddNewPlayer = [&fc, &result](const AddNewPlayer& msg) {result = fc.AddNewPlayerCalled(msg); };
	netHandler.handleMessage(hgs);

	EXPECT_EQ(2, result);
}

TEST(NetworkHandlerTest, RightEventCalled_onPlayername)
{
	NetworkHandler netHandler;
	FakeClass fc{};
	Message hgs = Playername();
	int result = 0;

	netHandler.onPlayername = [&fc, &result](const Playername& msg) {result = fc.PlayernameCalled(msg); };
	netHandler.handleMessage(hgs);

	EXPECT_EQ(3, result);
}