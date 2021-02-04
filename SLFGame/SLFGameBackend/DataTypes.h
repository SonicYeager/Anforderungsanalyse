#pragma once
#include <vector>
#include <string>
#include <functional>

template<typename ... Args>
using Event = std::function<void(Args...)>;

struct Letter
{
	bool operator==(const Letter& other);
	char letter{};
};

struct Letters
{
	std::vector<Letter> letters{};
};

using Categories = std::vector<std::string>;

struct PlayerStats
{
	int GetPoints()const;
	std::vector<std::string> GetAnswers()const;
	std::string GetAnswerAt(int)const;
	void SetPoints(int);
	void SetAnswers(const std::vector<std::string>&);

private:
	int points{};
	std::vector<std::string> answers;
};

struct GameStats
{
	Categories GetCategories()const;
	Letters GetUsedLetters()const;
	Letter GetCurrentLetter()const;
	int GetCurrentRound()const;
	int GetMaxRound()const;
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

inline int PlayerStats::GetPoints()	const
{
	return points;
}

inline std::vector<std::string> PlayerStats::GetAnswers() const
{
	return answers;
}

inline std::string PlayerStats::GetAnswerAt(int i) const
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

inline Categories GameStats::GetCategories() const 
{
	return categories;
}

inline Letters GameStats::GetUsedLetters() const
{
	return lettersUsed;
}

inline Letter GameStats::GetCurrentLetter()	const
{
	return currentLetter;
}

inline int GameStats::GetCurrentRound()	const
{
	return currentRound;
}

inline int GameStats::GetMaxRound()	const
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

inline bool Letter::operator==(const Letter& other)
{
	return letter == other.letter;
}