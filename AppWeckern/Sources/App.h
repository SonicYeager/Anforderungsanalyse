#pragma once
#include "AppWeckernDlg.h"
#include "Interactor.h"

class App
{
public:
	App(AppWeckernDlg&);

	void Run();

private:
	AppWeckernDlg* dlg{};
	Interactor inter{};
};
