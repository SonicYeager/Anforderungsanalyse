#pragma once

#include "Times.h"
#include "Event.h"

namespace Wecker
{
	class Clock
	{
	public:
		virtual void Start() = 0;
		virtual void Stop() = 0;

		Event<DateTime> onNow;

		virtual ~Clock() = default;
	};
} // namespace Wecker
