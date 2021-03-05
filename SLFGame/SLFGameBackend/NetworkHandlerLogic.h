#pragma once
#include "DataTypes.h"
#include "Messages.h"
#include <variant>

class NetworkHandlerLogic {
public:
	virtual void handleMessage(Messages::Message msg, NetworkData data) = 0;
	virtual void on(Messages::HandleGameStats pl, NetworkData data) = 0;
	virtual void on(Messages::Alternative pl, NetworkData data) = 0;

	Event<Messages::HandleGameStats, NetworkData> onHandleGameStats;
	Event<Messages::Alternative, NetworkData> onAlternative;
};