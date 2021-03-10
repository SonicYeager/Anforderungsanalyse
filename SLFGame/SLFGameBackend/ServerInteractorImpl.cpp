#include "ServerInteractorImpl.h"

ServerInteractorImpl::ServerInteractorImpl(ServerSource* s, SerializerSource* ss, MessageHandlerLogic* msg) :
	m_pServer(s),
	m_pSerializer(ss),
	m_pMsgHandler(msg)
{
	//m_server->onLog = [this](const std::string& text) {OnLog(text); };
	m_pServer->onNewConnection = [this](int id) {OnNewConnection(id); };
	m_pServer->onClientData = [this](const ByteStream& stream, int id) { OnData(stream, id); };

	m_pMsgHandler->onPlayername = [this](const Playername& playerName) { OnMsgPlayerName(playerName); };
}

ServerInteractorImpl::~ServerInteractorImpl()
{}

void ServerInteractorImpl::StartServer()
{
	m_pServer->StartServer();
}

void ServerInteractorImpl::OnNewConnection(int id)
{
	PlayerID ID{id};
	auto ser = m_pSerializer->Serialize(ID);
	m_pServer->WriteTo(ser, id);

	//onLog("ServerInteractor: New Connection Handled; ID: " + std::to_string(id));
}

void ServerInteractorImpl::OnData(const ByteStream& stream, int id)
{
	auto des = m_pSerializer->Deserialize(stream);
	m_pMsgHandler->handleMessage(des);

	//onLog("ServerInteractor: received data: " + text + " from client: " + std::to_string(id));
}

void ServerInteractorImpl::OnLog(const std::string& text)
{
	//if(onLog)
	//	onLog("Server: " + text);
}

void ServerInteractorImpl::OnMsgPlayerName(const Playername& playerName)
{
	auto stats = CreateGameStatsMessage();
	stats.gs.playerNames.push_back(playerName.playername);
	stats.gs.points.emplace_back();
	stats.gs.decisions.emplace_back();

	auto ser = m_pSerializer->Serialize(stats);
	m_pServer->Broadcast(ser);
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