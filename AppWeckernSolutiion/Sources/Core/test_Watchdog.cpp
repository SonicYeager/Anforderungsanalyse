#include <gmock/gmock.h>
#include "Watchdog.h"

using namespace testing;
using namespace Wecker;

class WatchdogEventsFake
{
public:
	MOCK_METHOD(void, OnRemainingTime, (const TimeSpan&));
	MOCK_METHOD(void, OnWackupTimeReached, ());
};

class TestWatchdog : public Test
{
public:
	TestWatchdog()
	{
		watch.onRemainingTime = std::bind(&WatchdogEventsFake::OnRemainingTime, &events, std::placeholders::_1);
		watch.onWackupTimeReached = std::bind(&WatchdogEventsFake::OnWackupTimeReached, &events);
	}
	StrictMock<WatchdogEventsFake> events;
	Watchdog watch;
};


TEST_F(TestWatchdog, StartWithWackupTime_CurrentTimeBeforWackupTime_RemainingTimeSmaller)
{
	watch.UpdateWithCurrentTime({});

	EXPECT_CALL(events, OnRemainingTime(TimeSpan{7h, 30min}));
	EXPECT_CALL(events, OnRemainingTime(TimeSpan{7h, 29min, 59s}));

	watch.SetWithWackupTime(DateTime{7h, 30min});

	watch.UpdateWithCurrentTime({1s});
}

TEST_F(TestWatchdog, StartWithWackupTime_CurrentTimeAfterWackupTime_RemainingTimeGreater)
{
	watch.UpdateWithCurrentTime({22h});

	EXPECT_CALL(events, OnRemainingTime(TimeSpan{9h, 30min}));
	EXPECT_CALL(events, OnRemainingTime(TimeSpan{9h, 29min, 59s}));

	watch.SetWithWackupTime(DateTime{7h, 30min});

	watch.UpdateWithCurrentTime({22h, 1s});
}

TEST_F(TestWatchdog, StartWithWackupTime_CurrentTimeIsWackupTime_CallWackupTimeReachedAndRemainingToZero)
{
	watch.UpdateWithCurrentTime({7h, 29min, 59s});

	EXPECT_CALL(events, OnRemainingTime(TimeSpan{1s}));
	EXPECT_CALL(events, OnRemainingTime(TimeSpan{0s}));
	EXPECT_CALL(events, OnWackupTimeReached());

	watch.SetWithWackupTime(DateTime{7h, 30min});

	watch.UpdateWithCurrentTime({7h, 30min});
}

TEST_F(TestWatchdog, StartWithRestTime_CurrentTimeIsWackupTime_CallWackupTimeReachedAndRemainingToZero)
{
	watch.UpdateWithCurrentTime({7h, 30min});

	EXPECT_CALL(events, OnRemainingTime(TimeSpan{2h, 30min, 15s}));
	EXPECT_CALL(events, OnRemainingTime(TimeSpan{0s}));
	EXPECT_CALL(events, OnWackupTimeReached());

	watch.SetWithRestTime(TimeSpan{2h, 30min, 15s});

	watch.UpdateWithCurrentTime({10h, 15s});
}

TEST_F(TestWatchdog, StartWithRestTime_CurrentTimeIsWackupTime_CallWackupTimeReachedAndRemainingToZeroOnce)
{
	watch.UpdateWithCurrentTime({7h, 30min});

	EXPECT_CALL(events, OnRemainingTime(TimeSpan{2h, 30min, 15s}));
	EXPECT_CALL(events, OnRemainingTime(TimeSpan{0s}));
	EXPECT_CALL(events, OnWackupTimeReached());

	watch.SetWithRestTime(TimeSpan{2h, 30min, 15s});

	watch.UpdateWithCurrentTime({10h, 15s});
	watch.UpdateWithCurrentTime({10h, 16s});
	watch.UpdateWithCurrentTime({10h, 17s});
}

TEST_F(TestWatchdog, StartWithRestTime_SmallestUnit_ShowFirstMinute)
{
	watch.UpdateWithCurrentTime({7h, 30min});

	EXPECT_CALL(events, OnRemainingTime(TimeSpan{60s}));
	EXPECT_CALL(events, OnRemainingTime(TimeSpan{59s}));

	watch.SetWithRestTime(TimeSpan({60s}));

	watch.UpdateWithCurrentTime({7h, 30min, 1s});
}

TEST_F(TestWatchdog, Stop_Running_CallRemainingTimeOnce)
{
	EXPECT_CALL(events, OnRemainingTime({7h}));
	EXPECT_CALL(events, OnWackupTimeReached()).Times(0);
	watch.SetWithWackupTime(DateTime{7h});

	watch.Stop();

	watch.UpdateWithCurrentTime({7h});
}
