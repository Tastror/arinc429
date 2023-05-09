#include "stdafx.h"
#include "resource.h"
#include "MoreWindow.h"

CMoreWindow::CMoreWindow() : CDialog(CMoreWindow::IDD)
{
	//{{AFX_DATA_INIT(CMoreWindow)
	//}}AFX_DATA_INIT
}

void CMoreWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoreWindow)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMoreWindow, CDialog)
	//{{AFX_MSG_MAP(CMoreWindow)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()