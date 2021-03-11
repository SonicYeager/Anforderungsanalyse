#pragma once
#include <variant>
#include "DataTypes.h"

namespace Messages
{
	enum class HEADER : int
	{
		PLAYER_NAME = 1,
		PLAYER_ID = 2,
		PLAYER_ANSWERS = 3,
		HANDLEGAMESETTINGS = 4,
		GAMESTATE = 5
	};

	struct HandleGameSettings	{ LobbySettings ls; };
	struct Playername			{ std::string playername; };
	struct PlayerID				{ int id; };
	struct PlayerAnswers		{ std::vector<std::string> answers; };
	struct GameState			{ STATE state; };

	using Message = std::variant<Playername, PlayerID, PlayerAnswers, HandleGameSettings, GameState>;

	inline HEADER GetMessageID(const Playername&) { return HEADER::PLAYER_NAME; };
	inline HEADER GetMessageID(const PlayerID&) { return HEADER::PLAYER_ID; };
	inline HEADER GetMessageID(const PlayerAnswers&) { return HEADER::PLAYER_ANSWERS; };
	inline HEADER GetMessageID(const HandleGameSettings&) { return HEADER::HANDLEGAMESETTINGS; };
	inline HEADER GetMessageID(const GameState&) { return HEADER::GAMESTATE; };

	inline Message CreateMessage(HEADER header)
	{
		switch (header)
		{
		case HEADER::PLAYER_NAME: return Playername{};
		case HEADER::PLAYER_ID: return PlayerID{};
		case HEADER::PLAYER_ANSWERS: return PlayerAnswers{};
		case HEADER::HANDLEGAMESETTINGS: return HandleGameSettings{};
		case HEADER::GAMESTATE: return GameState{};
		}
		return HandleGameSettings{};
	};
	
}