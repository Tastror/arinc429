// arinc429.h : main header file for the ARINC429 application
//

#if !defined(AFX_ARINC429_H__607C320B_84C2_4AED_8517_7953FB7ACF38__INCLUDED_)
#define AFX_ARINC429_H__607C320B_84C2_4AED_8517_7953FB7ACF38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CArinc429App:
// See arinc429.cpp for the implementation of this class
//

class CArinc429App : public CWinApp
{
public:
	CArinc429App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArinc429App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CArinc429App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARINC429_H__607C320B_84C2_4AED_8517_7953FB7ACF38__INCLUDED_)
