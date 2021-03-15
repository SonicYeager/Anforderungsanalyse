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
	ServerInteractorImpl(ServerSource*, SerializerSource*, MessageHandlerLogic*, RandomGenRessource*, DataOperationLogic*, GameLogic*, SLFParser*);
	virtual ~ServerInteractorImpl();											
		
		void StartServer() override;												

	//msg events
	void OnMsgPlayerName(const Playername&);
	void OnMsgHandleGameSettings(const HandleGameSettings&);
	void OnChatMessage(const ChatMessage&);
	void OnPlayerAnswers(const PlayerAnswers&);
	void OnGameState(const GameState&);

private:
	//server events
	void OnNewConnection(int);
	void OnData(const ByteStream&, int);
	void OnLog(const std::string&);
	void OnDisconnect(int);

	//helper funcs
	HandleGameSettings CreateHandleGameSettings();
	void HandleGameState(const GameState&);

	ServerSource* m_pServer{};
	SerializerSource* m_pSerializer{};
	MessageHandlerLogic* m_pMsgHandler{};
	RandomGenRessource* m_pRandomGenerator;
	DataOperationLogic* m_pDataOperation;
	GameLogic* m_pGame;
	SLFParser* m_pParser;

	GameStats m_GameStats{};
	int m_actualID{};	//temp solution -> ask if there are any better;
	int m_dataGatherCounter{};
};
