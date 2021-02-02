#pragma once
#include "Times.h"
#include "Event.h"

namespace Wecker
{
	class UI
	{
	public:
		virtual void SetRemainingTime(const TimeSpan&) = 0;
		virtual void SetCurrentTime(const DateTime&) = 0;
		virtual void Start() = 0;

		Event<DateTime> onStartWithWackupTime;
		Event<TimeSpan> onStartWithRestTime;
		Event<> onStopped;
		Event<> onReady;
		Event<> onClose;

		virtual ~UI() = default;
	};
} // namespace Wecker
