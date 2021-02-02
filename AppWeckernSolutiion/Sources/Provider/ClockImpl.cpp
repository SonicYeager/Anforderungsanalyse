#include "ClockImpl.h"
#include "TimesConversion.h"
#include <thread>
#include <chrono>

namespace Wecker
{
	void ClockImpl::Start()
	{
		m_run = true;
		std::thread t([this] {
			while(m_run)
			{
				// compute difference in millisecond to the next second to prevent to run out of sync
				auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
				auto msUntilNextSecond = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration_cast<std::chrono::seconds>(now + 1s) - now);
				std::this_thread::sleep_for(msUntilNextSecond);
				if(not m_run)
					return;
				onNow(Times::Now());
			}
		});
		t.detach();
	}

	void ClockImpl::Stop()
	{
		m_run = false;
	}
} // namespace Wecker
