#pragma once
#include "DataTypes.h"

class ServerInteractor
{
public:
	virtual ~ServerInteractor() = default;

	virtual void StartServer() = 0;

	//Event<const std::string> onLog;
};