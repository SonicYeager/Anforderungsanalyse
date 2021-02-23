#pragma once
#include "DataTypes.h"

class Interactor
{
public:
	virtual void PrepareGame(const std::string&, const std::string&, const std::string&) = 0;
	virtual std::pair<GameStats, PlayerStats> PrepareLobby(const std::string&) = 0;
	virtual void PrepareOverview(const std::vector<std::string>&) = 0;
	//virtual void PrepareNextRound(const std::vector<std::string>&) = 0; //<- maybe a enum? mapped
	virtual ~Interactor() = default;

	Event<GameStats, PlayerStats> onPrepareNextRound; //prepare game??
	Event<GameStats, PlayerStats> onPrepareOverview;
	//Event<GameStats, PlayerStats> onPrepareRound;
};