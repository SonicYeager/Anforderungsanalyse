#pragma once
#include <ctime>
#include <functional>
#include "SharedDataTypes.h"

class TimeRessource
{
public:
	virtual tm GetPresentTime() = 0;
	virtual void StartTimer() = 0;
	virtual void StopTimer() = 0;
	virtual void StartAlarmTimer(ALARMTYPE, tm) = 0;
	virtual void StopAlarmTimer() = 0;
	virtual void StartAlarmSound() = 0;
	virtual void StopAlarmSound() = 0;
	virtual ~TimeRessource() = default;

	ALARMTYPE aType;
	tm wakeTime{};
	tm timerStartTime{};
	bool remainingTimer = false;
	std::function<void(tm)> onPresentTime;
	std::function<void(tm, tm)> onRemainingTime;
	std::function<void()> onAlarm;
};