#pragma once
#include "framework.h"
#include "Interactor.h"
#include "DataOperationLogic.h"
#include "DataTypes.h"
#include "RandomGenRessource.h"
#include "NetworkSource.h"
#include "SLFParser.h"

class GameInteractor : public Interactor
{
public:
	explicit GameInteractor(RandomGenRessource*, DataOperationLogic*, NetworkSource*, SLFParser*);
	void PrepareGame(const std::string& cats, const std::string& roundTime, const std::string& roundCount) override;
	std::pair<GameStats, PlayerStats> PrepareLobby(const std::string& lobbyCode = "") override;
	std::pair<GameStats, PlayerStats> PrepareOverview(const std::vector<std::string>&) override;

private:
	RandomGenRessource* mp_rand;
	DataOperationLogic* mp_op;
	NetworkSource* mp_n;
	SLFParser* mp_p;

	GameStats m_GameStats;
	PlayerStats m_PlayerStats;
};

