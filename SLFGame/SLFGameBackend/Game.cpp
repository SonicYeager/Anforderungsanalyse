#pragma once
#include "Game.h"

int Game::CalculatePoints(const std::vector<DECISION>& decisions)
{
	int result = 0;

	for (unsigned int i = 0; i < decisions.size(); i++)
	{
		if (decisions[i] == DECISION::SOLO)
			result += 20;
		else if (decisions[i] == DECISION::UNIQUE)
			result += 10;
		else if (decisions[i] == DECISION::MULTIPLE)
			result += 5;
	}

	return result;
}

void Game::CheckGameFinished(GameStats& gs)
{
	if (gs.currentRound > gs.maxRounds)
		onGameOver();
	else
		onPrepareNextRound();
}
