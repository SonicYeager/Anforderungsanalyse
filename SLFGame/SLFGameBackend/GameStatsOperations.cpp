#include "GameStatsOperations.h"
#include <algorithm>

void GameStatsOperations::InkrementRound(GameStats& gameStats)
{
	gameStats.SetCurrentRound(gameStats.GetCurrentRound()+1);
}

void GameStatsOperations::AddPreviousLetter(GameStats& gameStats)
{
	auto curr = gameStats.GetCurrentLetter().letter;
	if(curr != '\0')
	{
		auto usedLetters = gameStats.GetUsedLetters();
		usedLetters.letters.push_back(Letter{ curr });
		gameStats.SetUsedLetters(usedLetters);
	}
}

void GameStatsOperations::SetNewLetter(Letter letter, GameStats& gameStats)
{
	gameStats.SetCurrentLetter(letter);
}

bool GameStatsOperations::LetterIsAlreadyUsed(Letter generated, Letters used)
{
	return std::find(std::begin(used.letters), std::end(used.letters), generated) != std::end(used.letters);
}