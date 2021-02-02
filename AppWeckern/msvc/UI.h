#pragma once
#include <string>
#include <functional>
#include "SharedDataTypes.h"

class UI
{
public:
	virtual void Init() = 0;
	virtual void SetPresentTime(const std::string&) = 0;
	virtual void SetRemainingTime(const std::string&) = 0;
	virtual ~UI() = default;

	std::function<void()> onInit;
	std::function<void()> onUIReady;
	std::function<void()> onUIShutdown;
	std::function<void(ALARMTYPE, const std::string&)> onStartAlarm;
	std::function<void()> onStopAlarm;
};