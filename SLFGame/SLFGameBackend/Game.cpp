#pragma once
#include "Game.h"
#include "DataTypes.h"
#include "Messages.h"

using namespace Messages;

int Game::CalculatePoints(GameStats& decisions)
{
	int result = 0;

	//for (unsigned int i = 0; i < decisions.size(); i++)
	//{
	//	if (decisions[i] == DECISION::SOLO)
	//		result += 20;
	//	else if (decisions[i] == DECISION::UNIQUE)
	//		result += 10;
	//	else if (decisions[i] == DECISION::MULTIPLE)
	//		result += 5;
	//}

	return result;
}

void Game::CheckGameFinished(GameStats& gs)
{
	if (gs.currentRound > gs.maxRounds)
		onGameOver();
	else
		onPrepareNextRound();
}

void Game::CheckAllAnswersRecived(int counter, int actualCount, Event<> onTrue)
{
	if (counter == actualCount)
	{
		onTrue();
	}
}

void Game::HandleGameState(const STATE& state, Event<> onSetupRound, Event<GameState> onStandart)
{
	switch (state)
	{
	case STATE::SETUPROUND:
		onSetupRound();
		break;
	default:
		onStandart(GameState{ state });
		break;
	}
}
