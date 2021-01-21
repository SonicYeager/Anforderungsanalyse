#include "TimeHandler.h"
#include <ctime>

#pragma warning(disable : 4996)

std::string TimeHandler::GetPresentTime()
{
	std::string presentTime = "";
	time_t now = time(0);
	tm* ltm = localtime(&now);

	presentTime += std::to_string(ltm->tm_hour) + ":";
	presentTime += std::to_string(ltm->tm_min) + ":";
	presentTime += std::to_string(ltm->tm_sec);

	return presentTime;
}
