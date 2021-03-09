#pragma once
#include "MessageHandlerLogic.h"

class MessageHandler : public MessageHandlerLogic {
public:
	void handleMessage(const Message&) override;
	void on(const HandleGameStats&) override;
	void on(const AddNewPlayer&) override;
	void on(const Playername&) override;
};