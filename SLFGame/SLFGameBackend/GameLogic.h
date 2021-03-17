#pragma once
#include <vector>
#include "DataTypes.h"

class GameLogic
{
public:
	virtual			~GameLogic() = default;

	virtual int		CalculatePoints		(GameStats&)	= 0;
	virtual void	CheckGameFinished	(GameStats&)					= 0;

	Event<> onGameOver;
	Event<> onPrepareNextRound;
};