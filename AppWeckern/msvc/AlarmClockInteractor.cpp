#include "Interactor.h"
#include "AlarmClockInteractor.h"
#include <thread>

AlarmClockInteractor::AlarmClockInteractor(TimeLogic* tl, TimeRessource* tr, ConverterLogic* fl)
	: p_tr(tr)
	, p_fl(fl)
	, p_tl(tl)
{
	auto onUpdate = [this](tm t) 
	{
		auto formatted = p_fl->TimeToString(t);
		onUpdatePresentTime(formatted);
		//remaining time (bool controlled)
	};
	p_tr->onPresentTime = onUpdate;
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
	return result;
}

std::string AlarmClockInteractor::InitApp()
{
	auto tm = p_tr->GetPresentTime();
	return p_fl->TimeToString(tm);
}
