#include "Program.h"
#include "App.h"
#include "AppWeckernDlg.h"
#include "Interactor.h"

AppWeckernApp theApp;

BEGIN_MESSAGE_MAP(AppWeckernApp, CWinApp)
END_MESSAGE_MAP()

BOOL AppWeckernApp::InitInstance()
{
	CWinApp::InitInstance();
	// TODO: Hier Code zur Konstruktion einfügen, die Integration in App machen

	AppWeckernDlg dlg{};
	Interactor inter{};
	App app{dlg, inter};
	app.Run();
	return FALSE;
}
