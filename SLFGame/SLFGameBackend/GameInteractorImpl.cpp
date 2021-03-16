#include "GameInteractorImpl.h"

GameInteractorImpl::GameInteractorImpl(
	GameLogic* gl,
	RandomGenRessource* rgr,
	DataOperationLogic* dol,
	ClientInteractor* ci,
	ServerInteractor* si)
	:
	m_pGame(gl),
	m_pRandomGenerator(rgr),
	m_pDataOperation(dol),
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

void GameInteractorImpl::RemovePlayer(const int& id)
{
	m_GameStats.players.erase(id);
	SendUpdatedLobbySettings();
}

void CheckAllAnswersRecived(int counter, int actualCount, Event<> onTrue)
{
	if (counter == actualCount)
	{
		onTrue();
	}
}

void GameInteractorImpl::AddAnswers(int id, const std::vector<std::string>& answers)
{
	m_GameStats.players[id].answers = answers;
	m_answerGatheredCounter++;
	
	auto broadcast = [this]()
	{		
		AllAnswers allAnsw{};
		
		for (const auto& player : m_GameStats.players)
			allAnsw.ans.push_back(player.second.answers);
		m_pServer->Broadcast(allAnsw);
	};
	
	CheckAllAnswersRecived(m_answerGatheredCounter, m_GameStats.players.size(), broadcast);
}

void GameInteractorImpl::AddPlayer(int id, const PlayerStats& playerName)
{
	m_GameStats.players.emplace(id, PlayerStats{ playerName.playerName, 0, {} });
	SendUpdatedLobbySettings();
}

void GameInteractorImpl::SetGameSettings(const LobbySettings& settings)
{
	m_GameStats.customCategoryString = settings.categories;
	m_GameStats.timeout = settings.timeout ;
	m_GameStats.maxRounds = std::stoi(settings.rounds);
	SendUpdatedLobbySettings();
}

void GameInteractorImpl::ChangeGameState(const STATE& state)
{
	m_GameStats.state = state;
	HandleGameState(state);
}

void GameInteractorImpl::SetLobbyCode(const LobbyCode& lobbyCode)
{
	m_GameStats.lobbyCode = lobbyCode;
}

//helper

HandleGameSettings GameInteractorImpl::CreateHandleGameSettings()
{
	HandleGameSettings result{};
	result.ls.categories = m_GameStats.customCategoryString;
	result.ls.rounds = std::to_string(m_GameStats.maxRounds);
	result.ls.timeout = m_GameStats.timeout;
	for (const auto& player : m_GameStats.players)
		result.ls.playerNames.emplace(player.first, player.second.playerName);
	return result;
}

void GameInteractorImpl::HandleGameState(const STATE& state) //bitte aufdröseln
{
	if (state == STATE::ANSWERREQUEST)
	{
		m_pServer->Broadcast(GameState{ state });
	}
	else if (state == STATE::SETUPROUND)
	{
		m_pDataOperation->InkrementRound(m_GameStats);
		m_pDataOperation->AddPreviousLetter(m_GameStats);
		m_pDataOperation->SetNewLetter(m_pRandomGenerator->GenerateUnusedLetter(m_GameStats.lettersUsed), m_GameStats);
		m_GameStats.categories = m_Parser.ParseCategories(m_GameStats.customCategoryString);

		RoundSetup msg;
		msg.data.categories = m_GameStats.categories;
		msg.data.currentRound = m_GameStats.currentRound;
		msg.data.letter = m_GameStats.currentLetter;
		msg.data.maxRounds = m_GameStats.maxRounds;
		msg.data.roundTime = m_GameStats.timeout;

		for (const auto& player : m_GameStats.players)
		{
			msg.data.points = player.second.points;
			m_pServer->WriteTo(player.first, msg);
		}
	}
}

void GameInteractorImpl::SendUpdatedLobbySettings()
{
	auto stats = CreateHandleGameSettings();
	m_pServer->Broadcast(stats.ls);
}
