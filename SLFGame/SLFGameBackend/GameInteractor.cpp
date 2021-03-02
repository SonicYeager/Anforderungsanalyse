#include "GameInteractor.h"

GameInteractor::GameInteractor(RandomGenRessource* gen, DataOperationLogic* op, GameLogic* game, NetworkSource* n, SLFParser* p) :
	m_pRandomGenerator(gen),
	m_pDataOperation(op),
	m_pGame(game),
	m_pNetwork(n),
	m_pParser(p)

{
	//filling the map

	onRead = std::map<HEADER, Event<NetworkData>>
	{
		{HEADER::GET, [this](NetworkData data) { data.header = HEADER::SET; m_pNetwork->WriteToHost(data); }},
		{HEADER::SET, [this](NetworkData data) { /**/ }},
	};

	//**************

	m_pGame->onGameOver = [this]() { onGameOver(m_GameStats); };
	m_pGame->onPrepareNextRound = [this]() 
	{
		Letter generated = m_pRandomGenerator->GenerateUnusedLetter(m_GameStats.GetUsedLetters());
		m_pDataOperation->SetNewLetter(generated, m_GameStats);
		m_pDataOperation->AddPreviousLetter(m_GameStats);
		onPrepareNextRound(m_GameStats);
	};
	m_pNetwork->onNewConnection = [this](int playerName) 
	{ 
		PlayerStats ps{};
		auto id = m_GameStats.GetPlayerCount();
		ps.SetPlayerID(id);
		m_GameStats.AddPlayer(ps);
		onNewPlayerJoined(m_GameStats, id); 
	};
	m_pNetwork->onReadyRead = [this](NetworkData data)
	{
		auto& func = onRead[data.header];
		func(data);
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
	onPrepareGame(m_GameStats);
}

void GameInteractor::PrepareOverview(const std::vector<std::string>& answ, int playerID)
{
	m_pDataOperation->SetAnswers(answ, m_GameStats.GetPlayerStats(playerID));
	onPrepareOverview(m_GameStats);
}

void GameInteractor::EndRound(const std::vector<DECISION>& decisions, int playerID)
{
	auto points = m_pGame->CalculatePoints(decisions);
	m_pDataOperation->AddPoints(points, m_GameStats.GetPlayerStats(playerID));
	m_pDataOperation->InkrementRound(m_GameStats);
	m_pGame->CheckGameFinished(m_GameStats);
}

void GameInteractor::HostGame(const std::string& playerName)
{
	auto lobbyCode = m_pNetwork->GenerateLobbyCode();
	m_pNetwork->StartServer();
	m_pNetwork->ConnectToServer(lobbyCode);
	auto gameStats = m_pDataOperation->CreateStats(lobbyCode, playerName);
	m_GameStats = gameStats;
	onGameHosted(m_GameStats);
}

void GameInteractor::JoinGame(const std::string& playerName, const std::string& lobbyCode)
{
	auto gameStats = m_pDataOperation->CreateStats(lobbyCode, playerName);
	m_GameStats = gameStats;
	m_pNetwork->ConnectToServer(lobbyCode);
	onGameJoined(m_GameStats);
}
