#pragma once
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <sstream>
#include <map>

template<typename ... Args>
using Event = std::function<void(Args...)>;

using LobbyCode = std::string;
using ByteStream = std::vector<char>;

enum class DECISION : int
{
	UNANSWERED = 0,
	SOLO = 1,
	UNIQUE = 2,
	MULTIPLE = 3,
	INVALID = 4
};

enum class STATE : int
{
	MAINMENU = 0,
	LOBBY = 1,
	SETUPROUND = 2,
	INGAME = 3,
	ANSWERREQUEST = 4,
	OVERVIEW = 5,
	INTERVENTION = 6,
	FINALSCORES = 7
};

using Letter = char;
using Letters = std::vector<Letter>;
using Categories = std::vector<std::string>;

struct PlayerStats
{
	std::string playerName = "";
	int points = 0;
	std::vector<std::string> answers;
};

using Players = std::map<int, PlayerStats>;

struct GameStats
{
	Categories categories{};
	Letter currentLetter{};
	Letters lettersUsed{};
	int currentRound{};
	int maxRounds = 5;
	std::string lobbyCode{};
	std::string timeout = "bis Stop";
	std::string customCategoryString = "Stadt,Land,Fluss,Name,Tier,Beruf";
	Players players{};
	STATE state{};
};

using Stats = std::pair<GameStats, PlayerStats>;

struct LobbySettings
{
	std::string categories{};
	std::string timeout{};
	std::string rounds{};
	std::map<int, std::string> playerNames{};
};

struct RoundData
{
	std::vector<std::string> categories; 
	std::string letter; 
	std::string roundTime; 
	int currentRound;
	int maxRounds;
	int points;
};

using HeaderType = int;
const int HEADERSIZE = sizeof(HeaderType);
const int PORT = 4242;

inline std::ostream& operator<<(std::ostream& out, const ByteStream& stream)
{
	for (const char& c : stream)
		out << c << ',';
	return out;
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
	return left.playerName == right.playerName
		&& left.answers == right.answers
		&& left.points == right.points;
}