#pragma once
#include <string>
#include <functional>

class UI
{
public:
	virtual void Init() = 0;
	virtual void SetPresentTime(const std::string&) = 0;
	virtual bool IsActive() = 0;
	virtual ~UI() = default;

	std::function<void()> onInit;
	std::function<void()> onStartUpdatePresentTime;
};