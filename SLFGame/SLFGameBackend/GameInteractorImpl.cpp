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
	m_pServer->onAddPlayer =		[this](const int id, const std::string& ans)					{ AddPlayer(id, ans); };
	m_pServer->onChangeGameState =	[this](const STATE& ans)										{ ChangeGameState(ans); };
	m_pServer->onRemovePlayer =		[this](const int id)											{ RemovePlayer(id); };
	m_pServer->onSetGameSettings =	[this](const LobbySettings& ans)								{ SetGameSettings(ans); };
	m_pServer->onSetLobbyCode =		[this](const LobbyCode& ans)									{ SetLobbyCode(ans); };
	m_pServer->onAnswerIndex =		[this](const Index& idx)										{ ToggleVote(idx); };
}

//server

void GameInteractorImpl::RemovePlayer(const int& id)
{
	m_GameStats.players.erase(id);
	SendUpdatedLobbySettings();
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
	
	m_pGame->CheckAllAnswersRecived(m_answerGatheredCounter, m_GameStats.players.size(), broadcast);
}

void GameInteractorImpl::AddPlayer(int id, const std::string& playerName)
{
	m_GameStats.players.emplace(id, PlayerStats{ playerName, 0, {} });
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
	m_GameStats.votes[index.categoryIDX][index.answerIDX][index.voterIDX] = !m_GameStats.votes[index.categoryIDX][index.answerIDX][index.voterIDX];
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

	auto onsetupround = [this]() 
	{
		m_pDataOperation->InkrementRound(m_GameStats);
		m_pDataOperation->AddPreviousLetter(m_GameStats);
		m_pDataOperation->SetNewLetter(m_pRandomGenerator->GenerateUnusedLetter(m_GameStats.lettersUsed), m_GameStats);
		m_GameStats.categories = m_Parser.ParseCategories(m_GameStats.customCategoryString);

		m_GameStats.votes = std::vector<std::vector<std::vector<bool>>>(m_GameStats.categories.size(), std::vector<std::vector<bool>>(m_GameStats.players.size(), std::vector<bool>(m_GameStats.players.size(), false)));
		//for (const auto& player : m_GameStats.players)
		//{
		//	std::vector<std::vector<bool>> percat{};
		//	for (const auto& cat : m_GameStats.categories)
		//	{
		//		std::vector<bool> peransw{};
		//		for (const auto& answ : player.second.answers)
		//		{
		//			peransw.emplace_back(false);
		//		}
		//		percat.push_back(peransw);
		//	}
		//	m_GameStats.votes.push_back(percat);
		//}

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
	};
	auto onbroadcast = [this](GameState state) {m_pServer->Broadcast(state); };

	m_pGame->HandleGameState(state, onsetupround, onbroadcast);
}

void GameInteractorImpl::SendUpdatedLobbySettings()
{
	auto stats = CreateHandleGameSettings();
	m_pServer->Broadcast(stats);
}
