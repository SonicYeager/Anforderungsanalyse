#pragma once
#include "FormatLogic.h"

class Formatter : public FormatLogic
{
public:
	std::string FormatTime(std::tm*) override;
};