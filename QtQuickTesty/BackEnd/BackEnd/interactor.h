#pragma once
#include "backend_global.h"
#include "datatypes.h"
#include "Client.h"
#include "ServerInteractor.h" //replace by another interactor

class Interactor
{
public:
    Interactor(Client*);
	virtual ~Interactor();

	void StartServer();
	void JoinServer();
	void SendData();

	Event<const std::string> onLog;
	Event<> onStartServer;

private:
	void OnData(const ByteStream&);
	void OnLog(const std::string&);

	std::string m_id;
	Client* m_client{};
};
