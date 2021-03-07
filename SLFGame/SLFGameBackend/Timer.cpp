#pragma once
#include "Timer.h"
#include <chrono>

using namespace std::chrono_literals;

Timer::Timer()
{
	timer.setTimerType(Qt::PreciseTimer);
	timer.setInterval(1000ms);
	timer.callOnTimeout(timeout);
}

void Timer::Start()
{
	timer.start();
}

void Timer::Stop()
{
	timer.stop();
}
