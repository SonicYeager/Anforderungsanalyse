#pragma once
#include "GameStatsOperations.h"
#include <algorithm>

void GameStatsOperations::InkrementRound(GameStats& gameStats)
{
	gameStats.currentRound += 1;
}

void GameStatsOperations::AddPreviousLetter(GameStats& gameStats)
{
	auto curr = gameStats.currentLetter;
	if(curr != '\0')
	{
		auto usedLetters = gameStats.lettersUsed;
		usedLetters.push_back(curr);
		gameStats.lettersUsed = usedLetters;
	}
}

void GameStatsOperations::SetNewLetter(Letter letter, GameStats& gameStats)
{
	gameStats.currentLetter = letter;
}

void GameStatsOperations::AddPoints(const int points, PlayerStats& ps)
{
	ps.points += points;
}

bool GameStatsOperations::LetterIsAlreadyUsed(Letter generated, Letters used)
{
	return std::find(std::begin(used), std::end(used), generated) != std::end(used);
}

void GameStatsOperations::SetAnswers(const std::vector<std::string>& answ, PlayerStats& ps)
{
	ps.answers = answ;
}

