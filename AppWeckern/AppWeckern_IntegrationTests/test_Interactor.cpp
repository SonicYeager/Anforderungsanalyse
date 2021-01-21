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
};

TEST(TestAlarmClockInteractor, InitApp_1pmflat_Return13colon00colon00)
{
	FakeTimeHandler fth{};
	Formatter f{};
	AlarmClockInteractor aci{&fth, &f};

	auto actual = aci.InitApp();

	EXPECT_EQ(actual, "13:00:00");
}