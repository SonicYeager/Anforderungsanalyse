#pragma once
#include "DataTypes.h"

class ClientLogic
{
public:
	virtual ByteStream ReceiveData() = 0;
	virtual void WriteToHost(const ByteStream&) = 0;
	virtual void ConnectToServer(const LobbyCode&) = 0;

	Event<ByteStream> onDataReceived;

	virtual ~ClientLogic() = default;
};