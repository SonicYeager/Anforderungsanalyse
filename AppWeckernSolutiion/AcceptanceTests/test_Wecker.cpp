#include "Fakes.h"
#include "App.h"
#include "Watchdog.h"
#include "Interactor.h"

using namespace testing;
using namespace Wecker;

class TestWecker : public Test
{
public:
	TestWecker()
		: interactor(&clock, &watchdog, &player)
		, wecker(&ui, &interactor)
	{
		wecker.Run();
	}

	NiceMock<UIFake> ui;
	NiceMock<ClockFake> clock;
	Watchdog watchdog;
	Interactor interactor;
	StrictMock<SoundPlayerFake> player;
	App wecker;
};

TEST_F(TestWecker, Run_NotRunningAndOnNow_CallSetCurrentTime)
{
	EXPECT_CALL(ui, SetCurrentTime(DateTime{22h, 30min, 15s}));
	EXPECT_CALL(ui, SetRemainingTime(_)).Times(0);

	clock.onNow({22h, 30min, 15s});
}

TEST_F(TestWecker, Run_NotRunningAndStartWithWackupTime_CallSetRemainingTime)
{
	clock.onNow({5h});
	EXPECT_CALL(ui, SetRemainingTime(TimeSpan{4h, 30min}));

	ui.onStartWithWackupTime({9h, 30min});
}

TEST_F(TestWecker, Run_NotRunningAndStartWithRestTime_CallSetRemainingTime)
{
	clock.onNow({5h});
	EXPECT_CALL(ui, SetRemainingTime(TimeSpan{2h}));

	ui.onStartWithRestTime({2h});
}

TEST_F(TestWecker, Run_RunningAndStop_CallSetRemainingTime)
{
	EXPECT_CALL(ui, SetCurrentTime(_)).Times(2);
	EXPECT_CALL(ui, SetRemainingTime(_)).Times(2);
	EXPECT_CALL(player, Stop());
	ui.onStartWithWackupTime({9h, 30min});
	clock.onNow({5h});

	ui.onStopped();
	clock.onNow({5h, 1s});
}

TEST_F(TestWecker, Run_RunningAndWackupTimeReached_CallPlaySoundOnce)
{
	EXPECT_CALL(player, Play());
	ui.onStartWithWackupTime({5h});

	clock.onNow({5h});
	clock.onNow({5h, 1s});
}

TEST_F(TestWecker, Run_RunningAndWackupTimeReached_CallSetRemainingTimeToZeroOnce)
{
	clock.onNow({5h});
	EXPECT_CALL(ui, SetRemainingTime(TimeSpan{0s})).Times(2);
	EXPECT_CALL(player, Play());

	ui.onStartWithWackupTime({5h});

	clock.onNow({5h, 1s});
}

TEST_F(TestWecker, Run_RunningAndWackupTimeReachedAndStopClicked_StoppedPlaying)
{
	EXPECT_CALL(player, Play());
	EXPECT_CALL(player, Stop());
	ui.onStartWithWackupTime({7h, 30min});
	clock.onNow({7h, 30min});

	ui.onStopped();
}
