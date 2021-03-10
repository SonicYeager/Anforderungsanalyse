#include "ServerInteractorImpl.h"

ServerInteractorImpl::ServerInteractorImpl(ServerSource* s, SerializerSource* ss, MessageHandlerLogic* msg) :
	m_pServer(s),
	m_pSerializer(ss),
	m_pMsgHandler(msg)
{
	//m_server->onLog = [this](const std::string& text) {OnLog(text); };
	m_pServer->onNewConnection = [this](int id) {OnNewConnection(id); };
	m_pServer->onClientData = [this](const ByteStream& stream, int id) { OnData(stream, id); };

	//msghandler
	//playername
}

ServerInteractorImpl::~ServerInteractorImpl()
{}

void ServerInteractorImpl::StartServer()
{
	m_pServer->StartServer();
}

void ServerInteractorImpl::OnNewConnection(int id)
{
	//onLog("ServerInteractor: New Connection Handled; ID: " + std::to_string(id));
	auto text = std::to_string(id);
	ByteStream stream{std::begin(text), std::end(text)};
	m_pServer->WriteTo(stream, id);


	////Erstellung von GameStatsMassage
	//HandleGameStats gameStatsMsg = CreateGameStatsMessage();
	//gameStatsMsg.gs.potentialId = m_GameStats.players.size();

	////Serialisierung und Senden der Daten an neuen Spieler
	//auto serializedMsg = m_pSerializer->Serialize(gameStatsMsg);

	////Erhalten der geupdateten Spielerdaten
	//auto data = m_pServer->ReceiveData(m_GameStats.players.size());
	//auto msg = m_pSerializer->Deserialize(data);
	//m_pMsgHandler->handleMessage(msg);

	////Host -> Hinzufügen des neuen Spielers
	//m_GameStats.players.push_back({ m_handleGS.gs.playerNames[m_GameStats.players.size()], (int)m_GameStats.players.size(), m_handleGS.gs.points[m_GameStats.players.size()], m_handleGS.gs.answers[m_GameStats.players.size()] });

	////Broadcasten der geupdaten Spielerdaten
	//HandleGameStats updatedGameStatsMsg = CreateGameStatsMessage();
	//auto serb = m_pSerializer->Serialize(updatedGameStatsMsg);
	//m_pHost->Broadcast(serb);

}

void ServerInteractorImpl::OnData(const ByteStream& stream, int id)
{
	std::string text{std::begin(stream), std::end(stream)};
	//onLog("ServerInteractor: received data: " + text + " from client: " + std::to_string(id));
}

void ServerInteractorImpl::OnLog(const std::string& text)
{
	//if(onLog)
	//	onLog("Server: " + text);
}

void ServerInteractorImpl::UpdateGameStats(const std::string& playerName)
{
	m_GameStats.categories = m_handleGS.gs.categories;
	m_GameStats.maxRounds = m_handleGS.gs.maxRounds;
	m_GameStats.timeout = m_handleGS.gs.timeout;
	for (int i{}; i < m_handleGS.gs.playerNames.size(); ++i)
		m_GameStats.players.push_back({ m_handleGS.gs.playerNames[i], i, 0, {} });
	m_GameStats.players.push_back({ playerName, m_handleGS.gs.potentialId, 0, {} });
}

void ServerInteractorImpl::AddPlayerStatsToMessage(const std::string& playerName)
{
	m_handleGS.gs.playerNames.push_back(playerName);
	m_handleGS.gs.answers.emplace_back();
	m_handleGS.gs.points.emplace_back();
	m_handleGS.gs.decisions.emplace_back();
}

HandleGameStats ServerInteractorImpl::CreateGameStatsMessage()
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