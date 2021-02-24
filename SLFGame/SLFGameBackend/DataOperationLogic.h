#pragma once
#include "DataTypes.h"

class DataOperationLogic
{
public:
	virtual void InkrementRound(GameStats&) = 0;
	virtual void AddPreviousLetter(GameStats&) = 0;
	virtual void SetNewLetter(Letter, GameStats&) = 0;
	virtual bool LetterIsAlreadyUsed(Letter, Letters) = 0;
	virtual void AddPoints(const int, PlayerStats&) = 0;
	virtual void SetAnswers(const std::vector<std::string>&, PlayerStats&) = 0;
	virtual std::pair<GameStats, PlayerStats> CreateStats(const std::string&) = 0;
	virtual ~DataOperationLogic() = default;
};