#pragma once
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <sstream>

template<typename ... Args>
using Event = std::function<void(Args...)>;

using LobbyCode = std::string;
using ByteStream = std::vector<char>;

enum class DECISION : int
{
	UNANSWERED = 0,
	SOLO = 1,
	UNIQUE = 2,
	MULTIPLE = 3
};

enum class STATE : int
{
	MAINMENU = 0,
	LOBBY = 1,
	INGAME = 2,
	OVERVIEW = 3,
	INTERVENTION = 4,
	FINALSCORES = 5
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
	Players players{};
	STATE state{};
};

using Stats = std::pair<GameStats, PlayerStats>;

struct NetworkData
{
	char currentLetter{};
	int maxRounds{};
	std::string timeout{};
	std::vector<int> points{};
	std::vector<std::string> categories{};
	std::vector<std::string> playerNames{};
	std::vector<std::vector<DECISION>> decisions{};
	std::vector<std::vector<std::string>> answers{};
	STATE state{};
};

const int HEADERSIZE = sizeof(int);

inline bool operator==(const NetworkData& left, const NetworkData& right)
{
	return left.currentLetter == right.currentLetter &&
		left.maxRounds == right.maxRounds &&
		left.timeout == right.timeout &&
		left.points == right.points &&
		left.categories == right.categories &&
		left.playerNames == right.playerNames &&
		left.decisions == right.decisions &&
		left.answers == right.answers &&
		left.state == right.state;
}

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
	return left.playerID == right.playerID 
		&& left.playerName == right.playerName
		&& left.answers == right.answers
		&& left.points == right.points;
}