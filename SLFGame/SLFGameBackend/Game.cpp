#pragma once
#include "Game.h"

int Game::CalculatePoints(GameStats& decisions)
{
	int result = 0;

	//for (unsigned int i = 0; i < decisions.size(); i++)
	//{
	//	if (decisions[i] == DECISION::SOLO)
	//		result += 20;
	//	else if (decisions[i] == DECISION::UNIQUE)
	//		result += 10;
	//	else if (decisions[i] == DECISION::MULTIPLE)
	//		result += 5;
	//}

	return result;
}

void Game::CheckGameFinished(GameStats& gs)
{
	if (gs.currentRound > gs.maxRounds)
		onGameOver();
	else
		onPrepareNextRound();
}

void Game::CheckAllAnswersRecived(Event<GameStats> onTrue)
{
	++m_answerGatheredCounter;
	if (m_answerGatheredCounter == m_GameStats.players.size())
	{
		onTrue(m_GameStats);
	}
}

void Game::HandleGameState(const STATE& state, Event<const std::string&, const Letters&> onSetupRound, Event<GameState> onStandart)
{
	switch (state)
	{
	case STATE::SETUPROUND:
		onSetupRound(m_GameStats.customCategoryString, m_GameStats.lettersUsed);
		break;
	default:
		onStandart(GameState{ state });
		break;
	}
}

void Game::AddPlayer(int id, const std::string& playerName)
{
	m_GameStats.players.emplace(id, PlayerStats{ playerName, 0, {} });
}

void Game::AddAnswers(int id, const std::vector<std::string>& answers, Event<GameStats> onAllAnswers)
{
	m_GameStats.players[id].answers = answers;
	CheckAllAnswersRecived(onAllAnswers);
}

void Game::RemovePlayer(int id)
{
	m_GameStats.players.erase(id);
}

void Game::SetGameSettings(const std::string& cat, const std::string& timeout, int maxRound)
{
	m_GameStats.customCategoryString = cat;
	m_GameStats.timeout = timeout;
	m_GameStats.maxRounds = maxRound;
}

void Game::SetGameState(STATE state)
{
	m_GameStats.state = state;
}

void Game::SetLobbyCode(const LobbyCode& lobbyCode)
{
	m_GameStats.lobbyCode = lobbyCode;
}

void Game::ToggleVote(const Index& index)
{
	m_GameStats.votes[index.categoryIDX][index.answerIDX][index.voterIDX] = !m_GameStats.votes[index.categoryIDX][index.answerIDX][index.voterIDX];
}

void Game::SetupRound(const Categories& categories, const Letter& letter, Event<RoundSetup, const GameStats&> onBroadcast)
{
	m_GameStats.currentRound += 1;
	auto curr = m_GameStats.currentLetter;
	if (curr != '\0')
	{
		auto usedLetters = m_GameStats.lettersUsed;
		usedLetters.push_back(curr);
		m_GameStats.lettersUsed = usedLetters;
	}
	m_GameStats.currentLetter = letter;
	m_GameStats.categories = categories;
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
	onBroadcast(msg, m_GameStats);
}

HandleGameSettings Game::CreateHandleGameSettings()
{
	HandleGameSettings result{};
	result.ls.categories = m_GameStats.customCategoryString;
	result.ls.rounds = std::to_string(m_GameStats.maxRounds);
	result.ls.timeout = m_GameStats.timeout;
	for (const auto& player : m_GameStats.players)
		result.ls.playerNames.emplace(player.first, player.second.playerName);
	return result;
}

GameStats& Game::GetGameStats()
{
	return m_GameStats;
}
