#pragma once
#include <functional>

namespace Wecker
{
	template<typename... Args>
	using Event = std::function<void(Args...)>;
}
