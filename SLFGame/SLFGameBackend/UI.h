#pragma once
#include "DataTypes.h"

class UI
{
public:
	virtual void Init(const GameStats&, const PlayerStats&) = 0;
	virtual ~UI() = default;

	Event<const GameStats&, const PlayerStats&> onPrepNextRound;
};