#include "ServerInteractorImpl.h"

ServerInteractorImpl::ServerInteractorImpl(
	ServerSource* s, 
	SerializerSource* ss, 
	MessageHandlerLogic* msg)
	:
	m_pServer(s),
	m_pSerializer(ss),
	m_pMsgHandler(msg)
{
	//m_server->onLog = [this](const std::string& text) {OnLog(text); };
	m_pServer->onNewConnection = [this](int id) {OnNewConnection(id); };
	m_pServer->onClientData = [this](const ByteStream& stream, int id) { OnData(stream, id); };
	m_pServer->onClientDisconnect = [this](int id) { OnDisconnect(id); };

	m_pMsgHandler->onPlayername = [this](const Playername& playerName) { OnMsgPlayerName(playerName); };
	m_pMsgHandler->onChatMessage = [this](const ChatMessage& cm) { OnChatMessage(cm); };
	m_pMsgHandler->onHandleGameSettings = [this](const HandleGameSettings& gs) { OnMsgHandleGameSettings(gs); };
	m_pMsgHandler->onGameState = [this](const GameState& gs) { OnGameState(gs); };
	m_pMsgHandler->onPlayerAnswers = [this](const PlayerAnswers& ans) { OnPlayerAnswers(ans); };
}

ServerInteractorImpl::~ServerInteractorImpl()
{}

void ServerInteractorImpl::StartServer()
{
	auto lobbyCode = m_pServer->StartServer();
	onSetLobbyCode(lobbyCode);
}

void ServerInteractorImpl::Broadcast(const LobbySettings& ls)
{
	auto ser = m_pSerializer->Serialize(HandleGameSettings{ ls });
	m_pServer->Broadcast(ser);
}

void ServerInteractorImpl::Broadcast(const AllAnswers& allAnsw)
{
	auto ser = m_pSerializer->Serialize(allAnsw);
	m_pServer->Broadcast(ser);
}

void ServerInteractorImpl::Broadcast(const GameState& gs)
{
	auto ser = m_pSerializer->Serialize(gs);
	m_pServer->Broadcast(ser);
}

void ServerInteractorImpl::WriteTo(int id, const RoundSetup& msg)
{
	auto ser = m_pSerializer->Serialize(msg);
	m_pServer->WriteTo(ser, id);
}

void ServerInteractorImpl::OnNewConnection(int id)
{
	PlayerID ID{id};
	auto serID = m_pSerializer->Serialize(ID);
	m_pServer->WriteTo(serID, id);

	//onLog("ServerInteractor: New Connection Handled; ID: " + std::to_string(id));
}

void ServerInteractorImpl::OnData(const ByteStream& stream, int id)
{
	auto des = m_pSerializer->Deserialize(stream);
	m_actualID = id; //how to pass through the id to the event funcs
	m_pMsgHandler->handleMessage(des);

	//onLog("ServerInteractor: received data: " + text + " from client: " + std::to_string(id));
}

void ServerInteractorImpl::OnLog(const std::string& text)
{
	//if(onLog)
	//	onLog("Server: " + text);
}

void ServerInteractorImpl::OnDisconnect(int id)
{
	onRemovePlayer(id);
}

void ServerInteractorImpl::OnMsgPlayerName(const Playername& playerName)
{
	onAddPlayer(m_actualID, PlayerStats{ playerName.playername, 0, {} });
}

void ServerInteractorImpl::OnMsgHandleGameSettings(const HandleGameSettings& settings)
{
	onSetGameSettings(settings.ls);
}

void ServerInteractorImpl::OnChatMessage(const ChatMessage& cm)
{
	auto ser = m_pSerializer->Serialize(cm);
	m_pServer->Broadcast(ser);
}

void ServerInteractorImpl::OnPlayerAnswers(const PlayerAnswers& answers)
{
	onAddAnswers(m_actualID, answers.answers);
}

void ServerInteractorImpl::OnGameState(const GameState& gs)
{
	onChangeGameState(gs.state);
}
