#include "Program.h"
#include "App.h"

AppWeckernApp theApp;

BEGIN_MESSAGE_MAP(AppWeckernApp, CWinApp)
END_MESSAGE_MAP()

BOOL AppWeckernApp::InitInstance()
{
	CWinApp::InitInstance();
	// TODO: Hier Code zur Konstruktion einfügen, die Integration in App machen

	App app;
	app.Run();
	return FALSE;
}
