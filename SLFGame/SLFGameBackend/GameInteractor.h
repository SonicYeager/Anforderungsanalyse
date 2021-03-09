#pragma once
#include "framework.h"
#include "Interactor.h"
#include "DataOperationLogic.h"
#include "DataTypes.h"
#include "RandomGenRessource.h"
#include "NetworkSource.h"
#include "SLFParser.h"
#include "GameLogic.h"
#include "ClientLogic.h"
#include "HostLogic.h"
#include "SerializerSource.h"
#include "MessageHandlerLogic.h"

class GameInteractor : public Interactor
{
public:
	explicit GameInteractor(RandomGenRessource*, DataOperationLogic*, GameLogic*, SLFParser*, ClientLogic*, HostLogic*, SerializerSource*, MessageHandlerLogic*);
	void PrepareGame(const std::string& cats, const std::string& roundTime, const std::string& roundCount) override;
	std::pair<GameStats, PlayerStats> PrepareLobby(const std::string& lobbyCode = "") override;
	void PrepareOverview(const std::vector<std::string>&) override;
	void EndRound(const std::vector<DECISION>&) override;
	void HostLobby(const std::string&) override;
	void JoinLobby(const LobbyCode&, const std::string&) override;

	GameStats m_GameStats;
	AddNewPlayer m_newPlayer;
	HandleGameStats m_handleGS;

private:
	void OnNewClientConnected();
	void OnDataReceived(const ByteStream&);
	void UpdateGameStats(const std::string&);
	void AddPlayerStatsToMessage(const std::string&);
	HandleGameStats CreateGameStatsMessage();

	RandomGenRessource* m_pRandomGenerator;
	DataOperationLogic* m_pDataOperation;
	GameLogic* m_pGame;
	SLFParser* m_pParser;
	ClientLogic* m_pClient;
	HostLogic* m_pHost;
	SerializerSource* m_pSerializer;
	MessageHandlerLogic* m_pMsgHandler;
};

