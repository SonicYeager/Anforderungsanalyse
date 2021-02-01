#pragma once
#include "ConverterLogic.h"

class Converter : public ConverterLogic
{
public:
	std::string TimeToString(std::tm) override;
	std::tm StringToTime(const std::string&) override;
};