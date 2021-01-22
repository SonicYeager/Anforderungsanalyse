#include "TimeHandler.h"
#include <ctime>
#include <thread>
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
			onPresentTime(time);
		}
	};

	timerRunning = true;
	auto thread = std::thread(presentTime);
	thread.detach();
}

void TimeHandler::StopTimer()
{
	timerRunning = false;
}
