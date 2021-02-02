#include "Program.h"
#include "App.h"
#include "AppWeckernDlg.h"
#include "AlarmClockInteractor.h"
#include "TimeHandler.h"
#include "Converter.h"
#include "TimeOperations.h"
#include "AudioPlayer.h"

AppWeckernApp theApp;

BEGIN_MESSAGE_MAP(AppWeckernApp, CWinApp)
END_MESSAGE_MAP()

BOOL AppWeckernApp::InitInstance()
{
	CWinApp::InitInstance();
	// TODO: Hier Code zur Konstruktion einfügen, die Integration in App machen
	TimeHandler th{};
	Converter f{};
	TimeOperations to{};
	AudioPlayer ap{};
	AlarmClockInteractor inter{&to, &th, &ap, &f};
	AppWeckernDlg dlg{};
	App app = App(dlg, inter);
	app.Run();
	return FALSE;
}
