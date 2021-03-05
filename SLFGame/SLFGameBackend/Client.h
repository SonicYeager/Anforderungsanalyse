#pragma once
#include "DataTypes.h"
#include "NetworkSource.h"
#include "ClientLogic.h"

class Client : public ClientLogic
{
public:
	explicit Client(NetworkSource*);
	ByteStream ReceiveData() override;
	void WriteToHost(const ByteStream&) override;
	void ConnectToServer(const LobbyCode&) override;

private:
	NetworkSource* m_pNetwork{};
};