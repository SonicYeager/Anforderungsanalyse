#pragma once
#include <chrono>
#include <string>
#include <thread>
#include "TimeRessource.h"

class TimeHandler : public TimeRessource
{
public:
	tm GetPresentTime() override;
	void StartTimer() override;
	void StopTimer() override;

private:
	bool timerRunning{};
	std::thread timeThread;
};
