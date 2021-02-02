#include <gmock/gmock.h>
#include "TimesConversion.h"

using namespace Wecker;
using namespace testing;

class ToStringUT : public TestWithParam<std::tuple<DateTime, std::string>>
{
public:
};

INSTANTIATE_TEST_SUITE_P(TestDateTime, ToStringUT,
						 Values(std::make_tuple(DateTime{}, std::string("00:00:00")),
								std::make_tuple(DateTime{1h, 3min, 5s}, std::string("01:03:05")),
								std::make_tuple(DateTime{0h, 1min}, std::string("00:01:00")),
								std::make_tuple(DateTime{23min, 15s}, std::string("00:23:15")),
								std::make_tuple(DateTime{11h, 5s}, std::string("11:00:05")),
								std::make_tuple(DateTime{1h, 13min}, std::string("01:13:00")),
								std::make_tuple(DateTime{31h, 13min}, std::string("07:13:00"))));

TEST_P(ToStringUT, Convert)
{
	auto [input, expected] = GetParam();

	auto actual = Times::DateToString(input);

	EXPECT_EQ(expected, actual);
}

class FromStringUT : public TestWithParam<std::tuple<std::string, DateTime>>
{
public:
};

INSTANTIATE_TEST_SUITE_P(TestDateTime, FromStringUT,
						 Values(std::make_tuple(std::string(" "), DateTime{}),
								std::make_tuple(std::string("1:30"), DateTime{1h, 30min}),
								std::make_tuple(std::string("1:30:15"), DateTime{1h, 30min, 15s}),
								std::make_tuple(std::string("00:00:15"), DateTime{15s}),
								std::make_tuple(std::string("00:01"), DateTime{1min}),
								std::make_tuple(std::string("1:1"), DateTime{1h, 1min}),
								std::make_tuple(std::string("0:1"), DateTime{1min}),
								std::make_tuple(std::string("0:1:1"), DateTime{1min, 1s}),
								std::make_tuple(std::string("0"), DateTime{0s}),
								std::make_tuple(std::string("01:35"), DateTime{1h, 35min})));

TEST_P(FromStringUT, Convert)
{
	auto [input, expected] = GetParam();

	auto actual = Times::DateFromString(input);

	EXPECT_EQ(expected, actual);
}

class NextUT : public TestWithParam<std::tuple<DateTime, DateTime, DateTime>>
{
public:
};

INSTANTIATE_TEST_SUITE_P(TestDateTime, NextUT,
						 Values(std::make_tuple(DateTime{7h, 30min}, DateTime{12h}, DateTime{12h}),
								std::make_tuple(DateTime{22h}, DateTime{7h, 30min}, DateTime{31h, 30min}),
								std::make_tuple(DateTime{}, DateTime{}, DateTime{}),
								std::make_tuple(DateTime{1s}, DateTime{}, DateTime{24h})));

TEST_P(NextUT, Convert)
{
	auto [source, time, expected] = GetParam();

	auto actual = Times::NextDate(source, time);

	EXPECT_EQ(expected, actual);
}
