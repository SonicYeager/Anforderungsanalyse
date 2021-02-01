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
			if(timerRunning)
			{
				auto time = GetPresentTime();
				onPresentTime(time);
			}
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
