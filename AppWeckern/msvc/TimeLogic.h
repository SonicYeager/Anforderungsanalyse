#pragma once
#include <ctime>
#include <functional>
#include "SharedDataTypes.h"

class TimeLogic
{
public:
	virtual void DetermineAlarm(ALARMTYPE, std::function<void()>, std::function<void()>) = 0;
	virtual tm CalculateTimer(tm, tm) = 0;
	virtual ~TimeLogic() = default;
};