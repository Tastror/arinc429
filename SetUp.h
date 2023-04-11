#if !defined(AFX_SETUP_H__097C8B46_9355_409C_8766_EF2057E8C288__INCLUDED_)
#define AFX_SETUP_H__097C8B46_9355_409C_8766_EF2057E8C288__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetUp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetUp dialog

class CSetUp : public CDialog
{
// Construction
public:
	CSetUp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetUp)
	enum { IDD = IDD_SETUP };
	CComboBox	m_combo_sd;
	CTabCtrl	m_tab_configure;
	CEdit	m_edit_stridep;
	CEdit	m_edit_stinterval;
	CEdit	m_edit_rtridep;
	CEdit	m_edit_btinterval;
	CComboBox	m_combo_parity;
	CComboBox	m_combo_brate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetUp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void StoreConfig(int idx);
	void ResumeConfig(int idx);
	// Generated message map functions
	//{{AFX_MSG(CSetUp)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonLoadconf();
	afx_msg void OnButtonSaveconf();
	afx_msg void OnSelchangeTabConfigure(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTabConfigure(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditBtinterval();
	afx_msg void OnChangeEditRtridep();
	afx_msg void OnChangeEditStinterval();
	afx_msg void OnChangeEditStridep();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillfocusEditBtinterval();
	afx_msg void OnKillfocusEditRtridep();
	afx_msg void OnKillfocusEditStinterval();
	afx_msg void OnKillfocusEditStridep();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeComboSd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUP_H__097C8B46_9355_409C_8766_EF2057E8C288__INCLUDED_)
