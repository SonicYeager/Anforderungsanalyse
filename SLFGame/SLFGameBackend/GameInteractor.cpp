#include "GameInteractor.h"
#include "../FileHandler/FileHandler/FileHandler.h"

GameInteractor::GameInteractor(RandomGenRessource* gen, DataOperationLogic* op, GameLogic* game, NetworkSource* n, SLFParser* p, ClientLogic* cl, HostLogic* hl) :
	m_pRandomGenerator(gen),
	m_pDataOperation(op),
	m_pGame(game),
	m_pNetwork(n),
	m_pParser(p),
	m_pClient(cl),
	m_pHost(hl)

{
	m_pGame->onGameOver = [this]() { onGameOver(m_GameStats); };
	m_pGame->onPrepareNextRound = [this]() 
	{
		Letter generated = m_pRandomGenerator->GenerateUnusedLetter(m_GameStats.lettersUsed);
		m_pDataOperation->SetNewLetter(generated, m_GameStats);
		m_pDataOperation->AddPreviousLetter(m_GameStats);
		onPrepareNextRound(m_GameStats);
	};
}

void GameInteractor::PrepareGame(const std::string& cats, const std::string& roundTime, const std::string& roundCount)
{
	auto parsedCats = m_pParser->ParseCategories(cats);
	auto parsedRound = m_pParser->ParseRoundCount(roundCount);
	m_GameStats.categories = parsedCats;
	m_GameStats.timeout = roundTime;
	m_GameStats.currentRound = 0;
	m_GameStats.maxRounds = parsedRound;
	m_pDataOperation->InkrementRound(m_GameStats);
	Letter generated = m_pRandomGenerator->GenerateLetter();
	m_pDataOperation->SetNewLetter(generated, m_GameStats);
	onPrepareGame(m_GameStats);
}

std::pair<GameStats, PlayerStats> GameInteractor::PrepareLobby(const std::string& lobbyCode)
{
	//auto code = m_pNetwork->GenerateLobbyCode();
	auto [gameStats, playerStats] = m_pDataOperation->CreateStats(lobbyCode);
	m_GameStats = gameStats;
	m_GameStats.players.push_back(playerStats);
	return {gameStats, playerStats};
}

void GameInteractor::PrepareOverview(const std::vector<std::string>& answ)
{
	m_pDataOperation->SetAnswers(answ, m_GameStats.players[0]);
	onPrepareOverview(m_GameStats);
}

void GameInteractor::EndRound(const std::vector<DECISION>& decisions)
{
	auto points = m_pGame->CalculatePoints(decisions);
	m_pDataOperation->AddPoints(points, m_GameStats.players[0]);
	m_pDataOperation->InkrementRound(m_GameStats);
	m_pGame->CheckGameFinished(m_GameStats);
}

void GameInteractor::HostLobby(const std::string&)
{
	//TODO
}

void GameInteractor::JoinLobby(const LobbyCode&, const std::string&)
{
	//TODO
}
