#pragma once
#include <vector>
#include <string>
#include <functional>

template<typename ... Args>
using Event = std::function<void(Args...)>;


enum class DECISION : int
{
	UNANSWERED = 0,
	SOLO = 1,
	UNIQUE = 2,
	MULTIPLE = 3
};

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
	std::vector<std::string>	GetAnswers		()const;
	std::string					GetAnswerAt		(int)const;
	std::string					GetPlayerName	()const;
	int							GetPlayerID		()const;
	void						SetPoints		(int);
	void						SetPlayerName	(const std::string&);
	void						SetAnswers		(const std::vector<std::string>&);
	void						SetPlayerID		(int);

private:
	std::string playerName = "Pete";
	int playerID = 0;
	int points = 0;
	std::vector<std::string> answers;
};

using Players = std::vector<PlayerStats>;

struct GameStats
{
	Categories GetCategories()const;
	Letters GetUsedLetters()const;
	Letter GetCurrentLetter()const;
	PlayerStats GetPlayerStats(int)const;
	std::vector<std::string> GetPlayerNames() const;
	int GetPlayerCount()const;
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
	void AddPlayer(PlayerStats);
	void SetTimeout(const std::string&);
	void SetPlayerName(const std::string&, int);
	void SetPlayers(const Players&);

private:
	Categories categories{};
	Letter currentLetter{};
	Letters lettersUsed{};
	int currentRound{};
	int maxRounds{};
	std::string lobbyCode{};
	std::string timeout{};
	Players players;
};

using Stats = std::pair<GameStats, PlayerStats>;

enum class HEADER : int
{
	GETNEWPLAYER = 1,
	SETNEWPLAYER = 2,
	UPDATELOBBY  = 3
};

struct NetworkData
{
	HEADER header{};
	char currentLetter{};
	int potentialId{};
	int maxRounds{};
	std::string timeout{};
	std::vector<int> points{};
	std::vector<std::string> categories{};
	std::vector<std::string> playerNames{};
	std::vector<std::vector<DECISION>> decisions{};
	std::vector<std::vector<std::string>> answers{};
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

inline std::string PlayerStats::GetPlayerName() const
{
	return playerName;
}

inline int PlayerStats::GetPlayerID() const
{
	return playerID;
}

inline void PlayerStats::SetPoints(int newPoints)
{
	points = newPoints;
}

inline void PlayerStats::SetPlayerName(const std::string& newName)
{
	playerName = newName;
}

inline void PlayerStats::SetAnswers(const std::vector<std::string>& newAnswers)
{
	answers = newAnswers;
}

inline void PlayerStats::SetPlayerID(int id)
{
	playerID = id;
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

inline PlayerStats GameStats::GetPlayerStats(int playerId) const
{
	return players[playerId];
}

inline std::vector<std::string> GameStats::GetPlayerNames() const
{
	std::vector<std::string> names{};
	for (auto name : players)
		names.push_back(name.GetPlayerName());
	return names;
}

inline int GameStats::GetPlayerCount() const
{
	return players.size();
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

inline void GameStats::AddPlayer(PlayerStats ps)
{
	players.push_back(ps);
}

inline std::string GameStats::GetTimeout() const
{
	return timeout;
}

inline void GameStats::SetTimeout(const std::string& t)
{
	timeout = t;
}

inline void GameStats::SetPlayerName(const std::string& name, int idx)
{
	PlayerStats ps{};
	ps.SetPlayerName(name);
	ps.SetPlayerID(idx);
	players.insert(std::next(std::begin(players), idx), ps);
}

inline void GameStats::SetPlayers(const Players& play)
{
	players = play;
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
