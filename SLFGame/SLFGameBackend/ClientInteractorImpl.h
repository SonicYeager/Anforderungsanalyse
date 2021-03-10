#pragma once
#include "framework.h"
#include "ClientInteractor.h"
#include "DataOperationLogic.h"
#include "DataTypes.h"
#include "RandomGenRessource.h"
#include "SLFParser.h"
#include "GameLogic.h"
#include "ClientSource.h"
#include "SerializerSource.h"
#include "MessageHandlerLogic.h"

class ClientInteractorImpl : public ClientInteractor
{
public:
	explicit ClientInteractorImpl(RandomGenRessource*, DataOperationLogic*, GameLogic*, SLFParser*, ClientSource*, SerializerSource*, MessageHandlerLogic*);
	void PrepareGame(const std::string& cats, const std::string& roundTime, const std::string& roundCount) override;
	std::pair<GameStats, PlayerStats> PrepareLobby(const std::string& lobbyCode = "") override;
	void PrepareOverview(const std::vector<std::string>&) override;
	void EndRound(const std::vector<DECISION>&) override;
	void HostLobby(const std::string&) override;
	void JoinLobby(const LobbyCode&, const std::string&) override;

	int m_ID;
	GameStats m_GameStats;

private:
	//client events
	void OnDataReceived(const ByteStream&);

	//msg events
	void OnMsgID(const PlayerID&);
	void OnMsgGameStats(const HandleGameStats&);

	ClientSource* m_pClient;
	MessageHandlerLogic* m_pMsgHandler;
	SerializerSource* m_pSerializer;
	RandomGenRessource* m_pRandomGenerator;
	DataOperationLogic* m_pDataOperation;
	GameLogic* m_pGame;
	SLFParser* m_pParser;
};

