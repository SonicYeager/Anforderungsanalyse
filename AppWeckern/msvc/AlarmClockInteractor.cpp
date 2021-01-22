#include "Interactor.h"
#include "AlarmClockInteractor.h"
#include <thread>

AlarmClockInteractor::AlarmClockInteractor(TimeRessource* tr, FormatLogic* fl)
	: p_tr(tr)
	, p_fl(fl)
{
	auto onUpdate = [this](tm t) { UpdatePresentTime(t); };
	p_tr->onPresentTime = onUpdate;
	//p_tr->Start();??
}

std::string AlarmClockInteractor::InitApp()
{
	auto tm = p_tr->GetPresentTime();
	return p_fl->FormatTime(tm);
}

void AlarmClockInteractor::UpdatePresentTime(tm t)
{
	//auto tm = p_tr->GetPresentTime();
	//auto newTimeStr = p_fl->FormatTime(tm);
	//onUpdate(newTimeStr);
}
