#include "App.h"

App::App(UI& otherUi, Interactor& otherInter)
	: ui(otherUi)
	, inter(otherInter)
{
	// TODO: Hier Code zur Integration einfügen
	auto oninit = [this]() 
	{
		auto presentTime = inter.InitApp();
		ui.SetPresentTime(presentTime);
	};

	auto onStartAlarm = [this](ALARMTYPE type, const std::string& wakeTime)
	{
		auto remainingTime = inter.StartRemainingTimer(type, wakeTime);
		ui.SetRemainingTime(remainingTime);
	};

	auto onStopAlarm = [this]() {inter.StopRemainingTimer();};

	ui.onInit = oninit;
	ui.onUIReady = [this]() { inter.StartTimer(); };
	ui.onUIShutdown = [this]() { inter.StopTimer(); };
	ui.onStartAlarm = onStartAlarm;
	ui.onStopAlarm = onStopAlarm;
	inter.onUpdatePresentTime = [this](const std::string& str) { ui.SetPresentTime(str); };
	inter.onUpdateRemainingTime = [this](const std::string& str) { ui.SetRemainingTime(str); };
}

void App::Run()
{
	//App starten
	ui.Init();
}
