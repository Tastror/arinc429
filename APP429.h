// APP429.h : main header file for the APP429 application
//

#if !defined(AFX_APP429_H__3CCF21FD_31D2_446D_9E4A_F281B1CA7F1C__INCLUDED_)
#define AFX_APP429_H__3CCF21FD_31D2_446D_9E4A_F281B1CA7F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAPP429App:
// See APP429.cpp for the implementation of this class
//

class CAPP429App : public CWinApp
{
public:
	CAPP429App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAPP429App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAPP429App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APP429_H__3CCF21FD_31D2_446D_9E4A_F281B1CA7F1C__INCLUDED_)
