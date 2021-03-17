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
	ServerInteractorImpl(ServerSource*, SerializerSource*, MessageHandlerLogic*);  //<-- GameServerInteractor
	virtual ~ServerInteractorImpl();											
		
	void StartServer() override;
	void Broadcast(const LobbySettings&) override;
	void Broadcast(const AllAnswers&) override;
	void Broadcast(const GameState&) override;
	void WriteTo(int, const RoundSetup&) override;

	//msg events
	void OnMsgPlayerName(const Playername&);
	void OnMsgHandleGameSettings(const HandleGameSettings&);
	void OnChatMessage(const ChatMessage&);
	void OnPlayerAnswers(const PlayerAnswers&);
	void OnGameState(const GameState&);

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

	int m_actualID{};	//temp solution -> ask if there are any better;
	int m_dataGatherCounter{};
};
