#pragma once
#include "Messages.h"

using namespace Messages;

class NetworkHandlerLogic {
public:
	virtual void handleMessage(const Message&) = 0;
	virtual void on(const HandleGameStats&) = 0;
	virtual void on(const AddNewPlayer&) = 0;

	Event<HandleGameStats> onHandleGameStats;
	Event<AddNewPlayer> onAddNewPlayer;
};