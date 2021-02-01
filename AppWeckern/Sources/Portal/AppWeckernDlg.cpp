#include "Program.h"
#include "AppWeckernDlg.h"
#include "Resource.h"
#include <future>
#include <thread>

AppWeckernDlg::AppWeckernDlg()
	: CDialogEx(IDD_APPWECKERN_DIALOG, nullptr)
{}

BOOL AppWeckernDlg::OnInitDialog()
{
	auto ret = __super::OnInitDialog();
	CheckDlgButton(weckzeit_rbtn, BST_CHECKED);
	SetDlgItemTextA(weckzeit_tbx, "0:00");
	SetDlgItemTextA(wakeUpTime_tbx, "0:00");
	//DO INIT HERE (ITEMS)
	onInit();
	onStartTimer();
	return ret;
}

void AppWeckernDlg::OnCancel()
{
	onStopTimer();
	__super::OnCancel();
}

void AppWeckernDlg::SetPresentTime(const std::string& presentTime)
{
	SetDlgItemTextA(presentTime_lbl, presentTime.c_str());
}

void AppWeckernDlg::Init()
{
	DoModal();
}

BEGIN_MESSAGE_MAP(AppWeckernDlg, CDialogEx)
END_MESSAGE_MAP()

//eventually Helpfull methods
//OnDestroy()