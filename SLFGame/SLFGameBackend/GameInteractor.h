#pragma once
#include "framework.h"
#include "Interactor.h"
#include "DataOperationLogic.h"
#include "DataTypes.h"
#include "RandomGenRessource.h"
#include "NetworkSource.h"
#include "SLFParser.h"
#include "GameLogic.h"

class GameInteractor : public Interactor
{
public:
	explicit GameInteractor(RandomGenRessource*, DataOperationLogic*, GameLogic*, NetworkSource*, SLFParser*);
	void PrepareGame(const std::string& cats, const std::string& roundTime, const std::string& roundCount) override;
	std::pair<GameStats, PlayerStats> PrepareLobby(const std::string& lobbyCode = "") override;
	void PrepareOverview(const std::vector<std::string>&) override;
	void EndRound(const std::vector<int>&) override;

	GameStats m_GameStats;
	PlayerStats m_PlayerStats;

private:
	RandomGenRessource* m_pRandomGenerator;
	DataOperationLogic* m_pDataOperation;
	GameLogic* m_pGame;
	NetworkSource* m_pNetwork;
	SLFParser* m_pParser;

};

