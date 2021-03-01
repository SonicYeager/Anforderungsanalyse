#pragma once
#include "DataTypes.h"

class Interactor
{
public:
	virtual	~Interactor() = default;

	virtual void	PrepareGame		(const std::string&, const std::string&, const std::string&)	= 0;
	virtual void	PrepareOverview	(const std::vector<std::string>&, int)							= 0;
	virtual void	EndRound		(const std::vector<DECISION>& decisions, int)					= 0;
	virtual void	HostGame		(const std::string&)											= 0;
	virtual void	JoinGame		(const std::string&, const std::string&)						= 0;

	Event<GameStats> onPrepareGame;
	Event<GameStats> onPrepareOverview;
	Event<GameStats> onPrepareNextRound;
	Event<GameStats> onGameOver;
	Event<GameStats> onGameHosted;
	Event<GameStats> onGameJoined;
	Event<GameStats, int> onNewPlayerJoined;
};