#pragma once
#include <variant>
#include "DataTypes.h"

namespace Messages
{
	enum class HEADER : int
	{
		HANDLEGAMESTATS = 1,
		ADDNEWPLAYER = 2,
		PLAYERNAME = 3
	};

	struct HandleGameStats { NetworkData gs; };
	struct AddNewPlayer    { PlayerStats player; };
	struct Playername	   { std::string playername; };

	using Message = std::variant<HandleGameStats, AddNewPlayer, Playername>;

	inline HEADER GetMessageID(const HandleGameStats&) { return HEADER::HANDLEGAMESTATS; };
	inline HEADER GetMessageID(const AddNewPlayer&) { return HEADER::ADDNEWPLAYER; };
	inline HEADER GetMessageID(const Playername&) { return HEADER::PLAYERNAME; };

	inline Message CreateMessage(HEADER header)
	{
		switch (header)
		{
		case HEADER::HANDLEGAMESTATS: return HandleGameStats{};
		case HEADER::ADDNEWPLAYER: return AddNewPlayer{};
		case HEADER::PLAYERNAME: return Playername{};
		}
		return HandleGameStats{};
	};
	
}