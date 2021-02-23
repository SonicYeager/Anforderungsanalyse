#include "GameInteractor.h"
#include "../FileHandler/FileHandler/FileHandler.h"

GameInteractor::GameInteractor(RandomGenRessource* gen, DataOperationLogic* op, NetworkSource* n, SLFParser* p) :
	mp_rand(gen), 
	mp_op(op), 
	mp_n(n),
	mp_p(p)
{}

void GameInteractor::PrepareGame(const std::string& cats, const std::string& roundTime, const std::string& roundCount)
{
	auto parsedCats = mp_p->ParseCategories(cats);
	auto parsedRound = mp_p->ParseRoundCount(roundCount);
	m_GameStats.SetCategories(parsedCats);
	m_GameStats.SetTimeout(roundTime);
	m_GameStats.SetCurrentRound(0);
	m_GameStats.SetMaxRounds(parsedRound);
	mp_op->InkrementRound(m_GameStats);
	Letter generated;
	do 
	{
		generated = mp_rand->GenerateLetter();
	} while (mp_op->LetterIsAlreadyUsed(generated, m_GameStats.GetUsedLetters()));
	mp_op->SetNewLetter(generated, m_GameStats);
	onPrepareNextRound(m_GameStats, m_PlayerStats);
}

std::pair<GameStats, PlayerStats> GameInteractor::PrepareLobby(const std::string& lobbyCode)
{
	auto code = mp_n->GenerateLobbyCode();
	auto stats = mp_op->CreateStats(code);
	m_GameStats = stats.first;
	m_PlayerStats = stats.second;
	return stats;
}
