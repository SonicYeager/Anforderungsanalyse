#include "GameInteractor.h"

GameInteractor::GameInteractor(RandomGenRessource* gen, DataOperationLogic* op, GameLogic* game, NetworkSource* n, SLFParser* p, Serializer* s) :
	m_pRandomGenerator(gen),
	m_pDataOperation(op),
	m_pGame(game),
	m_pNetwork(n),
	m_pParser(p), 
	m_pSerialzer(s)

{
	//filling the map

	onRead = std::map<HEADER, Event<NetworkData>>
	{
		{HEADER::GETNEWPLAYER, [this](NetworkData data) 
		{ 
			data.header = HEADER::SETNEWPLAYER;
			data.playerNames.insert(std::next(std::begin(data.playerNames), data.potentialId), m_GameStats.GetPlayerStats(data.potentialId).GetPlayerName());
			auto serialzed = m_pSerialzer->Serialize(data); 
			m_pNetwork->WriteToHost(serialzed);
			//maybe fetch all data here as well?
		}},
		{HEADER::SETNEWPLAYER, [this](NetworkData data)
		{ 
			m_GameStats.SetPlayerName(data.playerNames[data.potentialId], data.potentialId);
			Players ps;
			for (size_t i{}; i < data.playerNames.size(); ++i)
			{
				PlayerStats p{};
				p.SetPlayerName(data.playerNames[i]);
				p.SetPlayerID(i);
				p.SetPoints(data.points[i]);
				p.SetAnswers(data.answers[i]);
				ps.push_back(p);
			}
			m_GameStats.SetPlayers(ps);

			//data.header = HEADER::UPDATELOBBY;
			//data.playerNames = m_GameStats.GetPlayerNames();
			//auto serialize = m_pSerialzer->Serialize(data);
			//m_pNetwork->Broadcast(serialize);
			onNewPlayerJoined(m_GameStats, data.potentialId);
		}},
		{HEADER::UPDATELOBBY, [this](NetworkData data)
		{
			m_GameStats.SetCategories(data.categories);
			m_GameStats.SetMaxRounds(data.maxRounds);
			m_GameStats.SetTimeout(data.timeout);
			Players ps;
			for (size_t i{}; i < data.playerNames.size(); ++i)
			{
				PlayerStats p{};
				p.SetPlayerName(data.playerNames[i]);
				p.SetPlayerID(i);
				p.SetPoints(data.points[i]);
				p.SetAnswers(data.answers[i]);
				ps.push_back(p);
			}
			m_GameStats.SetPlayers(ps);
			// add event to trg update
		}}
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
	m_pNetwork->onNewConnection = [this](int playerId) 
	{ 
		PlayerStats ps{};
		ps.SetPlayerID(playerId);
		m_GameStats.AddPlayer(ps);
		NetworkData ndata;
		ndata.header = HEADER::GETNEWPLAYER;
		ndata.potentialId = playerId;
		ndata.categories = m_GameStats.GetCategories();
		ndata.currentLetter = m_GameStats.GetCurrentLetter().letter;
		ndata.maxRounds = m_GameStats.GetMaxRound();
		ndata.playerNames = m_GameStats.GetPlayerNames();
		ndata.timeout = m_GameStats.GetTimeout();
		auto serialize = m_pSerialzer->Serialize(ndata);
		m_pNetwork->Write(serialize, playerId);
	};
	m_pNetwork->onReadyRead = [this](QByteArray data)
	{
		auto deserialized = m_pSerialzer->Deserialize(data);
		auto& func = onRead[deserialized.header];
		func(deserialized);
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
