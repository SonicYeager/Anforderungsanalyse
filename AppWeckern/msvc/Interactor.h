#pragma once
#include <string>
#include <functional>

class Interactor
{
public:
	virtual std::string InitApp() = 0;
	virtual void StartTimer() = 0;
	virtual void StopTimer() = 0;
	virtual ~Interactor() = default;

	std::function<void(const std::string&)> onUpdatePresentTime;
};