#pragma once
#include <string>
#include "TimeRessource.h"
#include "FormatLogic.h"

class AlarmClockInteractor
{
public:
	AlarmClockInteractor(TimeRessource*, FormatLogic*); //UI?? - No
	std::string InitApp();

private:
	TimeRessource* p_tr;
	FormatLogic* p_fl;
};