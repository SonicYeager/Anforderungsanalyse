#include "GameStatsOperations.h"
#include <algorithm>

void GameStatsOperations::InkrementRound(GameStats& gameStats)
{
	gameStats.SetCurrentRound(gameStats.GetCurrentRound()+1);
}

void GameStatsOperations::AddPreviousLetter(GameStats& gameStats)
{
	auto curr = gameStats.GetCurrentLetter();
	if(curr != '\0')
	{
		auto usedLetters = gameStats.GetUsedLetters();
		usedLetters.push_back(curr);
		gameStats.SetUsedLetters(usedLetters);
	}
}

void GameStatsOperations::SetNewLetter(Letter letter, GameStats& gameStats)
{
	gameStats.SetCurrentLetter(letter);
}

void GameStatsOperations::AddPoints(const int points, PlayerStats& ps)
{
	ps.SetPoints(ps.GetPoints() + points);
}

bool GameStatsOperations::LetterIsAlreadyUsed(Letter generated, Letters used)
{
	return std::find(std::begin(used), std::end(used), generated) != std::end(used);
}

void GameStatsOperations::SetAnswers(const std::vector<std::string>& answ, PlayerStats& ps)
{
	ps.SetAnswers(answ);
}

std::pair<GameStats, PlayerStats> GameStatsOperations::CreateStats(const std::string& code)
{
	GameStats gs{};
	PlayerStats ps{};
	gs.SetMaxRounds(5);
	gs.SetCategories({ {{"Stadt"},{"Land"}, {"Fluss"}, {"Name"}, {"Tier"}, {"Beruf"}} });
	gs.SetLobbyCode(code);
    return std::make_pair(gs, ps);
}
