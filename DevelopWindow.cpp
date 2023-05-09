#include "stdafx.h"
#include "resource.h"
#include "DevelopWindow.h"

CDevelopWindow::CDevelopWindow() : CDialog(CDevelopWindow::IDD)
{
	//{{AFX_DATA_INIT(CDevelopWindow)
	//}}AFX_DATA_INIT
}

void CDevelopWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDevelopWindow)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDevelopWindow, CDialog)
	//{{AFX_MSG_MAP(CDevelopWindow)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()