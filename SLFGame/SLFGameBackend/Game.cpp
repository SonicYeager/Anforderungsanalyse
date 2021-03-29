#pragma once
#include "Game.h"

void Game::CalculatePoints(const DDDVector& decisions)
{
	int validVoteCount = 0;
	int validAnswers = 0;

	std::vector<bool> answersValid{ std::vector(m_GameStats.players.size() , false) };

	for (int categoryIDX = 0; categoryIDX < m_GameStats.categories.size(); categoryIDX++)
	{
		validAnswers = 0;
		answersValid = std::vector(m_GameStats.players.size(), false);

		for (int answerIDX = 0; answerIDX < m_GameStats.players.size(); answerIDX++)
		{
			validVoteCount = 0;
			for (int voterIDX = 0; voterIDX < m_GameStats.players.size(); voterIDX++)
			{
				if (decisions[categoryIDX][answerIDX][voterIDX] == true)
					validVoteCount += 1;

				if (validVoteCount >= decisions[categoryIDX][answerIDX].size() / 2)
				{
					validAnswers += 1;
					answersValid[answerIDX] = true;
					break;
				}
			}
		}
		HandOutPointsForCategory(categoryIDX, validAnswers, answersValid);
	}
}

void Game::CheckGameFinished(Event<const std::string&, const Letters&> setUpNextRound)
{
	if (m_GameStats.currentRound >= m_GameStats.maxRounds)
		int gameover = 1; // change NextIncrement
	else
	{
		setUpNextRound(m_GameStats.customCategoryString, m_GameStats.lettersUsed);
	}
}

void Game::ClearPlayerAnswers()
{
	for (int i = 0; i < m_GameStats.players.size(); i++)
		m_GameStats.players[i].answers = {};
}

void Game::CheckAllAnswersRecived(Event<GameStats> onTrue)
{
	++m_answerGatheredCounter;
	if (m_answerGatheredCounter == m_GameStats.players.size())
	{
		m_answerGatheredCounter = 0;
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
	case STATE::ROUNDOVER:
		CalculatePoints(m_GameStats.votes);
		ClearPlayerAnswers();
		CheckGameFinished(onSetupRound);
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
	m_GameStats.votes = std::vector<std::vector<std::vector<bool>>>(m_GameStats.categories.size(), std::vector<std::vector<bool>>(m_GameStats.players.size(), std::vector<bool>(m_GameStats.players.size(), true)));

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

void Game::HandOutPointsForCategory(int categoryIDX, int validAnswers, std::vector<bool> answersValid)
{
	bool sameAnswer = false;
	if (validAnswers > 0)
	{
		if (validAnswers > 1)
		{
			for (int i = 0; i < m_GameStats.players.size(); i++)
			{
				if (answersValid[i] == true)
				{
					sameAnswer = false;
					for (int j = 0; j < m_GameStats.players.size(); j++)
					{
						if (i != j)
						{
							if (m_GameStats.players[i].answers[categoryIDX] == m_GameStats.players[j].answers[categoryIDX])
							{
								sameAnswer = true;
								break;
							}
						}
					}
					if (sameAnswer == true)
						m_GameStats.players[i].points += 5;
					else
						m_GameStats.players[i].points += 10;
				}
			}
		}
		else
		{
			for (int i = 0; i < m_GameStats.players.size(); i++)
				if (answersValid[i] == true)
					m_GameStats.players[i].points += 20;
		}
	}
}

void Game::SetVotesFalseForEmptyAnswers()
{
	for (int i = 0; i < m_GameStats.categories.size(); i++)
	{
		for (int j = 0; j < m_GameStats.players.size(); j++)
		{
			if (m_GameStats.players[j].answers[i] == "")
			{
				for (int k = 0; k < m_GameStats.players.size(); k++)
				{
					m_GameStats.votes[i][j][k] = false;
				}
			}
		}
	}
}
