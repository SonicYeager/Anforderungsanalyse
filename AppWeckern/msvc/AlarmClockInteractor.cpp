#include "Interactor.h"
#include "AlarmClockInteractor.h"

AlarmClockInteractor::AlarmClockInteractor(TimeRessource* tr, FormatLogic* fl)
	: p_tr(tr)
	, p_fl(fl)
{}

std::string AlarmClockInteractor::InitApp()
{
	auto tm = p_tr->GetPresentTime();
	return p_fl->FormatTime(tm);
}
