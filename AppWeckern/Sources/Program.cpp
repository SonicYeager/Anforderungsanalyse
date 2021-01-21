#include "Program.h"
#include "App.h"
#include "AppWeckernDlg.h"
#include "AlarmClockInteractor.h"
#include "TimeHandler.h"
#include "Formatter.h"

AppWeckernApp theApp;

BEGIN_MESSAGE_MAP(AppWeckernApp, CWinApp)
END_MESSAGE_MAP()

BOOL AppWeckernApp::InitInstance()
{
	CWinApp::InitInstance();
	// TODO: Hier Code zur Konstruktion einfügen, die Integration in App machen
	TimeHandler th{};
	Formatter f{};
	AlarmClockInteractor inter{&th, &f};
	AppWeckernDlg dlg{};
	App app = App(dlg, inter);
	app.Run();
	return FALSE;
}
