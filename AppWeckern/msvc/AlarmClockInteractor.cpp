#include "Interactor.h"
#include "AlarmClockInteractor.h"
#include <thread>

AlarmClockInteractor::AlarmClockInteractor(TimeLogic* tl, TimeRessource* tr, FormatLogic* fl)
	: p_tr(tr)
	, p_fl(fl)
	, p_tl(tl)
{
	auto onUpdate = [this](tm t) 
	{
		auto formatted = p_fl->FormatTime(t);
		onUpdatePresentTime(formatted);
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

std::string AlarmClockInteractor::StartRemainingTimer(ALARMTYPE type, const tm& wakeTime)
{
	std::string result;
	auto onAlarmClock = [this, wakeTime, &result]()
	{
		auto time = p_tr->GetPresentTime();
		auto res = p_tl->CalculateTimer(time, wakeTime);
		result = p_fl->FormatTime(res);
	};

	auto onAlarmTimer = [this, wakeTime, &result]() { result = p_fl->FormatTime(wakeTime); };

	p_tl->DetermineAlarm(type, onAlarmClock, onAlarmTimer);
	return result;
}

std::string AlarmClockInteractor::InitApp()
{
	auto tm = p_tr->GetPresentTime();
	return p_fl->FormatTime(tm);
}
