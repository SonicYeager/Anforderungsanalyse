#include "gmock/gmock.h"
#include "AlarmClockInteractor.h"
#include "TimeRessource.h"
#include "Formatter.h"
#include "TimeHandler.h"
#include "UI.h"

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
};

class FakeUI : public UI
{
public:
	void Init() override
	{
		onStartTimer();
	}
	MOCK_METHOD(void, SetPresentTime, (const std::string&), (override));
	~FakeUI()
	{
		onStopTimer();
	}
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
	::testing::InSequence seq{};
	ui.onStartTimer = [&aci]() { aci.StartTimer(); };
	ui.onStopTimer = [&aci]() { aci.StopTimer(); };
	aci.onUpdatePresentTime = [&ui](const std::string& str) { ui.SetPresentTime(str); };
	ui.Init();

	EXPECT_CALL(ui, SetPresentTime("13:00:00")).Times(::testing::AtLeast(1));
}