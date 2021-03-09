#include "interactor.h"

Interactor::Interactor(Network* n) :
	net(n)
{
	//conect ress and log to each other or interactor events
	net->onData = [this](const ByteStream& data) { /*this->onDataReceived(data);*/ };
	net->onLog = [this](const std::string& data) { this->onLog(data); };
}

void Interactor::StartHost()
{
	auto addr = net->StartServer();
	net->ConnectToServer(addr);
	//after this the ui or the connection events should trigger anything else 
}

void Interactor::JoinHost()
{
	auto addr = net->GenerateLobbyCode();
	net->ConnectToServer(addr);
}
