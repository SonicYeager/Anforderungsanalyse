#pragma once
#include "DataTypes.h"

class UI
{
public:
    virtual void PrepareGame(const GameStats&) = 0;
    virtual void PrepareOverview(const GameStats&) = 0;
    virtual void PrepareFinalScores(const GameStats&) = 0;
    virtual void PrepareLobby (const GameStats&) = 0;
    virtual void PlayerJoined (const GameStats&, int) = 0;
	virtual ~UI() = default;

	Event<const std::string&, const std::string&, const std::string&> onPrepareGame;
    Event<const Categories&, int> onPrepareOverview;
    Event<const std::vector<DECISION>&, int> onPrepareNextRound;
    Event<> onHost;
    Event<const std::string&> onJoin;

};
