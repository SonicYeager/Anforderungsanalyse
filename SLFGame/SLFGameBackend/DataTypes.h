#pragma once
#include <vector>
#include <string>

struct Letter
{
	char letter{};
};

struct Letters
{
	std::vector<Letter> letters{};
};

struct Categories
{
	std::vector<std::string> categories{};
};

struct PlayerStats
{
	int GetPoints();
	std::vector<std::string> GetAnswers();
	std::string GetAnswerAt(int);
	void SetPoints(int);
	void SetAnswers(const std::vector<std::string>&);

private:
	int points{};
	std::vector<std::string> answers;
};

struct GameStats
{
	Categories GetCategories();
	Letters GetUsedLetters();
	Letter GetCurrentLetter();
	int GetCurrentRound();
	int GetMaxRound();
	void SetUsedLetters(Letters);
	void SetCurrentLetter(Letter);
	void SetCurrentRound(int);

private:
	Categories categories{};
	Letter currentLetter{};
	Letters lettersUsed{};
	int currentRound{};
	int maxRounds{};
	//Timeout
};

inline int PlayerStats::GetPoints()
{
	return points;
}

inline std::vector<std::string> PlayerStats::GetAnswers()
{
	return answers;
}

inline std::string PlayerStats::GetAnswerAt(int i)
{
	return answers[i];
}

inline void PlayerStats::SetPoints(int newPoints)
{
	points = newPoints;
}

inline void PlayerStats::SetAnswers(const std::vector<std::string>& newAsnwers)
{
	answers = newAsnwers;
}

inline Categories GameStats::GetCategories()
{
	return categories;
}

inline Letters GameStats::GetUsedLetters()
{
	return lettersUsed;
}

inline Letter GameStats::GetCurrentLetter()
{
	return currentLetter;
}

inline int GameStats::GetCurrentRound()
{
	return currentRound;
}

inline int GameStats::GetMaxRound()
{
	return maxRounds;
}

inline void GameStats::SetUsedLetters(Letters newLetters)
{
	lettersUsed = newLetters;
}

inline void GameStats::SetCurrentLetter(Letter newLetter)
{
	currentLetter = newLetter;
}

inline void GameStats::SetCurrentRound(int newCurrentRound)
{
	currentRound = newCurrentRound;
}
