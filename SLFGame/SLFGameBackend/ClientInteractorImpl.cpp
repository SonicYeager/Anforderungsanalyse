#pragma once
#include "ClientInteractorImpl.h"

ClientInteractorImpl::ClientInteractorImpl(
	RandomGenRessource* gen,
	ClientSource* cl,
	SerializerSource* s,
	MessageHandlerLogic* n)
	:
	m_pRandomGenerator(gen),
	m_pClient(cl),
	m_pSerializer(s),
	m_pMsgHandler(n)
{
	m_pClient->onData = [this](const ByteStream& stream) {OnDataReceived(stream); };
	
	m_pMsgHandler->onPlayerID = [this](const PlayerID& id) { OnMsgID(id); };
	m_pMsgHandler->onHandleGameSettings = [this](const HandleGameSettings& gs) { OnMsgHandleGameSettings(gs); };
	m_pMsgHandler->onGameState = [this](const GameState& gs) { OnMsgGameState(gs); };
	m_pMsgHandler->onChatMessage = [this](const ChatMessage& cm) { OnChatMessage(cm); };
	m_pMsgHandler->onAllAnswers = [this](const AllAnswers& aans) { OnAllAnswers(aans); };
	m_pMsgHandler->onRoundSetup = [this](const RoundSetup& msg) {OnRoundSetup(msg); };
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

	//LobbyCode an GUI
	onSetLobbyCode(lobbyCode);

	//senden vom spielernamen
	Playername msg{playerName};
	auto ser = m_pSerializer->Serialize(msg);
	m_pClient->WriteToHost(ser);
}

void ClientInteractorImpl::LobbyChanged(const std::string& cats, const std::string& timeout, const std::string& rounds)
{
	HandleGameSettings gs{ {cats, timeout, rounds} };
	auto ser = m_pSerializer->Serialize(gs);
	m_pClient->WriteToHost(ser);
}

void ClientInteractorImpl::ChatMessageReceived(const std::string& sender, const std::string& text)
{
	ChatMessage cm{ sender, text };
	auto ser = m_pSerializer->Serialize(cm);
	m_pClient->WriteToHost(ser);
}

void ClientInteractorImpl::OnDataReceived(const ByteStream& stream)
{
	auto des = m_pSerializer->Deserialize(stream);
	m_pMsgHandler->handleMessage(des);
}

void ClientInteractorImpl::StateChangeTriggered(const STATE& state)
{
	GameState gs;
	gs.state = state;
	auto ser = m_pSerializer->Serialize(gs);
	m_pClient->WriteToHost(ser);
}

void ClientInteractorImpl::AnswersReceived(const std::vector<std::string>& answers)
{
	PlayerAnswers ans{answers};

	auto ser = m_pSerializer->Serialize(ans);
	m_pClient->WriteToHost(ser);
}

void ClientInteractorImpl::OnMsgID(const PlayerID& id)
{
	onReceivedID(id.id);
}

void ClientInteractorImpl::OnMsgHandleGameSettings(const HandleGameSettings& settings)
{
	onUpdateLobbySettings(settings.ls);
	onGameState(STATE::LOBBY);
}

void ClientInteractorImpl::OnMsgGameState(const GameState& gs)
{
	onGameState(gs.state);
}

void ClientInteractorImpl::OnChatMessage(const ChatMessage& cm)
{
	onChatMessage(cm);
}

void ClientInteractorImpl::OnAllAnswers(const AllAnswers& msg)
{
	onAllAnswers(msg.ans);
	onGameState(STATE::OVERVIEW);
}

void ClientInteractorImpl::OnRoundSetup(const RoundSetup& msg)
{
	onRoundData(msg.data);
	onGameState(STATE::INGAME);
}
