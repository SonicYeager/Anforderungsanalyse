#pragma once
#include "backend_global.h"
#include "datatypes.h"
#include "Network.h"

class Interactor
{
public:
    Interactor(Network* );

	void StartHost();
	void JoinHost();

	Event<const std::string> onLog;

private:
	Network* net{};
};
