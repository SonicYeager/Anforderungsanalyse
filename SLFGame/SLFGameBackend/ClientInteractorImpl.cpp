#pragma once
#include "ClientInteractorImpl.h"

ClientInteractorImpl::ClientInteractorImpl(RandomGenRessource* gen,
	DataOperationLogic* op,
	GameLogic* game,
	SLFParser* p,
	ClientSource* cl,
	SerializerSource* s,
	MessageHandlerLogic* n)
	:
	m_pRandomGenerator(gen),
	m_pDataOperation(op),
	m_pGame(game),
	m_pParser(p),
	m_pClient(cl),
	m_pSerializer(s),
	m_pMsgHandler(n)
{
	m_pGame->onGameOver = [this]() { onGameOver(m_GameStats); };
	m_pGame->onPrepareNextRound = [this]() 
	{
		Letter generated = m_pRandomGenerator->GenerateUnusedLetter(m_GameStats.lettersUsed);
		m_pDataOperation->SetNewLetter(generated, m_GameStats);
		m_pDataOperation->AddPreviousLetter(m_GameStats);
		onPrepareNextRound(m_GameStats);
	};
	m_pClient->onData = [this](const ByteStream& stream) {OnDataReceived(stream); };
	
	m_pMsgHandler->onPlayerID = [this](const PlayerID& id) { OnMsgID(id); };
	m_pMsgHandler->onHandleGameStats = [this](const HandleGameStats& gs) { OnMsgGameStats(gs); };
}

void ClientInteractorImpl::PrepareGame(const std::string& cats, const std::string& roundTime, const std::string& roundCount)
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

std::pair<GameStats, PlayerStats> ClientInteractorImpl::PrepareLobby(const std::string& lobbyCode)
{
	//auto code = m_pNetwork->GenerateLobbyCode();
	auto gameStats = m_pDataOperation->CreateStats(lobbyCode, "");
	m_GameStats = gameStats;
	m_GameStats.players.push_back(m_GameStats.players[0]);
	return { m_GameStats, m_GameStats.players[0] };
}

void ClientInteractorImpl::PrepareOverview(const std::vector<std::string>& answ)
{
	m_pDataOperation->SetAnswers(answ, m_GameStats.players[0]);
	onPrepareOverview(m_GameStats);
}

void ClientInteractorImpl::EndRound(const std::vector<DECISION>& decisions)
{
	auto points = m_pGame->CalculatePoints(decisions);
	m_pDataOperation->AddPoints(points, m_GameStats.players[0]);
	m_pDataOperation->InkrementRound(m_GameStats);
	m_pGame->CheckGameFinished(m_GameStats);
}

void ClientInteractorImpl::HostLobby(const std::string& playerName)
{
	// Serverstart und LobbyCode-Generierung
	onStartServer();

	JoinLobby(m_pClient->GenerateLobbyCode(), playerName);
}

void ClientInteractorImpl::JoinLobby(const LobbyCode& lobbyCode, const std::string& playerName)
{
	//Verbindungsaufbau zum Server
	m_pClient->ConnectToServer(lobbyCode);

	//lobbycode einspeisen
	m_GameStats.lobbyCode = lobbyCode;

	//senden vom spielernamen
	Playername msg{playerName};
	auto ser = m_pSerializer->Serialize(msg);
	m_pClient->WriteToHost(ser);

	//Signal an GUI zum Übergang in Lobby
	onPrepareLobby(m_GameStats);
}

void ClientInteractorImpl::OnDataReceived(const ByteStream& stream)
{
	auto des = m_pSerializer->Deserialize(stream);
	m_pMsgHandler->handleMessage(des);
}

void ClientInteractorImpl::OnMsgID(const PlayerID& id)
{
	m_ID = id.id;
}

void ClientInteractorImpl::OnMsgGameStats(const HandleGameStats& gs)
{
	Players players{};
	for (int i{}; i < gs.gs.playerNames.size(); ++i)
		players.push_back({gs.gs.playerNames[i], gs.gs.points[i], gs.gs.answers[i]});

	m_GameStats.categories = gs.gs.categories;
	m_GameStats.maxRounds = gs.gs.maxRounds;
	m_GameStats.state = gs.gs.state;
	m_GameStats.timeout = gs.gs.timeout;
	m_GameStats.players = players;

	onUpdateLobby(m_GameStats);
}
