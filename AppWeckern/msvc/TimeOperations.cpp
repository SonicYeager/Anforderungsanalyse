#include "TimeOperations.h"

void TimeOperations::DetermineAlarm(ALARMTYPE type, std::function<void()> onAlarmClock, std::function<void()> onAlarmTimer)
{
	if(type == ALARMTYPE::ALARMCLOCK)
		onAlarmClock();
	else
		onAlarmTimer();
}

bool operator<(const tm& left, const tm& right)
{
	if(left.tm_hour < right.tm_hour)
		return true;
	if(left.tm_hour == right.tm_hour && left.tm_min < right.tm_min)
		return true;
	if(left.tm_hour == right.tm_hour && left.tm_min == right.tm_min && left.tm_sec < right.tm_sec)
		return true;
	return false;
}

tm operator-(const tm& left, const tm& right)
{
	tm res{};
	res.tm_hour = left.tm_hour - right.tm_hour;
	res.tm_min = left.tm_min - right.tm_min;
	res.tm_sec = left.tm_sec - right.tm_sec;
	if(res.tm_sec < 0)
	{
		res.tm_sec += 60;
		--res.tm_min;
	}
	if(res.tm_min < 0)
	{
		res.tm_min += 60;
		--res.tm_hour;
	}
	return res;
}

tm operator+(const tm& left, const tm& right)
{
	tm res{};
	res.tm_hour = left.tm_hour + right.tm_hour;
	res.tm_min = left.tm_min + right.tm_min;
	res.tm_sec = left.tm_sec + right.tm_sec;
	if(res.tm_sec > 60)
	{
		res.tm_sec -= 60;
		++res.tm_min;
	}
	if(res.tm_min > 60)
	{
		res.tm_min -= 60;
		++res.tm_hour;
	}
	return res;
}

tm TimeOperations::CalculateTimer(tm actualTime, tm wakeTime)
{
	tm result = actualTime;
	if(actualTime < wakeTime)
	{
		result = wakeTime - actualTime;
	}
	else
	{
		tm fullDay{};
		fullDay.tm_hour = 24;
		result = (fullDay - actualTime) + wakeTime;
	}
	return result;
}
