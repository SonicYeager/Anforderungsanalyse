#pragma once
#include "TimeLogic.h"

class TimeOperations : public TimeLogic
{
public:
	void DetermineAlarm(ALARMTYPE, std::function<void()>, std::function<void()>) override;
	tm CalculateTimer(tm, tm) override;
	tm SumTime(tm, tm) override;
};