#include "gmock/gmock.h"
#include "AlarmClockInteractor.h"
#include "TimeRessource.h"
#include "Formatter.h"
#include "TimeHandler.h"

class FakeTimeHandler : public TimeRessource
{
public:
	tm GetPresentTime() override
	{
		std::tm time{};
		time.tm_hour = 13;
		time.tm_min = 0;
		time.tm_sec = 0;
		return time;
	}
	void StartTimer() override
	{

	}
	void StopTimer() override
	{

	}
};

class FakeUI
{
public:
	MOCK_METHOD(void, OnUpdate, (const std::string&));
	MOCK_METHOD(bool, OnIsActive, ());
};

TEST(TestAlarmClockInteractor, InitApp_1pmflat_Return13colon00colon00)
{
	FakeTimeHandler fth{};
	Formatter f{};
	AlarmClockInteractor aci{&fth, &f};

	auto actual = aci.InitApp();

	EXPECT_EQ(actual, "13:00:00");
}

TEST(TestAlarmClockInteractor, UpdatePresentTime_1pmflat_CallOnUpdate13colon00colon00)
{
	FakeTimeHandler fth{};
	Formatter f{};
	AlarmClockInteractor aci{&fth, &f};
	::testing::NiceMock<FakeUI> ui{};
	EXPECT_CALL(ui, OnUpdate("13:00:00"));
	EXPECT_CALL(ui, OnIsActive()).WillOnce(::testing::Return(true)).WillOnce(::testing::Return(false));

	aci.UpdatePresentTime();
}

TEST(TestAlarmClockInteractor, UpdatePresentTime_SingleOnUpdateCall_CallOnIsActiveCalledTwice)
{
	FakeTimeHandler fth{};
	Formatter f{};
	AlarmClockInteractor aci{&fth, &f};
	::testing::InSequence seq;
	::testing::NiceMock<FakeUI> ui{};
	EXPECT_CALL(ui, OnIsActive()).WillOnce(::testing::Return(true));
	EXPECT_CALL(ui, OnIsActive()).WillOnce(::testing::Return(false));

	aci.UpdatePresentTime();
}