#pragma once
#include "DataTypes.h"

class Interactor
{
public:
	virtual void PrepareGame(const std::string&, const std::string&, const std::string&) = 0;
	virtual std::pair<GameStats, PlayerStats> PrepareLobby(const std::string&) = 0;
	virtual std::pair<GameStats, PlayerStats> PrepareOverview(const std::vector<std::string>&) = 0;
	//virtual std::pair<GameStats, PlayerStats> PrepareNextRound(const std::vector<std::string>&) = 0;
	virtual ~Interactor() = default;

	Event<GameStats, PlayerStats> onPrepareNextRound;
};