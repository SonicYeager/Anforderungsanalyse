#include "GameInteractorImpl.h"

GameInteractorImpl::GameInteractorImpl(
	GameLogic* gl,
	RandomGenRessource* rgr,
	DataOperationLogic* dol,
	ClientInteractor* ci,
	ServerInteractor* si)
	:
	m_pGame(gl),
	m_pRandGen(rgr),
	m_pGameStatsOperation(dol),
	m_pClient(ci),
	m_pServer(si)
{
	//link both inter to each other
	m_pClient->onStartServer = [this] {	m_pServer->StartServer(); };

	//relay client trgg to ui
	m_pClient->onAllAnswers				= [this](const std::vector<std::vector<std::string>>& answ) { onAllAnswers(answ); };
	m_pClient->onChatMessage			= [this](const ChatMessage& answ)							{ onChatMessage(answ); };
	m_pClient->onGameState				= [this](const STATE& answ)									{ onGameState(answ); };
	m_pClient->onReceivedID				= [this](const int& answ)									{ onReceivedID(answ); };
	m_pClient->onRoundData				= [this](const RoundData& answ)								{ onRoundData(answ); };
	m_pClient->onSetLobbyCode			= [this](const LobbyCode& answ)								{ onSetLobbyCode(answ); };
	m_pClient->onUpdateLobbySettings	= [this](const LobbySettings& answ)							{ onUpdateLobbySettings(answ); };

	//link server to own data ops
}

//ui

void GameInteractorImpl::HostLobby(const std::string& playerName)
{
	m_pClient->HostLobby(playerName);
}

void GameInteractorImpl::JoinLobby(const LobbyCode& lobbyCode, const std::string& playerName)
{
	m_pClient->JoinLobby(lobbyCode, playerName);
}

void GameInteractorImpl::LobbyChanged(const std::string& cats, const std::string& timeout, const std::string& rounds)
{
	m_pClient->LobbyChanged(cats, timeout, rounds);
}

void GameInteractorImpl::ChatMessageReceived(const std::string& sender, const std::string& text)
{
	m_pClient->ChatMessageReceived(sender, text);
}

void GameInteractorImpl::StateChangeTriggered(const STATE& state)
{
	m_pClient->StateChangeTriggered(state);
}

void GameInteractorImpl::AnswersReceived(const std::vector<std::string>& answers)
{
	m_pClient->AnswersReceived(answers);
}

//server

void GameInteractorImpl::AddAnswers(const PlayerAnswers&)
{
}

void GameInteractorImpl::AddPlayer(const PlayerStats&)
{
}

void GameInteractorImpl::SetGameSettings(const HandleGameSettings&)
{
}

void GameInteractorImpl::RemovePlayer(const int&)
{
}

void GameInteractorImpl::ChangeGameState(const GameState&)
{
}
