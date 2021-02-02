#include "Interactor.h"
#include "Watchdog.h"
#include "SoundPlayer.h"
#include "Clock.h"

namespace Wecker
{
	Interactor::Interactor(Clock* pC, Watchdog* pW, SoundPlayer* pS)
		: m_pClock(pC)
		, m_pWatchdog(pW)
		, m_pPlayer(pS)
	{
		m_pClock->onNow = [this](auto t) {m_pWatchdog->UpdateWithCurrentTime(t); onNow(t); };
		m_pWatchdog->onRemainingTime = [this](auto t) { onRemainingTime(t); };
		m_pWatchdog->onWackupTimeReached = std::bind(&SoundPlayer::Play, m_pPlayer);
	}

	void Interactor::SetWithRestTime(const TimeSpan& dur)
	{
		m_pWatchdog->SetWithRestTime(dur);
	}

	void Interactor::SetWithWackupTime(const DateTime& date)
	{
		m_pWatchdog->SetWithWackupTime(date);
	}

	void Interactor::StartTimer()
	{
		m_pClock->Start();
	}

	void Interactor::StopTimer()
	{
		m_pClock->Stop();
	}

	void Interactor::Stop()
	{
		m_pWatchdog->Stop();
		m_pPlayer->Stop();
	}

} // namespace Wecker
