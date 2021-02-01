#pragma once
#include <ctime>
#include <string>

class ConverterLogic
{
public:
	virtual std::string TimeToString(std::tm) = 0;
	virtual std::tm StringToTime(const std::string&) = 0;
	virtual ~ConverterLogic() = default;
};
