#include "GameInteractorImpl.h"

GameInteractorImpl::GameInteractorImpl(
	GameLogic* gl,
	RandomGenRessource* rgr,
	DataOperationLogic* dol,
	ServerInteractor* si)
	:
	m_pGame(gl),
	m_pRandomGenerator(rgr),
	m_pDataOperation(dol),
	m_pServer(si)
{

	//link server to own data ops
	m_pServer->onAddAnswers =		[this](const int id, const std::vector<std::string>& ans)		{ AddAnswers(id, ans); };
	m_pServer->onAddPlayer =		[this](const int id, const PlayerStats& ans)					{ AddPlayer(id, ans); };
	m_pServer->onChangeGameState =	[this](const STATE& ans)										{ ChangeGameState(ans); };
	m_pServer->onRemovePlayer =		[this](const int id)											{ RemovePlayer(id); };
	m_pServer->onSetGameSettings =	[this](const LobbySettings& ans)								{ SetGameSettings(ans); };
	m_pServer->onSetLobbyCode =		[this](const LobbyCode& ans)									{ SetLobbyCode(ans); };
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

void GameInteractorImpl::ToggleVote(const Index& index)
{
	m_GameStats.votes[index.playerID][index.catIndex][index.voteIndex] = !m_GameStats.votes[index.playerID][index.catIndex][index.voteIndex];
	m_pServer->Broadcast(AnswerIndex{ index });
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
		//3dvector bool -> decisions

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
	else if (state == STATE::OVERVIEW)
	{
		m_pServer->Broadcast(GameState{ state });
	}
}

void GameInteractorImpl::SendUpdatedLobbySettings()
{
	auto stats = CreateHandleGameSettings();
	m_pServer->Broadcast(stats);
}
