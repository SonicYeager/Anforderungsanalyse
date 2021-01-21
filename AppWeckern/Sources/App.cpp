#include "App.h"

App::App(UI& ui, Interactor& inter)
	: p_ui(ui)
	, p_inter(inter)
{
	// TODO: Hier Code zur Integration einfügen
	p_ui.Init();
}

void App::Run()
{
	//App starten
	auto presentTime = p_inter.InitApp();
	this->p_ui.SetPresentTime(presentTime);
}
