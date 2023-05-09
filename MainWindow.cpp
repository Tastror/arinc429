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
    stLabelTable = (LabelTable_STRUCT)({0});
    stSysTime = (SYSTEMTIME)({0});
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
    stTriggerLevel = (TriggerDepth_STRUCT)({0});

    data_send_Speed = 1;
    data_send_Roll = 0.0;
    data_send_Pitch = 0.0;
    data_send_High = 0;
    data_send_Azimuth = 0.0;
    data_send_Sideslip = 0.0;
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
    data_receive_Sideslip = 0.0;
    data_receive_RealSpeed = 0;
    data_receive_Mach = 0.0f;
    data_receive_AirP = 0.0f;
    data_receive_Attack = 0.0f;
    data_receive_SpeedUD = 0;
    data_receive_HighR = 0;
    data_receive_HighL = 0;
    data_receive_NormalOverload = 0.0f;

    data_difference_Speed.Format("%01x", 0);
    data_difference_Roll.Format("%01x", 0);
    data_difference_Pitch.Format("%01x", 0);
    data_difference_High.Format("%01x", 0);
    data_difference_Azimuth.Format("%01x", 0);
    data_difference_Sideslip.Format("%01x", 0);
    data_difference_RealSpeed.Format("%01x", 0);
    data_difference_Mach.Format("%01x", 0);
    data_difference_AirP.Format("%01x", 0);
    data_difference_Attack.Format("%01x", 0);
    data_difference_SpeedUD.Format("%01x", 0);
    data_difference_HighR.Format("%01x", 0);
    data_difference_HighL.Format("%01x", 0);
    data_difference_NormalOverload.Format("%01x", 0);

    data_ControlWord1.Format("%01x", 0);
    data_ControlWord2.Format("%01x", 0);

    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDI_NwpuPlane);
}

void CMainWindow::DoDataExchange(CDataExchange *pDX)
{
    CDialog::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_BUTTON_Receive, text_Button_Receive);
    DDX_Control(pDX, IDC_EDIT_NormalOverload, textbox_send_NormalOverload);
    DDX_Control(pDX, IDC_EDIT_HighL, textbox_send_HighL);
    DDX_Control(pDX, IDC_EDIT_HighR, textbox_send_HighR);
    DDX_Control(pDX, IDC_EDIT_SpeedUD, textbox_send_SpeedUD);
    DDX_Control(pDX, IDC_EDIT_Attack, textbox_send_Attack);
    DDX_Control(pDX, IDC_EDIT_AirP, textbox_send_AirP);
    DDX_Control(pDX, IDC_EDIT_Mach, textbox_send_Ma);
    DDX_Control(pDX, IDC_EDIT_RealSpeed, textbox_send_RealSpeed);
    DDX_Control(pDX, IDC_EDIT_Azimuth, textbox_send_Azimuth);
    DDX_Control(pDX, IDC_EDIT_High, textbox_send_High);
    DDX_Control(pDX, IDC_EDIT_Pitch, textbox_send_Pitch);
    DDX_Control(pDX, IDC_EDIT_Roll, textbox_send_Roll);
    DDX_Control(pDX, IDC_EDIT_SlideSlip, textbox_send_Sideslip);
    DDX_Control(pDX, IDC_EDIT_Speed, textbox_send_Speed);

    DDX_Text(pDX, IDC_EDIT_Speed, data_send_Speed);
    DDV_MinMaxInt(pDX, data_send_Speed, 0, 2048);
    DDX_Text(pDX, IDC_EDIT_Roll, data_send_Roll);
    DDV_MinMaxDouble(pDX, data_send_Roll, -180., 180.);
    DDX_Text(pDX, IDC_EDIT_Pitch, data_send_Pitch);
    DDV_MinMaxDouble(pDX, data_send_Pitch, -180., 180.);
    DDX_Text(pDX, IDC_EDIT_High, data_send_High);
    DDV_MinMaxInt(pDX, data_send_High, 0, 32768);
    DDX_Text(pDX, IDC_EDIT_Azimuth, data_send_Azimuth);
    DDV_MinMaxDouble(pDX, data_send_Azimuth, 0., 360.);
    DDX_Text(pDX, IDC_EDIT_SlideSlip, data_send_Sideslip);
    DDV_MinMaxDouble(pDX, data_send_Sideslip, -10., 10.);
    DDX_Text(pDX, IDC_EDIT_RealSpeed, data_send_RealSpeed);
    DDV_MinMaxInt(pDX, data_send_RealSpeed, 0, 4096);
    DDX_Text(pDX, IDC_EDIT_Mach, data_send_Mach);
    DDV_MinMaxFloat(pDX, data_send_Mach, 0.f, 4.096f);
    DDX_Text(pDX, IDC_EDIT_AirP, data_send_AirP);
    DDV_MinMaxFloat(pDX, data_send_AirP, -128.f, 128.f);
    DDX_Text(pDX, IDC_EDIT_Attack, data_send_Attack);
    DDV_MinMaxFloat(pDX, data_send_Attack, -45.f, 45.f);
    DDX_Text(pDX, IDC_EDIT_SpeedUD, data_send_SpeedUD);
    DDV_MinMaxInt(pDX, data_send_SpeedUD, -512, 512);
    DDX_Text(pDX, IDC_EDIT_HighR, data_send_HighR);
    DDV_MinMaxInt(pDX, data_send_HighR, 0, 1524);
    DDX_Text(pDX, IDC_EDIT_HighL, data_send_HighL);
    DDV_MinMaxInt(pDX, data_send_HighL, 0, 1500);
    DDX_Text(pDX, IDC_EDIT_NormalOverload, data_send_NormalOverload);
    DDV_MinMaxFloat(pDX, data_send_NormalOverload, -10.f, 10.f);

    DDX_Text(pDX, IDC_SHOW_Speed, data_receive_Speed);
    DDX_Text(pDX, IDC_SHOW_Roll, data_receive_Roll);
    DDX_Text(pDX, IDC_SHOW_Pitch, data_receive_Pitch);
    DDX_Text(pDX, IDC_SHOW_High, data_receive_High);
    DDX_Text(pDX, IDC_SHOW_Azimuth, data_receive_Azimuth);
    DDX_Text(pDX, IDC_SHOW_SlideSlip, data_receive_Sideslip);
    DDX_Text(pDX, IDC_SHOW_RealSpeed, data_receive_RealSpeed);
    DDX_Text(pDX, IDC_SHOW_Mach, data_receive_Mach);
    DDX_Text(pDX, IDC_SHOW_AirP, data_receive_AirP);
    DDX_Text(pDX, IDC_SHOW_Attack, data_receive_Attack);
    DDX_Text(pDX, IDC_SHOW_SpeedUD, data_receive_SpeedUD);
    DDX_Text(pDX, IDC_SHOW_HighR, data_receive_HighR);
    DDX_Text(pDX, IDC_SHOW_HighL, data_receive_HighL);
    DDX_Text(pDX, IDC_SHOW_NormalOverload, data_receive_NormalOverload);

    // in more window
    // DDX_Text(pDX, IDC_DIFF_Speed, data_difference_Speed);
    // DDX_Text(pDX, IDC_DIFF_Roll, data_difference_Roll);
    // DDX_Text(pDX, IDC_DIFF_Pitch, data_difference_Pitch);
    // DDX_Text(pDX, IDC_DIFF_High, data_difference_High);
    // DDX_Text(pDX, IDC_DIFF_Azimuth, data_difference_Azimuth);
    // DDX_Text(pDX, IDC_DIFF_SlideSlip, data_difference_Sideslip);
    // DDX_Text(pDX, IDC_DIFF_RealSpeed, data_difference_RealSpeed);
    // DDX_Text(pDX, IDC_DIFF_Mach, data_difference_Mach);
    // DDX_Text(pDX, IDC_DIFF_AirP, data_difference_AirP);
    // DDX_Text(pDX, IDC_DIFF_Attack, data_difference_Attack);
    // DDX_Text(pDX, IDC_DIFF_SpeedUD, data_difference_SpeedUD);
    // DDX_Text(pDX, IDC_DIFF_HighR, data_difference_HighR);
    // DDX_Text(pDX, IDC_DIFF_HighL, data_difference_HighL);
    // DDX_Text(pDX, IDC_DIFF_NormalOverload, data_difference_NormalOverload);

    DDX_Text(pDX, IDC_ControlWord1, data_ControlWord1);
    DDX_Text(pDX, IDC_ControlWord2, data_ControlWord2);
}

BEGIN_MESSAGE_MAP(CMainWindow, CDialog)

ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()

ON_EN_CHANGE(IDC_EDIT_Speed, OnChangeEDITSpeed)
ON_EN_KILLFOCUS(IDC_EDIT_Speed, OnKillfocusEDITSpeed)
ON_EN_CHANGE(IDC_EDIT_SlideSlip, OnChangeEDITSlideslip)
ON_EN_KILLFOCUS(IDC_EDIT_SlideSlip, OnKillfocusEDITSlideslip)
ON_EN_CHANGE(IDC_EDIT_Roll, OnChangeEDITRoll)
ON_EN_KILLFOCUS(IDC_EDIT_Roll, OnKillfocusEDITRoll)
ON_EN_CHANGE(IDC_EDIT_Pitch, OnChangeEDITPitch)
ON_EN_KILLFOCUS(IDC_EDIT_Pitch, OnKillfocusEDITPitch)
ON_EN_CHANGE(IDC_EDIT_High, OnChangeEDITHigh)
ON_EN_KILLFOCUS(IDC_EDIT_High, OnKillfocusEDITHigh)
ON_EN_CHANGE(IDC_EDIT_Azimuth, OnChangeEDITAzimuth)
ON_EN_KILLFOCUS(IDC_EDIT_Azimuth, OnKillfocusEDITAzimuth)
ON_EN_CHANGE(IDC_EDIT_RealSpeed, OnChangeEDITRealSpeed)
ON_EN_KILLFOCUS(IDC_EDIT_RealSpeed, OnKillfocusEDITRealSpeed)
ON_EN_CHANGE(IDC_EDIT_AirP, OnChangeEDITAirP)
ON_EN_KILLFOCUS(IDC_EDIT_AirP, OnKillfocusEDITAirP)
ON_EN_CHANGE(IDC_EDIT_Attack, OnChangeEDITAttack)
ON_EN_KILLFOCUS(IDC_EDIT_Attack, OnKillfocusEDITAttack)
ON_EN_CHANGE(IDC_EDIT_SpeedUD, OnChangeEDITSpeedUD)
ON_EN_KILLFOCUS(IDC_EDIT_SpeedUD, OnKillfocusEDITSpeedUD)
ON_EN_CHANGE(IDC_EDIT_HighR, OnChangeEDITHighR)
ON_EN_KILLFOCUS(IDC_EDIT_HighR, OnKillfocusEDITHighR)
ON_EN_CHANGE(IDC_EDIT_HighL, OnChangeEDITHighL)
ON_EN_KILLFOCUS(IDC_EDIT_HighL, OnKillfocusEDITHighL)
ON_EN_CHANGE(IDC_EDIT_NormalOverload, OnChangeEditn)
ON_EN_KILLFOCUS(IDC_EDIT_NormalOverload, OnKillfocusEditn)
ON_EN_KILLFOCUS(IDC_EDIT_Mach, OnKillfocusEDITMa)
ON_EN_CHANGE(IDC_EDIT_Mach, OnChangeEDITMa)

ON_EN_CHANGE(IDC_SHOW_Speed, OnChangeEDITSpeed)
ON_EN_CHANGE(IDC_SHOW_SlideSlip, OnChangeEDITSlideslip)
ON_EN_CHANGE(IDC_SHOW_Roll, OnChangeEDITRoll)
ON_EN_CHANGE(IDC_SHOW_Pitch, OnChangeEDITPitch)
ON_EN_CHANGE(IDC_SHOW_High, OnChangeEDITHigh)
ON_EN_CHANGE(IDC_SHOW_Azimuth, OnChangeEDITAzimuth)
ON_EN_CHANGE(IDC_SHOW_RealSpeed, OnChangeEDITRealSpeed)
ON_EN_CHANGE(IDC_SHOW_AirP, OnChangeEDITAirP)
ON_EN_CHANGE(IDC_SHOW_Attack, OnChangeEDITAttack)
ON_EN_CHANGE(IDC_SHOW_SpeedUD, OnChangeEDITSpeedUD)
ON_EN_CHANGE(IDC_SHOW_HighR, OnChangeEDITHighR)
ON_EN_CHANGE(IDC_SHOW_HighL, OnChangeEDITHighL)
ON_EN_CHANGE(IDC_SHOW_NormalOverload, OnChangeEditn)

ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON_Send, On_BUTTON_Send)
ON_BN_CLICKED(IDC_BUTTON_Receive, On_BUTTON_Receive)
ON_BN_CLICKED(IDC_BUTTON_StartTimer, On_BUTTON_StartTimer)
ON_BN_CLICKED(IDC_BUTTON_StopTimer, On_BUTTON_StopTimer)

// where is the button ???
// ON_BN_CLICKED(IDC_BUTTON_CheckControl1, OnCHECKControl1)
// ON_BN_CLICKED(IDC_BUTTON_CheckControl2, OnCHECKControl2)

// in more window
// ON_BN_CLICKED(IDC_RADIO_SelfSend, On_RADIO_SelfSend)
// ON_BN_CLICKED(IDC_RADIO_Normal, On_RADIO_Normal)
// ON_BN_CLICKED(IDC_RADIO_100K, On_RADIO_100K)
// ON_BN_CLICKED(IDC_RADIO_48K, On_RADIO_48K)
// ON_BN_CLICKED(IDC_RADIO_12p5K, On_RADIO_12p5K)
// ON_BN_CLICKED(IDC_RADIO_NoCheck, On_RADIO_NoCheck)
// ON_BN_CLICKED(IDC_RADIO_OddCheck, On_RADIO_OddCheck)
// ON_BN_CLICKED(IDC_RADIO_EvenCheck, On_RADIO_EvenCheck)

ON_BN_CLICKED(IDC_BUTTON_Jump, OnGoToMore)
ON_COMMAND(IDM_GoToMore, OnGoToMore)

END_MESSAGE_MAP()
