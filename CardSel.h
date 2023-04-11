#if !defined(AFX_CARDSEL_H__2036218A_CC28_4BE8_A3F8_463210F80B56__INCLUDED_)
#define AFX_CARDSEL_H__2036218A_CC28_4BE8_A3F8_463210F80B56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CardSel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCardSel dialog

class CCardSel : public CDialog
{
// Construction
public:
	CCardSel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCardSel)
	enum { IDD = IDD_CARDSEL };
	CEdit	m_edit_cardsel;
	CEdit	m_edit_cardid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCardSel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCardSel)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditCardsel();
	afx_msg void OnKillfocusEditCardsel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDSEL_H__2036218A_CC28_4BE8_A3F8_463210F80B56__INCLUDED_)
