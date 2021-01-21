#pragma once
#include <string>

class UI
{
public:
	virtual void Init() = 0;
	virtual void SetPresentTime(const std::string&) = 0;
};