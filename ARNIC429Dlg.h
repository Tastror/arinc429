// ARNIC8081Dlg.h : header file
//

#if !defined(AFX_ARNIC429DLG_H__8C615E06_307E_4CE0_BCD6_4A514F561FD5__INCLUDED_)
#define AFX_ARNIC429DLG_H__8C615E06_307E_4CE0_BCD6_4A514F561FD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CARNIC8081Dlg dialog

#define PI 3.141592654
#define radius 8
#define TriggerLevel 0
 

class CARNIC429Dlg : public CDialog
{
// Construction
public:
	friend DWORD WINAPI ThreadFunc(LPVOID lpParam);
	CARNIC429Dlg(CWnd* pParent = NULL);	// standard constructor
	BOOL SetUp429Card();
	void Coding();
	void Decoding();
	void Send();
	void Receive();
	


// Dialog Data
	//{{AFX_DATA(CARNIC8081Dlg)
	enum { IDD = IDD_ARNIC8081_DIALOG };
	CButton	m_Button_Receive;
	CEdit	s_Edit_N;
	CEdit	s_Edit_HighL;
	CEdit	s_Edit_HighR;
	CEdit	s_Edit_SpeedUD;
	CEdit	s_Edit_Attack;
	CEdit	s_Edit_AirP;
	CEdit	s_Edit_Ma;
	CEdit	s_Edit_Speed_Real;
	CEdit	s_Edit_Azimuth;
	CEdit	s_Edit_High;
	CEdit	s_Edit_Pitch;
	CEdit	s_Edit_Roll;
	CEdit	s_Edit_Sideslip;
	CEdit	s_Edit_Speed;

	CEdit	r_Edit_N;
	CEdit	r_Edit_HighL;
	CEdit	r_Edit_HighR;
	CEdit	r_Edit_SpeedUD;
	CEdit	r_Edit_Attack;
	CEdit	r_Edit_AirP;
	CEdit	r_Edit_Ma;
	CEdit	r_Edit_Speed_Real;
	CEdit	r_Edit_Azimuth;
	CEdit	r_Edit_High;
	CEdit	r_Edit_Pitch;
	CEdit	r_Edit_Roll;
	CEdit	r_Edit_Sideslip;
	CEdit	r_Edit_Speed;
	
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CARNIC8081Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CARNIC8081Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnDraw_Fighter(int x,int y,CDC *pDC);	
	afx_msg void OnDraw_HXJ(double x,CDC *pDC);
	afx_msg void OnDraw_High(int x,CDC *pDC);
	afx_msg void OnDraw_Speed(int x,CDC *pDC);
	afx_msg void OnDraw_HG(double HGJ,double FYJ,CDC *pCD);
	afx_msg void OnDraw_HGKD(double HGJ,CDC *pDC);
	afx_msg void OnDraw_BlackRect(CDC* pDC);
	afx_msg void OnDraw_SkyRect(CDC* pDC);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONSend();
	afx_msg void OnBUTTONReceive();
	afx_msg void OnClose();

	afx_msg void OnChangeEDITSpeed();
	afx_msg void OnKillfocusEDITSpeed();
	afx_msg void OnChangeEDITSlideslip();
	afx_msg void OnKillfocusEDITSlideslip();
	afx_msg void OnChangeEDITRoll();
	afx_msg void OnKillfocusEDITRoll();
	afx_msg void OnChangeEDITPitch();
	afx_msg void OnKillfocusEDITPitch();
	afx_msg void OnChangeEDITHigh();
	afx_msg void OnKillfocusEDITHigh();
	afx_msg void OnChangeEDITAzimuth();
	afx_msg void OnKillfocusEDITAzimuth();
	afx_msg void OnChangeEDITSpeedReal();
	afx_msg void OnKillfocusEDITSpeedReal();
	afx_msg void OnChangeEDITAirP();
	afx_msg void OnKillfocusEDITAirP();
	afx_msg void OnChangeEDITAttack();
	afx_msg void OnKillfocusEDITAttack();
	afx_msg void OnChangeEDITSpeedUD();
	afx_msg void OnKillfocusEDITSpeedUD();
	afx_msg void OnChangeEDITHighR();
	afx_msg void OnKillfocusEDITHighR();
	afx_msg void OnChangeEDITHighL();
	afx_msg void OnKillfocusEDITHighL();
	afx_msg void OnChangeEditn();
	afx_msg void OnKillfocusEditn();

	afx_msg void OnBUTTONStartTimer();
	afx_msg void OnBUTTONCLR();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRADIOSelftest();
	afx_msg void OnRADIONormal();
	afx_msg void OnCHECKControl1();
	afx_msg void OnCHECKControl2();
	afx_msg void OnKillfocusEDITMa();
	afx_msg void OnChangeEDITMa();
	afx_msg void OnButtonBITRATE100K();
	afx_msg void OnButtonBITRATE48K();
	afx_msg void OnButtonBITRATE12K();
	afx_msg void OnButtonPARITY_NONE();
	afx_msg void OnButtonPARITY_ODD();
	afx_msg void OnButtonPARITY_EVEN();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadionormal2();
	afx_msg void OnBnClickedOnbuttonbitrate12k();
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARNIC8081DLG_H__8C615E06_307E_4CE0_BCD6_4A514F561FD5__INCLUDED_)
