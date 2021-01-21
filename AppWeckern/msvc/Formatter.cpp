#include "Formatter.h"

std::string Formatter::FormatTime(std::tm ltm)
{
	std::string presentTime{};
	presentTime += ltm.tm_hour < 10 ? "0" + std::to_string(ltm.tm_hour) + ":" : std::to_string(ltm.tm_hour) + ":";
	presentTime += ltm.tm_min < 10 ? "0" + std::to_string(ltm.tm_min) + ":" : std::to_string(ltm.tm_min) + ":";
	presentTime += ltm.tm_sec < 10 ? "0" + std::to_string(ltm.tm_sec) : std::to_string(ltm.tm_sec);
	return presentTime;
}
