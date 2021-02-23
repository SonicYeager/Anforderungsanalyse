#pragma once
#include "framework.h"
#include "DataOperationLogic.h"

class GameStatsOperations : public DataOperationLogic
{
public:
	void InkrementRound(GameStats&) override;
	void AddPreviousLetter(GameStats&) override;
	void SetNewLetter(Letter, GameStats&) override;
	bool LetterIsAlreadyUsed(Letter, Letters) override;
	void SetAnswers(const std::vector<std::string>&, PlayerStats&) override;
	std::pair<GameStats, PlayerStats> CreateStats(const std::string&) override;
};

