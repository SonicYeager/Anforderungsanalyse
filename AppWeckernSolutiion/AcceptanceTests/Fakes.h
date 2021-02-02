#pragma once
#include <gmock/gmock.h>
#include "Clock.h"
#include "SoundPlayer.h"
#include "UI.h"

class UIFake : public Wecker::UI
{
public:
	UIFake();
	~UIFake() override;
	MOCK_METHOD(void, SetRemainingTime, (const Wecker::TimeSpan&), (override));
	MOCK_METHOD(void, SetCurrentTime, (const Wecker::DateTime&), (override));
	MOCK_METHOD(void, Start, (), (override));
};

class SoundPlayerFake : public Wecker::SoundPlayer
{
public:
	SoundPlayerFake();
	~SoundPlayerFake() override;
	MOCK_METHOD(void, Play, (), (override));
	MOCK_METHOD(void, Stop, (), (override));
};

class ClockFake : public Wecker::Clock
{
public:
	ClockFake();
	~ClockFake() override;
	MOCK_METHOD(void, Start, (), (override));
	MOCK_METHOD(void, Stop, (), (override));
};
