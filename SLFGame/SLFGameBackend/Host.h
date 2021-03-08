#pragma once
#include "DataTypes.h"
#include "NetworkSource.h"
#include "HostLogic.h"

class Host : public HostLogic
{
public:
	explicit Host(NetworkSource*);
	LobbyCode StartServer() override;
	void WriteTo(const ByteStream&, int) override;
	void Broadcast(const ByteStream&) override;
	ByteStream ReceiveData(int) override;
	void WaitForConnection() override;

private:
	NetworkSource* m_pNetwork{};
};