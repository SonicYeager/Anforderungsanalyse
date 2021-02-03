#pragma once
#include "framework.h"
#include "DataOperationLogic.h"

class GameStatsOperations : public DataOperationLogic
{
public:
	void InkrementRound(GameStats&) override;
	void AddPreviousLetter(GameStats&) override;
	void SetNewLetter(Letter, GameStats&) override;
};

