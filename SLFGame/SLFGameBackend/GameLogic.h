#pragma once
#include <vector>
#include "DataTypes.h"

class GameLogic
{
public:
	virtual			~GameLogic() = default;

	virtual int		CalculatePoints		(GameStats&) = 0;
	virtual void	CheckGameFinished	(GameStats&) = 0;
	virtual void	CheckAllAnswersRecived(int counter, int actualCount, Event<> onTrue) = 0;
	virtual void	HandleGameState(const STATE& state, Event<>, Event<GameState>) = 0;

	Event<> onGameOver;
	Event<> onPrepareNextRound;
};