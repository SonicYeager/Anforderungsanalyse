#include "App.h"

App::App(AppWeckernDlg& edlg)
	: dlg(&edlg)
{
	// TODO: Hier Code zur Integration einf�gen
	auto presentTime = inter.InitApp();
	this->dlg->SetPresentTime(presentTime);
}

void App::Run()
{
	//App starten
	dlg->DoModal();
}
