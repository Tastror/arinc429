#include "stdafx.h"
#include "resource.h"
#include "DevelopWindow.h"

CDevelopDlg::CDevelopDlg() : CDialog(CDevelopDlg::IDD)
{
	//{{AFX_DATA_INIT(CDevelopDlg)
	//}}AFX_DATA_INIT
}

void CDevelopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDevelopDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDevelopDlg, CDialog)
	//{{AFX_MSG_MAP(CDevelopDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()