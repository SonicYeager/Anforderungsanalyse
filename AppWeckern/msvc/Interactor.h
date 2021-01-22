#pragma once
#include <string>
#include <functional>

class Interactor
{
public:
	virtual std::string InitApp() = 0;
	virtual void UpdatePresentTime(tm) = 0;
	virtual ~Interactor() = default;
};