#include "Converter.h"

std::string Converter::TimeToString(std::tm ltm)
{
	std::string presentTime{};
	presentTime += ltm.tm_hour < 10 ? "0" + std::to_string(ltm.tm_hour) + ":" : std::to_string(ltm.tm_hour) + ":";
	presentTime += ltm.tm_min < 10 ? "0" + std::to_string(ltm.tm_min) + ":" : std::to_string(ltm.tm_min) + ":";
	presentTime += ltm.tm_sec < 10 ? "0" + std::to_string(ltm.tm_sec) : std::to_string(ltm.tm_sec);
	return presentTime;
}

std::tm Converter::StringToTime(const std::string& time)
{
	auto hpart = time.substr(0, time.find(":"));
	auto mpart = time.substr(time.find(":")+1);
	tm result{};
	result.tm_hour = std::stoi(hpart);
	result.tm_min = std::stoi(mpart);
	result.tm_sec = 00;
	return result;
}
