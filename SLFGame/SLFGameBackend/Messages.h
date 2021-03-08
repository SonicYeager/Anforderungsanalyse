#pragma once
#include <variant>
#include "DataTypes.h"

namespace Messages
{
	enum class HEADER : int
	{
		HANDLEGAMESTATS = 1,
		ADDNEWPLAYER = 2
	};

	struct HandleGameStats { NetworkData gs; };
	struct AddNewPlayer    { PlayerStats player; };

	using Message = std::variant<HandleGameStats, AddNewPlayer>;

	inline HEADER GetMessageID(const HandleGameStats&) { return HEADER::HANDLEGAMESTATS; };
	inline HEADER GetMessageID(const AddNewPlayer&) { return HEADER::ADDNEWPLAYER; };

	inline Message CreateMessage(HEADER header)
	{
		switch (header)
		{
		case HEADER::HANDLEGAMESTATS: return HandleGameStats{};
		case HEADER::ADDNEWPLAYER: return AddNewPlayer{};
		}
		return HandleGameStats{};
	};
	
}