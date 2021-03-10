#pragma once
#include "ServerSource.h"
#include "ServerInteractor.h"
#include "SerializerSource.h"
#include "MessageHandlerLogic.h"

class ServerInteractorImpl
{
public:
	ServerInteractorImpl(ServerSource*, SerializerSource*, MessageHandlerLogic*);
	virtual ~ServerInteractorImpl();

	void StartServer();

private:
	//server events
	void OnNewConnection(int);
	void OnData(const ByteStream&, int);
	void OnLog(const std::string&);

	//msg events
	void OnMsgPlayerName(const Playername&);

	//helper funcs
	HandleGameStats CreateGameStatsMessage();

	ServerSource* m_pServer{};
	SerializerSource* m_pSerializer{};
	MessageHandlerLogic* m_pMsgHandler{};

	GameStats m_GameStats{};
};
