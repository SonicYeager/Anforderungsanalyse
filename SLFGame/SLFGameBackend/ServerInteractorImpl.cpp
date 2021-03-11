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
	m_pMsgHandler->onHandleGameSettings = [this](const HandleGameSettings& gs) { OnMsgHandleGameSettings(gs); };
}

ServerInteractorImpl::~ServerInteractorImpl()
{}

void ServerInteractorImpl::StartServer()
{
	m_GameStats.lobbyCode = m_pServer->StartServer();
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
	m_GameStats.players.push_back({ playerName.playername, 0, {""} });

	auto stats = CreateHandleGameSettings();

	auto ser = m_pSerializer->Serialize(stats);
	m_pServer->Broadcast(ser);
}

void ServerInteractorImpl::OnMsgHandleGameSettings(const HandleGameSettings& settings)
{
	m_GameStats.customCategoryString = settings.ls.categories;
	m_GameStats.timeout = settings.ls.timeout ;
	m_GameStats.maxRounds = std::stoi(settings.ls.rounds);

	auto msg = CreateHandleGameSettings();

	auto ser = m_pSerializer->Serialize(msg);
	m_pServer->Broadcast(ser);
}

HandleGameSettings ServerInteractorImpl::CreateHandleGameSettings()
{
	HandleGameSettings result{};
	result.ls.categories = m_GameStats.customCategoryString;
	result.ls.rounds = std::to_string(m_GameStats.maxRounds);
	result.ls.timeout = m_GameStats.timeout;
	for (int i{}; i < m_GameStats.players.size(); ++i)
	{
		result.ls.playerNames.push_back(m_GameStats.players[i].playerName);
	}
	return result;
}