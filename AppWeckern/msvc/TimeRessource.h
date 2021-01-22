#pragma once
#include <ctime>
#include <functional>

class TimeRessource
{
public:
	virtual tm GetPresentTime() = 0;
	virtual void StartTimer() = 0;
	virtual void StopTimer() = 0;
	virtual ~TimeRessource() = default;

	 std::function<void(tm)> onPresentTime;
};