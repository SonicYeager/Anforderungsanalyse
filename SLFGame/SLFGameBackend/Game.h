#pragma once
#include "GameLogic.h"

class Game : public GameLogic
{
public:
	int		CalculatePoints		(GameStats&)	override;
	void	CheckGameFinished	(GameStats&)					override;
	void CheckAllAnswersRecived(int counter, int actualCount, Event<> onTrue) override;
	void HandleGameState(const STATE& state, Event<>, Event<GameState>) override;
};