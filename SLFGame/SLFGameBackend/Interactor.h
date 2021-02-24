#pragma once
#include "DataTypes.h"

class Interactor
{
public:
	virtual void PrepareGame(const std::string&, const std::string&, const std::string&) = 0;
	virtual std::pair<GameStats, PlayerStats> PrepareLobby(const std::string&) = 0;
	virtual void PrepareOverview(const std::vector<std::string>&) = 0;
	virtual void EndRound(const std::vector<int>& decisions) = 0;
	virtual ~Interactor() = default;

	Event<GameStats, PlayerStats> onPrepareGame;
	Event<GameStats, PlayerStats> onPrepareOverview;
	Event<GameStats, PlayerStats> onPrepareNextRound;
	Event<GameStats, PlayerStats> onGameOver;
};