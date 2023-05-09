// ARNIC429.h : main header file for the ARNIC429 application
//

#if !defined(AFX_ARNIC429_H__B6A927A6_C339_4D12_9EE7_87719B874300__INCLUDED_)
#define AFX_ARNIC429_H__B6A927A6_C339_4D12_9EE7_87719B874300__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH  // Ô¤±àÒëÍ·ÎÄ¼þ
#endif

#include "resource.h"  // main symbols

/////////////////////////////////////////////////////////////////////////////
// CARNIC429App:
// See ARNIC429.cpp for the implementation of this class
//

class CARNIC429App : public CWinApp
{
public:
	CARNIC429App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CARNIC429App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CARNIC429App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARNIC429_H__B6A927A6_C339_4D12_9EE7_87719B874300__INCLUDED_)
