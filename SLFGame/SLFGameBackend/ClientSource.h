#pragma once
#include "DataTypes.h"

class ClientSource
{
public:
	virtual ~ClientSource() = default;

	virtual std::string GenerateLobbyCode() = 0;
	virtual void ConnectToServer(const LobbyCode&) = 0;
	virtual void DisconnectFromServer() = 0;
	virtual void WriteToHost(const ByteStream&) = 0;

	//Event<std::string> onLog;
	Event<ByteStream> onData;
};