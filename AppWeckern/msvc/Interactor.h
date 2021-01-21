#pragma once
#include <string>

class Interactor
{
public:
	virtual std::string InitApp() = 0;
	virtual ~Interactor() = default;
};