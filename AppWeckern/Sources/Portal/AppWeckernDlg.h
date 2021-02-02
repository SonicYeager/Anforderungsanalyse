#pragma once
#include "targetver.h"
#include "resource.h"
#include "UI.h"
#include <string>
#include <afxdialogex.h>

class AppWeckernDlg : public CDialogEx, public UI
{
public:
	AppWeckernDlg();
	void SetPresentTime(const std::string&) override;
	void SetRemainingTime(const std::string&) override;
	void Init() override;

protected:
	BOOL OnInitDialog() override;
	void OnDestroy();

private:
	void StartAlarmTimer();
	void StopAlarmTimer();

#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_APPWECKERN_DIALOGß
	};
#endif

private:
	DECLARE_MESSAGE_MAP()
};
