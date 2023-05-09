// MainWindow.h : header file
//

#if !defined(AFX_MainWindow_H__8C615E06_307E_4CE0_BCD6_4A514F561FD5__INCLUDED_)
#define AFX_MainWindow_H__8C615E06_307E_4CE0_BCD6_4A514F561FD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMainWindow dialog

#define PI 3.141592654
#define radius 8
#define TriggerLevel 0

class CMainWindow : public CDialog
{
    // Construction
public:
    friend DWORD WINAPI ThreadFunc(LPVOID lpParam);
    CMainWindow(CWnd *pParent = NULL); // standard constructor
    BOOL SetUp429Card();
    void Coding();
    void Decoding(LPVOID lpParam);
    void Send();
    void Receive();

    // Dialog Data
    enum { IDD = IDD_OldFormat };
	
    CButton m_Button_Receive;
    CEdit textbot_send_NormalOverload;
    CEdit textbot_send_HighL;
    CEdit textbot_send_HighR;
    CEdit textbot_send_SpeedUD;
    CEdit textbot_send_Attack;
    CEdit textbot_send_AirP;
    CEdit textbot_send_Ma;
    CEdit textbot_send_RealSpeed;
    CEdit textbot_send_Azimuth;
    CEdit textbot_send_High;
    CEdit textbot_send_Pitch;
    CEdit textbot_send_Roll;
    CEdit textbot_send_Sideslip;
    CEdit textbot_send_Speed;

    CEdit textbot_receive_NormalOverload;
    CEdit textbot_receive_HighL;
    CEdit textbot_receive_HighR;
    CEdit textbot_receive_SpeedUD;
    CEdit textbot_receive_Attack;
    CEdit textbot_receive_AirP;
    CEdit textbot_receive_Ma;
    CEdit textbot_receive_RealSpeed;
    CEdit textbot_receive_Azimuth;
    CEdit textbot_receive_High;
    CEdit textbot_receive_Pitch;
    CEdit textbot_receive_Roll;
    CEdit textbot_receive_Sideslip;
    CEdit textbot_receive_Speed;

    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support

    // Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg void OnDraw_Fighter(int x, int y, CDC *pDC);
    afx_msg void OnDraw_HXJ(double x, CDC *pDC);
    afx_msg void OnDraw_High(int x, CDC *pDC);
    afx_msg void OnDraw_Speed(int x, CDC *pDC);
    afx_msg void OnDraw_HG(double HGJ, double FYJ, CDC *pCD);
    afx_msg void OnDraw_HGKD(double HGJ, CDC *pDC);
    afx_msg void OnDraw_BlackRect(CDC *pDC);
    afx_msg void OnDraw_SkyRect(CDC *pDC);
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
    afx_msg void OnChangeEDITRealSpeed();
    afx_msg void OnKillfocusEDITRealSpeed();
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
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedRadio4();
    afx_msg void OnBnClickedRadionormal2();
    afx_msg void OnBnClickedOnbuttonbitrate12k();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MainWindow_H__8C615E06_307E_4CE0_BCD6_4A514F561FD5__INCLUDED_)