#pragma once
#include "framework.h"
#include "Interactor.h"
#include "DataOperationLogic.h"
#include "DataTypes.h"
#include "RandomGenRessource.h"
#include "NetworkSource.h"
#include "../SLFGameBackendQt/Parser.h"

class GameInteractor : public Interactor
{
public:
	explicit GameInteractor(RandomGenRessource*, DataOperationLogic*, NetworkSource*, Parser*);
	std::pair<GameStats, PlayerStats> PrepareGame(const std::string& cats, const std::string& roundTime, const std::string& roundCount) override;
	std::pair<GameStats, PlayerStats> PrepareLobby(const std::string& lobbyCode = "") override;

private:
	RandomGenRessource* mp_rand;
	DataOperationLogic* mp_op;
	NetworkSource* mp_n;
	Parser* mp_p;
};

