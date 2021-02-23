#pragma once
#include "DataTypes.h"

class UI
{
public:
	virtual void Init(const GameStats&, const PlayerStats&) = 0;
	virtual void PrepareNextRound(const GameStats&, const PlayerStats&) = 0;
	virtual ~UI() = default;

	Event<const std::string&, const std::string&, const std::string&> onPrepareGame;
	Event<const Categories&> onPrepareOverview;
};