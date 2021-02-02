#include "gmock/gmock.h"
#include "AlarmClockInteractor.h"
#include "TimeRessource.h"
#include "Converter.h"
#include "TimeHandler.h"
#include "UI.h"
#include "TimeOperations.h"
#include "SharedDataTypes.h"

inline bool operator==(const tm& left, const tm& right)
{
	return left.tm_hour == right.tm_hour && left.tm_min == right.tm_min && left.tm_sec == right.tm_sec;
}

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
	MOCK_METHOD(void, StartAlarmTimer, (ALARMTYPE, tm), (override));
	MOCK_METHOD(void, StopAlarmTimer, (), (override));
};

class FakeUI : public UI
{
public:
	void Init() override
	{
		onUIReady();
	}
	MOCK_METHOD(void, SetPresentTime, (const std::string&), (override));
	MOCK_METHOD(void, SetRemainingTime, (const std::string&), (override));
	~FakeUI()
	{
		onUIShutdown();
	}
};

TEST(TestAlarmClockInteractor, InitApp_1pmflat_Return13colon00colon00)
{
	FakeTimeHandler fth{};
	Converter f{};
	TimeOperations tr{};
	AlarmClockInteractor aci{&tr, &fth, &f};

	auto actual = aci.InitApp();

	EXPECT_EQ(actual, "13:00:00");
}

TEST(TestAlarmClockInteractor, UpdatePresentTime_1pmflat_CallOnUpdate13colon00colon00)
{
	FakeTimeHandler fth{};
	Converter f{};
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
	Converter f{};
	TimeOperations tr{};
	AlarmClockInteractor aci{&tr, &fth, &f};
	std::string wakeTime{"15:00"};

	auto actual = aci.StartRemainingTimer(ALARMTYPE::ALARMCLOCK, wakeTime);

	EXPECT_EQ(actual, "02:00:00");
}

TEST(TestAlarmClockInteractor, StartRemainingTimer_1pmflatAlarmTimerIn3h_Return03colon00colon00)
{
	FakeTimeHandler fth{};
	Converter f{};
	TimeOperations tr{};
	AlarmClockInteractor aci{&tr, &fth, &f};
	std::string wakeTimer{"3:00"};

	auto actual = aci.StartRemainingTimer(ALARMTYPE::ALARMTIMER, wakeTimer);

	EXPECT_EQ(actual, "03:00:00");
}

TEST(TestAlarmClockInteractor, StartRemainingTimer_StartAlarmTimerIsCalled_CalledOnceWith3h)
{
	::testing::NiceMock<FakeTimeHandler> fth{};
	Converter f{};
	TimeOperations tr{};
	AlarmClockInteractor aci{&tr, &fth, &f};
	std::string wakeTimer{"3:00"};
	tm wakeTimertm{};
	wakeTimertm.tm_hour = 3;
	wakeTimertm.tm_min = 0;
	wakeTimertm.tm_sec = 0;
	EXPECT_CALL(fth, StartAlarmTimer(ALARMTYPE::ALARMTIMER, wakeTimertm)).Times(1);

	auto actual = aci.StartRemainingTimer(ALARMTYPE::ALARMTIMER, wakeTimer);
}

TEST(TestAlarmClockInteractor, StartRemainingTimer_StopAlarmTimerIsCalled_CalledOnce)
{
	::testing::NiceMock<FakeTimeHandler> fth{};
	Converter f{};
	TimeOperations tr{};
	AlarmClockInteractor aci{&tr, &fth, &f};
	std::string wakeTimer{"3:00"};
	tm wakeTimertm{};
	wakeTimertm.tm_hour = 3;
	wakeTimertm.tm_min = 0;
	wakeTimertm.tm_sec = 0;
	EXPECT_CALL(fth, StartAlarmTimer(ALARMTYPE::ALARMTIMER, wakeTimertm)).Times(1);
	EXPECT_CALL(fth, StopAlarmTimer()).Times(1);

	auto actual = aci.StartRemainingTimer(ALARMTYPE::ALARMTIMER, wakeTimer);
	aci.StopRemainingTimer();
}