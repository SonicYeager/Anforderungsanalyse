#pragma once
#include "targetver.h"
#include <afxdialogex.h>
#include "resource.h"
#include <string>
#include "UI.h"

class AppWeckernDlg : public CDialogEx, public UI
{
public:
	AppWeckernDlg();
	void SetPresentTime(const std::string&);
	BOOL OnInitDialog() override;

#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_APPWECKERN_DIALOGß
	};
#endif

private:
	DECLARE_MESSAGE_MAP()
};
