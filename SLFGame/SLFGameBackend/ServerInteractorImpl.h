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
	void OnNewConnection(int);
	void OnData(const ByteStream&, int);
	void OnLog(const std::string&);
	void UpdateGameStats(const std::string&);
	void AddPlayerStatsToMessage(const std::string&);
	HandleGameStats CreateGameStatsMessage();

	ServerSource* m_pServer{};
	SerializerSource* m_pSerializer{};
	MessageHandlerLogic* m_pMsgHandler{};

	GameStats m_GameStats{};
};
