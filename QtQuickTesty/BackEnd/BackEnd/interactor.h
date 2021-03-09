#pragma once
#include "backend_global.h"
#include "datatypes.h"
#include "network.h"

class Interactor
{
public:
    Interactor(Network* );

	void StartHost();
	void JoinHost();

	Event<const std::string> onNewConnection;
	Event<const std::string> onDataReceived;

private:
	Network* net{};
};
