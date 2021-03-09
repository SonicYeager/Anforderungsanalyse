#pragma once
#include "backend_global.h"
#include "datatypes.h"
#include "Client.h"
#include "ServerInteractor.h" //replace by another interactor

class Interactor
{
public:
    Interactor(Client*, ServerInteractor*);

	void StartHost();
	void JoinHost();

	Event<const std::string> onLog;

private:
	void OnData(const ByteStream&);
	void OnLog(const std::string&);

	Client* m_client{};
	ServerInteractor* m_server{};
};
