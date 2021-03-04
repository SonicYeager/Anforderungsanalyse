#include "Host.h"

LobbyCode HostLogic::StartServer()
{
    return LobbyCode();
}

void HostLogic::WriteTo(const ByteStream&, int)
{
}

void HostLogic::Broadcast(const ByteStream&)
{
}

ByteStream HostLogic::ReceiveData(int)
{
	return ByteStream();
}

ByteStream HostLogic::ReceiveData()
{
	return ByteStream();
}

void HostLogic::WriteToHost(const ByteStream&)
{
}

void HostLogic::ConnectToServer(const LobbyCode&)
{
}
