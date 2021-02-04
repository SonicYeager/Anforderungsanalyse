#pragma once
#include "framework.h"
#include "Interactor.h"
#include "DataOperationLogic.h"
#include "DataTypes.h"
#include "RandomGenRessource.h"

class GameInteractor : public Interactor
{
public:
	explicit GameInteractor(RandomGenRessource*, DataOperationLogic*);
	std::pair<GameStats, PlayerStats> PrepareNextRound(const GameStats&, const PlayerStats&) override;

private:
	RandomGenRessource* mp_rand;
	DataOperationLogic* mp_op;
};

