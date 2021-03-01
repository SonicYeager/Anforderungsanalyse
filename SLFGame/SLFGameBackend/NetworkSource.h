#pragma once
#include <string>
#include "DataTypes.h"

class NetworkSource 
{
public:
	virtual ~NetworkSource() = default;

	virtual std::string GenerateLobbyCode()					= 0;
	virtual void		StartServer()						= 0;
	virtual void		ConnectToServer(const std::string&) = 0;

	Event<const std::string&> onNewConnection;
	Event<const std::string&> onReadyRead;
};