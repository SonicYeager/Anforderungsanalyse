#pragma once
#include "framework.h"
#include "DataOperationLogic.h"

class GameStatsOperations : public DataOperationLogic
{
public:
	void InkrementRound(GameStats&) override;
	void AddPreviousLetter(GameStats&) override;
	void SetNewLetter(Letter, GameStats&) override;
	void AddPoints(const int, PlayerStats&) override;
	bool LetterIsAlreadyUsed(Letter, Letters) override;
	void SetAnswers(const std::vector<std::string>&, PlayerStats&) override;
	//GameStats CreateStats(const LobbyCode&, const std::string&) override;
	std::vector<std::pair<int, int>> SortPlayerByPoints(const std::map<int, PlayerStats>&) override;
};

