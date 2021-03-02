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
	virtual void		Broadcast(const NetworkData&)		= 0;
	virtual void		Write(const NetworkData&, int)		= 0;
	virtual void		WriteToHost(const NetworkData&)		= 0;

	Event<int> onNewConnection;
	Event<const NetworkData&> onReadyRead;
};