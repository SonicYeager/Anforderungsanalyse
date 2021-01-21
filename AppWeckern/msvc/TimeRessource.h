#pragma once
#include <ctime>

class TimeRessource
{
public:
	virtual tm* GetPresentTime() = 0;
	virtual ~TimeRessource() = default;
};