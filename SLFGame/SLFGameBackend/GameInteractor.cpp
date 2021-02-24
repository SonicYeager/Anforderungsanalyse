#include "GameInteractor.h"
#include "../FileHandler/FileHandler/FileHandler.h"

GameInteractor::GameInteractor(RandomGenRessource* gen, DataOperationLogic* op, GameLogic* game, NetworkSource* n, SLFParser* p) :
	m_pRandomGenerator(gen),
	m_pDataOperation(op),
	m_pGame(game),
	m_pNetwork(n),
	m_pParser(p)

{
	m_pGame->onGameOver = [this]() { onGameOver(m_GameStats, m_PlayerStats); };
	m_pGame->onPrepareNextRound = [this]() 
	{
		Letter generated = m_pRandomGenerator->GenerateUnusedLetter(m_GameStats.GetUsedLetters());
		m_pDataOperation->SetNewLetter(generated, m_GameStats);
		onPrepareNextRound(m_GameStats, m_PlayerStats);
	};
}

void GameInteractor::PrepareGame(const std::string& cats, const std::string& roundTime, const std::string& roundCount)
{
	auto parsedCats = m_pParser->ParseCategories(cats);
	auto parsedRound = m_pParser->ParseRoundCount(roundCount);
	m_GameStats.SetCategories(parsedCats);
	m_GameStats.SetTimeout(roundTime);
	m_GameStats.SetCurrentRound(0);
	m_GameStats.SetMaxRounds(parsedRound);
	m_pDataOperation->InkrementRound(m_GameStats);
	Letter generated = m_pRandomGenerator->GenerateLetter();
	m_pDataOperation->SetNewLetter(generated, m_GameStats);
	onPrepareGame(m_GameStats, m_PlayerStats);
}

std::pair<GameStats, PlayerStats> GameInteractor::PrepareLobby(const std::string& lobbyCode)
{
	auto code = m_pNetwork->GenerateLobbyCode();
	auto [gameStats, playerStats] = m_pDataOperation->CreateStats(code);
	m_GameStats = gameStats;
	m_PlayerStats = playerStats;
	return {gameStats, playerStats};
}

void GameInteractor::PrepareOverview(const std::vector<std::string>& answ)
{
	m_pDataOperation->SetAnswers(answ, m_PlayerStats);
	onPrepareOverview(m_GameStats, m_PlayerStats);
}

void GameInteractor::EndRound(const std::vector<int>& decisions)
{
	auto points = m_pGame->CalculatePoints(decisions);
	m_pDataOperation->AddPoints(points, m_PlayerStats);
	m_pDataOperation->InkrementRound(m_GameStats);
	m_pGame->CheckGameFinished(m_GameStats);
}