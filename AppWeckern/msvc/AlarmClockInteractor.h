#pragma once
#include <string>
#include "TimeRessource.h"
#include "FormatLogic.h"
#include "Interactor.h"
#include "TimeLogic.h"

class AlarmClockInteractor : public Interactor
{
public:
	explicit AlarmClockInteractor(TimeLogic*, TimeRessource*, FormatLogic*);
	void StartTimer() override;
	void StopTimer() override;
	std::string StartRemainingTimer(ALARMTYPE, const tm&) override;
	std::string InitApp() override;

private:
	TimeRessource* p_tr;
	TimeLogic* p_tl;
	FormatLogic* p_fl;
};