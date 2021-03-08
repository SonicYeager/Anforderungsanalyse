#pragma once
#include "GameInteractor.h"
#include "../FileHandler/FileHandler/FileHandler.h"

GameInteractor::GameInteractor(RandomGenRessource* gen,
	DataOperationLogic* op,
	GameLogic* game,
	SLFParser* p,
	ClientLogic* cl,
	HostLogic* hl,
	SerializerSource* s,
	NetworkHandlerLogic* n)
	:
	m_pRandomGenerator(gen),
	m_pDataOperation(op),
	m_pGame(game),
	m_pParser(p),
	m_pClient(cl),
	m_pHost(hl),
	m_pSerializer(s),
	m_pNetHandler(n)
{
	m_pGame->onGameOver = [this]() { onGameOver(m_GameStats); };
	m_pGame->onPrepareNextRound = [this]() 
	{
		Letter generated = m_pRandomGenerator->GenerateUnusedLetter(m_GameStats.lettersUsed);
		m_pDataOperation->SetNewLetter(generated, m_GameStats);
		m_pDataOperation->AddPreviousLetter(m_GameStats);
		onPrepareNextRound(m_GameStats);
	};
	m_pNetHandler->onAddNewPlayer = [this](const AddNewPlayer& nPlayer) { m_newPlayer = nPlayer; };
	m_pNetHandler->onHandleGameStats = [this](const HandleGameStats& handlegs) { m_handleGS = handlegs; };
	m_pHost->onNewConnection = [this]() {OnNewClientConnected(); };
	m_pHost->onDataReceived = [this](const ByteStream& stream) {OnDataReceived(stream); };
	m_pClient->onDataReceived = [this](const ByteStream& stream) {OnDataReceived(stream); };
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
	auto gameStats = m_pDataOperation->CreateStats(lobbyCode, "");
	m_GameStats = gameStats;
	m_GameStats.players.push_back(m_GameStats.players[0]);
	return { m_GameStats, m_GameStats.players[0] };
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

void GameInteractor::HostLobby(const std::string& playerName)
{
	// Serverstart und LobbyCode-Generierung
	auto lobbycode = m_pHost->StartServer();

	//Erstellung der GameStats
	m_GameStats = m_pDataOperation->CreateStats(lobbycode, playerName);

	// Verbindungsaufbau zum Server
	m_pClient->ConnectToServer(lobbycode);

	//Erhalten der GameStats
	auto data = m_pClient->ReceiveData();
	m_pClient->WriteToHost(data);

	// Signal an GUI zum Übergang in Lobby
	onPrepareLobby(m_GameStats);
}

void GameInteractor::JoinLobby(const LobbyCode& lobbyCode, const std::string& playerName)
{
	//Verbindungsaufbau zum Server
	m_pClient->ConnectToServer(lobbyCode);

	//Erhalten der GameStats
	auto data = m_pClient->ReceiveData();
	auto msg = m_pSerializer->Deserialize(data);
	m_pNetHandler->handleMessage(msg);

	//Update der GameStats und hinzufügen der eigenen Daten
	UpdateGameStats(playerName);
	AddPlayerStatsToMessage(playerName);

	//Übermittlung der geupdateten GameStats an Host
	auto serializedGS = m_pSerializer->Serialize(m_handleGS);
	m_pClient->WriteToHost(serializedGS);

	//Signal an GUI zum Übergang in Lobby
	onPrepareLobby(m_GameStats);
}

void GameInteractor::OnNewClientConnected()
{
	//Erstellung von GameStatsMassage
	HandleGameStats gameStatsMsg = CreateGameStatsMessage();
	gameStatsMsg.gs.potentialId = m_GameStats.players.size();

	//Serialisierung und Senden der Daten an neuen Spieler
	auto serializedMsg = m_pSerializer->Serialize(gameStatsMsg);
	m_pHost->WriteTo(serializedMsg, m_GameStats.players.size());

	//Erhalten der geupdateten Spielerdaten
	auto data = m_pHost->ReceiveData(m_GameStats.players.size());
	auto msg = m_pSerializer->Deserialize(data);
	m_pNetHandler->handleMessage(msg);

	//Host -> Hinzufügen des neuen Spielers
	m_GameStats.players.push_back({m_handleGS.gs.playerNames[m_GameStats.players.size()], (int)m_GameStats.players.size(), m_handleGS.gs.points[m_GameStats.players.size()], m_handleGS.gs.answers[m_GameStats.players.size()] });
	
	//Broadcasten der geupdaten Spielerdaten
	HandleGameStats updatedGameStatsMsg = CreateGameStatsMessage();
	auto serb = m_pSerializer->Serialize(updatedGameStatsMsg);
	m_pHost->Broadcast(serb);
}

void GameInteractor::OnDataReceived(const ByteStream& stream)
{
   //TODO
}

void GameInteractor::UpdateGameStats(const std::string& playerName)
{
	m_GameStats.categories = m_handleGS.gs.categories;
	m_GameStats.maxRounds = m_handleGS.gs.maxRounds;
	m_GameStats.timeout = m_handleGS.gs.timeout;
	for (int i{}; i < m_handleGS.gs.playerNames.size(); ++i)
		m_GameStats.players.push_back({ m_handleGS.gs.playerNames[i], i, 0, {} });
	m_GameStats.players.push_back({ playerName, m_handleGS.gs.potentialId, 0, {} });
}

void GameInteractor::AddPlayerStatsToMessage(const std::string& playerName)
{
	m_handleGS.gs.playerNames.push_back(playerName);
	m_handleGS.gs.answers.emplace_back();
	m_handleGS.gs.points.emplace_back();
	m_handleGS.gs.decisions.emplace_back();
}

HandleGameStats GameInteractor::CreateGameStatsMessage()
{
	HandleGameStats result{};
	result.gs.categories = m_GameStats.categories;
	result.gs.maxRounds = m_GameStats.maxRounds;
	result.gs.timeout = m_GameStats.timeout;
	for (int i{}; i < m_GameStats.players.size(); ++i)
	{
		result.gs.playerNames.push_back(m_GameStats.players[i].playerName);
		result.gs.points.push_back(m_GameStats.players[i].points);
		result.gs.answers.push_back(m_GameStats.players[i].answers);
	}
	return result;
}
