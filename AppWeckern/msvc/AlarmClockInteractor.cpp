#include "Interactor.h"
#include "AlarmClockInteractor.h"
#include <thread>

AlarmClockInteractor::AlarmClockInteractor(TimeRessource* tr, FormatLogic* fl)
	: p_tr(tr)
	, p_fl(fl)
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

std::string AlarmClockInteractor::InitApp()
{
	auto tm = p_tr->GetPresentTime();
	return p_fl->FormatTime(tm);
}
