#pragma once
#include <string>
#include "DataTypes.h"

class NetworkSource 
{
public:
	virtual ~NetworkSource() = default;

	virtual std::string GenerateLobbyCode() = 0; //pls remove
	virtual LobbyCode StartServer() = 0;
	virtual void ConnectToServer(const LobbyCode&) = 0;
	virtual void WriteTo(const ByteStream&, int) = 0;
	virtual void WriteToHost(const ByteStream&) = 0;
	virtual void Broadcast(const ByteStream&) = 0;
	virtual ByteStream ReceiveData() = 0;
	virtual ByteStream ReceiveData(int) = 0;

	Event<> onNewConnection;
	Event<ByteStream> onReceivedData;

};