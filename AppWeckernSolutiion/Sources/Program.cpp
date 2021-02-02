#include "Program.h"
#include "App.h"
#include "AppWeckernDlg.h"
#include "Watchdog.h"
#include "SoundPlayerImpl.h"
#include "ClockImpl.h"
#include "Interactor.h"

AppWeckernApp theApp;

BEGIN_MESSAGE_MAP(AppWeckernApp, CWinApp)
END_MESSAGE_MAP()

BOOL AppWeckernApp::InitInstance()
{
	CWinApp::InitInstance();

	Wecker::AppWeckernDlg ui;
	Wecker::Watchdog watchdog;
	Wecker::SoundPlayerImpl player;
	Wecker::ClockImpl clock;
	Wecker::Interactor interactor(&clock, &watchdog, &player);
	Wecker::App app(&ui, &interactor);
	app.Run();

	return FALSE;
}
