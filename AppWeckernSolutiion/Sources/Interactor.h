#pragma once
#include "Event.h"
#include "Times.h"

namespace Wecker
{
	class Clock;
	class Watchdog;
	class SoundPlayer;

	class Interactor
	{
	public:
		Interactor(Clock*, Watchdog*, SoundPlayer*);

		void SetWithRestTime(const TimeSpan& dur);
		void SetWithWackupTime(const DateTime& date);
		void StartTimer();
		void StopTimer();
		void Stop();

		Event<DateTime> onNow;
		Event<TimeSpan> onRemainingTime;

		Clock* m_pClock;
		Watchdog* m_pWatchdog;
		SoundPlayer* m_pPlayer;
	};
} // namespace Wecker
