#include "Program.h"
#include "AppWeckernDlg.h"
#include "Resource.h"

AppWeckernDlg::AppWeckernDlg()
	: CDialogEx(IDD_APPWECKERN_DIALOG, nullptr)
{}

BOOL AppWeckernDlg::OnInitDialog()
{
	auto ret = __super::OnInitDialog();
	//DO INIT HERE (ITEMS)
	SetPresentTime("Works");
	return ret;
}

void AppWeckernDlg::SetPresentTime(const std::string& presentTime) //should be part of interface
{
	SetDlgItemTextA(presentTime_lbl, presentTime.c_str());
}

BEGIN_MESSAGE_MAP(AppWeckernDlg, CDialogEx)
END_MESSAGE_MAP()

//eventually Helpfull methods
//OnDestroy()