#pragma once
#include <variant>
#include "DataTypes.h"

namespace Messages
{
	//code data messages here if there are any packages
	struct HandleGameStats {};
	struct Alternative {};

	using Message = std::variant<Alternative, HandleGameStats>;
}