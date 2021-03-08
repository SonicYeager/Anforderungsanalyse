#pragma once
#include "DataTypes.h"

class HostLogic
{
public:
	virtual LobbyCode StartServer() = 0;
	virtual void WriteTo(const ByteStream&, int) = 0;
	virtual void Broadcast(const ByteStream&) = 0;
	virtual ByteStream ReceiveData(int) = 0;
	virtual void WaitForConnection() = 0;

	Event<>	onNewConnection;
	Event<ByteStream> onDataReceived;
};