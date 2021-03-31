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
	m_pMsgHandler->onAnswerIndex = [this](const AnswerIndex& idx) { OnAnswerIndex(idx); };
}

ServerInteractorImpl::~ServerInteractorImpl()
{}

void ServerInteractorImpl::StartServer()
{
	auto lobbyCode = m_pServer->StartServer();
	onSetLobbyCode(lobbyCode);
}

void ServerInteractorImpl::StopListening()
{
	m_pServer->StopListening();
}

void ServerInteractorImpl::Broadcast(const Message& msg)
{
	auto ser = m_pSerializer->Serialize(msg);
	m_pServer->Broadcast(ser);
}

void ServerInteractorImpl::WriteTo(int id, const Message& msg)
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
	if (id == 0)
		m_pServer->Reset();
	onRemovePlayer(id);
}

void ServerInteractorImpl::OnMsgPlayerName(const Playername& playerName)
{
	onAddPlayer(playerName.id, playerName.playername);
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
	onAddAnswers(answers.id, answers.answers);
}

void ServerInteractorImpl::OnGameState(const GameState& gs)
{
	onChangeGameState(gs.state);
}

void ServerInteractorImpl::OnAnswerIndex(const AnswerIndex& answerIndex)
{
	onAnswerIndex(answerIndex.index);
}
