#include "Watchdog.h"
#include "TimesConversion.h"

namespace Wecker
{
	void Watchdog::SetWithWackupTime(const DateTime& timeOfDay)
	{
		m_wackup = Times::NextDate(m_now, timeOfDay);
		m_running = true;
		onRemainingTime(std::max(TimeSpan(0s), m_wackup - m_now));
	}
	void Watchdog::SetWithRestTime(const TimeSpan& s)
	{
		m_wackup = m_now + s;
		m_running = true;
		onRemainingTime(s);
	}
	void Watchdog::UpdateWithCurrentTime(const DateTime& t)
	{
		m_now = t;
		if(m_running)
		{
			auto diff = m_wackup - t;
			if(TimeSpan(1s) < diff)
			{
				onRemainingTime(diff);
			}
			else
			{
				onRemainingTime({});
				onWackupTimeReached();
				m_running = false;
			}
		}
	}
	void Watchdog::Stop()
	{
		m_running = false;
	}
} // namespace Wecker
