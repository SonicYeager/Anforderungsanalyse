#include "Interactor.h"
#include "AlarmClockInteractor.h"
#include <thread>

AlarmClockInteractor::AlarmClockInteractor(TimeLogic* tl, TimeRessource* tr, ConverterLogic* fl)
	: p_tr(tr)
	, p_fl(fl)
	, p_tl(tl)
{
	auto onUpdateTime = [this](tm t) 
	{
		auto formatted = p_fl->TimeToString(t);
		onUpdatePresentTime(formatted);
	};

	auto onUpdateRemaining = [this](tm t, tm waket) 
	{
		tm res{};
		auto onAlarmClock = [this, waket, &res, t]() 
		{
			res = p_tl->CalculateTimer(t, waket); //no idea
		};

		auto onAlarmTimer = [this, waket, &res, t]() 
		{
			auto wakeUpTime = p_tl->SumTime(p_tr->timerStartTime, waket);
			auto calcRemaining = p_tl->CalculateTimer(t, wakeUpTime);
			res = calcRemaining; //has to be calculated
		};

		p_tl->DetermineAlarm(p_tr->aType, onAlarmClock, onAlarmTimer);
		auto result = p_fl->TimeToString(res);
		onUpdateRemainingTime(result);
	};

	p_tr->onPresentTime = onUpdateTime;
	p_tr->onRemainingTime = onUpdateRemaining;
}

void AlarmClockInteractor::StartTimer()
{
	p_tr->StartTimer();
}

void AlarmClockInteractor::StopTimer()
{
	p_tr->StopTimer();
}

std::string AlarmClockInteractor::StartRemainingTimer(ALARMTYPE type, const std::string& wakeTime)
{
	std::string result{};
	tm res{};
	auto converted = p_fl->StringToTime(wakeTime);
	auto onAlarmClock = [this, converted, &res]()
	{
		auto time = p_tr->GetPresentTime();
		res = p_tl->CalculateTimer(time, converted);
	};

	auto onAlarmTimer = [this, converted, &res]() 
	{
		res = converted; 
	};

	p_tl->DetermineAlarm(type, onAlarmClock, onAlarmTimer);
	result = p_fl->TimeToString(res);
	p_tr->StartAlarmTimer(type, res);
	return result;
}

void AlarmClockInteractor::StopRemainingTimer()
{
	p_tr->StopAlarmTimer();
}

std::string AlarmClockInteractor::InitApp()
{
	auto tm = p_tr->GetPresentTime();
	return p_fl->TimeToString(tm);
}
