#include "ServerInteractor.h"

ServerInteractor::ServerInteractor(Server* s) :
	m_server(s)
{
	m_server->onLog = [this](const std::string& text) {OnLog(text); };
	m_server->onNewConnection = [this](int id) {OnNewConnection(id); };
	m_server->onClientData = [this](const ByteStream& stream, int id) { OnData(stream, id); };
}

void ServerInteractor::StartServer()
{
	m_server->StartServer();
}

void ServerInteractor::OnNewConnection(int id)
{
	onLog("ServerInteractor: New Connection Handled; ID: " + std::to_string(id));
	auto text = std::to_string(id);
	ByteStream stream{std::begin(text), std::end(text)};
	m_server->WriteTo(stream, id);
}

void ServerInteractor::OnData(const ByteStream& stream, int id)
{
	std::string text{std::begin(stream), std::end(stream)};
	onLog("ServerInteractor: received data: " + text + " from client: " + std::to_string(id));
}

void ServerInteractor::OnLog(const std::string& text)
{
	onLog("Server: " + text);
}
