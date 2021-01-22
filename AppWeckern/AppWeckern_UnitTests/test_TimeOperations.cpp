#include "gmock/gmock.h"
#include "TimeOperations.h"

struct FakeCallee
{
	MOCK_METHOD(void, OnAlarmClock, ());
	MOCK_METHOD(void, OnAlarmTimer, ());
};

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

TEST(TestTimeOperations, CalculateTimer_13pmFlatActualTime15pmWakeTime_Return2hTimer)
{
	TimeOperations to{};
	tm actualTime{};
	actualTime.tm_hour = 13;
	tm wakeTime{};
	wakeTime.tm_hour = 15;
	tm expected{};
	expected.tm_hour = 2;

	auto actual = to.CalculateTimer(actualTime, wakeTime);

	EXPECT_EQ(actual.tm_hour, expected.tm_hour);
}

TEST(TestTimeOperations, CalculateTimer_13pmFlatActualTime8amWakeTimeNextDay_Return19hTimer)
{
	TimeOperations to{};
	tm actualTime{};
	actualTime.tm_hour = 13;
	tm wakeTime{};
	wakeTime.tm_hour = 8;
	tm expected{};
	expected.tm_hour = 19;

	auto actual = to.CalculateTimer(actualTime, wakeTime);

	EXPECT_EQ(actual.tm_hour, expected.tm_hour);
}

TEST(TestTimeOperations, CalculateTimer_13pm15min30secActualTime14am30min00secWakeTimeNextDay_Return1h14min30secTimer)
{
	TimeOperations to{};
	tm actualTime{};
	actualTime.tm_hour = 13;
	actualTime.tm_min = 15;
	actualTime.tm_sec = 30;
	tm wakeTime{};
	wakeTime.tm_hour = 14;
	wakeTime.tm_min = 30;
	tm expected{};
	expected.tm_hour = 1;
	expected.tm_min = 14;
	expected.tm_sec = 30;

	auto actual = to.CalculateTimer(actualTime, wakeTime);

	EXPECT_EQ(actual.tm_hour, expected.tm_hour);
}