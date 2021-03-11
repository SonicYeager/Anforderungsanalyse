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
		//onPrepareNextRound(m_GameStats);
	};
	m_pClient->onData = [this](const ByteStream& stream) {OnDataReceived(stream); };
	
	m_pMsgHandler->onPlayerID = [this](const PlayerID& id) { OnMsgID(id); };
	m_pMsgHandler->onHandleGameSettings = [this](const HandleGameSettings& gs) { OnMsgHandleGameSettings(gs); };
	m_pMsgHandler->onGameState = [this](const GameState& gs) { OnMsgGameState(gs); };
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

void ClientInteractorImpl::OnDataReceived(const ByteStream& stream)
{
	auto des = m_pSerializer->Deserialize(stream);
	m_pMsgHandler->handleMessage(des);
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
