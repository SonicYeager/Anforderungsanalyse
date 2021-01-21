#pragma once
#include "targetver.h"
#include <afxdialogex.h>
#include "resource.h"

class AppWeckernDlg : public CDialogEx
{
public:
	AppWeckernDlg();

#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_APPWECKERN_DIALOGß
	};
#endif

private:
	DECLARE_MESSAGE_MAP()
	CStatic* pPresentTime_lbl = (CStatic*)GetDlgItem(presentTime_lbl);
};
