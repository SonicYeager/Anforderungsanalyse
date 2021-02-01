#pragma once
#include <string>
#include "TimeRessource.h"
#include "ConverterLogic.h"
#include "Interactor.h"
#include "TimeLogic.h"

class AlarmClockInteractor : public Interactor
{
public:
	explicit AlarmClockInteractor(TimeLogic*, TimeRessource*, ConverterLogic*);
	void StartTimer() override;
	void StopTimer() override;
	std::string StartRemainingTimer(ALARMTYPE, const std::string&) override;
	std::string InitApp() override;

private:
	TimeRessource* p_tr;
	TimeLogic* p_tl;
	ConverterLogic* p_fl;
};