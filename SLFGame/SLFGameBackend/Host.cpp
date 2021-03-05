#include "Host.h"

Host::Host(NetworkSource* source)
	: m_pNetwork(source)
{}

LobbyCode Host::StartServer()
{
	return m_pNetwork->StartServer();
}

void Host::WriteTo(const ByteStream& data, int id)
{
	m_pNetwork->WriteTo(data, id);
}

void Host::Broadcast(const ByteStream& data)
{
	m_pNetwork->Broadcast(data);
}

ByteStream Host::ReceiveData(int id)
{
	return m_pNetwork->ReceiveData(id);
}
