#pragma once
#include "framework.h"
#include "Interactor.h"
#include "DataOperationLogic.h"
#include "DataTypes.h"
#include "RandomGenRessource.h"
#include "NetworkSource.h"

class GameInteractor : public Interactor
{
public:
	explicit GameInteractor(RandomGenRessource*, DataOperationLogic*, NetworkSource*);
	std::pair<GameStats, PlayerStats> PrepareNextRound(const GameStats&, const PlayerStats&) override;
	std::pair<GameStats, PlayerStats> PrepareLobby(const std::string& lobbyCode = "") override;

private:
	RandomGenRessource* mp_rand;
	DataOperationLogic* mp_op;
	NetworkSource* mp_n;
};

