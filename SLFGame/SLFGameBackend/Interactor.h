#pragma once
#include "DataTypes.h"

class Interactor
{
public:
	virtual std::pair<GameStats, PlayerStats> PrepareNextRound(const GameStats&, const PlayerStats&) = 0;
	virtual std::pair<GameStats, PlayerStats> PrepareLobby(const std::string&) = 0;
	virtual ~Interactor() = default;
};