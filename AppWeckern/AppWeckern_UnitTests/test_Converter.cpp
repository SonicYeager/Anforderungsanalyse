#include "gmock/gmock.h"
#include "../msvc/Converter.h"

inline bool operator==(const tm& left, const tm& right)
{
	return left.tm_hour == right.tm_hour && left.tm_min == right.tm_min && left.tm_sec == right.tm_sec;
}

inline std::ostream& operator<<(std::ostream& os, const tm& time)
{
	return os << std::to_string(time.tm_hour) << ":" << std::to_string(time.tm_min) << ":" << std::to_string(time.tm_sec);
}

TEST(TestConverter, TimeToString_10am40min30sec_ReturnConvertedHHMMSS104020)
{
	Converter f{};
	std::tm time{};
	time.tm_hour = 10;
	time.tm_min = 40;
	time.tm_sec = 30;

	auto actual = f.TimeToString(time);

	EXPECT_EQ(actual, "10:40:30");
}

TEST(TestConverter, TimeToString_00am02min59sec_ReturnConvertedHHMMSS000259)
{
	Converter f{};
	std::tm time{};
	time.tm_hour = 0;
	time.tm_min = 2;
	time.tm_sec = 59;

	auto actual = f.TimeToString(time);

	EXPECT_EQ(actual, "00:02:59");
}

TEST(TestConverter, TimeToString_00am00min00sec_ReturnConvertedHHMMSS000000)
{
	Converter f{};
	std::tm time{};
	time.tm_hour = 00;
	time.tm_min = 00;
	time.tm_sec = 00;

	auto actual = f.TimeToString(time);

	EXPECT_EQ(actual, "00:00:00");
}

TEST(TestConverter, StringToTime_HHMMSS1040_ReturnConverted10am40min00sec)
{
	Converter f{};
	std::string time{"10:40"};

	auto actual = f.StringToTime(time);

	tm expected{};
	expected.tm_hour = 10;
	expected.tm_min = 40;
	expected.tm_sec = 00;
	EXPECT_EQ(actual, expected);
}

TEST(TestConverter, StringToTime_HMM730_ReturnConverted7am30min00sec)
{
	Converter f{};
	std::string time{"7:30"};

	auto actual = f.StringToTime(time);

	tm expected{};
	expected.tm_hour = 07;
	expected.tm_min = 30;
	expected.tm_sec = 00;
	EXPECT_EQ(actual, expected);
}

TEST(TestConverter, StringToTime_HHMMSS000200_ReturnConverted00am02min00sec)
{
	Converter f{};
	std::string time{"0:02"};

	auto actual = f.StringToTime(time);

	tm expected{};
	expected.tm_hour = 00;
	expected.tm_min = 02;
	expected.tm_sec = 00;
	EXPECT_EQ(actual, expected);
}

TEST(TestConverter, StringToTime_HHMMSS000000_ReturnConverted00am00min00sec)
{
	Converter f{};
	std::string time{"0:0"};

	auto actual = f.StringToTime(time);

	tm expected{};
	expected.tm_hour = 00;
	expected.tm_min = 00;
	expected.tm_sec = 00;
	EXPECT_EQ(actual, expected);
}