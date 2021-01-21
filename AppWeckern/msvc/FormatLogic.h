#pragma once
#include <ctime>
#include <string>

class FormatLogic
{
public:
	virtual std::string FormatTime(std::tm) = 0;
	virtual ~FormatLogic() = default;
};
