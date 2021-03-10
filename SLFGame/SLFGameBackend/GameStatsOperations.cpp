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

GameStats GameStatsOperations::CreateStats(const LobbyCode& code, const std::string& playerName)
{
	GameStats gs{};
	gs.maxRounds = 5;
	gs.categories = { {{"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"}} };
	gs.lobbyCode = code;
	PlayerStats ps{};
	ps.playerName = playerName;
	ps.answers = Categories{};
	gs.players.push_back(ps);
	return gs;
}
