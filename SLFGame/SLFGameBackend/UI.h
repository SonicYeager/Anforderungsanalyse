#pragma once
#include "DataTypes.h"

class UI
{
public:
    virtual void ReceiveID(int) = 0;
	virtual void PrepareGame(const GameStats&) = 0;
	virtual void PrepareOverview(const GameStats&) = 0;
	virtual void PrepareFinalScores(const GameStats&) = 0;
	virtual void PrepareLobby(const GameStats&) = 0;
	virtual void UpdateGameStats(const GameStats&) = 0;
    virtual void UpdateLobby(const LobbySettings&) = 0;
	virtual ~UI() = default;

	Event<const std::string&, const std::string&, const std::string&> onPrepareGame;
	Event<const Categories&> onPrepareOverview;
	Event<const std::vector<DECISION>&> onPrepareNextRound;
	Event<const std::string&> onHostLobby;
	Event<const std::string&, const std::string&> onJoinLobby;
    Event<const std::string&, const std::string&, const std::string&> onLobbySettingsChanged;
};
