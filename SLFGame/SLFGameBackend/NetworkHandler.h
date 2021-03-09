#pragma once
#include "NetworkHandlerLogic.h"

class NetworkHandler : public NetworkHandlerLogic {
public:
	void handleMessage(const Message&) override;
	void on(const HandleGameStats&) override;
	void on(const AddNewPlayer&) override;
	void on(const Playername&) override;
};