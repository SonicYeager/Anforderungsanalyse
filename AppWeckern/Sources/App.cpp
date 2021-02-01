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
	ui.onInit = oninit;
	ui.onUIReady = [this]() { inter.StartTimer(); };
	ui.onUIShutdown = [this]() { inter.StopTimer(); };
	inter.onUpdatePresentTime = [this](const std::string& str) { ui.SetPresentTime(str); };
}

void App::Run()
{
	//App starten
	ui.Init();
}
