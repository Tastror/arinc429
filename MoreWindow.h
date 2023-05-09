#include "stdafx.h"
#include "resource.h"

class CMoreWindow : public CDialog
{
public:
	CMoreWindow();
	enum { IDD = IDD_More };

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

