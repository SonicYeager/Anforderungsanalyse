#pragma once
#include "Game.h"

void Game::CalculatePoints(const DDDVector& decisions)
{
	int validVoteCount = 0;
	double validAnswers = 0;

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

				if (validVoteCount >= static_cast<double>(decisions[categoryIDX][answerIDX].size()) / 2.0f)
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

void Game::CheckGameFinished(Event<const std::string&, const Letters&> setUpNextRound, Event<const std::map<int, PlayerStats>&> onFinalScores)
{
	if (m_GameStats.currentRound >= m_GameStats.maxRounds)
		onFinalScores(m_GameStats.players);
	else
	{
		setUpNextRound(m_GameStats.customCategoryString, m_GameStats.lettersUsed);
	}
}

void Game::ClearPlayerAnswers()
{
	for (auto& player : m_GameStats.players)
		player.second.answers = {};
}

void Game::ResetGame()
{
	for (auto& player : m_GameStats.players)
	{
		player.second.points = 0;
		player.second.answers = {};
	}
	m_GameStats.currentRound = 0;
	m_GameStats.lettersUsed = {};
}

void Game::CheckAllAnswersRecived(Event<GameStats> onTrue)
{
	++m_answerGatheredCounter;
	if (m_answerGatheredCounter == m_GameStats.players.size())
	{
		SetVotesFalseForEmptyAnswers();
		m_answerGatheredCounter = 0;
		onTrue(m_GameStats);
	}
}

void Game::HandleGameState(const STATE& state, Event<const std::string&, const Letters&> onSetupRound, Event<const std::map<int, PlayerStats>&> onFinalScores, Event<> onNewGame, Event<GameState> onStandart)
{
	switch (state)
	{
	case STATE::SETUPROUND:
		onSetupRound(m_GameStats.customCategoryString, m_GameStats.lettersUsed);
		break;
	case STATE::ROUNDOVER:
		CalculatePoints(m_GameStats.votes);
		ClearPlayerAnswers();
		CheckGameFinished(onSetupRound, onFinalScores);
		break;
	case STATE::FINALSCORES:
		onFinalScores(m_GameStats.players);
		break;
	case STATE::NEWGAME:
		ResetGame();
		onNewGame();
		onStandart(GameState{ STATE::LOBBY });
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
							auto playerI = std::next(std::begin(m_GameStats.players), i);
							auto playerJ = std::next(std::begin(m_GameStats.players), j);
							if (playerI->second.answers[categoryIDX] == playerJ->second.answers[categoryIDX])
							{
								sameAnswer = true;
								break;
							}
						}
					}
					auto playerI = std::next(std::begin(m_GameStats.players), i);
					if (sameAnswer == true)
						playerI->second.points += 5;
					else
						playerI->second.points += 10;
				}
			}
		}
		else
		{
			for (int i = 0; i < m_GameStats.players.size(); i++)
			{
				auto playerI = std::next(std::begin(m_GameStats.players), i);
				if (answersValid[i] == true)
					playerI->second.points += 20;
			}
		}
	}
}

void Game::SetVotesFalseForEmptyAnswers()
{
	for (int i = 0; i < m_GameStats.categories.size(); i++)
	{
		for (int j = 0; j < m_GameStats.players.size(); j++)
		{
			auto playerJ = std::next(std::begin(m_GameStats.players), j);
			if (playerJ->second.answers[i] == "")
			{
				for (int k = 0; k < m_GameStats.players.size(); k++)
				{
					m_GameStats.votes[i][j][k] = false;
				}
			}
		}
	}
}
