#include "stdafx.h"
#include "resource.h"
#include "MainWindow.h"

#include "MoreWindow.h"
#include "cusfunc.h"
#include "DLL429D42_lib.h"

// in main window
extern CMainWindow* mother_window;

// this is for other class to use
CMoreWindow* more_window = NULL;

CMoreWindow::CMoreWindow() : CDialog(CMoreWindow::IDD)
{
    more_window = this;
	return;
}

void CMoreWindow::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
	
    // DDX_Text(pDX, IDC_DIFF_Speed, mother_window->string_difference_Speed);
    // DDX_Text(pDX, IDC_DIFF_Roll, mother_window->string_difference_Roll);
    // DDX_Text(pDX, IDC_DIFF_Pitch, mother_window->string_difference_Pitch);
    // DDX_Text(pDX, IDC_DIFF_High, mother_window->string_difference_High);
    // DDX_Text(pDX, IDC_DIFF_Azimuth, mother_window->string_difference_Azimuth);
    // DDX_Text(pDX, IDC_DIFF_SlideSlip, mother_window->string_difference_SideSlip);
    // DDX_Text(pDX, IDC_DIFF_RealSpeed, mother_window->string_difference_RealSpeed);
    // DDX_Text(pDX, IDC_DIFF_Mach, mother_window->string_difference_Mach);
    // DDX_Text(pDX, IDC_DIFF_AirP, mother_window->string_difference_AirP);
    // DDX_Text(pDX, IDC_DIFF_Attack, mother_window->string_difference_Attack);
    // DDX_Text(pDX, IDC_DIFF_SpeedUD, mother_window->string_difference_SpeedUD);
    // DDX_Text(pDX, IDC_DIFF_HighR, mother_window->string_difference_HighR);
    // DDX_Text(pDX, IDC_DIFF_HighL, mother_window->string_difference_HighL);
    // DDX_Text(pDX, IDC_DIFF_NormalOverload, mother_window->string_difference_NormalOverload);
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
    mother_window->wdMode = C429_SELFTEST;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_Normal()
{
    mother_window->wdMode = C429_NORMAL;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_100K()
{
    for (int i = 0; i < CHNO_TMAX; i++)
        mother_window->stComm[i].iSelBR = C429_BITRATE100K;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_48K()
{
    for (int i = 0; i < CHNO_TMAX; i++)
        mother_window->stComm[i].iSelBR = C429_BITRATE48K;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_12p5K()
{
    for (int i = 0; i < CHNO_TMAX; i++)
        mother_window->stComm[i].iSelBR = C429_BITRATE125K;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_NoCheck()
{
    for (int i = 0; i < CHNO_TMAX; i++)
        mother_window->stComm[i].iSelParity = C429_PARITY_NONE;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_OddCheck()
{
    for (int i = 0; i < CHNO_TMAX; i++)
        mother_window->stComm[i].iSelParity = C429_PARITY_ODD;
    mother_window->SetUp429Card();
}

void CMoreWindow::On_RADIO_EvenCheck()
{
    for (int i = 0; i < CHNO_TMAX; i++)
        mother_window->stComm[i].iSelParity = C429_PARITY_EVEN;
    mother_window->SetUp429Card();
}
