// arinc429Dlg.h : header file
//

#if !defined(AFX_ARINC429DLG_H__44690E77_2A32_4103_859E_63F76D262003__INCLUDED_)
#define AFX_ARINC429DLG_H__44690E77_2A32_4103_859E_63F76D262003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CArinc429Dlg dialog

#define PI 3.141592654
#define radius 8
#define TriggerLevel 0
 

class CArinc429Dlg : public CDialog
{
// Construction
public:
	void OnDraw_HG(double  Roll, double FYJ, CDC* pDC);
	void OnDraw_HGKD(double HGJ, CDC* pDC);
	void OnDraw_HXJ(double x, CDC* pDC);
	void OnDraw_BlackRect(CDC* pDC);
	void OnDraw_Speed(int x, CDC* pDC);
	void OnDraw_Fighteryujing(int x, int y, CDC* pDC);
	void OnDraw_High(int x,CDC* pDC);
	void OnDraw_Fighter(int x,int y,CDC* pDC);
//	void OnDraw_Fighter;
	void Send();
	void Coding();
	BOOL SetUp429Card();
	CArinc429Dlg(CWnd* pParent = NULL);	// standard constructor
	friend DWORD WINAPI ThreadFunc(LPVOID lpParam);


// Dialog Data
	//{{AFX_DATA(CArinc429Dlg)
	enum { IDD = IDD_ARINC429_DIALOG };
	CButton	m_Button_Receive;
	float	m_airp0;
	float	m_airp1;
	float	m_attack0;
	float	m_attack1;
	float	m_azimuth0;
	float	m_azimuth1;
	int		m_height_a0;
	int		m_height_a1;
	int		m_height_l0;
	int		m_height_l1;
	int		m_height_r0;
	int		m_height_r1;
	float	m_ma0;
	float	m_ma1;
	float	m_pitch0;
	float	m_pitch1;
	int		m_realspeed0;
	int		m_realspeed1;
	float	m_roll0;
	float	m_roll1;
	float	m_sideslip0;
	float	m_sideslip1;
	int		m_speed0;
	int		m_speed1;
	int		m_speedud0;
	float	m_t0;
	float	m_t1;
	CString	m_controlword1;
	CString	m_controlword2;
	int		m_speedud1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArinc429Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CArinc429Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnButtonSend();
	afx_msg void OnButtonReceive();
	afx_msg void OnClose();
	afx_msg void OnButtonStarttimer();
	afx_msg void OnButtonStoptimer();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRadio100k();
	afx_msg void OnCHECKControl2();
	afx_msg void OnCHECKControl1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARINC429DLG_H__44690E77_2A32_4103_859E_63F76D262003__INCLUDED_)
