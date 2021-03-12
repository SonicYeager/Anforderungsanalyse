#pragma once
#include "ServerSource.h"
#include "ServerInteractor.h"
#include "SerializerSource.h"
#include "MessageHandlerLogic.h"

class ServerInteractorImpl : public ServerInteractor
{
public:
	ServerInteractorImpl(ServerSource*, SerializerSource*, MessageHandlerLogic*);
	virtual ~ServerInteractorImpl();

	void StartServer() override;

private:
	//server events
	void OnNewConnection(int);
	void OnData(const ByteStream&, int);
	void OnLog(const std::string&);
	void OnDisconnect(int);

	//msg events
	void OnMsgPlayerName(const Playername&);
	void OnMsgHandleGameSettings(const HandleGameSettings&);
	void OnChatMessage(const ChatMessage&);

	//helper funcs
	HandleGameSettings CreateHandleGameSettings();

	ServerSource* m_pServer{};
	SerializerSource* m_pSerializer{};
	MessageHandlerLogic* m_pMsgHandler{};

	GameStats m_GameStats{};
};
