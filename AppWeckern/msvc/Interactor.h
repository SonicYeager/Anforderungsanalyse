#pragma once
#include <string>
#include <functional>
#include <ctime>
#include "SharedDataTypes.h"

class Interactor
{
public:
	virtual std::string InitApp() = 0;
	virtual void StartTimer() = 0;
	virtual void StopTimer() = 0;
	virtual std::string StartRemainingTimer(ALARMTYPE, const std::string&) = 0;
	virtual ~Interactor() = default;

	std::function<void(const std::string&)> onUpdatePresentTime;
};