#include "gmock/gmock.h"
#include "TimeOperations.h"
#include <ostream>

inline std::ostream& operator<<(std::ostream& os, const tm& time)
{
	return os << std::to_string(time.tm_hour) << ":" << std::to_string(time.tm_min) << ":" << std::to_string(time.tm_sec);
}

struct FakeCallee
{
	MOCK_METHOD(void, OnAlarmClock, ());
	MOCK_METHOD(void, OnAlarmTimer, ());
};

inline bool operator==(const tm& left, const tm& right)
{
	return left.tm_hour == right.tm_hour && left.tm_min == right.tm_min && left.tm_sec == right.tm_sec;
}

TEST(TestTimeOperations, DetermineAlarm_ALARMTYPEIsAlarmClock_CallOnAlarmClock)
{
	TimeOperations to{};
	::testing::StrictMock<FakeCallee> fc{};
	EXPECT_CALL(fc, OnAlarmClock());

	to.DetermineAlarm(ALARMTYPE::ALARMCLOCK, [&fc] {fc.OnAlarmClock();}, [&fc] {fc.OnAlarmTimer();});
}

TEST(TestTimeOperations, DetermineAlarm_ALARMTYPEIsAlarmTimer_CallOnAlarmTimer)
{
	TimeOperations to{};
	::testing::StrictMock<FakeCallee> fc{};
	EXPECT_CALL(fc, OnAlarmTimer());

	to.DetermineAlarm(
		ALARMTYPE::ALARMTIMER, [&fc] { fc.OnAlarmClock(); }, [&fc] { fc.OnAlarmTimer(); });
}

TEST(TestTimeOperations, CalculateTimer_13pmFlatActualTime15pmWakeTime_Return2h)
{
	TimeOperations to{};
	tm actualTime{};
	actualTime.tm_hour = 13;
	actualTime.tm_min = 0;
	actualTime.tm_sec = 0;
	tm wakeTime{};
	wakeTime.tm_hour = 15;
	wakeTime.tm_min = 0;
	wakeTime.tm_sec = 0;
	tm expected{};
	expected.tm_hour = 2;
	expected.tm_min = 0;
	expected.tm_sec = 0;

	auto actual = to.CalculateTimer(actualTime, wakeTime);

	EXPECT_EQ(actual, expected);
}

TEST(TestTimeOperations, CalculateTimer_13pmFlatActualTime8amWakeTimeNextDay_Return19h)
{
	TimeOperations to{};
	tm actualTime{};
	actualTime.tm_hour = 13;
	actualTime.tm_min = 0;
	actualTime.tm_sec = 0;
	tm wakeTime{};
	wakeTime.tm_hour = 8;
	wakeTime.tm_min = 0;
	wakeTime.tm_sec = 0;
	tm expected{};
	expected.tm_hour = 19;
	expected.tm_min = 0;
	expected.tm_sec = 0;

	auto actual = to.CalculateTimer(actualTime, wakeTime);

	EXPECT_EQ(actual, expected);
}

TEST(TestTimeOperations, CalculateTimer_13pm15min30secActualTime14am30min00secWakeTime_Return1h14min30sec)
{
	TimeOperations to{};
	tm actualTime{};
	actualTime.tm_hour = 13;
	actualTime.tm_min = 15;
	actualTime.tm_sec = 30;
	tm wakeTime{};
	wakeTime.tm_hour = 14;
	wakeTime.tm_min = 30;
	wakeTime.tm_sec = 00;
	tm expected{};
	expected.tm_hour = 1;
	expected.tm_min = 14;
	expected.tm_sec = 30;

	auto actual = to.CalculateTimer(actualTime, wakeTime);

	EXPECT_EQ(actual, expected);
}

TEST(TestTimeOperations, CalculateTimer_15pm00min00secActualTime7am30min00secWakeTimeNextDay_Return16h30min00sec)
{
	TimeOperations to{};
	tm actualTime{};
	actualTime.tm_hour = 15;
	actualTime.tm_min = 14;
	actualTime.tm_sec = 00;
	tm wakeTime{};
	wakeTime.tm_hour = 07;
	wakeTime.tm_min = 30;
	wakeTime.tm_sec = 00;
	tm expected{};
	expected.tm_hour = 16;
	expected.tm_min = 16;
	expected.tm_sec = 00;

	auto actual = to.CalculateTimer(actualTime, wakeTime);

	EXPECT_EQ(actual, expected);
}

TEST(TestTimeOperations, CalculateTimer_14pm58min00secActualTime17am00min00secWakeUpTime_Return2h2min0sec)
{
	TimeOperations to{};
	tm actualTime{};
	actualTime.tm_hour = 14;
	actualTime.tm_min = 58;
	actualTime.tm_sec = 00;
	tm wakeTime{};
	wakeTime.tm_hour = 17;
	wakeTime.tm_min = 00;
	wakeTime.tm_sec = 00;
	tm expected{};
	expected.tm_hour = 02;
	expected.tm_min = 02;
	expected.tm_sec = 00;

	auto actual = to.CalculateTimer(actualTime, wakeTime);

	EXPECT_EQ(actual, expected);
}

TEST(TestTimeOperations, SumTime_10pm30min30secActualTime2am30min00secWakeUpTime_Return13h00min30sec)
{
	TimeOperations to{};
	tm actualTime{};
	actualTime.tm_hour = 10;
	actualTime.tm_min = 30;
	actualTime.tm_sec = 30;
	tm wakeTime{};
	wakeTime.tm_hour = 2;
	wakeTime.tm_min = 30;
	wakeTime.tm_sec = 00;
	tm expected{};
	expected.tm_hour = 13;
	expected.tm_min = 00;
	expected.tm_sec = 30;

	auto actual = to.SumTime(actualTime, wakeTime);

	EXPECT_EQ(actual, expected);
}