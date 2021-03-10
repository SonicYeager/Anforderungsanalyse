#include "interactor.h"

Interactor::Interactor(Client* c) :
	m_client(c)
{
	//conect ress and log to each other or interactor events
	m_client->onData = [this](const ByteStream& data) { OnData(data); };
	m_client->onLog = [this](const std::string& log) { OnLog(log); };
}

Interactor::~Interactor()
{
	onLog = [](const std::string& text) { auto temp = text; temp.clear(); };
}

void Interactor::StartServer()
{
	onStartServer();
	JoinServer();
}

void Interactor::JoinServer()
{
	auto addr = m_client->GenerateLobbyCode();
	m_client->ConnectToServer(addr);
}

void Interactor::SendData()
{
	std::string text{"Hello World from Client: " + m_id};
	ByteStream stream{std::begin(text), std::end(text)};
	m_client->WriteToHost(stream);
}

void Interactor::OnData(const ByteStream& stream)
{
	std::string text{stream.begin(), stream.end()};
	onLog("Interactor: Received Data ->" + text);
	m_id = text;
}

void Interactor::OnLog(const std::string& log)
{
	if(onLog)
		onLog("Client: " + log);
}
