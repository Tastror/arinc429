// MainWindow.cpp : implementation file
//

#include "stdafx.h"
#include "ARNIC429.h"
#include "MainWindow.h"

#include "math.h"

#include "DevelopWindow.h"
#include "MoreWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// this is for other class to use
CMainWindow* mother_window = NULL;

CMainWindow::CMainWindow(CWnd *pParent) : CDialog(CMainWindow::IDD, pParent)
{
    mother_window = this;

    iTabID = 0;
    keep_receive = false;
    btCardId = 0;
    hCard = NULL;
    // stLabelTable = {0};
    // stSysTime = {0};
    wdMode = C429_SELFTEST;
    dwTime = 0;
    CWord_flg1 = FALSE;
    CWord_flg2 = FALSE;
    isNeedThread = FALSE;
    hThread = NULL;
    dwThreadId = 0;
    Timer_flg = FALSE;
    blRxNow = FALSE;
    ghWnd = NULL;
    wdTxBufLen = 0;
    // stTriggerLevel = {0};

    data_send_Speed = 1;
    data_send_Roll = 0.0;
    data_send_Pitch = 0.0;
    data_send_High = 0;
    data_send_Azimuth = 0.0;
    data_send_SideSlip = 0.0;
    data_send_RealSpeed = 0;
    data_send_Mach = 0.0f;
    data_send_AirP = 0.0f;
    data_send_Attack = 0.0f;
    data_send_SpeedUD = 0;
    data_send_HighR = 0;
    data_send_HighL = 0;
    data_send_NormalOverload = 0.0f;

    data_receive_Speed = 0;
    data_receive_Roll = 0.0;
    data_receive_Pitch = 0.0;
    data_receive_High = 0;
    data_receive_Azimuth = 0.0;
    data_receive_SideSlip = 0.0;
    data_receive_RealSpeed = 0;
    data_receive_Mach = 0.0f;
    data_receive_AirP = 0.0f;
    data_receive_Attack = 0.0f;
    data_receive_SpeedUD = 0;
    data_receive_HighR = 0;
    data_receive_HighL = 0;
    data_receive_NormalOverload = 0.0f;

    string_receive_Speed.Format("%01x", 0);
    string_receive_Roll.Format("%01x", 0);
    string_receive_Pitch.Format("%01x", 0);
    string_receive_High.Format("%01x", 0);
    string_receive_Azimuth.Format("%01x", 0);
    string_receive_SideSlip.Format("%01x", 0);
    string_receive_RealSpeed.Format("%01x", 0);
    string_receive_Mach.Format("%01x", 0);
    string_receive_AirP.Format("%01x", 0);
    string_receive_Attack.Format("%01x", 0);
    string_receive_SpeedUD.Format("%01x", 0);
    string_receive_HighR.Format("%01x", 0);
    string_receive_HighL.Format("%01x", 0);
    string_receive_NormalOverload.Format("%01x", 0);

    string_receive_ControlWord1.Format("%01x", 0);
    string_receive_ControlWord2.Format("%01x", 0);

    string_difference_Speed.Format("%01x", 0);
    string_difference_Roll.Format("%01x", 0);
    string_difference_Pitch.Format("%01x", 0);
    string_difference_High.Format("%01x", 0);
    string_difference_Azimuth.Format("%01x", 0);
    string_difference_SideSlip.Format("%01x", 0);
    string_difference_RealSpeed.Format("%01x", 0);
    string_difference_Mach.Format("%01x", 0);
    string_difference_AirP.Format("%01x", 0);
    string_difference_Attack.Format("%01x", 0);
    string_difference_SpeedUD.Format("%01x", 0);
    string_difference_HighR.Format("%01x", 0);
    string_difference_HighL.Format("%01x", 0);
    string_difference_NormalOverload.Format("%01x", 0);

    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDI_NwpuPlane);
}

void CMainWindow::DoDataExchange(CDataExchange *pDX)
{
    CDialog::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_BUTTON_Receive, button_Receive);
    DDX_Control(pDX, IDC_BUTTON_StartStopTimer, button_StartStopTimer);
    DDX_Control(pDX, IDC_SEND_NormalOverload, textbox_send_NormalOverload);
    DDX_Control(pDX, IDC_SEND_HighL, textbox_send_HighL);
    DDX_Control(pDX, IDC_SEND_HighR, textbox_send_HighR);
    DDX_Control(pDX, IDC_SEND_SpeedUD, textbox_send_SpeedUD);
    DDX_Control(pDX, IDC_SEND_Attack, textbox_send_Attack);
    DDX_Control(pDX, IDC_SEND_AirP, textbox_send_AirP);
    DDX_Control(pDX, IDC_SEND_Mach, textbox_send_Ma);
    DDX_Control(pDX, IDC_SEND_RealSpeed, textbox_send_RealSpeed);
    DDX_Control(pDX, IDC_SEND_Azimuth, textbox_send_Azimuth);
    DDX_Control(pDX, IDC_SEND_High, textbox_send_High);
    DDX_Control(pDX, IDC_SEND_Pitch, textbox_send_Pitch);
    DDX_Control(pDX, IDC_SEND_Roll, textbox_send_Roll);
    DDX_Control(pDX, IDC_SEND_SlideSlip, textbox_send_SideSlip);
    DDX_Control(pDX, IDC_SEND_Speed, textbox_send_Speed);

    DDX_Text(pDX, IDC_SEND_Speed, data_send_Speed);
    DDV_MinMaxInt(pDX, data_send_Speed, 0, 2048);
    DDX_Text(pDX, IDC_SEND_Roll, data_send_Roll);
    DDV_MinMaxDouble(pDX, data_send_Roll, -180., 180.);
    DDX_Text(pDX, IDC_SEND_Pitch, data_send_Pitch);
    DDV_MinMaxDouble(pDX, data_send_Pitch, -180., 180.);
    DDX_Text(pDX, IDC_SEND_High, data_send_High);
    DDV_MinMaxInt(pDX, data_send_High, 0, 32768);
    DDX_Text(pDX, IDC_SEND_Azimuth, data_send_Azimuth);
    DDV_MinMaxDouble(pDX, data_send_Azimuth, 0., 360.);
    DDX_Text(pDX, IDC_SEND_SlideSlip, data_send_SideSlip);
    DDV_MinMaxDouble(pDX, data_send_SideSlip, -10., 10.);
    DDX_Text(pDX, IDC_SEND_RealSpeed, data_send_RealSpeed);
    DDV_MinMaxInt(pDX, data_send_RealSpeed, 0, 4096);
    DDX_Text(pDX, IDC_SEND_Mach, data_send_Mach);
    DDV_MinMaxFloat(pDX, data_send_Mach, 0.f, 4.096f);
    DDX_Text(pDX, IDC_SEND_AirP, data_send_AirP);
    DDV_MinMaxFloat(pDX, data_send_AirP, -128.f, 128.f);
    DDX_Text(pDX, IDC_SEND_Attack, data_send_Attack);
    DDV_MinMaxFloat(pDX, data_send_Attack, -45.f, 45.f);
    DDX_Text(pDX, IDC_SEND_SpeedUD, data_send_SpeedUD);
    DDV_MinMaxInt(pDX, data_send_SpeedUD, -512, 512);
    DDX_Text(pDX, IDC_SEND_HighR, data_send_HighR);
    DDV_MinMaxInt(pDX, data_send_HighR, 0, 1524);
    DDX_Text(pDX, IDC_SEND_HighL, data_send_HighL);
    DDV_MinMaxInt(pDX, data_send_HighL, 0, 1500);
    DDX_Text(pDX, IDC_SEND_NormalOverload, data_send_NormalOverload);
    DDV_MinMaxFloat(pDX, data_send_NormalOverload, -10.f, 10.f);

    DDX_Text(pDX, IDC_RECE_Roll, string_receive_Roll);
    DDX_Text(pDX, IDC_RECE_Pitch, string_receive_Pitch);
    DDX_Text(pDX, IDC_RECE_Speed, string_receive_Speed);
    DDX_Text(pDX, IDC_RECE_High, string_receive_High);
    DDX_Text(pDX, IDC_RECE_Azimuth, string_receive_Azimuth);
    DDX_Text(pDX, IDC_RECE_SlideSlip, string_receive_SideSlip);
    DDX_Text(pDX, IDC_RECE_RealSpeed, string_receive_RealSpeed);
    DDX_Text(pDX, IDC_RECE_Mach, string_receive_Mach);
    DDX_Text(pDX, IDC_RECE_AirP, string_receive_AirP);
    DDX_Text(pDX, IDC_RECE_Attack, string_receive_Attack);
    DDX_Text(pDX, IDC_RECE_SpeedUD, string_receive_SpeedUD);
    DDX_Text(pDX, IDC_RECE_HighR, string_receive_HighR);
    DDX_Text(pDX, IDC_RECE_HighL, string_receive_HighL);
    DDX_Text(pDX, IDC_RECE_NormalOverload, string_receive_NormalOverload);

    // in more window
    // DDX_Text(pDX, IDC_DIFF_Speed, string_difference_Speed);
    // DDX_Text(pDX, IDC_DIFF_Roll, string_difference_Roll);
    // DDX_Text(pDX, IDC_DIFF_Pitch, string_difference_Pitch);
    // DDX_Text(pDX, IDC_DIFF_High, string_difference_High);
    // DDX_Text(pDX, IDC_DIFF_Azimuth, string_difference_Azimuth);
    // DDX_Text(pDX, IDC_DIFF_SlideSlip, string_difference_SideSlip);
    // DDX_Text(pDX, IDC_DIFF_RealSpeed, string_difference_RealSpeed);
    // DDX_Text(pDX, IDC_DIFF_Mach, string_difference_Mach);
    // DDX_Text(pDX, IDC_DIFF_AirP, string_difference_AirP);
    // DDX_Text(pDX, IDC_DIFF_Attack, string_difference_Attack);
    // DDX_Text(pDX, IDC_DIFF_SpeedUD, string_difference_SpeedUD);
    // DDX_Text(pDX, IDC_DIFF_HighR, string_difference_HighR);
    // DDX_Text(pDX, IDC_DIFF_HighL, string_difference_HighL);
    // DDX_Text(pDX, IDC_DIFF_NormalOverload, string_difference_NormalOverload);

    DDX_Text(pDX, IDC_RECE_ControlWord1, string_receive_ControlWord1);
    DDX_Text(pDX, IDC_RECE_ControlWord2, string_receive_ControlWord2);
}

BEGIN_MESSAGE_MAP(CMainWindow, CDialog)

ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()

ON_EN_CHANGE(IDC_SEND_Speed, OnChange_Speed)
ON_EN_KILLFOCUS(IDC_SEND_Speed, OnKillFocus_Speed)
ON_EN_CHANGE(IDC_SEND_SlideSlip, OnChange_SlideSlip)
ON_EN_KILLFOCUS(IDC_SEND_SlideSlip, OnKillFocus_SlideSlip)
ON_EN_CHANGE(IDC_SEND_Roll, OnChange_Roll)
ON_EN_KILLFOCUS(IDC_SEND_Roll, OnKillFocus_Roll)
ON_EN_CHANGE(IDC_SEND_Pitch, OnChange_Pitch)
ON_EN_KILLFOCUS(IDC_SEND_Pitch, OnKillFocus_Pitch)
ON_EN_CHANGE(IDC_SEND_High, OnChange_High)
ON_EN_KILLFOCUS(IDC_SEND_High, OnKillFocus_High)
ON_EN_CHANGE(IDC_SEND_Azimuth, OnChange_Azimuth)
ON_EN_KILLFOCUS(IDC_SEND_Azimuth, OnKillFocus_Azimuth)
ON_EN_CHANGE(IDC_SEND_RealSpeed, OnChange_RealSpeed)
ON_EN_KILLFOCUS(IDC_SEND_RealSpeed, OnKillFocus_RealSpeed)
ON_EN_CHANGE(IDC_SEND_AirP, OnChange_AirP)
ON_EN_KILLFOCUS(IDC_SEND_AirP, OnKillFocus_AirP)
ON_EN_CHANGE(IDC_SEND_Attack, OnChange_Attack)
ON_EN_KILLFOCUS(IDC_SEND_Attack, OnKillFocus_Attack)
ON_EN_CHANGE(IDC_SEND_SpeedUD, OnChange_SpeedUD)
ON_EN_KILLFOCUS(IDC_SEND_SpeedUD, OnKillFocus_SpeedUD)
ON_EN_CHANGE(IDC_SEND_HighR, OnChange_HighR)
ON_EN_KILLFOCUS(IDC_SEND_HighR, OnKillFocus_HighR)
ON_EN_CHANGE(IDC_SEND_HighL, OnChange_HighL)
ON_EN_KILLFOCUS(IDC_SEND_HighL, OnKillFocus_HighL)
ON_EN_CHANGE(IDC_SEND_NormalOverload, OnChange_NormalOverload)
ON_EN_KILLFOCUS(IDC_SEND_NormalOverload, OnKillFocus_NormalOverload)
ON_EN_CHANGE(IDC_SEND_Mach, OnChange_Mach)
ON_EN_KILLFOCUS(IDC_SEND_Mach, OnKillFocus_Mach)

// ON_EN_CHANGE(IDC_RECE_Speed, OnChange_Speed)
// ON_EN_CHANGE(IDC_RECE_SlideSlip, OnChange_SlideSlip)
// ON_EN_CHANGE(IDC_RECE_Roll, OnChange_Roll)
// ON_EN_CHANGE(IDC_RECE_Pitch, OnChange_Pitch)
// ON_EN_CHANGE(IDC_RECE_High, OnChange_High)
// ON_EN_CHANGE(IDC_RECE_Azimuth, OnChange_Azimuth)
// ON_EN_CHANGE(IDC_RECE_RealSpeed, OnChange_RealSpeed)
// ON_EN_CHANGE(IDC_RECE_AirP, OnChange_AirP)
// ON_EN_CHANGE(IDC_RECE_Attack, OnChange_Attack)
// ON_EN_CHANGE(IDC_RECE_SpeedUD, OnChange_SpeedUD)
// ON_EN_CHANGE(IDC_RECE_HighR, OnChange_HighR)
// ON_EN_CHANGE(IDC_RECE_HighL, OnChange_HighL)
// ON_EN_CHANGE(IDC_RECE_NormalOverload, OnChange_NormalOverload)

// ON_EN_CHANGE(IDC_DIFF_Speed, OnChange_Speed)
// ON_EN_CHANGE(IDC_DIFF_SlideSlip, OnChange_SlideSlip)
// ON_EN_CHANGE(IDC_DIFF_Roll, OnChange_Roll)
// ON_EN_CHANGE(IDC_DIFF_Pitch, OnChange_Pitch)
// ON_EN_CHANGE(IDC_DIFF_High, OnChange_High)
// ON_EN_CHANGE(IDC_DIFF_Azimuth, OnChange_Azimuth)
// ON_EN_CHANGE(IDC_DIFF_RealSpeed, OnChange_RealSpeed)
// ON_EN_CHANGE(IDC_DIFF_AirP, OnChange_AirP)
// ON_EN_CHANGE(IDC_DIFF_Attack, OnChange_Attack)
// ON_EN_CHANGE(IDC_DIFF_SpeedUD, OnChange_SpeedUD)
// ON_EN_CHANGE(IDC_DIFF_HighR, OnChange_HighR)
// ON_EN_CHANGE(IDC_DIFF_HighL, OnChange_HighL)
// ON_EN_CHANGE(IDC_DIFF_NormalOverload, OnChange_NormalOverload)

ON_WM_TIMER()

ON_BN_CLICKED(IDC_BUTTON_Send, OnButton_Send)
ON_BN_CLICKED(IDC_BUTTON_Receive, OnButton_Receive)
ON_BN_CLICKED(IDC_BUTTON_StartStopTimer, OnButton_StartStopTimer)
ON_BN_CLICKED(IDC_BUTTON_ClearTimer, OnButton_ClearTimer)
ON_BN_CLICKED(IDC_BUTTON_Jump, OnGoToMore)
ON_BN_CLICKED(IDC_BUTTON_ChangeImage, OnChange_Background)

// in more window
// ON_BN_CLICKED(IDC_RADIO_SelfSend, On_RADIO_SelfSend)
// ON_BN_CLICKED(IDC_RADIO_Normal, On_RADIO_Normal)
// ON_BN_CLICKED(IDC_RADIO_100K, On_RADIO_100K)
// ON_BN_CLICKED(IDC_RADIO_48K, On_RADIO_48K)
// ON_BN_CLICKED(IDC_RADIO_12p5K, On_RADIO_12p5K)
// ON_BN_CLICKED(IDC_RADIO_NoCheck, On_RADIO_NoCheck)
// ON_BN_CLICKED(IDC_RADIO_OddCheck, On_RADIO_OddCheck)
// ON_BN_CLICKED(IDC_RADIO_EvenCheck, On_RADIO_EvenCheck)

ON_COMMAND(IDM_GoToMore, OnGoToMore)

END_MESSAGE_MAP()
