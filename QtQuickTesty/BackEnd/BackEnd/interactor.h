#pragma once
#include "backend_global.h"
#include "datatypes.h"
#include "Client.h"
#include "ServerInteractor.h" //replace by another interactor

class Interactor
{
public:
    Interactor(Client*);

	void StartHost();
	void JoinHost();

	Event<const std::string> onLog;
	Event<> onStartServer;

private:
	void OnData(const ByteStream&);
	void OnLog(const std::string&);

	Client* m_client{};
};
