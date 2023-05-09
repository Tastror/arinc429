// MainWindow.h : header file
//

#if !defined(AFX_MainWindow_H_INCLUDED_)
#define AFX_MainWindow_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PI 3.141592654
#define radius 8
#define TriggerLevel 0
#define THREAD_EXITCODE 0

#include "coding.h"
#include "cusfunc.h"
#include "DLL429D42_lib.h"

DWORD WINAPI DecodeThreadFunc(LPVOID lpParam);

class CMainWindow : public CDialog
{
public:
    enum { IDD = IDD_MainWindow };
    CMainWindow(CWnd *pParent = NULL);

public:
    BOOL SetUp429Card();
    void Coding();
    void Decoding(LPVOID lpParam);
    void Send();
    void Receive();
    friend DWORD WINAPI DecodeThreadFunc(LPVOID lpParam);

protected:
    virtual void DoDataExchange(CDataExchange *pDX);

public:
    int iTabID = 0;
    bool keep_receive = false;

    /* Confusing Variables */
    BYTE btCardId = 0;                    // 板卡号
    HANDLE hCard = NULL;                  // 全局板卡句柄
    LabelTable_STRUCT stLabelTable = {0}; // 标注区
    BOOL blFilter[CHNO_RMAX];             // 标号过滤
    STCOMMUNICATION stComm[CHNO_TMAX];
    SYSTEMTIME stSysTime = {0};  // 系统时间
    WORD wdMode = C429_SELFTEST; // 工作模式
    BOOL blTimeTag[CHNO_RMAX];   // 使能时间标签
    DWORD dwTime = 0;            // 时间
    WORD wdBInterval[CHNO_TMAX]; // 群定时
    WORD wdSInterval[CHNO_TMAX]; // 自定时
    BOOL CWord_flg1 = FALSE;
    BOOL CWord_flg2 = FALSE;
    BOOL isNeedThread = FALSE;
    HANDLE hThread = NULL; // handle to thread function（穿插功能）
    DWORD dwThreadId = 0;
    BOOL Timer_flg = FALSE;
    BOOL blRxNow = FALSE;
    HWND ghWnd = NULL;

    DWORD dwTxBuf[FIFO_TMAX];                 // 发送 FIFO
    WORD wdTxBufLen = 0;                      // 发送FIFO长度
    TriggerDepth_STRUCT stTriggerLevel = {0}; // 缓冲区触发深度

    DWORD ReceiveData_Vector[FIFO_RMAX];
    BOOL Mode_flg;
    BOOL Complete_flg; // 接收完成标志

    CButton text_Button_Receive;
    CEdit textbox_send_NormalOverload;
    CEdit textbox_send_HighL;
    CEdit textbox_send_HighR;
    CEdit textbox_send_SpeedUD;
    CEdit textbox_send_Attack;
    CEdit textbox_send_AirP;
    CEdit textbox_send_Ma;
    CEdit textbox_send_RealSpeed;
    CEdit textbox_send_Azimuth;
    CEdit textbox_send_High;
    CEdit textbox_send_Pitch;
    CEdit textbox_send_Roll;
    CEdit textbox_send_Sideslip;
    CEdit textbox_send_Speed;

    CEdit textbox_receive_NormalOverload;
    CEdit textbox_receive_HighL;
    CEdit textbox_receive_HighR;
    CEdit textbox_receive_SpeedUD;
    CEdit textbox_receive_Attack;
    CEdit textbox_receive_AirP;
    CEdit textbox_receive_Ma;
    CEdit textbox_receive_RealSpeed;
    CEdit textbox_receive_Azimuth;
    CEdit textbox_receive_High;
    CEdit textbox_receive_Pitch;
    CEdit textbox_receive_Roll;
    CEdit textbox_receive_Sideslip;
    CEdit textbox_receive_Speed;

    int time_counter;

    int data_send_RealSpeed;        // 指示空速
    int data_send_Speed;            // 真空速
    float data_send_Roll;           // 横滚角
    float data_send_Pitch;          // 俯仰角
    int data_send_High;             // 气压高度
    float data_send_Azimuth;        // 方位角
    float data_send_Sideslip;       // 侧滑角
    float data_send_Mach;           // 马赫数
    float data_send_AirP;           // 装订气压
    float data_send_Attack;         // 攻角
    int data_send_SpeedUD;          // 升降高度
    int data_send_HighR;            // 无线电高度
    int data_send_HighL;            // 最低安全高度
    float data_send_NormalOverload; // 过载

    int data_receive_RealSpeed;
    int data_receive_Speed;
    float data_receive_Roll;
    float data_receive_Pitch;
    int data_receive_High;
    float data_receive_Azimuth;
    float data_receive_Sideslip;
    float data_receive_Mach;
    float data_receive_AirP;
    float data_receive_Attack;
    int data_receive_SpeedUD;
    int data_receive_HighR;
    int data_receive_HighL;
    float data_receive_NormalOverload;

    CString data_difference_Speed;
    CString data_difference_Roll;
    CString data_difference_Pitch;
    CString data_difference_High;
    CString data_difference_Azimuth;
    CString data_difference_Sideslip;
    CString data_difference_RealSpeed;
    CString data_difference_Mach;
    CString data_difference_AirP;
    CString data_difference_Attack;
    CString data_difference_SpeedUD;
    CString data_difference_HighR;
    CString data_difference_HighL;
    CString data_difference_NormalOverload;

    DWORD m_ControlWord1;
    DWORD m_ControlWord2;

    CString data_ControlWord1;
    CString data_ControlWord2;

protected:
    HICON m_hIcon;

    virtual BOOL OnInitDialog();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnClose();

    afx_msg void OnPaint();
    afx_msg void OnDraw_SkyRect(CDC *pDC);
    afx_msg void OnDraw_Fighter(int x_offset, int y_offset, int x, int y, CDC *pDC);
    afx_msg void OnDraw_HXJ(int x_offset, int y_offset, double x, CDC *pDC);
    afx_msg void OnDraw_High(int x_offset, int y_offset, int x, CDC *pDC);
    afx_msg void OnDraw_Speed(int x_offset, int y_offset, int x, CDC *pDC);
    afx_msg void OnDraw_HG(int x_offset, int y_offset, double HGJ, double FYJ, CDC *pCD);
    afx_msg void OnDraw_HGKD(int x_offset, int y_offset, double HGJ, CDC *pDC);

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
    afx_msg void OnChangeEDITMa();
    afx_msg void OnKillfocusEDITMa();

    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void On_BUTTON_StartTimer();
    afx_msg void On_BUTTON_Send();
    afx_msg void On_BUTTON_Receive();
    afx_msg void On_BUTTON_StopTimer();

    afx_msg void OnCHECKControl1();
    afx_msg void OnCHECKControl2();

    // in more window
    // afx_msg void On_RADIO_SelfSend();
    // afx_msg void On_RADIO_Normal();
    // afx_msg void On_RADIO_100K();
    // afx_msg void On_RADIO_48K();
    // afx_msg void On_RADIO_12p5K();
    // afx_msg void On_RADIO_NoCheck();
    // afx_msg void On_RADIO_OddCheck();
    // afx_msg void On_RADIO_EvenCheck();

    afx_msg void OnGoToMore();

    DECLARE_MESSAGE_MAP()
};

#endif
