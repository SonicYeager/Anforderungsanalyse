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
	m_pGame->RemovePlayer(id);
	SendUpdatedLobbySettings();
}

void GameInteractorImpl::AddAnswers(int id, const std::vector<std::string>& answers)
{
	auto broadcast = [this](const GameStats& gameStats)
	{		
		AllAnswers allAnsw{};
		
		for (const auto& player : gameStats.players)
			allAnsw.ans.push_back(player.second.answers);
		m_pServer->Broadcast(allAnsw);
	};
	
	m_pGame->AddAnswers(id, answers, broadcast);
}

void GameInteractorImpl::AddPlayer(int id, const std::string& playerName)
{
	m_pGame->AddPlayer(id, playerName);
	SendUpdatedLobbySettings();
}

void GameInteractorImpl::SetGameSettings(const LobbySettings& settings)
{
	m_pGame->SetGameSettings(settings.categories, settings.timeout, std::stoi(settings.rounds));
	SendUpdatedLobbySettings();
}

void GameInteractorImpl::ChangeGameState(const STATE& state)
{
	m_pGame->SetGameState(state);
	HandleGameState(state);
}

void GameInteractorImpl::SetLobbyCode(const LobbyCode& lobbyCode)
{
	m_pGame->SetLobbyCode(lobbyCode);
}

void GameInteractorImpl::ToggleVote(const Index& index)
{
	m_pGame->ToggleVote(index);
	m_pServer->Broadcast(AnswerIndex{ index });
}

//helper

void GameInteractorImpl::HandleGameState(const STATE& state)
{

	auto onsetupround = [this](const std::string& customcats, const Letters& usedLetters) 
	{
		auto broadcast = [this](RoundSetup roundsetup, const GameStats& gameStats)
		{
			for (const auto& player : gameStats.players)
			{
				roundsetup.data.points = player.second.points;
				m_pServer->WriteTo(player.first, roundsetup);
			}
		};
		m_pGame->SetupRound(m_Parser.ParseCategories(customcats), m_pRandomGenerator->GenerateUnusedLetter(usedLetters), broadcast);
	};

	auto onbroadcast = [this](GameState state) {m_pServer->Broadcast(state); };

	m_pGame->HandleGameState(state, onsetupround, onbroadcast);
}

void GameInteractorImpl::SendUpdatedLobbySettings()
{
	auto stats = m_pGame->CreateHandleGameSettings();
	m_pServer->Broadcast(stats);
}
