#pragma once

#include "Times.h"
#include "Event.h"

namespace Wecker
{
	class Watchdog
	{
	public:
		void SetWithWackupTime(const DateTime&);
		void SetWithRestTime(const TimeSpan&);
		void UpdateWithCurrentTime(const DateTime&);
		void Stop();

		Event<TimeSpan> onRemainingTime;
		Event<> onWackupTimeReached;

	private:
		DateTime m_now = {};
		DateTime m_wackup = {};
		bool m_running = false;
	};
} // namespace Wecker
