#include "TimeOperations.h"

void TimeOperations::DetermineAlarm(ALARMTYPE type, std::function<void()> onAlarmClock, std::function<void()> onAlarmTimer)
{
	if(type == ALARMTYPE::ALARMCLOCK)
		onAlarmClock();
	else
		onAlarmTimer();
}

tm TimeOperations::CalculateTimer(tm, tm)
{
	return tm();
}
