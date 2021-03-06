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
			if(alarmRunning && timerRunning)
				onAlarm();
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
	timerStartTime = GetPresentTime();
	remainingTimer = true;
}

void TimeHandler::StopAlarmTimer()
{
	remainingTimer = false;
}

void TimeHandler::StartAlarmSound()
{
	alarmRunning = true;
}

void TimeHandler::StopAlarmSound()
{
	alarmRunning = false;
}
