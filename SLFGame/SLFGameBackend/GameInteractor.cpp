#include "GameInteractor.h"
#include "../FileHandler/FileHandler/FileHandler.h"

GameInteractor::GameInteractor(RandomGenRessource* gen, DataOperationLogic* op, NetworkSource* n, SLFParser* p) :
	m_pRandomGenerator(gen), 
	m_pDataOperation(op), 
	m_pNetwork(n),
	m_pParser(p)
{}

void GameInteractor::PrepareGame(const std::string& cats, const std::string& roundTime, const std::string& roundCount)
{
	auto parsedCats = m_pParser->ParseCategories(cats);
	auto parsedRound = m_pParser->ParseRoundCount(roundCount);
	m_GameStats.SetCategories(parsedCats);
	m_GameStats.SetTimeout(roundTime);
	m_GameStats.SetCurrentRound(0);
	m_GameStats.SetMaxRounds(parsedRound);
	m_pDataOperation->InkrementRound(m_GameStats);
	Letter generated = m_pRandomGenerator->GenerateUnusedLetter(m_GameStats.GetUsedLetters());
	auto fun = m_pRandomGenerator->GenerateLetter();
	m_pDataOperation->SetNewLetter(generated, m_GameStats);
	onPrepareNextRound(m_GameStats, m_PlayerStats);
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

//void GameInteractor::PrepareNextRound(const std::vector<std::string>& evals)
//{
//}
