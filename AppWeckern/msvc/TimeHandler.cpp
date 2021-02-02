#include "TimeHandler.h"
#include <ctime>
#include <chrono>

using namespace std::chrono_literals;

#pragma warning(disable : 4996)

tm TimeHandler::GetPresentTime()
{
	time_t now = time(0);
	auto ltm = localtime(&now);

	return *ltm;
}

void TimeHandler::StartTimer()
{
	auto presentTime = [this]() 
	{
		while(timerRunning)
		{
			std::this_thread::sleep_for(1000ms);
			auto time = GetPresentTime();
			if(timerRunning)
				onPresentTime(time);
			if(remainingTimer && timerRunning)
				onRemainingTime(time, wakeTime);
		}
	};

	timerRunning = true;
	timeThread = std::thread(presentTime);
}

void TimeHandler::StopTimer()
{
	timerRunning = false;
	timeThread.join();
}

void TimeHandler::StartAlarmTimer(ALARMTYPE type, tm wakeTime)
{
	aType = type;
	this->wakeTime = wakeTime;
	remainingTimer = true;
}

void TimeHandler::StopAlarmTimer()
{
	remainingTimer = false;
}
