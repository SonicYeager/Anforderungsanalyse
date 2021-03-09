#pragma once
#include "backend_global.h"
#include "datatypes.h"
#include "Server.h"

class ServerInteractor
{
public:
	ServerInteractor(Server*);

	void StartServer();

	Event<const std::string> onLog;

private:
	void OnNewConnection(int);
	void OnData(const ByteStream&, int);
	void OnLog(const std::string&);

	Server* m_server{};
};
