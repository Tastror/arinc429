// APP429Dlg.h : header file
//

#if !defined(AFX_APP429DLG_H__13C4546E_A04B_4E4C_8AAF_B186D7571D38__INCLUDED_)
#define AFX_APP429DLG_H__13C4546E_A04B_4E4C_8AAF_B186D7571D38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAPP429Dlg dialog

class CAPP429Dlg : public CDialog
{
// Construction
public:
	CAPP429Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAPP429Dlg)
	enum { IDD = IDD_APP429_DIALOG };
	CButton	m_check_sl2;
	CButton	m_check_sl1;
	CListBox	m_list_sl;
	CEdit	m_edit_sendcount;
	CButton	m_button_startrev;
	CEdit	m_edit_senddata;
	CTabCtrl	m_tab_rev;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAPP429Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAPP429Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonClr();
	afx_msg void OnButtonDel();
	afx_msg void OnButtonLoadf();
	afx_msg void OnButtonSavef();
	afx_msg void OnButtonSend();
	afx_msg void OnButtonStartrev();
	afx_msg void OnButtonStoptimertra();
	afx_msg void OnChangeEditSenddata();
	afx_msg void OnKillfocusEditSenddata();
	afx_msg void OnSelchangeTabRev(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTabRev(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetup();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APP429DLG_H__13C4546E_A04B_4E4C_8AAF_B186D7571D38__INCLUDED_)
