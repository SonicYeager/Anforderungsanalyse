#pragma once
#include "TimerRessource.h"
#include "../SLFGameBackendQt/slfgamebackendqt_global.h"

class Timer : public TimerRessource
{
public:
	Timer();

	void Start()	override;
	void Stop()		override;

private:
	QTimer timer{};
};