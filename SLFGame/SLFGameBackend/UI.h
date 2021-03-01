#pragma once
#include "DataTypes.h"

class UI
{
public:
    virtual void Init(const GameStats&, const int&) = 0;
    virtual void PrepareGame(const GameStats&, const int&) = 0;
    virtual void PrepareOverview(const GameStats&, const int&) = 0;
    virtual void PrepareFinalScores(const GameStats&, const int&) = 0;
    virtual void PrepareLobby (const GameStats&, const int&) = 0;
    virtual void PlayerJoined (const GameStats&) = 0;
	virtual ~UI() = default;

	Event<const std::string&, const std::string&, const std::string&> onPrepareGame;
	Event<const Categories&> onPrepareOverview;
    Event<const std::vector<DECISION>&> onPrepareNextRound;
    Event<> onHost;
    Event<const std::string&> onJoin;

};
