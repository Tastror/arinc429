#include "stdafx.h"
#include "resource.h"

class CMoreWindow : public CDialog
{
public:
	CMoreWindow();
	enum { IDD = IDD_More };

// Dialog Data
	//{{AFX_DATA(CMoreWindow)
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoreWindow)
	
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CMoreWindow)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
};

