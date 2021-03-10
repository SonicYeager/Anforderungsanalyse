#pragma once
#include <variant>
#include "DataTypes.h"

namespace Messages
{
	enum class HEADER : int
	{
		HANDLEGAMESTATS = 1,
		PLAYER_NAME = 2,
		PLAYER_ID= 3,
		PLAYER_ANSWERS = 4,
		HANDLEGAMESETTINGS = 5
	};

	struct HandleGameStats		{ NetworkData gs; };
	struct HandleGameSettings	{ LobbySettings gs; };
	struct Playername			{ std::string playername; };
	struct PlayerID				{ int id; };
	struct PlayerAnswers		{ std::vector<std::string> answers; };

	using Message = std::variant<HandleGameStats, Playername, PlayerID, PlayerAnswers, HandleGameSettings>;

	inline HEADER GetMessageID(const HandleGameStats&) { return HEADER::HANDLEGAMESTATS; };
	inline HEADER GetMessageID(const Playername&) { return HEADER::PLAYER_NAME; };
	inline HEADER GetMessageID(const PlayerID&) { return HEADER::PLAYER_ID; };
	inline HEADER GetMessageID(const PlayerAnswers&) { return HEADER::PLAYER_ANSWERS; };
	inline HEADER GetMessageID(const HandleGameSettings&) { return HEADER::HANDLEGAMESETTINGS; };

	inline Message CreateMessage(HEADER header)
	{
		switch (header)
		{
		case HEADER::HANDLEGAMESTATS: return HandleGameStats{};
		case HEADER::PLAYER_NAME: return Playername{};
		case HEADER::PLAYER_ID: return PlayerID{};
		case HEADER::PLAYER_ANSWERS: return PlayerAnswers{};
		case HEADER::HANDLEGAMESETTINGS: return HandleGameSettings{};
		}
		return HandleGameStats{};
	};
	
}