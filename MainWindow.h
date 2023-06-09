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
    int iTabID;
    bool keep_receive;

    /* Confusing Variables */
    BYTE btCardId;  // 板卡号
    HANDLE hCard;  // 全局板卡句柄
    LabelTable_STRUCT stLabelTable; // 标注区
    BOOL blFilter[CHNO_RMAX];  // 标号过滤
    STCOMMUNICATION stComm[CHNO_TMAX];
    SYSTEMTIME stSysTime;  // 系统时间
    WORD wdMode;  // 工作模式
    BOOL blTimeTag[CHNO_RMAX];  // 使能时间标签
    DWORD dwTime;  // 时间
    WORD wdBInterval[CHNO_TMAX];  // 群定时
    WORD wdSInterval[CHNO_TMAX];  // 自定时
    BOOL CWord_flg1;
    BOOL CWord_flg2;
    BOOL isNeedThread;
    HANDLE hThread;  // handle to thread function（穿插功能）
    DWORD dwThreadId;
    BOOL Timer_flg;
    BOOL blRxNow;
    HWND ghWnd;

    DWORD dwTxBuf[FIFO_TMAX];  // 发送 FIFO
    WORD wdTxBufLen;  // 发送FIFO长度
    TriggerDepth_STRUCT stTriggerLevel; // 缓冲区触发深度

    DWORD ReceiveData_Vector[FIFO_RMAX];
    BOOL Mode_flg;
    BOOL Complete_flg; // 接收完成标志

    int time_counter;

    CButton button_Receive;
    CButton button_StartStopTimer;

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
    CEdit textbox_send_SideSlip;
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
    CEdit textbox_receive_SideSlip;
    CEdit textbox_receive_Speed;

    int data_send_RealSpeed;        // 指示空速
    int data_send_Speed;            // 真空速
    float data_send_Roll;           // 横滚角
    float data_send_Pitch;          // 俯仰角
    int data_send_High;             // 气压高度
    float data_send_Azimuth;        // 方位角
    float data_send_SideSlip;       // 侧滑角
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
    float data_receive_SideSlip;
    float data_receive_Mach;
    float data_receive_AirP;
    float data_receive_Attack;
    int data_receive_SpeedUD;
    int data_receive_HighR;
    int data_receive_HighL;
    float data_receive_NormalOverload;
    DWORD data_receive_ControlWord1;
    DWORD data_receive_ControlWord2;

    CString string_receive_Speed;
    CString string_receive_Roll;
    CString string_receive_Pitch;
    CString string_receive_High;
    CString string_receive_Azimuth;
    CString string_receive_SideSlip;
    CString string_receive_RealSpeed;
    CString string_receive_Mach;
    CString string_receive_AirP;
    CString string_receive_Attack;
    CString string_receive_SpeedUD;
    CString string_receive_HighR;
    CString string_receive_HighL;
    CString string_receive_NormalOverload;
    CString string_receive_ControlWord1;
    CString string_receive_ControlWord2;

    CString string_difference_Speed;
    CString string_difference_Roll;
    CString string_difference_Pitch;
    CString string_difference_High;
    CString string_difference_Azimuth;
    CString string_difference_SideSlip;
    CString string_difference_RealSpeed;
    CString string_difference_Mach;
    CString string_difference_AirP;
    CString string_difference_Attack;
    CString string_difference_SpeedUD;
    CString string_difference_HighR;
    CString string_difference_HighL;
    CString string_difference_NormalOverload;

protected:
    HICON m_hIcon;

    virtual BOOL OnInitDialog();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnClose();

    afx_msg void OnPaint();
    afx_msg void OnChange_Background();
    afx_msg void OnDraw_SkyRect(CDC *pDC);
    afx_msg void OnDraw_Fighter(int color, int x_offset, int y_offset, int x, int y, CDC *pDC);
    afx_msg void OnDraw_HXJ(int color, int x_offset, int y_offset, double x, CDC *pDC);
    afx_msg void OnDraw_High(int color, int x_offset, int y_offset, int x, CDC *pDC);
    afx_msg void OnDraw_Speed(int color, int x_offset, int y_offset, int x, CDC *pDC);
    afx_msg void OnDraw_HG(int color, int x_offset, int y_offset, double HGJ, double FYJ, CDC *pCD);
    afx_msg void OnDraw_HGKD(int color, int x_offset, int y_offset, double HGJ, CDC *pDC);

    afx_msg void OnChange_Speed();
    afx_msg void OnKillFocus_Speed();
    afx_msg void OnChange_SlideSlip();
    afx_msg void OnKillFocus_SlideSlip();
    afx_msg void OnChange_Roll();
    afx_msg void OnKillFocus_Roll();
    afx_msg void OnChange_Pitch();
    afx_msg void OnKillFocus_Pitch();
    afx_msg void OnChange_High();
    afx_msg void OnKillFocus_High();
    afx_msg void OnChange_Azimuth();
    afx_msg void OnKillFocus_Azimuth();
    afx_msg void OnChange_RealSpeed();
    afx_msg void OnKillFocus_RealSpeed();
    afx_msg void OnChange_AirP();
    afx_msg void OnKillFocus_AirP();
    afx_msg void OnChange_Attack();
    afx_msg void OnKillFocus_Attack();
    afx_msg void OnChange_SpeedUD();
    afx_msg void OnKillFocus_SpeedUD();
    afx_msg void OnChange_HighR();
    afx_msg void OnKillFocus_HighR();
    afx_msg void OnChange_HighL();
    afx_msg void OnKillFocus_HighL();
    afx_msg void OnChange_NormalOverload();
    afx_msg void OnKillFocus_NormalOverload();
    afx_msg void OnChange_Mach();
    afx_msg void OnKillFocus_Mach();

    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnButton_StartStopTimer();
    afx_msg void OnButton_ClearTimer();
    afx_msg void OnButton_Send();
    afx_msg void OnButton_Receive();

    afx_msg void OnCheck_Control1();
    afx_msg void OnCheck_Control2();

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
