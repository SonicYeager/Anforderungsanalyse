#pragma once
#include "DataTypes.h"

class ServerSource
{
public:
	virtual ~ServerSource() = default;

	virtual std::string GenerateLobbyCode() = 0;
	virtual LobbyCode StartServer() = 0;
	virtual void WriteTo(const ByteStream&, int) = 0;
	virtual void Broadcast(const ByteStream&) = 0;

	//Event<std::string> onLog;
	Event<int> onNewConnection;
	Event<ByteStream, int> onClientData;
	Event<int> onClientDisconnect;
};