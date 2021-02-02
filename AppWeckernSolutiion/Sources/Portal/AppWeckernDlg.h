#pragma once
#include "targetver.h"
#include <afxdialogex.h>
#include "UI.h"

namespace Wecker
{
	class AppWeckernDlg : public CDialogEx, public UI
	{
	public:
		AppWeckernDlg();

#ifdef AFX_DESIGN_TIME
		enum
		{
			IDD = IDD_APPWECKERN_DIALOG
		};
#endif
		void Start() override;
		void SetCurrentTime(const DateTime&) override;
		void SetRemainingTime(const TimeSpan&) override;


	private:
		DECLARE_MESSAGE_MAP()
		BOOL OnInitDialog() override;
		afx_msg void OnDestroy();
		afx_msg void OnBnClickedBtStart();
		afx_msg void OnBnClickedBtStop();
		void OnOK() override;
	};
} // namespace Wecker
