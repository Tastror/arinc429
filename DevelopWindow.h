#include "stdafx.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDevelopDlg dialog used for App About
class CDevelopDlg : public CDialog
{
public:
	CDevelopDlg();
	enum { IDD = IDD_Develop };

// Dialog Data
	//{{AFX_DATA(CDevelopDlg)
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDevelopDlg)
	
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CDevelopDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
};

