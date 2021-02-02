#include "Program.h"
#include "winuser.h"
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
	onUIReady();
	return ret;
}

void AppWeckernDlg::OnDestroy()
{
	onUIShutdown();
	__super::OnDestroy();
}

void AppWeckernDlg::StartAlarmTimer()
{
	GetDlgItem(weckzeit_tbx)->EnableWindow(false);
	GetDlgItem(wakeUpTime_tbx)->EnableWindow(false);
	GetDlgItem(remainingTime_lbl)->ShowWindow(SW_SHOW);
	GetDlgItem(remainingTimeIdentifier_lbl)->ShowWindow(SW_SHOW);
	GetDlgItem(stop_btn)->ShowWindow(SW_SHOW);
	GetDlgItem(start_btn)->ShowWindow(SW_HIDE);
	CString str{};
	if(IsDlgButtonChecked(weckzeit_rbtn))
	{
		GetDlgItemTextA(weckzeit_tbx, str);
		onStartAlarm(ALARMTYPE::ALARMCLOCK, std::string(str));
	}
	else
	{
		GetDlgItemTextA(wakeUpTime_tbx, str);
		onStartAlarm(ALARMTYPE::ALARMTIMER, std::string(str));
	}
}

void AppWeckernDlg::StopAlarmTimer()
{
	GetDlgItem(weckzeit_tbx)->EnableWindow(true);
	GetDlgItem(wakeUpTime_tbx)->EnableWindow(true);
	GetDlgItem(remainingTime_lbl)->ShowWindow(SW_HIDE);
	GetDlgItem(remainingTimeIdentifier_lbl)->ShowWindow(SW_HIDE);
	GetDlgItem(stop_btn)->ShowWindow(SW_HIDE);
	GetDlgItem(start_btn)->ShowWindow(SW_SHOW);
	onStopAlarm();
}

void AppWeckernDlg::SetPresentTime(const std::string& presentTime)
{
	SetDlgItemTextA(presentTime_lbl, presentTime.c_str());
}

void AppWeckernDlg::SetRemainingTime(const std::string& presentTime)
{
	SetDlgItemTextA(remainingTime_lbl, presentTime.c_str());
}

void AppWeckernDlg::Init()
{
	DoModal();
}

BEGIN_MESSAGE_MAP(AppWeckernDlg, CDialogEx)
ON_WM_DESTROY()
ON_BN_CLICKED(start_btn, StartAlarmTimer)
ON_BN_CLICKED(stop_btn, StopAlarmTimer)
END_MESSAGE_MAP()

//eventually Helpfull methods
//OnDestroy()