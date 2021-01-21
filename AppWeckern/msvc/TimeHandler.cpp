#include "TimeHandler.h"
#include <ctime>

#pragma warning(disable : 4996)

tm* TimeHandler::GetPresentTime()
{
	time_t now = time(0);
	auto ltm = localtime(&now);

	return ltm;
}
