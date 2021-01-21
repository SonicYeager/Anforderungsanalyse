#pragma once
#include <string>
#include "TimeRessource.h"
#include "FormatLogic.h"
#include "Interactor.h"

class AlarmClockInteractor : public Interactor
{
public:
	AlarmClockInteractor(TimeRessource*, FormatLogic*); //UI?? - No
	std::string InitApp();

private:
	TimeRessource* p_tr;
	FormatLogic* p_fl;
};