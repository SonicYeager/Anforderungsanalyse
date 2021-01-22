#pragma once
#include <string>
#include "TimeRessource.h"
#include "FormatLogic.h"
#include "Interactor.h"

class AlarmClockInteractor : public Interactor
{
public:
	explicit AlarmClockInteractor(TimeRessource*, FormatLogic*);
	std::string InitApp() override;
	void UpdatePresentTime(tm) override;

private:
	TimeRessource* p_tr;
	FormatLogic* p_fl;
};