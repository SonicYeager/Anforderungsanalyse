#pragma once
#include "DataTypes.h"

class Interactor
{
public:
	virtual void PrepareGame(const std::string&, const std::string&, const std::string&) = 0;
	virtual std::pair<GameStats, PlayerStats> PrepareLobby(const std::string&) = 0;	//???
	virtual void PrepareOverview(const std::vector<std::string>&) = 0;
	virtual void EndRound(const std::vector<DECISION>& decisions) = 0;
	virtual void HostLobby(const std::string&) = 0;
	virtual void JoinLobby(const LobbyCode&, const std::string&) = 0;
	virtual ~Interactor() = default;

	Event<GameStats> onPrepareGame;
	Event<GameStats> onPrepareOverview;
	Event<GameStats> onPrepareNextRound;
	Event<GameStats> onPrepareLobby;
	Event<GameStats> onUpdateLobby;
	Event<GameStats> onGameOver;
};