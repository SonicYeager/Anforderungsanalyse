#pragma once
#include "GameLogic.h"

class Game : public GameLogic
{
public:
	int		CalculatePoints		(GameStats&)	override;
	void	CheckGameFinished	(GameStats&)					override;
};