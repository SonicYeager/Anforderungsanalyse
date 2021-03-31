#pragma once
#include "ServerSource.h"
#include "ServerInteractor.h"
#include "SerializerSource.h"
#include "MessageHandlerLogic.h"
#include "RandomGenRessource.h"
#include "DataOperationLogic.h"
#include "SLFParser.h"
#include "GameLogic.h"

class ServerInteractorImpl : public ServerInteractor
{
public:
	ServerInteractorImpl(ServerSource*, SerializerSource*, MessageHandlerLogic*); 
	virtual ~ServerInteractorImpl();
		
	void StartServer() override;
	void StopListening() override;
	void Broadcast(const Message&) override;
	void WriteTo(int, const Message&) override;

	//msg events
	void OnMsgPlayerName(const Playername&);
	void OnMsgHandleGameSettings(const HandleGameSettings&);
	void OnChatMessage(const ChatMessage&);
	void OnPlayerAnswers(const PlayerAnswers&);
	void OnGameState(const GameState&);
	void OnAnswerIndex(const AnswerIndex&);

	//GameStats m_GameStats{};

private:
	//server events
	void OnNewConnection(int);
	void OnData(const ByteStream&, int);
	void OnLog(const std::string&);
	void OnDisconnect(int);

	ServerSource* m_pServer{};
	SerializerSource* m_pSerializer{};
	MessageHandlerLogic* m_pMsgHandler{};

	int m_dataGatherCounter{};
};
