#pragma once
#include <vector>
#include <string>
#include <functional>

template<typename ... Args>
using Event = std::function<void(Args...)>;

struct Letter
{
	bool operator==(const Letter& other) const;
	bool operator<(const Letter& other) const;
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
	std::string GetLobbyCode() const;
	std::string GetTimeout() const;
	void SetLobbyCode(const std::string&);
	void SetUsedLetters(Letters);
	void SetCurrentLetter(Letter);
	void SetCategories(Categories);
	void SetCurrentRound(int);
	void SetMaxRounds(int);
	void SetTimeout(const std::string&);

private:
	Categories categories{};
	Letter currentLetter{};
	Letters lettersUsed{};
	int currentRound{};
	int maxRounds{};
	std::string lobbyCode{};
	std::string timeout{};
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

inline void GameStats::SetCategories(Categories cats)
{
	categories = cats;
}

inline int GameStats::GetCurrentRound()	const
{
	return currentRound;
}

inline int GameStats::GetMaxRound()	const
{
	return maxRounds;
}

inline std::string GameStats::GetLobbyCode() const
{
	return lobbyCode;
}

inline void GameStats::SetLobbyCode(const std::string& code)
{
	lobbyCode = code;
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

inline void GameStats::SetMaxRounds(int num)
{
	maxRounds = num;
}

inline std::string GameStats::GetTimeout() const
{
	return timeout;
}

inline void GameStats::SetTimeout(const std::string& t)
{
	timeout = t;
}

inline bool Letter::operator==(const Letter& other)	const
{
	return letter == other.letter;
}

inline bool Letter::operator<(const Letter& other) const
{
	return letter < other.letter;
}

//inline bool operator==(const Letter& left, const Letter& right)
//{
//	return left.letter == right.letter;
//}

inline bool operator==(const GameStats& left, const GameStats& right)
{
	return left.GetCategories() == right.GetCategories() &&
		left.GetCurrentLetter() == right.GetCurrentLetter() &&
		left.GetCurrentRound() == right.GetCurrentRound() &&
		left.GetLobbyCode() == right.GetLobbyCode() &&
		left.GetMaxRound() == right.GetMaxRound() &&
		left.GetUsedLetters().letters == right.GetUsedLetters().letters;
}

inline bool operator==(const PlayerStats& left, const PlayerStats& right)
{
	return left.GetAnswers() == right.GetAnswers() && left.GetPoints() == right.GetPoints();
}