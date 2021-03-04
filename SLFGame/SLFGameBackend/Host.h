#include "DataTypes.h"
#include "Network.h"

class HostLogic : public Network
{
public:
	using Network::Network;

	LobbyCode StartServer() override;
	void WriteTo(const ByteStream&, int) override;
	void Broadcast(const ByteStream&) override;
	ByteStream ReceiveData(int) override;

private:
	ByteStream ReceiveData() override;
	void WriteToHost(const ByteStream&) override;
	void ConnectToServer(const LobbyCode&) override;

};