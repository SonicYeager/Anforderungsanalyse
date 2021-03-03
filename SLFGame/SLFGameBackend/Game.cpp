#include "Game.h"

int Game::CalculatePoints(const std::vector<DECISION>& decisions)
{
	int result = 0;

	for (unsigned int i = 0; i < decisions.size(); i++)
	{
		if (decisions[i] == 1)
			result += 20;
		else if (decisions[i] == 2)
			result += 10;
		else if (decisions[i] == 3)
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
