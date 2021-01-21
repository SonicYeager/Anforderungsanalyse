#pragma once
#include <ctime>

class TimeRessource
{
public:
	virtual tm* GetPresentTime() = 0;
};