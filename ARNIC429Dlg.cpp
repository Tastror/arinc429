// ARNIC8081Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ARNIC429.h"
#include "ARNIC429Dlg.h"

#include "math.h"
#include "coding.h"
#include "message.h"
#include "cusfunc.h"
#include "DLL429D42_lib.h"

#include "CAboutDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	THREAD_EXITCODE		0

int iTabID=0;                 

bool keep_receive = false;

<<<<<<< HEAD
/* Confusing Variables */
BYTE				btCardId=0;				//�忨��         
HANDLE				hCard=NULL;				//ȫ�ְ忨���
LabelTable_STRUCT	stLabelTable={0};		//��ע��
BOOL				blFilter[CHNO_RMAX];    //��Ź���
STCOMMUNICATION		stComm[CHNO_TMAX];   
SYSTEMTIME			stSysTime={0};			//ϵͳʱ��
WORD				wdMode=C429_SELFTEST;   //����ģʽ
BOOL				blTimeTag[CHNO_RMAX];   //ʹ��ʱ���ǩ
DWORD				dwTime=0;               //ʱ��
WORD				wdBInterval[CHNO_TMAX]; //Ⱥ��ʱ
WORD				wdSInterval[CHNO_TMAX]; //�Զ�ʱ
BOOL				CWord_flg1 = FALSE;
BOOL				CWord_flg2 = FALSE;
BOOL				isNeedThread=FALSE;
HANDLE				hThread=NULL;			// handle to thread function�����幦�ܣ�
=======
BYTE				btCardId=0;							//�忨��         
HANDLE				hCard=NULL;							//ȫ�ְ忨���
TriggerDepth_STRUCT stTriggerLevel={0};		//�������������
LabelTable_STRUCT	stLabelTable={0};			//��ע��
BOOL				blFilter[CHNO_RMAX];         //��Ź���
STCOMMUNICATION		stComm[CHNO_TMAX];   
SYSTEMTIME			stSysTime={0};      //ϵͳʱ��
WORD				wdMode=C429_SELFTEST;       //����ģʽ
BOOL				blTimeTag[CHNO_RMAX];      //ʹ��ʱ���ǩ
DWORD				dwTime=0;                //ʱ��
WORD				wdBInterval[CHNO_TMAX];     //Ⱥ��ʱ
WORD				wdSInterval[CHNO_TMAX];    //�Զ�ʱ
BOOL				CWord_flg1 = FALSE;
BOOL				CWord_flg2 = FALSE;
BOOL				isNeedThread=FALSE;
HANDLE				hThread=NULL; // handle to thread function�����幦�ܣ�
>>>>>>> refs/remotes/origin/master
DWORD				dwThreadId=0;  
BOOL				Timer_flg = FALSE;
BOOL				blRxNow=FALSE;
HWND				ghWnd=NULL;

DWORD dwTxBuf[FIFO_TMAX];    //���� FIFO
WORD wdTxBufLen=0;        //����FIFO����
TriggerDepth_STRUCT stTriggerLevel={0};		//�������������

DWORD ReceiveData_Vector[FIFO_RMAX];
BOOL Mode_flg;
BOOL Complete_flg;//������ɱ�־

DWORD WINAPI ThreadFunc(LPVOID lpParam);

int		s_Air_Speed;		//�����
float	s_Air_Roll;			//�����
float	s_Air_Pitch;		//������
int		s_Air_High;			//��ѹ�߶�
float	s_Air_Azimuth;		//��λ��
float	s_Air_Sideslip;		//�໬��
int		s_Air_Speed_Real;	//ָʾ����
float	s_Air_Ma;			//�����
float	s_Air_AirP;			//װ����ѹ
float	s_Air_Attack;		//����
int		s_Air_SpeedUD;		//�����߶�
int		s_Air_HighR;		//���ߵ�߶�
int		s_Air_HighL;		//��Ͱ�ȫ�߶�
float	s_Air_N;			//����

int		r_Air_Speed;		//�����
float	r_Air_Roll;			//�����
float	r_Air_Pitch;		//������
int		r_Air_High;			//���ߵ�߶�
float	r_Air_Azimuth;		//��λ��
float	r_Air_Sideslip;		//�໬��
int		r_Air_Speed_Real;	//ָʾ����
float	r_Air_Ma;			//�����
float	r_Air_AirP;			//װ����ѹ
float	r_Air_Attack;		//����
int		r_Air_SpeedUD;		//�����߶�
int		r_Air_HighR;		//��ѹ�߶�
int		r_Air_HighL;		//��Ͱ�ȫ�߶�
float	r_Air_N;			//����
int		T;

CString	x_Air_Speed;		//�����
CString	x_Air_Roll;			//�����
CString	x_Air_Pitch;		//������
CString	x_Air_High;			//���ߵ�߶�
CString	x_Air_Azimuth;		//��λ��
CString	x_Air_Sideslip;		//�໬��
CString	x_Air_Speed_Real;	//ָʾ����
CString	x_Air_Ma;			//�����
CString	x_Air_AirP;			//װ����ѹ
CString	x_Air_Attack;		//����
CString	x_Air_SpeedUD;		//�����߶�
CString	x_Air_HighR;		//��ѹ�߶�
CString	x_Air_HighL;		//��Ͱ�ȫ�߶�
CString	x_Air_N;			//����

DWORD m_ControlWord1=0;
DWORD m_ControlWord2=0;

CString x_ControlWord1;
CString x_ControlWord2;


// Construc Function
// Set init variables used in sending and receiving
CARNIC429Dlg::CARNIC429Dlg(CWnd* pParent)
	: CDialog(CARNIC429Dlg::IDD, pParent)
{
	// used in sending
	s_Air_Speed = 1;
	s_Air_Roll = 0.0;
	s_Air_Pitch = 0.0;
	s_Air_High = 0;
	s_Air_Azimuth = 0.0;
	s_Air_Sideslip = 0.0;
	s_Air_Speed_Real = 0;
	s_Air_Ma = 0.0f;
	s_Air_AirP = 0.0f;
	s_Air_Attack = 0.0f;
	s_Air_SpeedUD = 0;
	s_Air_HighR = 0;
	s_Air_HighL = 0;
	s_Air_N = 0.0f;
	
	// used in receiving
	r_Air_Speed = 0;
	r_Air_Roll = 0.0;
	r_Air_Pitch = 0.0;
	r_Air_High = 0;
	r_Air_Azimuth = 0.0;
	r_Air_Sideslip = 0.0;
	r_Air_Speed_Real = 0;
	r_Air_Ma = 0.0f;
	r_Air_AirP = 0.0f;
	r_Air_Attack = 0.0f;
	r_Air_SpeedUD = 0;
	r_Air_HighR = 0;
	r_Air_HighL = 0;
	r_Air_N = 0.0f;
	
	// used to output
	x_Air_Speed.Format("%01x", 0);
	x_Air_Roll.Format("%01x", 0);
	x_Air_Pitch.Format("%01x", 0);
	x_Air_High.Format("%01x", 0);
	x_Air_Azimuth.Format("%01x", 0);
	x_Air_Sideslip.Format("%01x", 0);
	x_Air_Speed_Real.Format("%01x", 0);
	x_Air_Ma.Format("%01x", 0);
	x_Air_AirP.Format("%01x", 0);
	x_Air_Attack.Format("%01x", 0);
	x_Air_SpeedUD.Format("%01x", 0);
	x_Air_HighR.Format("%01x", 0);
	x_Air_HighL.Format("%01x", 0);
	x_Air_N.Format("%01x", 0);
	x_ControlWord1.Format("%01x", 0);
	x_ControlWord2.Format("%01x", 0);

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

// formulated by ARNIC429.rc
// No need to change here
void CARNIC429Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTONReceive, m_Button_Receive);
	DDX_Control(pDX, IDC_EDITN, s_Edit_N);
	DDX_Control(pDX, IDC_EDITHighL, s_Edit_HighL);
	DDX_Control(pDX, IDC_EDITHighR, s_Edit_HighR);
	DDX_Control(pDX, IDC_EDITSpeedUD, s_Edit_SpeedUD);
	DDX_Control(pDX, IDC_EDITAttack, s_Edit_Attack);
	DDX_Control(pDX, IDC_EDITAirP, s_Edit_AirP);
	DDX_Control(pDX, IDC_EDITMa, s_Edit_Ma);
	DDX_Control(pDX, IDC_EDITSpeed_Real, s_Edit_Speed_Real);
	DDX_Control(pDX, IDC_EDITAzimuth, s_Edit_Azimuth);
	DDX_Control(pDX, IDC_EDITHigh, s_Edit_High);
	DDX_Control(pDX, IDC_EDITPitch, s_Edit_Pitch);
	DDX_Control(pDX, IDC_EDITRoll, s_Edit_Roll);
	DDX_Control(pDX, IDC_EDITSlideslip, s_Edit_Sideslip);
	DDX_Control(pDX, IDC_EDITSpeed, s_Edit_Speed);
	DDX_Text(pDX, IDC_EDITSpeed, s_Air_Speed);
	DDV_MinMaxInt(pDX, s_Air_Speed, 0, 2048);
	DDX_Text(pDX, IDC_EDITRoll, s_Air_Roll);
	DDV_MinMaxDouble(pDX, s_Air_Roll, -180., 180.);
	DDX_Text(pDX, IDC_EDITPitch, s_Air_Pitch);
	DDV_MinMaxDouble(pDX, s_Air_Pitch, -180., 180.);
	DDX_Text(pDX, IDC_EDITHigh, s_Air_High);
	DDV_MinMaxInt(pDX, s_Air_High, 0, 32768);
	DDX_Text(pDX, IDC_EDITAzimuth, s_Air_Azimuth);
	DDV_MinMaxDouble(pDX, s_Air_Azimuth, 0., 360.);
	DDX_Text(pDX, IDC_EDITSlideslip, s_Air_Sideslip);
	DDV_MinMaxDouble(pDX, s_Air_Sideslip, -10., 10.);
	DDX_Text(pDX, IDC_EDITSpeed_Real, s_Air_Speed_Real);
	DDV_MinMaxInt(pDX, s_Air_Speed_Real, 0, 4096);
	DDX_Text(pDX, IDC_EDITMa, s_Air_Ma);
	DDV_MinMaxFloat(pDX, s_Air_Ma, 0.f, 4.096f);
	DDX_Text(pDX, IDC_EDITAirP, s_Air_AirP);
	DDV_MinMaxFloat(pDX, s_Air_AirP, -128.f, 128.f);
	DDX_Text(pDX, IDC_EDITAttack, s_Air_Attack);
	DDV_MinMaxFloat(pDX, s_Air_Attack, -45.f, 45.f);
	DDX_Text(pDX, IDC_EDITSpeedUD, s_Air_SpeedUD);
	DDV_MinMaxInt(pDX, s_Air_SpeedUD, -512, 512);
	DDX_Text(pDX, IDC_EDITHighR, s_Air_HighR);
	DDV_MinMaxInt(pDX, s_Air_HighR, 0, 1524);
	DDX_Text(pDX, IDC_EDITHighL, s_Air_HighL);
	DDV_MinMaxInt(pDX, s_Air_HighL, 0, 1500);
	DDX_Text(pDX, IDC_EDITN, s_Air_N);
	DDV_MinMaxFloat(pDX, s_Air_N, -10.f, 10.f);

	DDX_Text(pDX, IDC_EDITSpeed0, r_Air_Speed);
	DDX_Text(pDX, IDC_EDITRoll0, r_Air_Roll);
	DDX_Text(pDX, IDC_EDITPitch0, r_Air_Pitch);
	DDX_Text(pDX, IDC_EDITHigh0, r_Air_High);
	DDX_Text(pDX, IDC_EDITAzimuth0, r_Air_Azimuth);
	DDX_Text(pDX, IDC_EDITSlideslip0, r_Air_Sideslip);
	DDX_Text(pDX, IDC_EDITSpeed_Real0, r_Air_Speed_Real);
	DDX_Text(pDX, IDC_EDITMa0, r_Air_Ma);
	DDX_Text(pDX, IDC_EDITAirP0, r_Air_AirP);
	DDX_Text(pDX, IDC_EDITAttack0, r_Air_Attack);
	DDX_Text(pDX, IDC_EDITSpeedUD0, r_Air_SpeedUD);
	DDX_Text(pDX, IDC_EDITHighR0, r_Air_HighR);
	DDX_Text(pDX, IDC_EDITHighL0, r_Air_HighL);
	DDX_Text(pDX, IDC_EDITN0, r_Air_N);

	DDX_Text(pDX, IDC_EDITSpeed1, x_Air_Speed);
	DDX_Text(pDX, IDC_EDITRoll1, x_Air_Roll);
	DDX_Text(pDX, IDC_EDITPitch1, x_Air_Pitch);
	DDX_Text(pDX, IDC_EDITHigh1, x_Air_High);
	DDX_Text(pDX, IDC_EDITAzimuth1, x_Air_Azimuth);
	DDX_Text(pDX, IDC_EDITSlideslip1, x_Air_Sideslip);
	DDX_Text(pDX, IDC_EDITSpeed_Real1, x_Air_Speed_Real);
	DDX_Text(pDX, IDC_EDITMa1, x_Air_Ma);
	DDX_Text(pDX, IDC_EDITAirP1, x_Air_AirP);
	DDX_Text(pDX, IDC_EDITAttack1, x_Air_Attack);
	DDX_Text(pDX, IDC_EDITSpeedUD1, x_Air_SpeedUD);
	DDX_Text(pDX, IDC_EDITHighR1, x_Air_HighR);
	DDX_Text(pDX, IDC_EDITHighL1, x_Air_HighL);
	DDX_Text(pDX, IDC_EDITN1, x_Air_N);

	DDX_Text(pDX, IDC_ControlWord1, x_ControlWord1);
	DDX_Text(pDX, IDC_ControlWord2, x_ControlWord2);
}

BEGIN_MESSAGE_MAP(CARNIC429Dlg, CDialog)

	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONSend, OnBUTTONSend)

	ON_BN_CLICKED(IDC_BUTTONStartTimer, OnBUTTONStartTimer)
	ON_BN_CLICKED(IDC_BUTTONReceive, OnBUTTONReceive)

	ON_EN_CHANGE(IDC_EDITSpeed, OnChangeEDITSpeed)
	ON_EN_KILLFOCUS(IDC_EDITSpeed, OnKillfocusEDITSpeed)
	ON_EN_CHANGE(IDC_EDITSlideslip, OnChangeEDITSlideslip)
	ON_EN_KILLFOCUS(IDC_EDITSlideslip, OnKillfocusEDITSlideslip)
	ON_EN_CHANGE(IDC_EDITRoll, OnChangeEDITRoll)
	ON_EN_KILLFOCUS(IDC_EDITRoll, OnKillfocusEDITRoll)
	ON_EN_CHANGE(IDC_EDITPitch, OnChangeEDITPitch)
	ON_EN_KILLFOCUS(IDC_EDITPitch, OnKillfocusEDITPitch)
	ON_EN_CHANGE(IDC_EDITHigh, OnChangeEDITHigh)
	ON_EN_KILLFOCUS(IDC_EDITHigh, OnKillfocusEDITHigh)
	ON_EN_CHANGE(IDC_EDITAzimuth, OnChangeEDITAzimuth)
	ON_EN_KILLFOCUS(IDC_EDITAzimuth, OnKillfocusEDITAzimuth)
	ON_EN_CHANGE(IDC_EDITSpeed_Real, OnChangeEDITSpeedReal)
	ON_EN_KILLFOCUS(IDC_EDITSpeed_Real, OnKillfocusEDITSpeedReal)
	ON_EN_CHANGE(IDC_EDITAirP, OnChangeEDITAirP)
	ON_EN_KILLFOCUS(IDC_EDITAirP, OnKillfocusEDITAirP)
	ON_EN_CHANGE(IDC_EDITAttack, OnChangeEDITAttack)
	ON_EN_KILLFOCUS(IDC_EDITAttack, OnKillfocusEDITAttack)
	ON_EN_CHANGE(IDC_EDITSpeedUD, OnChangeEDITSpeedUD)
	ON_EN_KILLFOCUS(IDC_EDITSpeedUD, OnKillfocusEDITSpeedUD)
	ON_EN_CHANGE(IDC_EDITHighR, OnChangeEDITHighR)
	ON_EN_KILLFOCUS(IDC_EDITHighR, OnKillfocusEDITHighR)
	ON_EN_CHANGE(IDC_EDITHighL, OnChangeEDITHighL)
	ON_EN_KILLFOCUS(IDC_EDITHighL, OnKillfocusEDITHighL)
	ON_EN_CHANGE(IDC_EDITN, OnChangeEditn)
	ON_EN_KILLFOCUS(IDC_EDITN, OnKillfocusEditn)

	ON_EN_CHANGE(IDC_EDITSpeed0, OnChangeEDITSpeed)
	ON_EN_CHANGE(IDC_EDITSlideslip0, OnChangeEDITSlideslip)
	ON_EN_CHANGE(IDC_EDITRoll0, OnChangeEDITRoll)
	ON_EN_CHANGE(IDC_EDITPitch0, OnChangeEDITPitch)
	ON_EN_CHANGE(IDC_EDITHigh0, OnChangeEDITHigh)
	ON_EN_CHANGE(IDC_EDITAzimuth0, OnChangeEDITAzimuth)
	ON_EN_CHANGE(IDC_EDITSpeed_Real0, OnChangeEDITSpeedReal)
	ON_EN_CHANGE(IDC_EDITAirP0, OnChangeEDITAirP)
	ON_EN_CHANGE(IDC_EDITAttack0, OnChangeEDITAttack)
	ON_EN_CHANGE(IDC_EDITSpeedUD0, OnChangeEDITSpeedUD)
	ON_EN_CHANGE(IDC_EDITHighR0, OnChangeEDITHighR)
	ON_EN_CHANGE(IDC_EDITHighL0, OnChangeEDITHighL)
	ON_EN_CHANGE(IDC_EDITN0, OnChangeEditn)

	
	ON_BN_CLICKED(IDC_BUTTONStopTimer, OnBUTTONCLR)	
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIOSelftest, OnRADIOSelftest)
	ON_BN_CLICKED(IDC_RADIONormal, OnRADIONormal)
	ON_BN_CLICKED(IDC_CHECKControl1, OnCHECKControl1)
	ON_BN_CLICKED(IDC_CHECKControl2, OnCHECKControl2)
	ON_EN_KILLFOCUS(IDC_EDITMa, OnKillfocusEDITMa)
	ON_EN_CHANGE(IDC_EDITMa, OnChangeEDITMa)

	ON_BN_CLICKED(IDC_RADIO1, OnButtonBITRATE100K)
	ON_BN_CLICKED(IDC_RADIO2, OnButtonBITRATE48K)
	
	ON_BN_CLICKED(IDC_RADIO4, OnButtonPARITY_NONE)
	ON_BN_CLICKED(IDC_RADIO6, OnButtonPARITY_ODD)
	ON_BN_CLICKED(IDC_RADIO5, OnButtonPARITY_EVEN)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedOnbuttonbitrate12k)

END_MESSAGE_MAP()

// Init function, called when the dialog is created
BOOL CARNIC429Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog. The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Add extra initialization here
	int i,j;

	// default Trigger Level
	stTriggerLevel.Chan0Depth_I = TriggerLevel;
	stTriggerLevel.Chan1Depth_I = TriggerLevel;
	stTriggerLevel.Chan2Depth_I = TriggerLevel; 
	stTriggerLevel.Chan3Depth_I = TriggerLevel;
	stTriggerLevel.Chan0Depth_O = TriggerLevel;
	stTriggerLevel.Chan1Depth_O = TriggerLevel;

	// default Label Filter
	for (i = 0; i < SD_MAX; i++) 
	{
		for (j = 0; j < LABEL_MAX; j++)
		{
			stLabelTable.LabFilterChan0[i][j]=0;
			stLabelTable.LabFilterChan1[i][j]=0;
			stLabelTable.LabFilterChan2[i][j]=0;
			stLabelTable.LabFilterChan3[i][j]=0;
		}
	}
	
	// bits rate & parity
	// �����ʵ�ѡ��
	for (i=0; i<CHNO_TMAX; i++) 
	{	
		// followed definitions can be found in cusfunc.h
		stComm[i].iSelBR = C429_BITRATE100K;		// 0: 100k    1: 48k    2: 12.5k   
		stComm[i].iSelParity = C429_PARITY_NONE;	// 0: odd    1: even    2: none
		wdBInterval[i] = 0;
		wdSInterval[i] = 0;							// 100K / ��У��
	}

	for (i=0; i<CHNO_RMAX; i++)
	{
		blFilter[i] = FALSE;  // disable label filter function
		blTimeTag[i] = FALSE;  // disable Time Tag function
	}

	wdMode=C429_SELFTEST; // SELFTEST work mode

	for(i=0;i<FIFO_RMAX;i++)
		ReceiveData_Vector[i] = 0x0;
	T = 0;
	m_ControlWord1 = 0x00000630;     ////????
	m_ControlWord2 = 0x00000631;    ////????
	Complete_flg = FALSE;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CARNIC429Dlg::SetUp429Card()
{
	WORD wd=0;
	int i=0;
#ifndef CARD_DEBUG
	//	Try to Open card and setting up the card with default configuration
	//

	//  0. open card
	//
	if (!Card_Open(&hCard, btCardId))
	{
		MessageBox(TEXT("�����Ҳ����忨,�����˳�!\n\n(Card_Open��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
		ExitProcess(0);
		//return FALSE; // quit program
	}
	if (hCard==NULL)
	{
		MessageBox(TEXT("�����Ҳ����忨,�����˳�!\n\n(�忨�����ȡʧ��)"), TEXT("����"), MB_OK | MB_ICONERROR);
		ExitProcess(0);
		//return FALSE; // quit program
	}

	//  1. reset card�����ð忨��
	//
	if (!ResetCard(hCard)) // reset Card
	{
		MessageBox(TEXT("��λ�忨ʧ��,�����˳�����!\n\n(ResetCard��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
		if (!Card_Close(hCard))
		{
			MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
		}
		ExitProcess(0);
		//return FALSE; // quit program
	}

	//  2. setting up configure word for communication
	//
	for (i=0; i<CHNO_TMAX; i++)//����ͨ����2ͨ����
	{
		wd = ::Get429ConfigureWord(stComm[i].iSelBR, stComm[i].iSelParity, wdMode);//wdMode����ģʽ
		switch (wd)    
		{
			case 0xFFFF:
				MessageBox("baudrate", "Error", MB_OK);
				break;
			case 0xFFFE:
				MessageBox("parity", "Error", MB_OK);
				break;
			case 0xFFFD:
				MessageBox("workmode", "Error", MB_OK);
				break;
		}
		if (SetConfigureWord(hCard, (BYTE)(i), wd))//���˼��䲨���ʵ�ѡ��//����429 ��������
		{
			if (stComm[i].iSelBR == C429_BITRATE48K) // enable 48k function
			{
				EnableBaudrate_48K(hCard, (BYTE)(i), TRUE);//�˱����£�������ͳһѡ��48k
			}
			else
			{
				EnableBaudrate_48K(hCard, (BYTE)(i), FALSE);
			}
		}
		else
		{
			MessageBox(TEXT("����Ӳ������,�����˳�����!\n\n(SetConfigureWord��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
			if (!Card_Close(hCard))
			{
				MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
			}
			ExitProcess(0);
			//return FALSE; // quit program
		}
	}

	//  3. configuring Trigger Level
	//
	SetTriggerDepth(hCard, &stTriggerLevel);//���ô������

	//  4. setting up Label Filter
	//
	SetLabelFilter(hCard, &stLabelTable);//���ñ�ǩ����
	for (i=0; i<CHNO_RMAX; i++)//ֻ����ڽ���ͨ��
	{
		if (blFilter[i])
		{
			if (!StartLabelFilter(hCard, (BYTE)(i), TRUE))
			{
				MessageBox(TEXT("��ӱ�Ź��˹��ܳ���,�����˳�����!\n\n(StartLabelFilter��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
				if (!Card_Close(hCard))
				{
					MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
				}
				ExitProcess(0);
			//	return FALSE; // quit program
			}
		}
		else
		{
			if (!StartLabelFilter(hCard, (BYTE)(i), FALSE))
			{
				MessageBox(TEXT("ȡ����Ź��˹��ܳ���,�����˳�����!\n\n(StartLabelFilter��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
				if (!Card_Close(hCard))
				{
					MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
				}
				ExitProcess(0);
			//	return FALSE; // quit program
			}
		}
	}

	//  5. configuring Time Tag�����ʱ���ǩ
	//
	for (i=0; i<CHNO_RMAX; i++)
	{
		if (blTimeTag[i])
		{
			if (!AddTimeTag(hCard, (BYTE)(i), TRUE))
			{
				MessageBox(TEXT("���ʱ���ǩ���ܳ���,�����˳�����!\n\n(AddTimeTag��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
				if (!Card_Close(hCard))
				{
					MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
				}
				ExitProcess(0);
			//	return FALSE; // quit program
			}
		}
		else
		{
			if (!AddTimeTag(hCard, (BYTE)(i), FALSE))
			{
				MessageBox(TEXT("ȡ��ʱ���ǩ���ܳ���,�����˳�����!\n\n(AddTimeTag��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
				if (!Card_Close(hCard))
				{
					MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
				}
				ExitProcess(0);
			//	return FALSE; // quit program
			}
		}
	}
	StartTimeTag(hCard, FALSE, &stSysTime); // disable time tag
	dwTime = 0;
	
	//  6. setting up Tx Timer Interval
	//
	for (i=0; i<CHNO_TMAX; i++)//��Ϣ�ķ���
	{
		if (!SetTimerIntervalB(hCard, (BYTE)(i), wdBInterval[i]))//b��Ⱥ��ʱ����
		{
			MessageBox(TEXT("����Ⱥ��ʱ���͹��ܳ���,�����˳�����!\n\n(SetTimerIntervalB��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
			if (!Card_Close(hCard))
			{
				MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
			}
			//ExitProcess(0);
			ExitProcess(0);
		//	return FALSE; // quit program
		}

		if (!SetTimerIntervalS(hCard, (BYTE)(i), wdSInterval[i]))//s���ֶ�ʱ����
		{
			MessageBox(TEXT("�����ֶ�ʱ���͹��ܳ���,�����˳�����!\n\n(SetTimerIntervalS��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
			if (!Card_Close(hCard))
			{
				MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
			}
			ExitProcess(0);
		//	return FALSE; // quit program
		}

		if (wdBInterval[i]>0)
		{
			StartTimerB(hCard, (BYTE)(i), TRUE);// enable Tx Timer//����Ⱥ��ʱ����
		}
		else
		{
			StartTimerB(hCard, (BYTE)(i), FALSE);// disable Tx Timer
		}

		if (wdSInterval[i]>0)
		{
			StartTimerS(hCard, (BYTE)(i), TRUE);// enable Tx Timer//�����ֶ�ʱ����
		}
		else
		{
			StartTimerS(hCard, (BYTE)(i), FALSE);// disable Tx Timer
		}
	}

	if(!Enable_R(hCard,TRUE))//ʹ�ܽ��գ��ڸ�λ�忨ʱ��ֹ�˽���
	{
		MessageBox(TEXT("ʹ�ܽ���ʧ��"), TEXT("����"), MB_OK | MB_ICONERROR);
	}
#endif	
	return TRUE; 
}

void CARNIC429Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CARNIC429Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon��ͼ�꣩
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{	
		int x_mov = 250, y_mov = 10; //ƽ�Ժ��������λ��
		CDC *pMem = new CDC;
		CBitmap *pBmp = new CBitmap;
		CBitmap *pOldBmp;
		CDC *pDC = GetDC();
		CRect rectTemp(10+x_mov,10+y_mov,535+x_mov,460+y_mov);
		pMem->CreateCompatibleDC(pDC);
		pBmp->CreateCompatibleBitmap(pDC,rectTemp.Width(),rectTemp.Height());
		pOldBmp = pMem->SelectObject(pBmp);
		
		OnDraw_SkyRect(pMem);
		OnDraw_Fighter(205+(int)r_Air_Pitch,260+(int)r_Air_Sideslip,pMem);
		OnDraw_High(r_Air_High,pMem);
		OnDraw_Speed(r_Air_Speed,pMem);	
		OnDraw_HXJ(r_Air_Azimuth,pMem);//��λ��
		OnDraw_HGKD(r_Air_Roll,pMem);
		OnDraw_HG(-r_Air_Roll,r_Air_Pitch,pMem);
		
		pDC->BitBlt(rectTemp.left,rectTemp.top,rectTemp.Width(),rectTemp.Height(),pMem,0,0,SRCCOPY);		
		pMem->SelectObject(pOldBmp);
		pBmp->DeleteObject() ;
		pMem->DeleteDC();

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CARNIC429Dlg::OnQueryDragIcon()//demo
{
	return (HCURSOR) m_hIcon;
}
//����ʮ���ߺ��ٶ�ʸ��
void CARNIC429Dlg::OnDraw_Fighter(int x,int y,CDC* pDC)//����ʮ���ߺ��ٶ�ʸ��
{
	

		CPen GreenPen,WhitePen;
		GreenPen.CreatePen(PS_SOLID, 2, RGB(0, 250, 0));
		WhitePen.CreatePen(PS_SOLID, 2, RGB(250, 250, 250));

		//poldPen =pDC->SelectObject(&WhitePen);
		//pDC->SetArcDirection(AD_CLOCKWISE);   //˳ʱ��
		//pDC->Arc(CRect(30, 30, 150, 150), CPoint(30, 90), CPoint(90, 30));
		//pDC->Arc(CRect(375, 320, 495, 440), CPoint(495, 380), CPoint(435, 440));
		//pDC->SetArcDirection(AD_COUNTERCLOCKWISE);   //��ʱ��
		//pDC->Arc(CRect(30, 320, 150, 440), CPoint(30, 380), CPoint(90, 440));
		//pDC->Arc(CRect(375, 30, 495, 150), CPoint(495, 90), CPoint(435, 30));
		//pDC->MoveTo(30, 90);
		//pDC->LineTo(30, 380);
		//pDC->MoveTo(495, 90);
		//pDC->LineTo(495,380);//ֱ�߽߱� 
		
		
		CPen*poldPen = pDC->SelectObject(&WhitePen);
		pDC->MoveTo(260,190);
		pDC->LineTo(260,220);
		pDC->MoveTo(245,205);
		pDC->LineTo(275,205);			
	    pDC->Arc(y-radius,x-radius,y+radius,x+radius,y-radius,x-radius,y-radius,x-radius);	
		pDC->MoveTo(y-radius,x);
		pDC->LineTo(y-radius-10,x);
		pDC->MoveTo(y+radius,x);
		pDC->LineTo(y+radius+10,x);
		pDC->MoveTo(y,x-radius);
		pDC->LineTo(y,x-radius-10);

		

		if(r_Air_High<=r_Air_HighL)
		{
			pDC->MoveTo(y-20,x-5);
			pDC->LineTo(y-20,x+10);
			pDC->MoveTo(y-20,x+10);
			pDC->LineTo(y-1,x+10);
			pDC->MoveTo(y+1,x+10);
			pDC->LineTo(y+20,x+10);
			pDC->MoveTo(y+20,x+10);
			pDC->LineTo(y+20,x-5);
		}
			
		pDC->SelectObject(poldPen);	
}
//���߶�
void CARNIC429Dlg::OnDraw_High(int x,CDC* pDC)
{
	char c[80];
	int a;
	unsigned int ad;
	unsigned int High_cas,High_casD,High_casU;
	int i,j;
	int text_offset = 7;

	CPen pNewPen;
	pNewPen.CreatePen(PS_SOLID ,2,RGB(0,250,0)); 
	CPen* poldPen=pDC->SelectObject(&pNewPen);
	pDC->SetTextColor(RGB(0,250,0));
	pDC->SetBkMode(TRANSPARENT);

	pDC->MoveTo(390,205);
	pDC->LineTo(420,205);
	pDC->TextOutA(431, 356, _T("FY.T"));
	pDC->TextOutA(431, 376, _T("NAV GPS"));
	pDC->TextOutA(400, 208, _T("U"));
	itoa(r_Air_SpeedUD, c, 10);
	if (r_Air_SpeedUD < 10)
	{
		pDC->TextOutA(400, 188, c);
	}
	else if (r_Air_SpeedUD < 100)
	{
		pDC->TextOutA(396, 36, c);
	}
	else if (r_Air_SpeedUD < 1000)
	{
		pDC->TextOutA(392, 36, c);
	}
	else if (r_Air_SpeedUD < 10000)
	{
		pDC->TextOutA(388, 36, c);
	}
	else
	{
		pDC->TextOutA(384, 36, c);
	}
	pDC->TextOutA(400, 188, c);

	gcvt(r_Air_AirP, 4, c);
	pDC->TextOutA(431, 16, _T("BP"));
	pDC->TextOutA(451, 16, c);

	pDC->TextOutA(431,36,_T("H"));


	itoa(x,c,10);//����ת��Ϊ�ַ���
	if(x<10)
	{
		pDC->TextOutA(451,36,c);
	}
	else if(x<100)
	{
		pDC->TextOutA(447,36,c);
	}
	else if(x<1000)
	{
		pDC->TextOutA(443,36,c);
	}
	else if(x<10000)
	{
		pDC->TextOutA(439,36,c);
	}
	else
	{
		pDC->TextOutA(435,36,c);
	}

	a = x % 500;
	ad = a/10;

	High_cas = x/500*500;
	
	itoa(High_cas,c,10);
	pDC->TextOutA(450,198+ad,c);
	pDC->MoveTo(425,205+ad);
	pDC->LineTo(445,205+ad);
	
	for(i = 1;i<5;i++)
	{
		j = i * 10;
		pDC->MoveTo(425,205+ad-j);
		pDC->LineTo(435,205+ad-j);
	}

	for(i = 1;i<15;i++)
	{
		j = i*10;
		pDC->MoveTo(425,205+ad-j-(ad/10)*10);
		pDC->LineTo(435,205+ad-j-(ad/10)*10);
	}
	for(i = 1;i<15;i++)
	{
		j = i*10;
		pDC->MoveTo(425,205+ad+j-(ad/10)*10);
		pDC->LineTo(435,205+ad+j-(ad/10)*10);
	}

	if(a<100)
	{
		pDC->MoveTo(425,205+ad-50);
		pDC->LineTo(445,205+ad-50);
		High_casU = High_cas + 500;
		itoa(High_casU,c,10);
		pDC->TextOutA(450,205+ad-50-text_offset,c);

		pDC->MoveTo(425,205+ad-100);
		pDC->LineTo(445,205+ad-100);
		High_casU = High_cas + 1000;
		itoa(High_casU,c,10);
		pDC->TextOutA(450,205+ad-100-text_offset,c);
	}
	else
	{
		pDC->MoveTo(425,205+ad-50);
		pDC->LineTo(445,205+ad-50);
		High_casU = High_cas + 500;
		itoa(High_casU,c,10);
		pDC->TextOutA(450,205+ad-50-text_offset,c);

		pDC->MoveTo(425,205+ad-100);
		pDC->LineTo(445,205+ad-100);
		High_casU = High_cas + 1000;
		itoa(High_casU,c,10);
		pDC->TextOutA(450,205+ad-100-text_offset,c);

		pDC->MoveTo(425,205+ad-150);
		pDC->LineTo(445,205+ad-150);
		High_casU = High_cas + 1500;
		itoa(High_casU,c,10);
		pDC->TextOutA(450,205+ad-150-text_offset,c);
	}
	if(a>400)
	{
		pDC->MoveTo(435,205+ad+50);
		pDC->LineTo(445,205+ad+50);
		High_casD = High_cas - 500;
		itoa(High_casD,c,10);
		pDC->TextOutA(450,205+ad+50-text_offset,c);
	}
	else
	{
		pDC->MoveTo(435,205+ad+50);
		pDC->LineTo(445,205+ad+50);
		High_casD = High_cas - 500;
		itoa(High_casD,c,10);
		pDC->TextOutA(450,205+ad+50-text_offset,c);

		pDC->MoveTo(425,205+ad+100);
		pDC->LineTo(445,205+ad+100);
		High_casD = High_cas - 1000;
		itoa(High_casD,c,10);
		pDC->TextOutA(450,205+ad+100-text_offset,c);
	}
	pDC->SelectObject(poldPen);	
}
//���ٶ�
void CARNIC429Dlg::OnDraw_Speed(int x,CDC* pDC)
{
	char c[80];
	int a;
	unsigned int ad;
	unsigned int V_cas,V_casD,V_casU;
	int i,j;
	int text_offset = 7;
	int amp = 2;

	CPen pNewPen;
	pNewPen.CreatePen(PS_SOLID ,2,RGB(0,250,0)); 
	CPen* poldPen=pDC->SelectObject(&pNewPen);
	pDC->SetTextColor(RGB(0,255,0));
	pDC->SetBkMode(TRANSPARENT);

	pDC->MoveTo(100,205);
	pDC->LineTo(130,205);
	
	pDC->TextOutA(52, 376, _T(".CCIL"));

	gcvt(r_Air_Ma,2,c);
	pDC->TextOutA(52,36,_T("Ma"));
	pDC->TextOutA(72,36,c);

	gcvt(r_Air_N, 2, c);
	pDC->TextOutA(52,356, _T("N"));
	pDC->TextOutA(72,356, c);

	gcvt(r_Air_Attack, 4, c);
	pDC->TextOutA(112,208, _T("A"));
	pDC->TextOutA(112, 188, c);

	pDC->TextOutA(52,16,_T("T"));
itoa(x,c,10);//x����ת�������ݣ�c:Ŀ���ַ����ĵ�ַ��10��ʮ����
	if(x<10)
	{
		pDC->TextOutA(72,16,c);
	}
	else if(x<100)
	{
		pDC->TextOutA(72,16,c);
	}
	else if(x<1000)
	{
		pDC->TextOutA(68,16,c);
	}
	else
	{
		pDC->TextOutA(68,16,c);
	}

	a = x % 25;
	ad = a/5;
	V_cas = x/25*25;
	
	itoa(V_cas,c,10);
	if(x<10)
	{
		pDC->TextOutA(64,198+a*amp,c);
	}
	else if(x<100)
	{
		pDC->TextOutA(56,198+a*amp,c);
	}
	else if(x<1000)
	{
		pDC->TextOutA(48,198+a*amp,c);
	}
	else
	{
		pDC->TextOutA(40,198+a*amp,c);
	}

	pDC->MoveTo(95,205+a*amp);
	pDC->LineTo(75,205+a*amp);
	
	for(i = 1;i<5;i++)
	{
		j = i * 5;
		pDC->MoveTo(95,205+(a-j)*amp);
		pDC->LineTo(85,205+(a-j)*amp);
	}
	
	for(i = 1;i<15;i++)
	{
		j = i*5;
		pDC->MoveTo(95,205+(a-j-ad*5)*amp);
		pDC->LineTo(85,205+(a-j-ad*5)*amp);
	}
	for(i = 1;i<15;i++)
	{
		j = i*5;
		pDC->MoveTo(95,205+(a+j-ad*5)*amp);
		pDC->LineTo(85,205+(a+j-ad*5)*amp);
	}

	if(a<5)
	{
		pDC->MoveTo(95,205+(a-25)*amp);
		pDC->LineTo(75,205+(a-25)*amp);
		V_casU = V_cas + 25;
		itoa(V_casU,c,10);
		if(x<10)
		{
			pDC->TextOutA(56,205+(a-25)*amp-text_offset,c);
		}
		else if(x<100)
		{
			pDC->TextOutA(48,205+(a-25)*amp-text_offset,c);
		}
		else if(x<1000)
		{
			pDC->TextOutA(40,205+(a-25)*amp-text_offset,c);
		}
		else
		{
			pDC->TextOutA(32,205+(a-25)*amp-text_offset,c);
		}

		pDC->MoveTo(95,205+(a-50)*amp);
		pDC->LineTo(75,205+(a-50)*amp);
		V_casU = V_cas + 50;
		itoa(V_casU,c,10);
		if(x<10)
		{
			pDC->TextOutA(56,205+(a-50)*amp-text_offset,c);
		}
		else if(x<100)
		{
			pDC->TextOutA(48,205+(a-50)*amp-text_offset,c);
		}
		else if(x<1000)
		{
			pDC->TextOutA(40,205+(a-50)*amp-text_offset,c);
		}
		else
		{
			pDC->TextOutA(32,205+(a-50)*amp-text_offset,c);
		}

	}
	else
	{
		pDC->MoveTo(95,205+(a-25)*amp);
		pDC->LineTo(75,205+(a-25)*amp);
		V_casU = V_cas + 25;
		itoa(V_casU,c,10);
		if(x<10)
		{
			pDC->TextOutA(56,205+(a-25)*amp-text_offset,c);
		}
		else if(x<100)
		{
			pDC->TextOutA(48,205+(a-25)*amp-text_offset,c);
		}
		else if(x<1000)
		{
			pDC->TextOutA(40,205+(a-25)*amp-text_offset,c);
		}
		else
		{
			pDC->TextOutA(32,205+(a-25)*amp-text_offset,c);
		}


		pDC->MoveTo(95,205+(a-50)*amp);
		pDC->LineTo(75,205+(a-50)*amp);
		V_casU = V_cas + 50;
		itoa(V_casU,c,10);
		if(x<10)
		{
			pDC->TextOutA(56,205+(a-50)*amp-text_offset,c);
		}
		else if(x<100)
		{
			pDC->TextOutA(48,205+(a-50)*amp-text_offset,c);
		}
		else if(x<1000)
		{
			pDC->TextOutA(40,205+(a-50)*amp-text_offset,c);
		}
		else
		{
			pDC->TextOutA(32,205+(a-50)*amp-text_offset,c);
		}

		pDC->MoveTo(95,205+(a-75)*amp);
		pDC->LineTo(75,205+(a-75)*amp);
		V_casU = V_cas + 75;
		itoa(V_casU,c,10);
		if(x<10)
		{
			pDC->TextOutA(56,205+(a-75)*amp-text_offset,c);
		}
		else if(x<100)
		{
			pDC->TextOutA(48,205+(a-75)*amp-text_offset,c);
		}
		else if(x<1000)
		{
			pDC->TextOutA(40,205+(a-75)*amp-text_offset,c);
		}
		else
		{
			pDC->TextOutA(32,205+(a-75)*amp-text_offset,c);
		}
	}
	if(a>20)
	{
		pDC->MoveTo(95,205+(a+25)*amp);
		pDC->LineTo(75,205+(a+25)*amp);
		V_casD = V_cas - 25;
		itoa(V_casD,c,10);
		if(x<10)
		{
			pDC->TextOutA(56,205+(a+25)*amp-text_offset,c);
		}
		else if(x<100)
		{
			pDC->TextOutA(48,205+(a+25)*amp-text_offset,c);
		}
		else if(x<1000)
		{
			pDC->TextOutA(40,205+(a+25)*amp-text_offset,c);
		}
		else
		{
			pDC->TextOutA(32,205+(a+25)*amp-text_offset,c);
		}
	}
	else
	{
		pDC->MoveTo(95,205+(a+25)*amp);
		pDC->LineTo(75,205+(a+25)*amp);
		V_casD = V_cas - 25;
		itoa(V_casD,c,10);
		if(x<10)
		{
			pDC->TextOutA(50,205+(a+25)*amp-text_offset,c);
		}
		else if(x<100)
		{
			pDC->TextOutA(50,205+(a+25)*amp-text_offset,c);
		}
		else if(x<1000)
		{
			pDC->TextOutA(42,205+(a+25)*amp-text_offset,c);
		}
		else
		{
			pDC->TextOutA(34,205+(a+25)*amp-text_offset,c);
		}

		pDC->MoveTo(95,205+(a+50)*amp);
		pDC->LineTo(75,205+(a+50)*amp);
		V_casD = V_cas - 50;
		itoa(V_casD,c,10);
		if(x<10)
		{
			pDC->TextOutA(50,205+(a+50)*amp-text_offset,c);
		}
		else if(x<100)
		{
			pDC->TextOutA(50,205+(a+50)*amp-text_offset,c);
		}
		else if(x<1000)
		{
			pDC->TextOutA(42,205+(a+50)*amp-text_offset,c);
		}
		else
		{
			pDC->TextOutA(34,205+(a+50)*amp-text_offset,c);
		}
	}
	pDC->SelectObject(poldPen);
}

//����
void CARNIC429Dlg::OnDraw_BlackRect(CDC* pDC)
{
	CRect rect(0,0,600,530);
	CBrush brush;
	brush.CreateSolidBrush(RGB(0,0,0));
	pDC->FillRect(rect,&brush);
}

//��������ձ�����
void CARNIC429Dlg::OnDraw_SkyRect(CDC* pDC)
{

	CRect rect(0, 0, 600, 530);
	CBrush brush;
	CDC   dcBmp;             //���岢����һ���ڴ��豸����
	CBitmap   bmpBackground;  //����λͼ���
	bmpBackground.LoadBitmap(IDB_BITMAP1);    //��λͼ��Դ����λͼ�����
	brush.CreatePatternBrush(&bmpBackground);  //����λͼ��ˢ��
	pDC->FillRect(rect, &brush);
}

//����λ��
void CARNIC429Dlg::OnDraw_HXJ(double x,CDC *pDC)
{
	//CDC *pDC = GetDC();
	int HX_int;
	int HX_cas,HX_casL;
	unsigned int a;
	unsigned int al;
	int i,j;
	unsigned int amp = 4;
	char c[80];

	pDC->SetTextColor(RGB(0,250,0));
	pDC->SetBkMode(TRANSPARENT);
	CPen pNewPen;
	pNewPen.CreatePen(PS_SOLID ,2,RGB(0,250,0)); 
	CPen* poldPen=pDC->SelectObject(&pNewPen);

	HX_int = (int)x;
	pDC->MoveTo(260,80);
	pDC->LineTo(260,60);
	
	a = x * 4;
	HX_int = (int)a;
	HX_cas = HX_int/80 * 20;
	a = HX_int%80;   

	pDC->MoveTo(260-a,55);
	pDC->LineTo(260-a,40);	
		
	al = a/25 ;//����ѻ�������������Χ��0~3��
	for(i=-6;i<7;i++)
	{
		j = i*5;
		pDC->MoveTo(260-a+(al*5-j)*amp,55);
		pDC->LineTo(260-a+(al*5-j)*amp,45);
	}

	for(i=-1;i<2;i++)
	{
		pDC->MoveTo(260-a+20*i*amp,55);
		pDC->LineTo(260-a+20*i*amp,35);
		if(HX_cas==0&&i==-2)
		{
			HX_casL = 320;
		}
		else if(HX_cas==0&&i==-1)
		{
			HX_casL = 340;
		}
		else if(HX_cas==20&&i==-2)
		{
			HX_casL = 340;
		}
		else if(HX_cas==340&&i==1)
		{
			HX_casL = 0;
		}
		else if(HX_cas==340&&i==2)
		{
			HX_casL = 20;
		}
		else if(HX_cas==320&&i==2)
		{
			HX_casL = 0;
		}
		else
		{
			HX_casL = HX_cas + 20*i;
		}
		itoa(HX_casL,c,10);
		if(HX_casL<10)
		{
			pDC->TextOutA(260-a+20*i*amp-4,17,c);
		}
		else if(HX_casL<100)
		{
			pDC->TextOutA(260-a+20*i*amp-8,17,c);
		}
		else
		{
			pDC->TextOutA(260-a+20*i*amp-12,17,c);
		}
	}		
	pDC->SelectObject(poldPen);	
}

//����ת��
void CARNIC429Dlg::OnDraw_HGKD(double HGJ,CDC *pDC)
{
	//CDC *pDC = GetDC();
	char c[80];
	int i;
	int R = 215;
	int r = 185;
	int dr = 200;
	double x,y;
	double theta;
	int x1,y1;
	int text;
	
	CPen pNewPen;
	pNewPen.CreatePen(PS_SOLID ,2,RGB(0,250,0)); 
	CPen* poldPen=pDC->SelectObject(&pNewPen);

	HGJ = HGJ/180*PI;
	for(i = 0;i<5;i++)
	{
		x = 260 + R*cos(PI/3+i*PI/12);
		y = 205 + R*sin(PI/3+i*PI/12);
		x1 = (int)x;
		y1 = (int)y;
		pDC->MoveTo(x1,y1);
		x = 260 + r*cos(PI/3+i*PI/12);
		y = 205 + r*sin(PI/3+i*PI/12);
		x1 = (int)x;
		y1 = (int)y;
		pDC->LineTo(x1,y1);
	}
		itoa(-180,c,10);
		pDC->TextOutA(335,345,c);
		itoa(-90,c,10);
		pDC->TextOutA(293,365,c);
		itoa(0,c,10);
		pDC->TextOutA(255,370,c);
		itoa(90,c,10);
		pDC->TextOutA(205,365,c);
		itoa(180,c,10);
		pDC->TextOutA(155,345,c);
	for(i = 0;i<13;i++)
	{
		x = 260 + R*cos(PI/3+i*PI/36);
		y = 205 + R*sin(PI/3+i*PI/36);
		x1 = (int)x;
		y1 = (int)y;
		pDC->MoveTo(x1,y1);
		x = 260 + dr*cos(PI/3+i*PI/36);
		y = 205 + dr*sin(PI/3+i*PI/36);
		x1 = (int)x;
		y1 = (int)y;
		pDC->LineTo(x1,y1);
	}


	x = 260 + (R+5)*cos(PI/2+HGJ/6);
	y = 205 + (R+5)*sin(PI/2+HGJ/6);
	x1 = (int)(x+0.5);
	y1 = (int)(y+0.5);
	pDC->MoveTo(x1,y1);

	x = 252-260;
	y = 435-205;
	R = sqrt(x*x+y*y);
	theta = atan(x/y);
	x = 260 + R*cos(PI/2+HGJ/6+theta);
	y = 205 + R*sin(PI/2+HGJ/6+theta);
	x1 = (int)(x+0.5);
	y1 = (int)(y+0.5);
	pDC->LineTo(x1,y1);

	x = 268-260;
	y = 435-205;
	R = sqrt(x*x+y*y);
	theta = atan(x/y);
	x = 260 + R*cos(PI/2+HGJ/6+theta);
	y = 205 + R*sin(PI/2+HGJ/6+theta);
	x1 = (int)(x+0.5);
	y1 = (int)(y+0.5);
	pDC->LineTo(x1,y1);

	y = 425 - 205;
	R = (int)y;
	x = 260 + R*cos(PI/2+HGJ/6);
	y = 205 + R*sin(PI/2+HGJ/6);
	x1 = (int)(x+0.5);
	y1 = (int)(y+0.5);
	pDC->LineTo(x1,y1);	
	pDC->SelectObject(poldPen);
}

void  CARNIC429Dlg::OnDraw_HG(double HGJ,double FYJ,CDC *pDC)
{
	char c[80];
	int a;
	int i,j,k;
	double x,y,R;
	int x1,y1;
	double theta;
	int FYJ_int;
	int FYJ_cas;
	int amp = 20;
	int text_offset = 12;
	CPen pNewPen;
	pNewPen.CreatePen(PS_SOLID ,2,RGB(0,250,0)); 
	CPen* poldPen=pDC->SelectObject(&pNewPen);
	pDC->SetTextColor(RGB(0,250,0));
	pDC->SetBkMode(TRANSPARENT);	

	 CFont font;
     LOGFONT lf;
     memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	 //��&if�е�ǰλ�ú����sizeof���ֽ� ��typedef unsigned int size_t ���� 0 �滻������ lf��
     lf.lfHeight = 17;                      // request a 12-pixel-height font
     lf.lfEscapement = HGJ * 10;
     VERIFY(font.CreateFontIndirect(&lf));  // create the font
	 pDC->SelectObject(&font);

	HGJ = -HGJ/180*PI;

	FYJ_int = (int)FYJ;
	FYJ_cas = FYJ_int/5*5;
	FYJ_int = FYJ * amp;
	a = FYJ_int % 100;


	for(i = -1;i<2;i++)
	{
		j = i*5;
		if(FYJ_cas+j>=0)
		{
			x = 240 - 260;
			y = -a + j*amp;
			R = x*x + y*y;
			R = sqrt(R);
			theta = atan(y/x);
			if(x<0&&y<0)
			{
				theta = theta - PI;
			}
			else if(x<0&&y>=0)
			{
				theta = theta +PI;
			}
			x = 260 + R *cos(theta+HGJ);
			y = 205 + R *sin(theta+HGJ);
			x1 = (int)(x+0.5);
			y1 = (int)(y+0.5);
			pDC->MoveTo(x1,y1);

			x = 180 - 260;
			y = -a + j*amp;
			R = x*x + y*y;
			R = sqrt(R);
			theta = atan(y/x);
			if(x<0&&y<0)
			{
				theta = theta - PI;
			 }
			else if(x<0&&y>=0)
			{
				theta = theta +PI;
			}
			x = 260 + R *cos(theta+HGJ);
			y = 205 + R *sin(theta+HGJ);
			x1 = (int)(x+0.5);
			y1 = (int)(y+0.5);
			pDC->LineTo(x1,y1);

			x = 180 - 260;
			y = -a+j*amp-10;
			R = x*x + y*y;
			R = sqrt(R);
			theta = atan(y/x);
			if(x<0&&y<0)
			{
				theta = theta - PI;
			}
			else if(x<0&&y>=0)
			{
				theta = theta +PI;
			}
			x = 260 + R *cos(theta+HGJ);
			y = 205 + R *sin(theta+HGJ);
			x1 = (int)(x+0.5);
			y1 = (int)(y+0.5);
			pDC->LineTo(x1,y1);

	
			x = 280 - 260;
			y = -a+j*amp;
			R = x*x + y*y;
			R = sqrt(R);
			theta = atan(y/x);
			if(x<0&&y<0)
			{
				theta = theta - PI;
			}
			else if(x<0&&y>=0)
			{
				theta = theta +PI;
			}
			x = 260 + R *cos(theta+HGJ);
			y = 205 + R *sin(theta+HGJ);
			x1 = (int)(x+0.5);
			y1 = (int)(y+0.5);
			pDC->MoveTo(x1,y1);

			x = 340 - 260;
			y = -a+j*amp;
			R = x*x + y*y;
			R = sqrt(R);
			theta = atan(y/x);
			if(x<0&&y<0)
			{
				theta = theta - PI;
			}
			else if(x<0&&y>=0)
			{
				theta = theta +PI;
			}
			x = 260 + R *cos(theta+HGJ);
			y = 205 + R *sin(theta+HGJ);
			x1 = (int)(x+0.5);
			y1 = (int)(y+0.5);
			pDC->LineTo(x1,y1);

			x = 340 - 260;
			y = -a+j*amp-10;
			R = x*x + y*y;
			R = sqrt(R);
			theta = atan(y/x);
			if(x<0&&y<0)
			{
				theta = theta - PI;
			}
			else if(x<0&&y>=0)
			{
				theta = theta +PI;
			}
			x = 260 + R *cos(theta+HGJ);
			y = 205 + R *sin(theta+HGJ);
			x1 = (int)(x+0.5);
			y1 = (int)(y+0.5);
			pDC->LineTo(x1,y1);
		}
		else
		{
			x = 240 - 260;
			y = -a + j*amp;
			R = x*x + y*y;
			R = sqrt(R);
			theta = atan(y/x);
			if(x<0&&y<0)
			{
				theta = theta - PI;
			}
			else if(x<0&&y>=0)
			{
				theta = theta +PI;
			}
			x = 260 + R *cos(theta+HGJ);
			y = 205 + R *sin(theta+HGJ);
			x1 = (int)(x+0.5);
			y1 = (int)(y+0.5);
			pDC->MoveTo(x1,y1);

			for(k=1;k<=30;k=k+2)
			{
				x = 240 - k*2 - 260;
				y = -a + j*amp;
				R = x*x + y*y;
				R = sqrt(R);
				theta = atan(y/x);
				if(x<0&&y<0)
				{
					theta = theta - PI;
				}
				else if(x<0&&y>=0)
				{
					theta = theta +PI;
				}
				x = 260 + R *cos(theta+HGJ);
				y = 205 + R *sin(theta+HGJ);
				x1 = (int)(x+0.5);
				y1 = (int)(y+0.5);
				pDC->LineTo(x1,y1);

				x = 240 - (k+1)*2 - 260;
				y = -a + j*amp;
				R = x*x + y*y;
				R = sqrt(R);
				theta = atan(y/x);
				if(x<0&&y<0)
				{
					theta = theta - PI;
				}
				else if(x<0&&y>=0)
				{
					theta = theta +PI;
				}
				x = 260 + R *cos(theta+HGJ);
				y = 205 + R *sin(theta+HGJ);
				x1 = (int)(x+0.5);
				y1 = (int)(y+0.5);
				pDC->MoveTo(x1,y1);
			}

			x = 180 - 260;
			y = -a+j*amp-10;
			R = x*x + y*y;
			R = sqrt(R);
			theta = atan(y/x);
			if(x<0&&y<0)
			{
				theta = theta - PI;
			}
			else if(x<0&&y>=0)
			{
				theta = theta +PI;
			}
			x = 260 + R *cos(theta+HGJ);
			y = 205 + R *sin(theta+HGJ);
			x1 = (int)(x+0.5);
			y1 = (int)(y+0.5);
			pDC->LineTo(x1,y1);


			x = 280 - 260;
			y = -a+j*amp;
			R = x*x + y*y;
			R = sqrt(R);
			theta = atan(y/x);
			if(x<0&&y<0)
			{
				theta = theta - PI;
			}
			else if(x<0&&y>=0)
			{
				theta = theta +PI;
			}
			x = 260 + R *cos(theta+HGJ);
			y = 205 + R *sin(theta+HGJ);
			x1 = (int)(x+0.5);
			y1 = (int)(y+0.5);
			pDC->MoveTo(x1,y1);

			for(k=1;k<=30;k=k+2)
			{
				x = 280 + k*2 - 260;
				y = -a + j*amp;
				R = x*x + y*y;
				R = sqrt(R);
				theta = atan(y/x);
				if(x<0&&y<0)
				{
					theta = theta - PI;
				}
				else if(x<0&&y>=0)
				{
					theta = theta +PI;
				}
				x = 260 + R *cos(theta+HGJ);
				y = 205 + R *sin(theta+HGJ);
				x1 = (int)(x+0.5);
				y1 = (int)(y+0.5);
				pDC->LineTo(x1,y1);

				x = 280+(k+1)*2 - 260;
				y = -a + j*amp;
				R = x*x + y*y;
				R = sqrt(R);
				theta = atan(y/x);
				if(x<0&&y<0)
				{
					theta = theta - PI;
				}
				else if(x<0&&y>=0)
				{
					theta = theta +PI;
				}
				x = 260 + R *cos(theta+HGJ);
				y = 205 + R *sin(theta+HGJ);
				x1 = (int)(x+0.5);
				y1 = (int)(y+0.5);
				pDC->MoveTo(x1,y1);
			}

			x = 340 - 260;
			y = -a+j*amp-10;
			R = x*x + y*y;
			R = sqrt(R);
			theta = atan(y/x);
			if(x<0&&y<0)
			{
				theta = theta - PI;
			}
			else if(x<0&&y>=0)
			{
				theta = theta +PI;
			}
			x = 260 + R *cos(theta+HGJ);
			y = 205 + R *sin(theta+HGJ);
			x1 = (int)(x+0.5);
			y1 = (int)(y+0.5);
			pDC->LineTo(x1,y1);
		}
		itoa(FYJ_cas+j,c,10);
		
		//��ษ�����ַ�
		x = 160 - 260;
		y = -a+j*amp-text_offset;
		R = x*x + y*y;
		R = sqrt(R);
		theta = atan(y/x);
		if(x<0&&y<0)
		{
			theta = theta - PI;
		}
		else if(x<0&&y>=0)
		{
			theta = theta +PI;
		}
		x = 260 + R *cos(theta+HGJ);
		y = 205 + R *sin(theta+HGJ);
		x1 = (int)(x+0.5);
		y1 = (int)(y+0.5);
		pDC->TextOutA(x1,y1,c);

		//�Ҳษ�����ַ�
		x = 350 - 260;
		y = -a+j*amp-text_offset;
		R = x*x + y*y;
		R = sqrt(R);
		theta = atan(y/x);
		if(x<0&&y<0)
		{
			theta = theta - PI;
		}
		else if(x<0&&y>=0)
		{
			theta = theta +PI;
		}
		x = 260 + R *cos(theta+HGJ);
		y = 205 + R *sin(theta+HGJ);
		x1 = (int)(x+0.5);
		y1 = (int)(y+0.5);
		pDC->TextOutA(x1,y1,c);
	}
	pDC->SelectObject(poldPen);
}


////////////////////////////////////////�ӶԻ�����ȡ����////////////////////////////////////////////////////
void CARNIC429Dlg::OnChangeEDITSpeed() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80], s[80],f[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;
	int ii = 0;
	float ff = 0;

	l = this->s_Edit_Speed.LineLength(-1);
	if (l==0)
		return;

	memset(s, 0, sizeof(s));//s��c����������ʼ��Ϊ��
	memset(c, 0, sizeof(c));

	dw = this->s_Edit_Speed.GetSel();

	this->s_Edit_Speed.GetWindowText(c, sizeof(c)); // get data string with 

	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if ((tc>='0')&&(tc<='9'))
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}

	if (!isErr)
	{
		ii = atoi(c);//�ַ���ת��Ϊ����
		ff = ii/3.6/340;
		sprintf(f,"%f",ff);
		this->s_Edit_Ma.SetWindowText("3");
		return;
	}

	//  write back the HEX value
	//
	ii = atoi(s);
	ff = ii/3.6/340;
	sprintf(f,"%f",ff);
	this->s_Edit_Ma.SetWindowText(f);
	this->s_Edit_Speed.SetWindowText(s);
	this->s_Edit_Speed.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);
}

void CARNIC429Dlg::OnKillfocusEDITSpeed() 
{
	// TODO: Add your control notification handler code here
	if (this->s_Edit_Speed.LineLength(-1)==0)
	{
		this->s_Edit_Speed.SetWindowText(TEXT("0"));
	}	
}

void CARNIC429Dlg::OnChangeEDITSlideslip() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;

	l = this->s_Edit_Sideslip.LineLength(-1);
	if (l==0)
		return;

	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));

	dw = this->s_Edit_Sideslip.GetSel();

	this->s_Edit_Sideslip.GetWindowText(c, sizeof(c)); // get data string with HEX

	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if ((tc>='0')&&(tc<='9')||tc=='.'||tc=='-')
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}

	if (!isErr)
		return;

	//  write back the HEX value
	//
	this->s_Edit_Sideslip.SetWindowText(s);
	this->s_Edit_Sideslip.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);
}

void CARNIC429Dlg::OnKillfocusEDITSlideslip() 
{
	// TODO: Add your control notification handler code here
	if (this->s_Edit_Sideslip.LineLength(-1)==0)
	{
		this->s_Edit_Sideslip.SetWindowText(TEXT("0"));
	}	
}

void CARNIC429Dlg::OnChangeEDITRoll() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;

	l = this->s_Edit_Roll.LineLength(-1);
	if (l==0)
		return;

	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));

	dw = this->s_Edit_Roll.GetSel();

	this->s_Edit_Roll.GetWindowText(c, sizeof(c)); // get data string with HEX

	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if ((tc>='0')&&(tc<='9')||tc=='.'||tc=='-')
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}

	if (!isErr)
		return;

	//  write back the HEX value
	//
	this->s_Edit_Roll.SetWindowText(s);
	this->s_Edit_Roll.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);
}

void CARNIC429Dlg::OnKillfocusEDITRoll() 
{
	// TODO: Add your control notification handler code here
	if (this->s_Edit_Roll.LineLength(-1)==0)
	{
		this->s_Edit_Roll.SetWindowText(TEXT("0"));
	}
	
}

void CARNIC429Dlg::OnChangeEDITPitch() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;

	l = this->s_Edit_Pitch.LineLength(-1);
	if (l==0)
		return;

	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));

	dw = this->s_Edit_Pitch.GetSel();

	this->s_Edit_Pitch.GetWindowText(c, sizeof(c)); // get data string with HEX

	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if ((tc>='0')&&(tc<='9')||tc=='.'||tc=='-')
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}

	if (!isErr)
		return;

	//  write back the HEX value
	//
	this->s_Edit_Pitch.SetWindowText(s);
	this->s_Edit_Pitch.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);
}

void CARNIC429Dlg::OnKillfocusEDITPitch() 
{
	// TODO: Add your control notification handler code here
	if (this->s_Edit_Pitch.LineLength(-1)==0)
	{
		this->s_Edit_Pitch.SetWindowText(TEXT("0"));
	}	
}

void CARNIC429Dlg::OnChangeEDITHigh() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;

	l = this->s_Edit_High.LineLength(-1);
	if (l==0)
		return;

	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));

	dw = this->s_Edit_High.GetSel();

	this->s_Edit_High.GetWindowText(c, sizeof(c)); // get data string with HEX

	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if ((tc>='0')&&(tc<='9'))
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}

	if (!isErr)
		return;

	//  write back the HEX value
	//
	this->s_Edit_High.SetWindowText(s);
	this->s_Edit_High.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);
}

void CARNIC429Dlg::OnKillfocusEDITHigh() 
{
	// TODO: Add your control notification handler code here
	if (this->s_Edit_High.LineLength(-1)==0)
	{
		this->s_Edit_High.SetWindowText(TEXT("0"));
	}	
}

void CARNIC429Dlg::OnChangeEDITAzimuth() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;

	l = this->s_Edit_Azimuth.LineLength(-1);
	if (l==0)
		return;

	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));

	dw = this->s_Edit_Azimuth.GetSel();

	this->s_Edit_Azimuth.GetWindowText(c, sizeof(c)); // get data string with HEX

	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if ((tc>='0')&&(tc<='9')||tc=='.')
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}

	if (!isErr)
		return;

	//  write back the HEX value
	//
	this->s_Edit_Azimuth.SetWindowText(s);
	this->s_Edit_Azimuth.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);
}

void CARNIC429Dlg::OnKillfocusEDITAzimuth() 
{
	// TODO: Add your control notification handler code here
	if (this->s_Edit_Azimuth.LineLength(-1)==0)
	{
		this->s_Edit_Azimuth.SetWindowText(TEXT("0"));
	}		
}

void CARNIC429Dlg::OnChangeEDITSpeedReal() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;
	
	l = this->s_Edit_Speed_Real.LineLength(-1);
	if (l==0)
		return;
	
	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));
	
	dw = this->s_Edit_Speed_Real.GetSel();
	
	this->s_Edit_Speed_Real.GetWindowText(c, sizeof(c)); // get data string with HEX
	
	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if ((tc>='0')&&(tc<='9'))
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}
	
	if (!isErr)
		return;
	
	//  write back the HEX value
	//
	this->s_Edit_Speed_Real.SetWindowText(s);
	this->s_Edit_Speed_Real.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);
	
}

void CARNIC429Dlg::OnKillfocusEDITSpeedReal() 
{
	// TODO: Add your control notification handler code here
	if (this->s_Edit_Azimuth.LineLength(-1)==0)
	{
		this->s_Edit_Azimuth.SetWindowText(TEXT("0"));
	}
}

void CARNIC429Dlg::OnKillfocusEDITMa() 
{
	// TODO: Add your control notification handler code here
		if (this->s_Edit_Ma.LineLength(-1)==0)
	{
		this->s_Edit_Ma.SetWindowText(TEXT("0"));
	}
}

void CARNIC429Dlg::OnChangeEDITMa() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

}

void CARNIC429Dlg::OnChangeEDITAirP() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;
	
	l = this->s_Edit_AirP.LineLength(-1);
	if (l==0)
		return;
	
	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));
	
	dw = this->s_Edit_AirP.GetSel();
	
	this->s_Edit_AirP.GetWindowText(c, sizeof(c)); // get data string with HEX
	
	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if ((tc>='0')&&(tc<='9')||tc=='.'||tc=='-')
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}
	
	if (!isErr)
		return;
	
	//  write back the HEX value
	//
	this->s_Edit_AirP.SetWindowText(s);
	this->s_Edit_AirP.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);	
}

void CARNIC429Dlg::OnKillfocusEDITAirP() 
{
	// TODO: Add your control notification handler code here
	if (this->s_Edit_Azimuth.LineLength(-1)==0)
	{
		this->s_Edit_Azimuth.SetWindowText(TEXT("0"));
	}
}

void CARNIC429Dlg::OnChangeEDITAttack() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;
	
	l = this->s_Edit_Attack.LineLength(-1);
	if (l==0)
		return;
	
	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));
	
	dw = this->s_Edit_Attack.GetSel();
	
	this->s_Edit_Attack.GetWindowText(c, sizeof(c)); // get data string with HEX
	
	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if ((tc>='0')&&(tc<='9')||tc=='.'||tc=='-')
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}
	
	if (!isErr)
		return;
	
	//  write back the HEX value
	//
	this->s_Edit_Attack.SetWindowText(s);
	this->s_Edit_Attack.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);	
}

void CARNIC429Dlg::OnKillfocusEDITAttack() 
{
	// TODO: Add your control notification handler code here
	if (this->s_Edit_Azimuth.LineLength(-1)==0)
	{
		this->s_Edit_Azimuth.SetWindowText(TEXT("0"));
	}
}

void CARNIC429Dlg::OnChangeEDITSpeedUD() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;
	
	l = this->s_Edit_SpeedUD.LineLength(-1);
	if (l==0)
		return;
	
	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));
	
	dw = this->s_Edit_SpeedUD.GetSel();
	
	this->s_Edit_SpeedUD.GetWindowText(c, sizeof(c)); // get data string with HEX
	
	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if ((tc>='0')&&(tc<='9'))
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}
	
	if (!isErr)
		return;
	
	//  write back the HEX value
	//
	this->s_Edit_SpeedUD.SetWindowText(s);
	this->s_Edit_SpeedUD.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);	
}

void CARNIC429Dlg::OnKillfocusEDITSpeedUD() 
{
	// TODO: Add your control notification handler code here
	if (this->s_Edit_Azimuth.LineLength(-1)==0)
	{
		this->s_Edit_Azimuth.SetWindowText(TEXT("0"));
	}
}

void CARNIC429Dlg::OnChangeEDITHighR() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;
	
	l = this->s_Edit_HighR.LineLength(-1);
	if (l==0)
		return;
	
	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));
	
	dw = this->s_Edit_HighR.GetSel();
	
	this->s_Edit_HighR.GetWindowText(c, sizeof(c)); // get data string with HEX
	
	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if ((tc>='0')&&(tc<='9'))
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}
	
	if (!isErr)
		return;
	
	//  write back the HEX value
	//
	this->s_Edit_HighR.SetWindowText(s);
	this->s_Edit_HighR.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);	
}

void CARNIC429Dlg::OnKillfocusEDITHighR() 
{
	// TODO: Add your control notification handler code here
	if (this->s_Edit_Azimuth.LineLength(-1)==0)
	{
		this->s_Edit_Azimuth.SetWindowText(TEXT("0"));
	}
}

void CARNIC429Dlg::OnChangeEDITHighL() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;
	
	l = this->s_Edit_HighL.LineLength(-1);
	if (l==0)
		return;
	
	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));
	
	dw = this->s_Edit_HighL.GetSel();
	
	this->s_Edit_HighL.GetWindowText(c, sizeof(c)); // get data string with HEX
	
	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if ((tc>='0')&&(tc<='9'))
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}
	
	if (!isErr)
		return;
	
	//  write back the HEX value
	//
	this->s_Edit_HighL.SetWindowText(s);
	this->s_Edit_HighL.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);	
}

void CARNIC429Dlg::OnKillfocusEDITHighL() 
{
	// TODO: Add your control notification handler code here
	if (this->s_Edit_Azimuth.LineLength(-1)==0)
	{
		this->s_Edit_Azimuth.SetWindowText(TEXT("0"));
	}
}

void CARNIC429Dlg::OnChangeEditn() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;
	
	l = this->s_Edit_N.LineLength(-1);
	if (l==0)
		return;
	
	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));
	
	dw = this->s_Edit_N.GetSel();
	
	this->s_Edit_N.GetWindowText(c, sizeof(c)); // get data string with HEX
	
	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if ((tc>='0')&&(tc<='9')||tc=='-')
		{
			s[j] = tc;
			j++;
		}
		else
		{
			isErr=TRUE;
		}
	}
	
	if (!isErr)
		return;
	
	//  write back the HEX value
	//
	this->s_Edit_N.SetWindowText(s);
	this->s_Edit_N.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);//ΪFALSE��ʾ������λ�øı��������������
}

void CARNIC429Dlg::OnKillfocusEditn() 
{
	// TODO: Add your control notification handler code here
	if (this->s_Edit_Azimuth.LineLength(-1)==0)
	{
		this->s_Edit_Azimuth.SetWindowText(TEXT("0"));
	}
}


////////////////////////////////������ʽ/////////////////////////////////////////////
void CARNIC429Dlg::OnRADIOSelftest() 
{
	// TODO: Add your control notification handler code here
	wdMode = C429_SELFTEST;	
	CARNIC429Dlg::SetUp429Card();	//�Լ��
}

void CARNIC429Dlg::OnRADIONormal() 
{
	// TODO: Add your control notification handler code here
	wdMode = C429_NORMAL;
	CARNIC429Dlg::SetUp429Card();	
}

void CARNIC429Dlg::OnCHECKControl1() 
{
	
	if (!CWord_flg1) {
		m_ControlWord1 = 0x00000630;
		CWord_flg1 = TRUE;
	}
	else
	{
		m_ControlWord1 = 0;
		x_ControlWord1.Format("%01x", 0);
		CWord_flg1 = FALSE;
	}
	UpdateData(FALSE);
}

void CARNIC429Dlg::OnCHECKControl2() 
{
	
	if (!CWord_flg2) {
		m_ControlWord2 = 0x00000631;
		CWord_flg2 = TRUE;
	}
	else
	{
		m_ControlWord2 = 0;
		x_ControlWord2.Format("%01x", 0);
		CWord_flg2 = FALSE;
	}
	UpdateData(FALSE);
}


///////////////////////////////�շ���ť///////////////////////////////////////////////
void CARNIC429Dlg::OnBUTTONSend()      //����
{
	// TODO: Add your control notification handler code here
	UpdateData(true);      //��ȡ         
	Sleep(20);
	Send();
	Sleep(20);
	UpdateData(FALSE);     //��ʾ
}

void CARNIC429Dlg::OnBUTTONReceive()  //һֱ����
{
	// TODO: Add your control notification handler code here	
	if (blRxNow)
	{
		if (hThread!=NULL)
		{
			isNeedThread = FALSE;
			//  wait thread to terminated
			//
			{
				DWORD dwRet;
				do
				{
					dwRet = ::MsgWaitForMultipleObjects(1, &hThread, FALSE, INFINITE, QS_ALLINPUT);
					if (dwRet != WAIT_OBJECT_0)
					{
						{
							MSG msg;
							while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
							{
								TranslateMessage(&msg);
								DispatchMessage(&msg);
							}
						}
					}
				} while ((dwRet != WAIT_OBJECT_0) && (dwRet != WAIT_FAILED));
			}
			::CloseHandle(hThread);
			hThread = NULL;
		}
		this->m_Button_Receive.SetWindowText(TEXT("��ʼ����"));
		blRxNow = FALSE;		
		KillTimer(3);
		KillTimer(2);
		
	}
	else
	{		
		// create thread to receive data
		//
		isNeedThread = TRUE;
		hThread = ::CreateThread(NULL,                        // no security attributes 
			0,                           // use default stack size  
			ThreadFunc,                  // thread function 
			(LPVOID)ghWnd,                // argument to thread function 
			0,		//CREATE_SUSPENDED,            // use default creation flags 
			&dwThreadId);                // returns the thread identifier 
		//AfxBeginThread(ThreadFunc, 0, 0, 0, NULL);
		if (hThread==NULL)
		{
			MessageBox(TEXT("�޷����������߳�,����������Ӧ�ó���!"), TEXT("����"), MB_OK | MB_ICONERROR);
			return;
		}		
		this->m_Button_Receive.SetWindowText(TEXT("ֹͣ����"));
		blRxNow = TRUE;
		/*Sleep(20);
		Decoding();
		UpdateData(FALSE);
		this->OnPaint();*/
		SetTimer(2, 100, NULL);
	}
}

void CARNIC429Dlg::OnClose()
{
	if (MessageBox(TEXT("��ȷ��Ҫ�˳���?"), TEXT("�˳���ʾ"), MB_YESNO | MB_ICONQUESTION)!=IDYES)
	{
		return;
	}

	if (hThread!=NULL)
	{
		isNeedThread = FALSE;
		//  wait thread to terminated
		//
		{
			DWORD dwRet;
			do
			{
				dwRet = ::MsgWaitForMultipleObjects(1, &hThread, FALSE, INFINITE, QS_ALLINPUT);
				if (dwRet != WAIT_OBJECT_0)
				{
					{
						MSG msg;
						while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
						{
							TranslateMessage(&msg);
							DispatchMessage(&msg);
						}
					}
				}
			} while ((dwRet != WAIT_OBJECT_0) && (dwRet != WAIT_FAILED));
		}
		::CloseHandle(hThread);
		hThread = NULL;
	}

	if (hCard!=NULL)
	{
		ResetCard(hCard); // reset Card
		if (!Card_Close(hCard))
		{
			MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
		}
	}
	
	CDialog::OnClose();
}

//////////////////////////////////�������/////////////////////////////////////
// void CARNIC429Dlg::Coding()
// {
// 	wdTxBufLen=0;
// 	dwTxBuf[wdTxBufLen] = m_ControlWord1;
// 	dwTxBuf[++wdTxBufLen] = m_ControlWord2;
	
// 	dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_Speed_Real/(4096.0/32768));
// 	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000688;	
	
// 	dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_Speed/(2048.0/32768));
// 	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000686;	
	
// 	s_Air_Ma = s_Air_Speed/3.6/340;//�����������
// 	dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_Ma/(4.096/32768));
// 	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000685;


// 	{
// 		dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_AirP/(128.0/32768));
// 		dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000697;		
// 	}	


// 	{
// 		dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_Attack/(45.0/32768));
// 		dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x000006a1;
// 	}

// 	dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_High);
// 	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000684;	

// 	dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_SpeedUD/(512.0/32768)); 
// 	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x0000068a;	
	
// 	dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_Azimuth/(360.0/32768));
// 	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000632;	


// 	{
// 		dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_Pitch/(180.0/32768));
// 		dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000633;
// 	}	


// 	{
// 		dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_Roll/(180.0/32768));
// 		dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000634;
// 	}	
	
// 	dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_HighR/(1524.0/32768));    
// 	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000635;

// 	dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_HighL/(1500.0/32768));
// 	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000636;		


// 	{
// 		dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_Sideslip/(10.0/32768));
// 		dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000637;
// 	}	
	

// 	{
// 		dwTxBuf[++wdTxBufLen] = (DWORD)(s_Air_N/(10.0/32768));
// 		dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000638;
// 	}
	
// }

/////////////////////////////���ͽ�������////////////////////////////////////////////
void CARNIC429Dlg::Send()   //�ο�demo  OnButtonSend����
{
	int i=0;  //�������ݸ���
	char c[128];
	
	//  get Tx data
	//
	wdTxBufLen = 0;
	memset(dwTxBuf, 0, sizeof(DWORD)*FIFO_TMAX);
	
	//  fill Tx Buffer
	Coding();    //����
	
#ifndef CARD_DEBUG
	//  data transmission
	//
    i = 0;                  //��ʼ��0����ͨ��Ϊ����ͨ��1
	// we must stop the Tx timer before we want to write data to Tx FIFO
	//
	if (wdBInterval[i]>0)
	{
		if (!StartTimerB(hCard, i, FALSE))//����ʧ��
		{
			sprintf(c, "��[%d]·��ֹȺ��ʱ���͹��ܳ���!\n\n(StartTimerB��������ֵΪ[0])", i+1);
			MessageBox(TEXT(c), TEXT("��Ϣ��ʾ"), MB_OK | MB_ICONINFORMATION);
		}
	}
	
	if (wdSInterval[i]>0)
	{
		if (!StartTimerS(hCard, i, FALSE))
		{
			sprintf(c, "��[%d]·��ֹ�ֶ�ʱ���͹��ܳ���!\n\n(StartTimerS��������ֵΪ[0])", i+1);
			MessageBox(TEXT(c), TEXT("��Ϣ��ʾ"), MB_OK | MB_ICONINFORMATION);
		}
	}
	
	if(ReadFIFOStatus_S(hCard, i)!=FIFOFull)//��FIFO����������ʱ���ͣ����򱨴�
	{
		wdTxBufLen=16;
		SendData(hCard, i, (BYTE) wdTxBufLen, dwTxBuf);//����������ݳ��ȣ�32λ��������dwTxBuf���͵�����
//		if (!SendData(hCard, i, (BYTE) wdTxBufLen, dwTxBuf))
//		{
//			sprintf(c, "��[%d]·�������ݳ���!\n\n(SendData��������ֵΪ[0])", i+1);
//			MessageBox(TEXT(c), TEXT("��Ϣ��ʾ"), MB_OK | MB_ICONINFORMATION);
//		}					
	}
	else
	{ // Tx FIFO is not empty
		sprintf(c, "��[%d]·Ӳ������������!\n\n(ReadFIFOStatus_S��������ֵΪ[0x12])", i+1);
		MessageBox(TEXT(c), TEXT("��Ϣ��ʾ"), MB_OK | MB_ICONINFORMATION);
	}
#endif	
	//UpdateData(FALSE);
}

void CARNIC429Dlg::Receive()
{
	
}

void CARNIC429Dlg::OnBUTTONStartTimer() //�򿪶�ʱ����
{
	// TODO: Add your control notification handler here	
	if (!Timer_flg) {
		UpdateData(TRUE);				//���ڽ���Ļ�Ͽؼ��е����ݽ����������У��������е�ֵ����������
		//UpdateData(FALSE);			//���ڽ���������Ļ�ж�Ӧ�ؼ�����ʾ�������������е�ֵ�ڴ�������ʾ
		for (int i = 0; i < FIFO_RMAX; i++)	//���FIFO
			ReceiveData_Vector[i] = 0x0;
		SetTimer(3, 100, NULL);      
		Timer_flg = TRUE;
		//this->m_Button_StartTimer.SetWindowText(TEXT("��ʱ����"));
	}
	else {
		KillTimer(3);
		Sleep(10);
		Sleep(10);
		Sleep(10);
		Timer_flg = FALSE;
	/*	this->m_Button_StartTimer.SetWindowText(TEXT("������ʱ"));*/
	}
}

void CARNIC429Dlg::OnBUTTONCLR() //������ʱ����
{
	memset(dwTxBuf, 0, sizeof(DWORD) * FIFO_TMAX);
	T = 0;
	s_Air_Speed=0;		//�����
	s_Air_Roll = 0.0;			//�����
	s_Air_Pitch = 0.0;		//������
	s_Air_High = 0;			//���ߵ�߶�
	s_Air_Azimuth = 0;		//��λ��
	s_Air_Sideslip = 0.0;		//�໬��
	s_Air_Speed_Real = 0;	//ָʾ����
	s_Air_Ma = 0;			//�����
	s_Air_AirP = 0;			//װ����ѹ
	s_Air_Attack = 0.0;		//����
	s_Air_SpeedUD = 0;		//�����߶�
	s_Air_HighR = 0;		//��ѹ�߶�
	s_Air_HighL = 0;		//��Ͱ�ȫ�߶�
	s_Air_N = 0;			//����

	r_Air_Speed = 0;		//�����
	r_Air_Roll = 0;			//�����
	r_Air_Pitch = 0;		//������
	r_Air_High = 0;			//���ߵ�߶�
	r_Air_Azimuth = 0;		//��λ��
	r_Air_Sideslip = 0.0;		//�໬��
	r_Air_Speed_Real = 0;	//ָʾ����
	r_Air_Ma = 0;			//�����
	r_Air_AirP = 0;			//װ����ѹ
	r_Air_Attack = 0;		//����
	r_Air_SpeedUD = 0;		//�����߶�
	r_Air_HighR = 0;		//��ѹ�߶�
	r_Air_HighL = 0;		//��Ͱ�ȫ�߶�
	r_Air_N = 0;			//����

	x_Air_Speed.Format("%01x", 0);		
	x_Air_Roll.Format("%01x", 0);			
	x_Air_Pitch.Format("%01x", 0);		
	x_Air_High.Format("%01x", 0);			
	x_Air_Azimuth.Format("%01x", 0);		
	x_Air_Sideslip.Format("%01x", 0);		
	x_Air_Speed_Real.Format("%01x", 0);	
	x_Air_Ma.Format("%01x", 0);			
	x_Air_AirP.Format("%01x", 0);			
	x_Air_Attack.Format("%01x", 0);		
	x_Air_SpeedUD.Format("%01x", 0);		
	x_Air_HighR.Format("%01x", 0);		
	x_Air_HighL.Format("%01x", 0);		
	x_Air_N.Format("%01x", 0);			
	x_ControlWord1.Format("%01x", 0);
    x_ControlWord2.Format("%01x", 0);

	Sleep(20);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	//�����Ƴ���ǰ���õĶ�ʱ��
}

void CARNIC429Dlg::OnTimer(UINT_PTR nIDEvent)//��ʱ��
{
	T++;
	switch(nIDEvent)
	{
		case 3:
			s_Air_Speed_Real +=1;
			if (s_Air_Speed_Real > 4096)
			{
				s_Air_Speed_Real = 4096;
				//s_Air_Speed_Real = 0;
			}
			s_Air_Speed +=1 ;

			if (s_Air_Speed > 2048)
			{
				s_Air_Speed = 2048;
				//s_Air_Speed = 0;
			}
			s_Air_AirP += 0.1;

			if (s_Air_AirP > 128)
			{
				s_Air_AirP = -128;
			}
			s_Air_Attack = 45*sin(0.02*T);
			s_Air_High += 5;

			if(s_Air_High == 32768)
				s_Air_High = 0;
			s_Air_SpeedUD += 1;
			if (s_Air_SpeedUD > 512)
			{
				s_Air_SpeedUD = -512;
			}
			s_Air_Azimuth += 0.5;
			if(s_Air_Azimuth>360)
				s_Air_Azimuth = 0;
			s_Air_Pitch = 180*sin(0.005*T);
			s_Air_Roll = 180*sin(0.02*T);
			s_Air_HighR += 5;
			if (s_Air_HighR > 1524)
			{
				//s_Air_HighR = 0;
				s_Air_HighR = 1524;
			}
			s_Air_HighL =300;
		//	if (s_Air_HighL > 1500)
		//	{
		//		s_Air_HighL = 0;
		//	}
			s_Air_Sideslip = 10*sin(0.02*T);
			s_Air_N += 0.1;
			if (s_Air_N > 10)
			{
				s_Air_N = -10;
			}
			Send();
			UpdateData(FALSE);
			break;
		

		case 2:


			this->OnPaint();
		break;
	}
}

/*++
	Routine Description:
		Thread function used to read six channels counter and two AD's sampling data.
		
	Arguments:
		1) lpParam: [IN/OUT] needed parameter for thread.
		
	Return Value:
		If the function is seceeded, return value is TRUE else is FALSE;
--*/
DWORD WINAPI ThreadFunc(LPVOID lpParam)  //����ŵ�������
{
start:	HWND hWnd = (HWND)lpParam;
	DWORD d = 0;
	BYTE chno = 0; ///����ͨ��1Ϊ����
	BYTE btTriggerLevel = 0;
	int i = 0;
#ifndef CARD_DEBUG
	while (isNeedThread)        //////////////////
	{
		//  Get trigger level
		//
		btTriggerLevel = stTriggerLevel.Chan0Depth_I;

		//  Rx channel 1~CHNO_RMAX
		// ----------------------------------------------------------------
		if (btTriggerLevel > 0) // triggered//xu yao guo lv 
		{
			if (IsFIFOTriggered_R(hCard, chno))//�ж��Ƿ񵽴ﴥ�����
			{
				EnablReadFIFO(hCard, chno);//ʹ�ܶ�FIFO����
				while ((ReadFIFOStatus_R(hCard, chno) != FIFOEmpty) && (ReadFIFOStatus_R(hCard, chno) != FIFOError))
					//��recieveFIFO �����Ҳ����ʱ
				{
					d = ReceiveData(hCard, chno);
					if ((wdMode == C429_SELFTEST) && (stComm[chno / 2].iSelParity == C429_PARITY_NONE)) // resume 429 Word
					{
						d = Resume429Word(d);//429��ת��������֣�����
					}
					Save_ReceiveData(d, ReceiveData_Vector + i);
				}
				DisablReadFIFO(hCard);//��ֹ��FIFO����
			}
		}
		else // untriggered//����Ҫ���� .
		{
			if ((ReadFIFOStatus_R(hCard, chno) != FIFOEmpty) && (ReadFIFOStatus_R(hCard, chno) != FIFOError))//��ȡ״̬��recieveFIFO �����Ҳ����ʱ
			{
				EnablReadFIFO(hCard, chno);//ʹ�ܶ�FIFO����
				d = ReceiveData(hCard, chno);
				if ((wdMode == C429_SELFTEST) && (stComm[chno / 2].iSelParity == C429_PARITY_NONE)) // resume 429 Word
				{
					d = Resume429Word(d);
				}
				DWORD temp;  
				temp = d >> 24;
				short s;
				switch (temp)//�жϱ�����ʲô
				{
				case 0x30://������1
					x_ControlWord1.Format("%08x", d); break;
					//0000 0110 0011 0000
				case 0x31://������2
					x_ControlWord2.Format("%08x", d); break;
					//0000 0110 0011 0001
				
				case 0x88:	//�����
					s = (short)(d >> 16);
					r_Air_Speed_Real = s * (4096. / 32768);
					x_Air_Speed_Real.Format("%08x", d); break;
					//0000 0110 1000 1000
				case 0x86://ָʾ����
					s = (short)(d >> 16);
					r_Air_Speed = s * (2048. / 32768);
					x_Air_Speed.Format("%08x", d); break;
					//0000 0110 1000 0110
				case 0x85://�����
					s = (short)(d >> 16);
					r_Air_Ma = s * (4.096 / 32768);
					x_Air_Ma.Format("%08x", d); break;
					//	0000 0110 0001 0101
				case 0x97://װ����ѹ
					s = (short)(d >> 16);
					r_Air_AirP = s * (128. / 32768);
					x_Air_AirP.Format("%08x", d); break;
					//0000 0110 1001 0111
				case 0xA1://����
					s = (short)(d >> 16);
					r_Air_Attack = s * (45. / 32768);
					x_Air_Attack.Format("%08x", d); break;
					//0000 0110 1010 0001
				case 0x84://�����ѹ�߶�
					s = (short)(d >> 16);
					r_Air_High = s;
					x_Air_High.Format("%08x", d); break;
					//0000 0110 1000 0100
				case 0x8A://�����ٶ�
					s = (short)(d >> 16);
					r_Air_SpeedUD = s * (512. / 32768);
					x_Air_SpeedUD.Format("%08x", d); break;
					//0000 0110 1000 1010
				case 0x32://�����
					s = (short)(d >> 16);
					r_Air_Azimuth = s * (360. / 32768);
					x_Air_Azimuth.Format("%08x", d); break;
					//0000 0110 0011 0010
				case 0x33://������
					s = (short)(d >> 16);
					r_Air_Pitch = s * (180. / 32768);
					x_Air_Pitch.Format("%08x", d); break;
					//0000 0110 0011 0011
				case 0x34://�����
					s = (short)(d >> 16);
					r_Air_Roll = s * (180. / 32768);
					x_Air_Roll.Format("%08x", d); break;
					//0000 0110 0011 0100
				case 0x35://���ߵ�߶�
					s = (short)(d >> 16);
					r_Air_HighR = s * (1524. / 32768);
					x_Air_HighR.Format("%08x", d); break;
					//0000 0110 0011 0101
				case 0x36://��Ͱ�ȫ�߶�
					s = (short)(d >> 16);
					r_Air_HighL = s * (1500. / 32768);
					x_Air_HighL.Format("%08x", d); break;
					//0000 0110 0011 0110 
				case 0x37://�໬��
					s = (short)(d >> 16);
					r_Air_Sideslip = s * (10. / 32768);
					x_Air_Sideslip.Format("%08x", d); break;
					//0000 0110 0011 0111
				case 0x38://�������
					s = (short)(d >> 16);
					r_Air_N = s * (10. / 32768);
					x_Air_N.Format("%08x", d); break;
					//0000 0110 0011 1000
				default:
					break;
				}
			}
			DisablReadFIFO(hCard);//��ֹ��FIFO����			
		} // end of if (btTriggerLevel...		
	} // end of while ((chno<CHNO_RMAX...
	

	

#endif	

		ExitThread(THREAD_EXITCODE);
return 0;

}
	
void CARNIC429Dlg::OnButtonBITRATE100K()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for (int i = 0; i < CHNO_TMAX; i++) // bits rate & parity//�����ʵ�ѡ��
	{ // followed definitions can be found in cusfunc.h
		stComm[i].iSelBR = C429_BITRATE100K; // 0: 100k    1: 48k    2: 12.5k   
	}
	CARNIC429Dlg::SetUp429Card();
}

void CARNIC429Dlg::OnButtonBITRATE48K()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for (int i = 0; i < CHNO_TMAX; i++) // bits rate & parity//�����ʵ�ѡ��
	{ // followed definitions can be found in cusfunc.h
		stComm[i].iSelBR = C429_BITRATE48K; // 0: 100k    1: 48k    2: 12.5k   
	}
	CARNIC429Dlg::SetUp429Card();
}

void CARNIC429Dlg::OnBnClickedOnbuttonbitrate12k()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for (int i = 0; i < CHNO_TMAX; i++) // bits rate & parity//�����ʵ�ѡ��
	{ // followed definitions can be found in cusfunc.h
		stComm[i].iSelBR = C429_BITRATE125K; // 0: 100k    1: 48k    2: 12.5k   
	}
	CARNIC429Dlg::SetUp429Card();
}



void CARNIC429Dlg::OnButtonPARITY_NONE()
{
	for (int i = 0; i < CHNO_TMAX; i++)
	{
		stComm[i].iSelParity = C429_PARITY_NONE;
	}
	CARNIC429Dlg::SetUp429Card();
}

void CARNIC429Dlg::OnButtonPARITY_ODD()//��
{
	for (int i = 0; i < CHNO_TMAX; i++)
	{
		stComm[i].iSelParity = C429_PARITY_ODD;
	}
	CARNIC429Dlg::SetUp429Card();
}

void CARNIC429Dlg::OnButtonPARITY_EVEN()//ż
{
	for (int i = 0; i < CHNO_TMAX; i++)
	{
		stComm[i].iSelParity = C429_PARITY_EVEN;
	}
	CARNIC429Dlg::SetUp429Card();
}





