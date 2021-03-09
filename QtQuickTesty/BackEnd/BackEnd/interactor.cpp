#include "interactor.h"

Interactor::Interactor(Client* c) :
	m_client(c)
{
	//conect ress and log to each other or interactor events
	m_client->onData = [this](const ByteStream& data) { OnData(data); };
	m_client->onLog = [this](const std::string& log) { OnLog(log); };
}

void Interactor::StartHost()
{
	onStartServer();
	JoinHost();
}

void Interactor::JoinHost()
{
	auto addr = m_client->GenerateLobbyCode();
	m_client->ConnectToServer(addr);
}

void Interactor::OnData(const ByteStream& stream)
{
	std::string text{stream.begin(), stream.end()};
	onLog("Interactor: Received Data ->" + text);
}

void Interactor::OnLog(const std::string& log)
{
	onLog("Network: " + log);
}
