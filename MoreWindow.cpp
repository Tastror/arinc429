#include "stdafx.h"
#include "resource.h"
#include "MainWindow.h"

#include "cusfunc.h"
#include "DLL429D42_lib.h"

// in main window
extern CMainWindow* mother_window;
extern WORD wdMode;
extern STCOMMUNICATION stComm[];

// in main window
extern CString data_difference_Speed;
extern CString data_difference_Roll;
extern CString data_difference_Pitch;
extern CString data_difference_High;
extern CString data_difference_Azimuth;
extern CString data_difference_Sideslip;
extern CString data_difference_RealSpeed;
extern CString data_difference_Mach;
extern CString data_difference_AirP;
extern CString data_difference_Attack;
extern CString data_difference_SpeedUD;
extern CString data_difference_HighR;
extern CString data_difference_HighL;
extern CString data_difference_NormalOverload;

CMoreWindow::CMoreWindow() : CDialog(CMoreWindow::IDD)
{
    return;
}

void CMoreWindow::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
	
    DDX_Text(pDX, IDC_DIFF_Speed, data_difference_Speed);
    DDX_Text(pDX, IDC_DIFF_Roll, data_difference_Roll);
    DDX_Text(pDX, IDC_DIFF_Pitch, data_difference_Pitch);
    DDX_Text(pDX, IDC_DIFF_High, data_difference_High);
    DDX_Text(pDX, IDC_DIFF_Azimuth, data_difference_Azimuth);
    DDX_Text(pDX, IDC_DIFF_SlideSlip, data_difference_Sideslip);
    DDX_Text(pDX, IDC_DIFF_RealSpeed, data_difference_RealSpeed);
    DDX_Text(pDX, IDC_DIFF_Mach, data_difference_Mach);
    DDX_Text(pDX, IDC_DIFF_AirP, data_difference_AirP);
    DDX_Text(pDX, IDC_DIFF_Attack, data_difference_Attack);
    DDX_Text(pDX, IDC_DIFF_SpeedUD, data_difference_SpeedUD);
    DDX_Text(pDX, IDC_DIFF_HighR, data_difference_HighR);
    DDX_Text(pDX, IDC_DIFF_HighL, data_difference_HighL);
    DDX_Text(pDX, IDC_DIFF_NormalOverload, data_difference_NormalOverload);
}

BEGIN_MESSAGE_MAP(CMoreWindow, CDialog)
ON_BN_CLICKED(IDC_RADIO_SelfSend, On_RADIO_SelfSend)
ON_BN_CLICKED(IDC_RADIO_Normal, On_RADIO_Normal)
ON_BN_CLICKED(IDC_RADIO_100K, On_RADIO_100K)
ON_BN_CLICKED(IDC_RADIO_48K, On_RADIO_48K)
ON_BN_CLICKED(IDC_RADIO_12p5K, On_RADIO_12p5K)
ON_BN_CLICKED(IDC_RADIO_NoCheck, On_RADIO_NoCheck)
ON_BN_CLICKED(IDC_RADIO_OddCheck, On_RADIO_OddCheck)
ON_BN_CLICKED(IDC_RADIO_EvenCheck, On_RADIO_EvenCheck)
END_MESSAGE_MAP()


void CMoreWindow::On_RADIO_SelfSend()
{
    wdMode = C429_SELFTEST;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_Normal()
{
    wdMode = C429_NORMAL;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_100K()
{
    for (int i = 0; i < CHNO_TMAX; i++)
        stComm[i].iSelBR = C429_BITRATE100K;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_48K()
{
    for (int i = 0; i < CHNO_TMAX; i++)
        stComm[i].iSelBR = C429_BITRATE48K;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_12p5K()
{
    for (int i = 0; i < CHNO_TMAX; i++)
        stComm[i].iSelBR = C429_BITRATE125K;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_NoCheck()
{
    for (int i = 0; i < CHNO_TMAX; i++)
        stComm[i].iSelParity = C429_PARITY_NONE;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_OddCheck()
{
    for (int i = 0; i < CHNO_TMAX; i++)
        stComm[i].iSelParity = C429_PARITY_ODD;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_EvenCheck()
{
    for (int i = 0; i < CHNO_TMAX; i++)
        stComm[i].iSelParity = C429_PARITY_EVEN;
    mother_window->SetUp429Card();
}