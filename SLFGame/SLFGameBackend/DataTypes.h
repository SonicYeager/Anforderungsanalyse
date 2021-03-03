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

using Letter = char;
using Letters = std::vector<Letter>;
using Categories = std::vector<std::string>;

struct PlayerStats
{
	std::string playerName = "";
	int playerID = 0;
	int points = 0;
	std::vector<std::string> answers;
};

using Players = std::vector<PlayerStats>;

struct GameStats
{
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

inline bool operator==(const GameStats& left, const GameStats& right)
{
	return left.categories == right.categories &&
		left.currentLetter == right.currentLetter &&
		left.currentRound == right.currentRound &&
		left.lobbyCode == right.lobbyCode &&
		left.maxRounds == right.maxRounds &&
		left.lettersUsed == right.lettersUsed;
}

inline bool operator==(const PlayerStats& left, const PlayerStats& right)
{
	return left == right && left == right;
}
