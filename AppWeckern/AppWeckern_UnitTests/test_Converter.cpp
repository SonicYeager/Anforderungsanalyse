#include "gmock/gmock.h"
#include "../msvc/Converter.h"

TEST(TestFormatter, FormatTime_10am40min30sec_ReturnFormattedHHMMSS104020)
{
	Converter f{};
	std::tm time{};
	time.tm_hour = 10;
	time.tm_min = 40;
	time.tm_sec = 30;

	auto actual = f.TimeToString(time);

	EXPECT_EQ(actual, "10:40:30");
}

TEST(TestFormatter, FormatTime_00am02min59sec_ReturnFormattedHHMMSS000259)
{
	Converter f{};
	std::tm time{};
	time.tm_hour = 0;
	time.tm_min = 2;
	time.tm_sec = 59;

	auto actual = f.TimeToString(time);

	EXPECT_EQ(actual, "00:02:59");
}

TEST(TestFormatter, FormatTime_00am00min00sec_ReturnFormattedHHMMSS000000)
{
	Converter f{};
	std::tm time{};
	time.tm_hour = 00;
	time.tm_min = 00;
	time.tm_sec = 00;

	auto actual = f.TimeToString(time);

	EXPECT_EQ(actual, "00:00:00");
}