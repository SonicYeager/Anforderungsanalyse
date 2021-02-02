#include "Program.h"
#include "AppWeckernDlg.h"
#include "Resource.h"
#include "TimesConversion.h"

namespace Wecker
{
	AppWeckernDlg::AppWeckernDlg()
		: CDialogEx(IDD_APPWECKERN_DIALOG, nullptr)
	{}

	void AppWeckernDlg::Start()
	{
		DoModal();
	}

	void AppWeckernDlg::SetCurrentTime(const DateTime& time)
	{
		auto txt = Times::DateToString(time);
		SetDlgItemTextA(IDC_CURRENT_TIME, txt.c_str());
	}

	void AppWeckernDlg::SetRemainingTime(const TimeSpan& span)
	{
		auto txt = Times::SpanToString(span);
		SetDlgItemTextA(IDC_REMAINING_TIME, txt.c_str());
	}

	BOOL AppWeckernDlg::OnInitDialog()
	{
		auto res = __super::OnInitDialog();
		CheckDlgButton(IDC_RADIO_WACKUP_TIME, TRUE);
		auto pCtrl = GetDlgItem(IDC_REMAINING_TIME);
		pCtrl->ShowWindow(FALSE);
		SetDlgItemTextA(IDC_EDIT_REST_TIME, "0");
		SetDlgItemTextA(IDC_EDIT_WACKUP_TIME, "7:30");
		this->onReady();
		return res;
	}

	void AppWeckernDlg::OnDestroy()
	{
		this->onClose();
		__super::OnDestroy();
	}

	void AppWeckernDlg::OnBnClickedBtStart()
	{
		auto pCtrl = GetDlgItem(IDC_BT_START);
		pCtrl->EnableWindow(FALSE);
		pCtrl = GetDlgItem(IDC_BT_STOP);
		pCtrl->EnableWindow(TRUE);
		pCtrl = GetDlgItem(IDC_REMAINING_TIME);
		pCtrl->ShowWindow(TRUE);

		if(IsDlgButtonChecked(IDC_RADIO_WACKUP_TIME) == TRUE)
		{
			CString s;
			GetDlgItemTextA(IDC_EDIT_WACKUP_TIME, s);
			onStartWithWackupTime(Times::DateFromString(static_cast<const char*>(s)));
		}
		else
		{
			CString s;
			GetDlgItemTextA(IDC_EDIT_REST_TIME, s);
			onStartWithRestTime(Times::SpanFromString(static_cast<const char*>(s)));
		}
	}

	void AppWeckernDlg::OnBnClickedBtStop()
	{
		auto pCtrl = GetDlgItem(IDC_BT_START);
		pCtrl->EnableWindow(TRUE);
		pCtrl = GetDlgItem(IDC_BT_STOP);
		pCtrl->EnableWindow(FALSE);
		pCtrl = GetDlgItem(IDC_REMAINING_TIME);
		pCtrl->ShowWindow(FALSE);

		onStopped();
	}
	void AppWeckernDlg::OnOK()
	{
		// Nothing inside to prevent the dialog from being closed when the ENTER key is pressed
	}

	BEGIN_MESSAGE_MAP(AppWeckernDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BT_START, &AppWeckernDlg::OnBnClickedBtStart)
	ON_BN_CLICKED(IDC_BT_STOP, &AppWeckernDlg::OnBnClickedBtStop)
	END_MESSAGE_MAP()
} // namespace Wecker
