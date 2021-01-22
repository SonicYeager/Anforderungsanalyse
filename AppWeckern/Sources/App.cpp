#include "App.h"

App::App(UI& otherUi, Interactor& otherInter)
	: ui(otherUi)
	, inter(otherInter)
{
	// TODO: Hier Code zur Integration einf�gen
	auto oninit = [this]() 
	{
		auto presentTime = inter.InitApp();
		ui.SetPresentTime(presentTime);
	};
	ui.onInit = oninit;
	ui.onStartTimer = [this]() { inter.StartTimer(); };
	ui.onStopTimer = [this]() { inter.StopTimer(); };
	inter.onUpdatePresentTime = [this](const std::string& str) { ui.SetPresentTime(str); };
}

void App::Run()
{
	//App starten
	ui.Init();
}
