#include "Client.h"

Client::Client(NetworkSource* source)
	: m_pNetwork(source)
{
	m_pNetwork->onReceivedData = [this](const ByteStream& stream) { onDataReceived(stream); };
}

ByteStream Client::ReceiveData()
{
	return m_pNetwork->ReceiveData();
}

void Client::WriteToHost(const ByteStream& data)
{
	m_pNetwork->WriteToHost(data);
}

void Client::ConnectToServer(const LobbyCode& ip)
{
	m_pNetwork->ConnectToServer(ip);
}