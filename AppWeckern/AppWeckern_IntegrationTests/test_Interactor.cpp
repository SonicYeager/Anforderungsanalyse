#include "gmock/gmock.h"
#include "AlarmClockInteractor.h"
#include "TimeRessource.h"
#include "Formatter.h"
#include "TimeHandler.h"
#include "UI.h"
#include "TimeOperations.h"

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
		for(size_t i{}; i < 5; ++i)
		{
			auto time = GetPresentTime();
			onPresentTime(time);
		}
	}
	MOCK_METHOD(void, StopTimer, (), (override));
	MOCK_METHOD(void, StartAlarmTimer,(),(override));
};

class FakeUI : public UI
{
public:
	void Init() override
	{
		onUIReady();
	}
	MOCK_METHOD(void, SetPresentTime, (const std::string&), (override));
	~FakeUI()
	{
		onUIShutdown();
	}
};

TEST(TestAlarmClockInteractor, InitApp_1pmflat_Return13colon00colon00)
{
	FakeTimeHandler fth{};
	Formatter f{};
	TimeOperations tr{};
	AlarmClockInteractor aci{&tr, &fth, &f};

	auto actual = aci.InitApp();

	EXPECT_EQ(actual, "13:00:00");
}

TEST(TestAlarmClockInteractor, UpdatePresentTime_1pmflat_CallOnUpdate13colon00colon00)
{
	FakeTimeHandler fth{};
	Formatter f{};
	TimeOperations tr{};
	AlarmClockInteractor aci{&tr, &fth, &f};
	::testing::NiceMock<FakeUI> ui{};
	::testing::InSequence seq{};
	ui.onUIReady = [&aci]() { aci.StartTimer(); };
	ui.onUIShutdown = [&aci]() { aci.StopTimer(); };
	aci.onUpdatePresentTime = [&ui](const std::string& str) { ui.SetPresentTime(str); };
	EXPECT_CALL(ui, SetPresentTime("13:00:00")).Times(::testing::AtLeast(1));

	ui.Init();
}

TEST(TestAlarmClockInteractor, StartRemainingTimer_1pmflatAlarmClockFor3pm_Return02colon00colon00)
{
	FakeTimeHandler fth{};
	Formatter f{};
	TimeOperations tr{};
	AlarmClockInteractor aci{&tr, &fth, &f};
	tm wakeTime{};
	wakeTime.tm_hour = 15;
	wakeTime.tm_min = 0;
	wakeTime.tm_sec = 0;

	auto actual = aci.StartRemainingTimer(ALARMTYPE::ALARMCLOCK, wakeTime);

	EXPECT_EQ(actual, "02:00:00");
}

TEST(TestAlarmClockInteractor, StartRemainingTimer_1pmflatAlarmTimerIn3h_Return03colon00colon00)
{
	FakeTimeHandler fth{};
	Formatter f{};
	TimeOperations tr{};
	AlarmClockInteractor aci{&tr, &fth, &f};
	tm wakeTimer{};
	wakeTimer.tm_hour = 3;
	wakeTimer.tm_min = 0;
	wakeTimer.tm_sec = 0;

	auto actual = aci.StartRemainingTimer(ALARMTYPE::ALARMTIMER, wakeTimer);

	EXPECT_EQ(actual, "03:00:00");
}