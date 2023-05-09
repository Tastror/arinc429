#ifndef _DEVELOPWINDOW_H_
#define _DEVELOPWINDOW_H_

#include "stdafx.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDevelopWindow dialog used for App About
class CDevelopWindow : public CDialog
{
public:
	CDevelopWindow();
	enum { IDD = IDD_Develop };

// Dialog Data
	//{{AFX_DATA(CDevelopWindow)
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDevelopWindow)
	
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CDevelopWindow)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
};

#endif