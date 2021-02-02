#include "App.h"
#include "UI.h"
#include "Interactor.h"

namespace Wecker
{
	App::App(UI* pU, Interactor* pI)
		: m_pUI(pU)
		, m_pInteractor(pI)
	{
		m_pUI->onClose = std::bind(&Interactor::StopTimer, m_pInteractor);
		m_pUI->onReady = std::bind(&Interactor::StartTimer, m_pInteractor);
		m_pUI->onStartWithRestTime = std::bind(&Interactor::SetWithRestTime, m_pInteractor, std::placeholders::_1);
		m_pUI->onStartWithWackupTime = std::bind(&Interactor::SetWithWackupTime, m_pInteractor, std::placeholders::_1);
		m_pUI->onStopped = std::bind(&Interactor::Stop, m_pInteractor);
		m_pInteractor->onNow = std::bind(&UI::SetCurrentTime, m_pUI, std::placeholders::_1);
		m_pInteractor->onRemainingTime = std::bind(&UI::SetRemainingTime, m_pUI, std::placeholders::_1);
	}

	void App::Run()
	{
		m_pUI->Start();
	}
} // namespace Wecker
