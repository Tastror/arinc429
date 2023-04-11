// arinc429Dlg.cpp : implementation file
//XP��s_edit_���ҵ�m_


#include "stdafx.h"
#include "arinc429.h"
#include "arinc429Dlg.h"
#include "math.h"
#include "DLL429D42_lib.h"
#include "cusfunc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define THREAD_EXITCODE	0
int iTabID=0; 
BYTE btCardId=0;     //�忨��         
HANDLE hCard=NULL;//���
TriggerDepth_STRUCT stTriggerLevel={0};   //FIFO������������Ƚṹ���� ����Ϊ�Լ���
LabelTable_STRUCT stLabelTable={0};       //��ע��
BOOL blFilter[CHNO_RMAX];         //��Ź���
STCOMMUNICATION stComm[CHNO_TMAX];   
SYSTEMTIME stSysTime={0};      //ϵͳʱ��
WORD wdMode=C429_SELFTEST;       //����ģʽ
BOOL blTimeTag[CHNO_RMAX];      //ʹ��ʱ���ǩ
DWORD dwTime=0;                //ʱ��
WORD wdBInterval[CHNO_TMAX];     //Ⱥ��ʱ
WORD wdSInterval[CHNO_TMAX];    //�Զ�ʱ
BOOL CWord_flg1 = FALSE;
BOOL CWord_flg2 = FALSE;
BOOL isNeedThread=FALSE;
HANDLE hThread=NULL; // handle to thread function�����幦�ܣ�
DWORD dwThreadId=0;  
BOOL Timer_flg = FALSE;
BOOL blRxNow=FALSE;
HWND ghWnd=NULL;

DWORD dwTxBuf[FIFO_TMAX];    //���� FIFO
WORD wdTxBufLen=0;        //����FIFO����

DWORD ReceiveData_Vector[FIFO_RMAX];
BOOL Mode_flg;
BOOL Complete_flg;//������ɱ�־

DWORD WINAPI ThreadFunc(LPVOID lpParam);

int T;

float	airp0;
float	airp1;
float	attack0;
float	attack1 ;
float	azimuth0;
float	azimuth1;
int	height_a0;
int	height_a1;
int	height_l0;
int	height_l1;
int	height_r0;
int	height_r1;
float	ma0 ;
float	ma1;
float	pitch0;
float	pitch1;
float	realspeed0;
float	realspeed1;
float	roll0;
float	roll1;
float	sideslip0;
float	sideslip1;
int	speed0;
int	speed1;
int	speedud0;
float	t0;
float	t1 ;
DWORD m_controlword1in=0;
DWORD m_controlword2in=0;
CString	controlword1;
CString	controlword2;
int	speedud1;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArinc429Dlg dialog

CArinc429Dlg::CArinc429Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CArinc429Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArinc429Dlg)
	m_airp0 = 0.0f;
	m_airp1 = 0.0f;
	m_attack0 = 0.0f;
	m_attack1 = 0.0f;
	m_azimuth0 = 0.0f;
	m_azimuth1 = 0.0f;
	m_height_a0 = 0;
	m_height_a1 = 0;
	m_height_l0 = 0;
	m_height_l1 = 0;
	m_height_r0 = 0;
	m_height_r1 = 0;
	m_ma0 = 0.0f;
	m_ma1 = 0.0f;
	m_pitch0 = 0.0f;
	m_pitch1 = 0.0f;
	m_realspeed0 = 0;
	m_realspeed1 = 0;
	m_roll0 = 0.0f;
	m_roll1 = 0.0f;
	m_sideslip0 = 0.0f;
	m_sideslip1 = 0.0f;
	m_speed0 = 0;
	m_speed1 = 0;
	m_speedud0 = 0;
	m_t0 = 0.0f;
	m_t1 = 0.0f;
	//m_controlword1 = _T("");
//	m_controlword2 = _T("");
	m_speedud1 = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CArinc429Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArinc429Dlg)
	DDX_Control(pDX, IDC_BUTTON_RECEIVE, m_Button_Receive);
	DDV_MinMaxFloat(pDX, m_airp0, -128.f, 128.f);
	DDX_Text(pDX, IDC_EDIT_AIRP1, m_airp1);
	DDV_MinMaxFloat(pDX, m_airp1, -128.f, 128.f);
	DDV_MinMaxFloat(pDX, m_attack0, -45.f, 45.f);
	DDX_Text(pDX, IDC_EDIT_ATTACK1, m_attack1);
	DDV_MinMaxFloat(pDX, m_attack1, -45.f, 45.f);
	DDV_MinMaxFloat(pDX, m_azimuth0, 0.f, 360.f);
	DDX_Text(pDX, IDC_EDIT_AZIMUTH1, m_azimuth1);
	DDV_MinMaxFloat(pDX, m_azimuth1, 0.f, 360.f);
	DDV_MinMaxInt(pDX, m_height_a0, 0, 32768);
	DDX_Text(pDX, IDC_EDIT_HEIGHT_A1, m_height_a1);
	DDV_MinMaxInt(pDX, m_height_a1, 0, 32768);
	DDV_MinMaxInt(pDX, m_height_l0, 0, 150);
	DDX_Text(pDX, IDC_EDIT_HEIGHT_L1, m_height_l1);
	DDV_MinMaxInt(pDX, m_height_l1, 0, 150);
	DDV_MinMaxInt(pDX, m_height_r0, 0, 1524);
	DDX_Text(pDX, IDC_EDIT_HEIGHT_R1, m_height_r1);
	DDV_MinMaxInt(pDX, m_height_r1, 0, 1524);
	DDV_MinMaxFloat(pDX, m_ma0, 0.f, 4.096f);
	DDX_Text(pDX, IDC_EDIT_MA1, m_ma1);
	DDV_MinMaxFloat(pDX, m_ma1, 0.f, 4.096f);
	DDV_MinMaxFloat(pDX, m_pitch0, -180.f, 180.f);
	DDX_Text(pDX, IDC_EDIT_PITCH1, m_pitch1);
	DDV_MinMaxFloat(pDX, m_pitch1, -180.f, 180.f);
	DDV_MinMaxInt(pDX, m_realspeed0, 0, 4096);
	DDX_Text(pDX, IDC_EDIT_REALSPEED1, m_realspeed1);
	DDV_MinMaxInt(pDX, m_realspeed1, 0, 4096);
	DDV_MinMaxFloat(pDX, m_roll0, -180.f, 180.f);
	DDX_Text(pDX, IDC_EDIT_ROLL1, m_roll1);
	DDV_MinMaxFloat(pDX, m_roll1, -180.f, 180.f);
	DDX_Text(pDX, IDC_EDIT_SLIDESLIP1, m_sideslip1);
	DDV_MinMaxInt(pDX, m_speed0, 0, 2048);
	DDX_Text(pDX, IDC_EDIT_SPEED1, m_speed1);
	DDV_MinMaxInt(pDX, m_speed1, 0, 2048);
	DDV_MinMaxInt(pDX, m_speedud0, -512, 512);
	DDX_Text(pDX, IDC_EDIT_T1, m_t1);

	DDX_Text(pDX, IDC_EDIT_SPEEDUD1, m_speedud1);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_T0, t0);
	DDX_Text(pDX, IDC_EDIT_SPEED0, speed0);
	DDX_Text(pDX, IDC_EDIT_SLIDESLIP0, sideslip0);
	DDX_Text(pDX, IDC_EDIT_REALSPEED0, realspeed0);
	DDX_Text(pDX, IDC_EDIT_PITCH0, pitch0);
	DDX_Text(pDX, IDC_EDIT_HEIGHT_R0, height_r0);
	DDX_Text(pDX, IDC_EDIT_HEIGHT_L0, height_l0);
	DDX_Text(pDX, IDC_EDIT_HEIGHT_A0, height_a0);
	DDX_Text(pDX, IDC_EDIT_SPEEDUD0, speedud0);
	DDX_Text(pDX, IDC_EDIT_AZIMUTH0, azimuth0);
	DDX_Text(pDX, IDC_EDIT_ATTACK0, attack0);
	DDX_Text(pDX, IDC_EDIT_AIRP0, airp0);
	DDX_Text(pDX, IDC_EDIT_ROLL0, roll0);
	DDX_Text(pDX, IDC_EDIT_MA0, ma0);
	DDX_Text(pDX, IDC_EDIT_CONTROLWORD1, controlword1);
	DDX_Text(pDX, IDC_EDIT_CONTROLWORD2, controlword2);

}

BEGIN_MESSAGE_MAP(CArinc429Dlg, CDialog)
	//{{AFX_MSG_MAP(CArinc429Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()


	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_RECEIVE, OnButtonReceive)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_STARTTIMER, OnButtonStarttimer)
	ON_BN_CLICKED(IDC_BUTTON_STOPTIMER, OnButtonStoptimer)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO_100K, OnRadio100k)

	ON_BN_CLICKED(IDC_CHECKControl2, OnCHECKControl2)
	ON_BN_CLICKED(IDC_CHECKControl1, OnCHECKControl1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArinc429Dlg message handlers

BOOL CArinc429Dlg::OnInitDialog()//��ʼ��
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//�����������
	int i,j;

	stTriggerLevel.Chan0Depth_I = TriggerLevel; // default Trigger Level
	stTriggerLevel.Chan1Depth_I = TriggerLevel;
	stTriggerLevel.Chan2Depth_I = TriggerLevel; 
	stTriggerLevel.Chan3Depth_I = TriggerLevel;//��·����
	stTriggerLevel.Chan0Depth_O = TriggerLevel;
	stTriggerLevel.Chan1Depth_O = TriggerLevel;//��·����

	//��ǩ���˱�����
	for (i=0; i<SD_MAX; i++) // default Label Filter
	{
		for (j=0; j<LABEL_MAX; j++)
		{
			stLabelTable.LabFilterChan0[i][j]=0;//Ƶ��0��S/DΪi�ұ��Ϊj�����ݣ�if=1�ᱻ���գ�
			stLabelTable.LabFilterChan1[i][j]=0;
			stLabelTable.LabFilterChan2[i][j]=0;
			stLabelTable.LabFilterChan3[i][j]=0;
		}
	}

	//ѡ������
	for (i=0; i<CHNO_TMAX; i++) // bits rate & parity
	{ // followed definitions can be found in cusfunc.h
		stComm[i].iSelBR = C429_BITRATE100K; // 0: 100k    1: 48k    2: 12.5k
		stComm[i].iSelParity = C429_PARITY_NONE; // 0: odd    1: even    2: none
		wdBInterval[i] = 0;
		wdSInterval[i] = 0;
	}
	//ʱ���ǩ�ͱ��ɾѡ
	for (i=0; i<CHNO_RMAX; i++)
	{
		blFilter[i] = FALSE;  // disable label filter function����
		blTimeTag[i] = FALSE;  // disable Time Tag function����ʱ���ǩ
	}

	wdMode=C429_SELFTEST; // SELFTEST work mode�Ի�
	CArinc429Dlg::SetUp429Card();
	for(i=0;i<FIFO_RMAX;i++)
	ReceiveData_Vector[i] = 0x0;
	T = 0;
	m_controlword1in = 0x00000630;     ////????
	m_controlword2in = 0x00000631;    ////????
	Complete_flg = FALSE;

	//����
	return TRUE;  // return TRUE  unless you set the focus to a control
}




void CArinc429Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CArinc429Dlg::OnPaint() 
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

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		int x_mov = 250, y_mov = 10; //ƽ�Ժ��������λ��
		CDC *pMem = new CDC;
		CBitmap *pBmp = new CBitmap;
		CBitmap *pOldBmp;
		CDC *pDC = GetDC();
		CRect rectTemp(0,0,600,530);
		pMem->CreateCompatibleDC(pDC);
		pBmp->CreateCompatibleBitmap(pDC,rectTemp.Width(),rectTemp.Height());
		pOldBmp = pMem->SelectObject(pBmp);
		
		OnDraw_Fighter(205+(int)pitch0,260+(int)sideslip0,pMem);// ��Ԥ�������ź�
		OnDraw_BlackRect(pMem);                // ����ɫ����
	
		OnDraw_High(height_a0, pMem);      // ����ѹ�߶�
		OnDraw_Speed(speed0, pMem);	 // ��ָʾ����
		OnDraw_HXJ(azimuth0, pMem);//��λ��
		OnDraw_HGKD(roll0, pMem);
		OnDraw_HG(roll0, pitch0, pMem);
		
		pDC->BitBlt(rectTemp.left,rectTemp.top,rectTemp.Width(),rectTemp.Height(),pMem,0,0,SRCCOPY);		
		pMem->SelectObject(pOldBmp);
		pBmp->DeleteObject() ;
		pMem->DeleteDC();
		CDialog::OnPaint();
	}
}


// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CArinc429Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CArinc429Dlg::SetUp429Card()
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

}//�����忨����

///////////////////////ģʽ�ؼ�////////////////////





////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void CArinc429Dlg::OnCHECKControl2() 
{
	// TODO: Add your control notification handler code here
	
	if (!CWord_flg2) {
		m_controlword2in = 0x00000631;
		CWord_flg2 = TRUE;
	}
	else
	{
		m_controlword2in = 0;
		controlword2.Format("%01x", 0);
		CWord_flg2 = FALSE;
	}
	UpdateData(FALSE);
}

void CArinc429Dlg::OnCHECKControl1() 
{
	// TODO: Add your control notification handler code here
		if (!CWord_flg1) {
		m_controlword1in = 0x00000630;
		CWord_flg1 = TRUE;
	}
	else
	{
		m_controlword1in = 0;
		controlword1.Format("%01x", 0);
		CWord_flg1 = FALSE;
	}
	UpdateData(FALSE);
}


//////////////////////�շ���ť//////////////////////
///////////////////////////////////////////////////
void CArinc429Dlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);      //��ȡ         
	Sleep(20);
	Send();
	Sleep(20);
	UpdateData(FALSE);     //��ʾ	
}


void CArinc429Dlg::OnButtonReceive() 
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





/////////////////////////�رմ���//////////////////////////////////


void CArinc429Dlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
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

void CArinc429Dlg::Coding()
{
	wdTxBufLen=0;
	dwTxBuf[wdTxBufLen] = m_controlword1in;
	dwTxBuf[++wdTxBufLen] = m_controlword2in;
	
	dwTxBuf[++wdTxBufLen] = (DWORD)(m_realspeed1/(4096.0/32768));
	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000688;	
	
	dwTxBuf[++wdTxBufLen] = (DWORD)(m_speed1/(2048.0/32768));
	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000686;	
	
	m_ma1 = m_speed1/3.6/340;//�����������
	dwTxBuf[++wdTxBufLen] = (DWORD)(m_ma1/(4.096/32768));
	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000685;


	{
		dwTxBuf[++wdTxBufLen] = (DWORD)(m_airp1/(128.0/32768));
		dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000697;		
	}	


	{
		dwTxBuf[++wdTxBufLen] = (DWORD)(m_attack1/(45.0/32768));
		dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x000006a1;
	}

	dwTxBuf[++wdTxBufLen] = (DWORD)(m_height_a1);
	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000684;	

	dwTxBuf[++wdTxBufLen] = (DWORD)(m_speedud1/(512.0/32768)); 
	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x0000068a;	
	
	dwTxBuf[++wdTxBufLen] = (DWORD)(m_azimuth1/(360.0/32768));
	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000632;	


	{
		dwTxBuf[++wdTxBufLen] = (DWORD)(m_pitch1/(180.0/32768));
		dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000633;
	}	


	{
		dwTxBuf[++wdTxBufLen] = (DWORD)(m_roll1/(180.0/32768));
		dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000634;
	}	
	
	dwTxBuf[++wdTxBufLen] = (DWORD)(m_height_r1/(1524.0/32768));    
	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000635;

	dwTxBuf[++wdTxBufLen] = (DWORD)(m_height_l1/(1500.0/32768));
	dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000636;		


	{
		dwTxBuf[++wdTxBufLen] = (DWORD)(m_sideslip1/(10.0/32768));
		dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000637;
	}	
	

	{
		dwTxBuf[++wdTxBufLen] = (DWORD)(m_t1/(10.0/32768));
		dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000638;
	}

}

////////////////////////////////////////����///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void CArinc429Dlg::Send()
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

}

////////////////////////////////////////��ʱ����///////////////////////////////////////
void CArinc429Dlg::OnButtonStarttimer() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here	
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

void CArinc429Dlg::OnButtonStoptimer() 
{
	// TODO: Add your control notification handler code here
	memset(dwTxBuf, 0, sizeof(DWORD) * FIFO_TMAX);
	m_airp0 = 0.0;
	m_airp1 = 0.0;
	m_attack0 = 0.0;
	m_attack1 = 0.0;
	m_azimuth0 = 0.0;
	m_azimuth1 = 0.0;
	m_height_a0 = 0;
	m_height_a1 = 0;
	m_height_l0 = 0;
	m_height_l1 = 0;
	m_height_r0 = 0;
	m_height_r1 = 0;
	m_ma0 = 0.0;
	m_ma1 = 0.0;
	m_pitch0 = 0.0;
	m_pitch1 = 0.0;
	m_realspeed0 = 0;
	m_realspeed1 = 0;
	m_roll0 = 0.0f;
	m_roll1 = 0.0f;
	m_sideslip0 = 0.0;
	m_sideslip1 = 0.0;
	m_speed0 = 0;
	m_speed1 = 0;
	m_speedud0 = 0;
	m_t0 = 0.0;
	m_t1 = 0.0;
	m_speedud0 = 0;
	m_speedud1 = 0;
	Sleep(20);
	UpdateData(FALSE);
	
}





void CArinc429Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	T++;
	switch(nIDEvent)
	{
		case 3:
			m_realspeed1 +=1 ;
			if (m_realspeed1 > 4096)
			{
				m_realspeed1 = 0;
			}

			m_speed1 +=1 ;
			if (m_speed1 > 2048)
			{
				m_speed1 = 0;
			}

			m_airp1 += 0.1;
			if (m_airp1 > 128)
			{
				m_airp1 = -128;
			}

			m_attack1 = 45*sin(0.02*T);

			m_height_a1 += 5;
			if(m_height_a1 == 32768)
				m_height_a1 = 0;

			m_speedud1 += 1;
			if (m_speedud1 > 512)
			{
				m_speedud1 = -512;
			}

			m_azimuth1 += 0.5;
			if(m_azimuth1>360)
				m_azimuth1 = 0;
			m_pitch1 = 180*sin(0.005*T);
			m_roll1 = 180*sin(0.02*T);
			m_height_r1 += 5;
			if (m_height_r1 > 1524)
			{
				m_height_r1 = 0;
			}
			m_height_l1=300;
			
			m_sideslip1 = 10*sin(0.02*T);
			m_t1 += 0.1;
			if (m_t1 > 10)
			{
				m_t1 = -10;
			}
			Send();
			UpdateData(FALSE);
			break;
		

		case 2:


			this->OnPaint();
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

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
				temp = d & 0x00FF;
				short s;
				switch (temp)//�жϱ�����ʲô
				{
				case 0x30://������1

					controlword1.Format("%08x", d); break;
					//0000 0110 0011 0000
				case 0x31://������2
					controlword2.Format("%08x", d); break;
					//0000 0110 0011 0001
				
				case 0x88:	//�����
					s = (short)(d >> 16);
					realspeed0 = s * (4096. / 32768);
				//	x_Air_Speed_Real.Format("%08x", d); 
					break;
					//0000 0110 1000 1000
				case 0x86://ָʾ����
					s = (short)(d >> 16);
					speed0 = s * (2048. / 32768); break;
				//	x_Air_Speed.Format("%08x", d);
					//0000 0110 1000 0110
				case 0x85://�����
					s = (short)(d >> 16);
					ma0 = s * (4.096 / 32768);break;
				//	x_Air_Ma.Format("%08x", d); 
					//	0000 0110 0001 0101
				case 0x97://װ����ѹ
					s = (short)(d >> 16);
					airp0 = s * (128. / 32768);break;
					//x_Air_AirP.Format("%08x", d); 
					//0000 0110 1001 0111
				case 0xA1://����
					s = (short)(d >> 16);
					attack0 = s * (45. / 32768); break;
					//x_Air_Attack.Format("%08x", d);
					//0000 0110 1010 0001
				case 0x84://�����ѹ�߶�
					s = (short)(d >> 16);
					height_a0 = s;
					//0000 0110 1000 0100
				case 0x8A://�����ٶ�
					s = (short)(d >> 16);
					speedud0 = s * (512. / 32768);
					break;
					//0000 0110 1000 1010
				case 0x32://�����
					s = (short)(d >> 16);
					azimuth0 = s * (360. / 32768);
					break;
					//0000 0110 0011 0010
				case 0x33://������
					s = (short)(d >> 16);
					pitch0 = s * (180. / 32768);
					break;
					//0000 0110 0011 0011
				case 0x34://�����
					s = (short)(d >> 16);
					roll0 = s * (180. / 32768);
					break;
					//0000 0110 0011 0100
				case 0x35://���ߵ�߶�
					s = (short)(d >> 16);
					height_r0 = s * (1524. / 32768);
					break;
					//0000 0110 0011 0101
				case 0x36://��Ͱ�ȫ�߶�
					s = (short)(d >> 16);
					height_l0 = s * (1500. / 32768);
					break;
					//0000 0110 0011 0110 
				case 0x37://�໬��
					s = (short)(d >> 16);
					sideslip0 = s * (10. / 32768);
					break;
					//0000 0110 0011 0111
				case 0x38://�������
					s = (short)(d >> 16);
					t0 = s * (10. / 32768);
					break;
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


void CArinc429Dlg::OnRadio100k() 
{
	// TODO: Add your control notification handler code here
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	 // bits rate & parity//�����ʵ�ѡ��
	 // followed definitions can be found in cusfunc.h
	stComm[0].iSelBR = C429_BITRATE100K; // 0: 100k    1: 48k    2: 12.5k   
	
	CArinc429Dlg::SetUp429Card();
	
}


void CArinc429Dlg::OnDraw_Fighter(int x,int y,CDC* pDC)//��ʮ���ߺͿ���ʸ��
{

	
		CPen GreenPen,WhitePen;// �������ʶ���
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
		
		
		CPen*poldPen = pDC->SelectObject(&WhitePen); // ��һ������(λͼ�����ʡ���ˢ��)ѡ��ָ�����豸�������µĶ������ͬһ���͵��϶���
		// ��һ��С����
		pDC->MoveTo(260,190);// ����ƶ���ĳ������
		pDC->LineTo(260,220);// �ӵ�ǰ���꿪ʼ
	// ��һ��С���ߣ�����������ʮ����
		pDC->MoveTo(245,205);
		pDC->LineTo(275,205);	
		// x1,y1,x2,y2Ϊ��Բ����������.x3,y3,x4,y4Ϊ��Բ����ʼ��,�յ�. Arc ��Բ���ǰ���ʱ�뷽��.
	    pDC->Arc(y-radius,x-radius,y+radius,x+radius,y-radius,x-radius,y-radius,x-radius);	
		//��ԲȦ  �뾶����
		// ��ߵ�С����
		pDC->MoveTo(y-radius,x);
		pDC->LineTo(y-radius-10,x);
		// �ұ߻�һ��С����
		pDC->MoveTo(y+radius,x);
		pDC->LineTo(y+radius+10,x);
// ���滭һ��С����
		pDC->MoveTo(y,x-radius);
		pDC->LineTo(y,x-radius-10);

		

		if(height_a0<=height_l0)
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

void CArinc429Dlg::OnDraw_High(int x,CDC* pDC)// ����ѹ�߶ȱ��
{
char c[80];
	int a;
	unsigned int ad;
	unsigned int High_cas,High_casD,High_casU;
	int i,j;
	int text_offset = 7; // ��������ʹ���������Ķ�׼����

	CPen pNewPen;
	pNewPen.CreatePen(PS_SOLID ,2,RGB(0,250,0));  // ���ñʵ� ��ʽ ��� ��ɫ����ɫ��
	CPen* poldPen=pDC->SelectObject(&pNewPen);
	pDC->SetTextColor(RGB(0,250,0)); // �����ı�����ɫ����ɫ��
	pDC->SetBkMode(TRANSPARENT);//  ����DrawText�����������ʽ������Ϊ͸�����
// ��һ������
	pDC->MoveTo(390,205);
	pDC->LineTo(420,205);
	// �ں����±߻����ı� ��ʾ�߶�
	pDC->TextOutA(431, 356, _T("FY.T"));
	pDC->TextOutA(431, 376, _T("NAV GPS"));
	pDC->TextOutA(400, 208, _T("U"));
	 //  ����ת��Ϊ�ַ�����Ҫת�������� c����Ž�����ַ��� 10����ʾҪת��Ϊʮ���ƣ�
	itoa(speedud0, c, 10);
	// ������ֵ��С�ں������潫������ʾ������if�ж���Ϊ��ʼ�ձ��������ں��ߵ��м䣬������Ϊλ���ı䵼�³������߷�Χ
	if (speedud0 < 10)
	{
		pDC->TextOutA(400, 188, c);
	}
	else if (speedud0 < 100)
	{
		pDC->TextOutA(396, 36, c);
	}
	else if (speedud0 < 1000)
	{
		pDC->TextOutA(392, 36, c);
	}
	else if (speedud0 < 10000)
	{
		pDC->TextOutA(388, 36, c);
	}
	else
	{
		pDC->TextOutA(384, 36, c);
	}
	pDC->TextOutA(400, 188, c);

	gcvt(airp0, 4, c);
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

	a = x % 500;// �����ȡ��������ӦС������
	ad = a/10; // ������С��


	High_cas = x/500*500;// ����߶���500�Ķ��ٱ� 
	
	itoa(High_cas,c,10);// ת�����ַ���
	pDC->TextOutA(450,198+ad,c); // ��������ʾ���� ���续���ϵ�500  198��Ӧ0�̶�λ��
	// ����Ӧ�ĳ�����
	pDC->MoveTo(425,205+ad);
	pDC->LineTo(445,205+ad);
	
	for(i = 1;i<5;i++)
	{
		j = i * 10;// 10��ӦһС��
// �������̺���
		pDC->MoveTo(425,205+ad-j);
		pDC->LineTo(435,205+ad-j);
	}
// ���ϻ�ʮ���С��
	for(i = 1;i<15;i++)
	{
		j = i*10;
		pDC->MoveTo(425,205+ad-j-(ad/10)*10);
		pDC->LineTo(435,205+ad-j-(ad/10)*10);
	}
	// ���»�ʮ���С��
	for(i = 1;i<15;i++)
	{
		j = i*10;
		pDC->MoveTo(425,205+ad+j-(ad/10)*10);
		pDC->LineTo(435,205+ad+j-(ad/10)*10);
	}
// ���ݸ߶ȵ���ֵ�����䶯���ϰ���̶ȱ�
	if(a<100)// adƫ����С�ڿ̶ȱ��һ�񣬿������ϻ�������ٵĴ��
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
	else// adƫ�������ڿ̶ȱ��һ�񣬿������ϻ�������ٵĴ��
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
// ���ݸ߶ȵ���ֵ����̬�Ļ��°���̶ȱ�
	if(a>400) // adƫ�������ڿ̶ȱ���ĸ�С�񣬿������»�һ����ٵĴ��
	{
		pDC->MoveTo(435,205+ad+50);
		pDC->LineTo(445,205+ad+50);
		High_casD = High_cas - 500;
		itoa(High_casD,c,10);
		pDC->TextOutA(450,205+ad+50-text_offset,c);
	}
	else// ad��ƫ����С��̶ȱ���ĸ�С�񣬿������»�������ٵĴ��
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

void CArinc429Dlg::OnDraw_Fighteryujing(int x, int y, CDC* pDC)// Ԥ������
{
CPen pNewPen1;   // �������ʶ���
	pNewPen1.CreatePen(PS_SOLID, 1.5, RGB(255, 255, 0));	// ��ɫ
	CPen* poldPen = pDC->SelectObject(&pNewPen1);    // ���ʶ����滻

	if (height_a0 <= height_l0)
	{
		// �����ߺ��������Ԥ�������źţ�ע������y�Ǻ����꣬x��������
		pDC->MoveTo(y - 20, x - 5);
		pDC->LineTo(y - 20, x + 10);
		pDC->MoveTo(y - 20, x + 10);
		pDC->LineTo(y - 1, x + 10);
		pDC->MoveTo(y + 1, x + 10);
		pDC->LineTo(y + 20, x + 10);
		pDC->MoveTo(y + 20, x + 10);
		pDC->LineTo(y + 20, x - 5);
	}

	pDC->SelectObject(poldPen);	   // �����滻��ԭ���Ļ���
}

void CArinc429Dlg::OnDraw_Speed(int x, CDC* pDC)//  ���ٶȺ������
{
char c[80];
	int a;
	unsigned int ad;
	unsigned int V_cas, V_casD, V_casU;
	int i, j;
	int text_offset = 7;   // ��������Ϊ�˱�֤�������ֵ�ں��ߵ�����λ��
	int amp = 2;        // 10/5=2 һ�����10����С�̶���5�����amp������ֵ1Ҫ�����ļ��

	CPen pNewPen;     // �������ʶ���
	pNewPen.CreatePen(PS_SOLID, 1.5, RGB(0, 250, 0));   // ���û������� ����ɫ��
	CPen* poldPen = pDC->SelectObject(&pNewPen);
	pDC->SetTextColor(RGB(0, 255, 0));      // �����ı�����ɫ
	pDC->SetBkMode(TRANSPARENT);          // ����DrawText�����������ʽ������Ϊ͸�����

	// ��һ������
	pDC->MoveTo(80, 205);
	pDC->LineTo(110, 205);

	// �ں��ߵ����滭һ��V����
	pDC->TextOutA(92, 208, _T("V"));

	// ��������ת��Ϊ�ַ���
	gcvt(ma0, 4, c);  // params��Ҫת������ֵ ��Чλ�� �����λ��   return���ַ���ָ��

	// ��ָ��λ�û�һ��M����
	pDC->TextOutA(32, 40, _T("M"));

	// ��M���ŵ��ұ���ʾ����ֵ
	pDC->TextOutA(48, 40, c);

	itoa(x, c, 10);//x����ת�������ݣ�c:Ŀ���ַ����ĵ�ַ��10��ʮ����
		// ������ֵ��λ������V��ֵ�����λ�ã�Ϊ�˱�֤��������ں��ߵ�����
	if (x < 10)
	{
		pDC->TextOutA(92, 188, c);
	}
	else if (x < 100)
	{
		pDC->TextOutA(88, 188, c);
	}
	else if (x < 1000)
	{
		pDC->TextOutA(84, 188, c);
	}
	else
	{
		pDC->TextOutA(80, 188, c);
	}

	a = x % 25;
	ad = a / 5;

	V_cas = x / 25 * 25;

	itoa(V_cas, c, 10);
	// ������ֵλ���������λ������֤��ֵ����Ϳ̶ȱ����ص�����Ϊ���ǽ��ٶ���������࣬���Ҳ�ĸ߶���û��������⡣
	if (x < 10)
	{
		pDC->TextOutA(44, 198 + a * amp, c);
	}
	else if (x < 100)
	{
		pDC->TextOutA(38, 198 + a * amp, c);
	}
	else if (x < 1000)
	{
		pDC->TextOutA(30, 198 + a * amp, c);
	}
	else
	{
		pDC->TextOutA(22, 198 + a * amp, c);
	}

	// ����ֵ�����������Ļ�һ�����ĳ�����
	pDC->MoveTo(75, 205 + a * amp);
	pDC->LineTo(55, 205 + a * amp);

	//���ϻ������̺���
	for (i = 1; i < 5; i++)
	{
		j = i * 5;
		pDC->MoveTo(75, 205 + (a - j) * amp);
		pDC->LineTo(65, 205 + (a - j) * amp);
	}

	// ���ϱߵĵ������̺���Ϊ��׼���ϻ�ʮ�����̺���
	for (i = 1; i < 15; i++)
	{
		j = i * 5;
		pDC->MoveTo(75, 205 + (a - j - ad * 5) * amp);
		pDC->LineTo(65, 205 + (a - j - ad * 5) * amp);
	}

	// ���ϱߵĵ������̺���Ϊ��׼���»�ʮ�����̺���
	for (i = 1; i < 15; i++)
	{
		j = i * 5;
		pDC->MoveTo(75, 205 + (a + j - ad * 5) * amp);
		pDC->LineTo(65, 205 + (a + j - ad * 5) * amp);
	}

	// ����adƫ�������̶ȱ���ϰ벿��
	if (a < 5)   // ���adƫ����С��1����������ϻ��������
	{
		pDC->MoveTo(75, 205 + (a - 25) * amp);
		pDC->LineTo(55, 205 + (a - 25) * amp);
		V_casU = V_cas + 25;
		itoa(V_casU, c, 10);

		// ����Ҫ�������ʾ��ֵ����˿��ǵ��������⣬������ֵ��λ���������λ��
		if (x < 10)
		{
			pDC->TextOutA(44, 205 + (a - 25) * amp - text_offset, c);
		}
		else if (x < 100)
		{
			pDC->TextOutA(38, 205 + (a - 25) * amp - text_offset, c);
		}
		else if (x < 1000)
		{
			pDC->TextOutA(30, 205 + (a - 25) * amp - text_offset, c);
		}
		else
		{
			pDC->TextOutA(22, 205 + (a - 25) * amp - text_offset, c);
		}

		pDC->MoveTo(75, 205 + (a - 50) * amp);
		pDC->LineTo(55, 205 + (a - 50) * amp);
		V_casU = V_cas + 50;
		itoa(V_casU, c, 10);
		if (x < 10)
		{
			pDC->TextOutA(44, 205 + (a - 50) * amp - text_offset, c);
		}
		else if (x < 100)
		{
			pDC->TextOutA(38, 205 + (a - 50) * amp - text_offset, c);
		}
		else if (x < 1000)
		{
			pDC->TextOutA(30, 205 + (a - 50) * amp - text_offset, c);
		}
		else
		{
			pDC->TextOutA(22, 205 + (a - 50) * amp - text_offset, c);
		}

	}
	else  // ���adƫ��������һ��Ļ�����ô�������ϻ��������
	{
		pDC->MoveTo(75, 205 + (a - 25) * amp);
		pDC->LineTo(55, 205 + (a - 25) * amp);
		V_casU = V_cas + 25;
		itoa(V_casU, c, 10);

		// ������ֵλ������
		if (x < 10)
		{
			pDC->TextOutA(44, 205 + (a - 25) * amp - text_offset, c);
		}
		else if (x < 100)
		{
			pDC->TextOutA(38, 205 + (a - 25) * amp - text_offset, c);
		}
		else if (x < 1000)
		{
			pDC->TextOutA(30, 205 + (a - 25) * amp - text_offset, c);
		}
		else
		{
			pDC->TextOutA(22, 205 + (a - 25) * amp - text_offset, c);
		}


		pDC->MoveTo(75, 205 + (a - 50) * amp);
		pDC->LineTo(55, 205 + (a - 50) * amp);
		V_casU = V_cas + 50;
		itoa(V_casU, c, 10);
		if (x < 10)
		{
			pDC->TextOutA(44, 205 + (a - 50) * amp - text_offset, c);
		}
		else if (x < 100)
		{
			pDC->TextOutA(38, 205 + (a - 50) * amp - text_offset, c);
		}
		else if (x < 1000)
		{
			pDC->TextOutA(30, 205 + (a - 50) * amp - text_offset, c);
		}
		else
		{
			pDC->TextOutA(22, 205 + (a - 50) * amp - text_offset, c);
		}

		pDC->MoveTo(75, 205 + (a - 75) * amp);
		pDC->LineTo(55, 205 + (a - 75) * amp);
		V_casU = V_cas + 75;
		itoa(V_casU, c, 10);
		if (x < 10)
		{
			pDC->TextOutA(44, 205 + (a - 75) * amp - text_offset, c);
		}
		else if (x < 100)
		{
			pDC->TextOutA(38, 205 + (a - 75) * amp - text_offset, c);
		}
		else if (x < 1000)
		{
			pDC->TextOutA(30, 205 + (a - 75) * amp - text_offset, c);
		}
		else
		{
			pDC->TextOutA(22, 205 + (a - 75) * amp - text_offset, c);
		}
	}

	// ����adƫ�������̶ȱ���°벿��
	if (a > 20) // ���adƫ���������ĸ���ô�������»�һ�����
	{
		pDC->MoveTo(75, 205 + (a + 25) * amp);
		pDC->LineTo(55, 205 + (a + 25) * amp);
		V_casD = V_cas - 25;
		itoa(V_casD, c, 10);

		// ������ֵλ���������λ�ý��ж���
		if (x < 10)
		{
			pDC->TextOutA(44, 205 + (a + 25) * amp - text_offset, c);
		}
		else if (x < 100)
		{
			pDC->TextOutA(38, 205 + (a + 25) * amp - text_offset, c);
		}
		else if (x < 1000)
		{
			pDC->TextOutA(30, 205 + (a + 25) * amp - text_offset, c);
		}
		else
		{
			pDC->TextOutA(22, 205 + (a + 25) * amp - text_offset, c);
		}
	}
	else  // ���adƫ����С����С����������»��������
	{
		pDC->MoveTo(75, 205 + (a + 25) * amp);
		pDC->LineTo(55, 205 + (a + 25) * amp);
		V_casD = V_cas - 25;
		itoa(V_casD, c, 10);

		// ������ֵλ���������λ�� 
		if (x < 10)
		{
			pDC->TextOutA(44, 205 + (a + 25) * amp - text_offset, c);
		}
		else if (x < 100)
		{
			pDC->TextOutA(38, 205 + (a + 25) * amp - text_offset, c);
		}
		else if (x < 1000)
		{
			pDC->TextOutA(30, 205 + (a + 25) * amp - text_offset, c);
		}
		else
		{
			pDC->TextOutA(22, 205 + (a + 25) * amp - text_offset, c);
		}

		pDC->MoveTo(75, 205 + (a + 50) * amp);
		pDC->LineTo(55, 205 + (a + 50) * amp);
		V_casD = V_cas - 50;
		itoa(V_casD, c, 10);
		if (x < 10)
		{
			pDC->TextOutA(44, 205 + (a + 50) * amp - text_offset, c);
		}
		else if (x < 100)
		{
			pDC->TextOutA(38, 205 + (a + 50) * amp - text_offset, c);
		}
		else if (x < 1000)
		{
			pDC->TextOutA(30, 205 + (a + 50) * amp - text_offset, c);
		}
		else
		{
			pDC->TextOutA(22, 205 + (a + 50) * amp - text_offset, c);
		}
	}
	pDC->SelectObject(poldPen);   // �滻��ԭ���Ļ��ʶ���  MFC�̶���ʽ
}

void CArinc429Dlg::OnDraw_BlackRect(CDC* pDC)// ��ɫ����
{
CRect rect(0, 0, 0, 0);  
	CBrush brush;         //  ��ˢ����
	brush.CreateSolidBrush(RGB(0, 0, 0));   // Ĭ��ʡȴ��windows�����ǰ�ɫ�ģ�Ҫ����һ����ɫ�ı������ȣ�1.����һ����ˢ 
	pDC->FillRect(rect, &brush);           // 2.��䱳��


}

void CArinc429Dlg::OnDraw_HXJ(double x, CDC* pDC) //  ������ǣ��Ϸ���
{
//CDC *pDC = GetDC();
	int HX_int;
	int HX_cas, HX_casL;
	unsigned int a;
	unsigned int al;
	int i, j;
	unsigned int amp = 4;  // ��ֵ1���ĸ����  20/5 �̶ȱ�һ��С����Ϊ20��������ֵ5
	char c[80];

	pDC->SetTextColor(RGB(0, 250, 0));   // �����ı���ɫΪ��ɫ
	pDC->SetBkMode(TRANSPARENT);      // ���������ʽΪ͸�����
	CPen pNewPen;  // �������ʶ���
	pNewPen.CreatePen(PS_SOLID, 1.5, RGB(0, 250, 0));   // ���û�������
	CPen* poldPen = pDC->SelectObject(&pNewPen);   // �̶���ʽ

	HX_int = (int)x;   // ת��Ϊ��������

	// ��ָ��λ�û�һ�����ߣ��̶������ָ�����ߣ�
	pDC->MoveTo(260, 80);
	pDC->LineTo(260, 60);

	a = x * 4;   // ����ֵת��Ϊ��Ҫ�Ŀ��  ����1ռ�ĸ���ȣ���ô20��ռ20*4=80�����
	HX_int = (int)a;
	HX_cas = HX_int / 80 * 20;

	// ��������ƫ����
	a = HX_int % 80;

	// ����һ������
	pDC->MoveTo(260 - a, 55);
	pDC->LineTo(260 - a, 40);

	al = a / 25;//����ѻ�������������Χ��0~3��

	// ���ҵ��󻭶����� 
	for (i = -9; i < 9; i++)
	{
		j = i * 5;
		pDC->MoveTo(260 - a + (al * 5 - j) * amp, 55);
		pDC->LineTo(260 - a + (al * 5 - j) * amp, 45);
	}

	// ���ҵ������������߲�������Ӧ����ֵ
	for (i = -2; i < 3; i++)
	{
		pDC->MoveTo(260 - a + 20 * i * amp, 55);
		pDC->LineTo(260 - a + 20 * i * amp, 35);
		if (HX_cas == 0 && i == -2)
		{
			HX_casL = 320;
		}
		else if (HX_cas == 0 && i == -1)
		{
			HX_casL = 340;
		}
		else if (HX_cas == 20 && i == -2)
		{
			HX_casL = 340;
		}
		else if (HX_cas == 340 && i == 1)
		{
			HX_casL = 0;
		}
		else if (HX_cas == 340 && i == 2)
		{
			HX_casL = 20;
		}
		else if (HX_cas == 320 && i == 2)
		{
			HX_casL = 0;
		}
		else
		{
			HX_casL = HX_cas + 20 * i;
		}
		itoa(HX_casL, c, 10);
		if (HX_casL < 10)
		{
			pDC->TextOutA(260 - a + 20 * i * amp - 4, 17, c);
		}
		else if (HX_casL < 100)
		{
			pDC->TextOutA(260 - a + 20 * i * amp - 8, 17, c);
		}
		else
		{
			pDC->TextOutA(260 - a + 20 * i * amp - 12, 17, c);
		}
	}
	pDC->SelectObject(poldPen);
}

void CArinc429Dlg::OnDraw_HGKD(double HGJ, CDC* pDC)//  ������̶ȣ��·���
{
//CDC *pDC = GetDC();
	char c[80];
	int i;
	int R = 215;    // ��Բ�뾶
	int r = 185;    // СԲ�뾶
	int dr = 200;
	double x, y;
	double theta;
	int x1, y1;
	int text;

	CPen pNewPen;
	pNewPen.CreatePen(PS_SOLID, 1.5, RGB(0, 255, 0));
	CPen* poldPen = pDC->SelectObject(&pNewPen);

	HGJ = HGJ / 180 * PI;   // ת��Ϊ����

	// ���̶��߻�ΪԲ��״���ܽǶ���120��
	for (i = 0; i < 5; i++)
	{
		// ��60�㿪ʼ��ÿ��ʮ������ž���һ��������
		x = 260 + R * cos(PI / 3 + i * PI / 12);
		y = 205 + R * sin(PI / 3 + i * PI / 12);
		x1 = (int)x;
		y1 = (int)y;
		pDC->MoveTo(x1, y1);
		x = 260 + r * cos(PI / 3 + i * PI / 12);
		y = 205 + r * sin(PI / 3 + i * PI / 12);
		x1 = (int)x;
		y1 = (int)y;
		pDC->LineTo(x1, y1);
	}

	// ��������ֵ90 0 180 �Ȼ��ڿ̶�����
	itoa(-180, c, 10);
	pDC->TextOutA(335, 345, c);
	itoa(-90, c, 10);
	pDC->TextOutA(293, 365, c);
	itoa(0, c, 10);
	pDC->TextOutA(255, 370, c);
	itoa(90, c, 10);
	pDC->TextOutA(205, 365, c);
	itoa(180, c, 10);
	pDC->TextOutA(155, 345, c);

	// ��60�㿪ʼÿ��5�����ž���һ��������
	for (i = 0; i < 13; i++)
	{
		x = 260 + R * cos(PI / 3 + i * PI / 36);
		y = 205 + R * sin(PI / 3 + i * PI / 36);
		x1 = (int)x;
		y1 = (int)y;
		pDC->MoveTo(x1, y1);
		x = 260 + dr * cos(PI / 3 + i * PI / 36);
		y = 205 + dr * sin(PI / 3 + i * PI / 36);
		x1 = (int)x;
		y1 = (int)y;
		pDC->LineTo(x1, y1);
	}

	//  ��С���Ƿ���
	x = 260 + (R + 5) * cos(PI / 2 + HGJ / 6);
	y = 205 + (R + 5) * sin(PI / 2 + HGJ / 6);
	x1 = (int)(x + 0.5);
	y1 = (int)(y + 0.5);
	pDC->MoveTo(x1, y1);

	x = 252 - 260;
	y = 435 - 205;
	R = sqrt(x * x + y * y);
	theta = atan(x / y);
	x = 260 + R * cos(PI / 2 + HGJ / 6 + theta);
	y = 205 + R * sin(PI / 2 + HGJ / 6 + theta);
	x1 = (int)(x + 0.5);
	y1 = (int)(y + 0.5);
	pDC->LineTo(x1, y1);

	x = 268 - 260;
	y = 435 - 205;
	R = sqrt(x * x + y * y);
	theta = atan(x / y);
	x = 260 + R * cos(PI / 2 + HGJ / 6 + theta);
	y = 205 + R * sin(PI / 2 + HGJ / 6 + theta);
	x1 = (int)(x + 0.5);
	y1 = (int)(y + 0.5);
	pDC->LineTo(x1, y1);

	y = 425 - 205;
	R = (int)y;
	x = 260 + R * cos(PI / 2 + HGJ / 6);
	y = 205 + R * sin(PI / 2 + HGJ / 6);
	x1 = (int)(x + 0.5);
	y1 = (int)(y + 0.5);
	pDC->LineTo(x1, y1);
	pDC->SelectObject(poldPen);
}

void CArinc429Dlg::OnDraw_HG(double  Roll, double FYJ, CDC* pDC)//  ����̬��
{
char c[80];
	int a;
	int i, j, k;
	double x, y, R;
	int x1, y1;
	double theta;
	int FYJ_int;
	int FYJ_cas;
	int amp = 20;
	int text_offset = 12;
	CPen pNewPen;
	pNewPen.CreatePen(PS_SOLID, 1.5, RGB(0, 255, 0));
	CPen* poldPen = pDC->SelectObject(&pNewPen);
	pDC->SetTextColor(RGB(0, 255, 0));
	pDC->SetBkMode(TRANSPARENT);

	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	//��&if�е�ǰλ�ú����sizeof���ֽ� ��typedef unsigned int size_t ���� 0 �滻������ lf��
	lf.lfHeight = 17;                      // request a 12-pixel-height font
	lf.lfEscapement = Roll * 10;
	VERIFY(font.CreateFontIndirect(&lf));  // create the font
	pDC->SelectObject(&font);

	Roll = Roll / 180 * PI;// ת��Ϊ����

	FYJ_int = (int)FYJ;
	FYJ_cas = FYJ_int / 5 * 5;
	FYJ_int = FYJ * amp;//amp=20
	a = FYJ_int % 100;

	//  ������໭������̬��
	for (i = -3; i < 4; i++)
	{
		j = i * 5;
		if (FYJ_cas + j >= 0)
		{
			x = 240 - 260;
			y = -a + j * amp;
			R = x * x + y * y;
			R = sqrt(R);//������
			theta = atan(y / x);
			if (x < 0 && y < 0)
			{
				theta = theta - PI;
			}
			else if (x < 0 && y >= 0)
			{
				theta = theta + PI;
			}
			x = 260 + R * cos(theta + Roll);
			y = 205 + R * sin(theta + Roll);
			x1 = (int)(x + 0.5);
			y1 = (int)(y + 0.5);
			pDC->MoveTo(x1, y1);

			x = 180 - 260;
			y = -a + j * amp;
			R = x * x + y * y;
			R = sqrt(R);
			theta = atan(y / x);
			if (x < 0 && y < 0)
			{
				theta = theta - PI;
			}
			else if (x < 0 && y >= 0)
			{
				theta = theta + PI;
			}
			x = 260 + R * cos(theta + Roll);
			y = 205 + R * sin(theta + Roll);
			x1 = (int)(x + 0.5);
			y1 = (int)(y + 0.5);
			pDC->LineTo(x1, y1);

			x = 180 - 260;
			y = -a + j * amp - 10;
			R = x * x + y * y;
			R = sqrt(R);
			theta = atan(y / x);
			if (x < 0 && y < 0)
			{
				theta = theta - PI;
			}
			else if (x < 0 && y >= 0)
			{
				theta = theta + PI;
			}
			x = 260 + R * cos(theta + Roll);
			y = 205 + R * sin(theta + Roll);
			x1 = (int)(x + 0.5);
			y1 = (int)(y + 0.5);
			pDC->LineTo(x1, y1);


			x = 280 - 260;
			y = -a + j * amp;
			R = x * x + y * y;
			R = sqrt(R);
			theta = atan(y / x);
			if (x < 0 && y < 0)
			{
				theta = theta - PI;
			}
			else if (x < 0 && y >= 0)
			{
				theta = theta + PI;
			}
			x = 260 + R * cos(theta + Roll);
			y = 205 + R * sin(theta + Roll);
			x1 = (int)(x + 0.5);
			y1 = (int)(y + 0.5);
			pDC->MoveTo(x1, y1);

			x = 340 - 260;
			y = -a + j * amp;
			R = x * x + y * y;
			R = sqrt(R);
			theta = atan(y / x);
			if (x < 0 && y < 0)
			{
				theta = theta - PI;
			}
			else if (x < 0 && y >= 0)
			{
				theta = theta + PI;
			}
			x = 260 + R * cos(theta + Roll);
			y = 205 + R * sin(theta + Roll);
			x1 = (int)(x + 0.5);
			y1 = (int)(y + 0.5);
			pDC->LineTo(x1, y1);

			x = 340 - 260;
			y = -a + j * amp - 10;
			R = x * x + y * y;
			R = sqrt(R);
			theta = atan(y / x);
			if (x < 0 && y < 0)
			{
				theta = theta - PI;
			}
			else if (x < 0 && y >= 0)
			{
				theta = theta + PI;
			}
			x = 260 + R * cos(theta + Roll);
			y = 205 + R * sin(theta + Roll);
			x1 = (int)(x + 0.5);
			y1 = (int)(y + 0.5);
			pDC->LineTo(x1, y1);
		}
		else
		{
			x = 240 - 260;
			y = -a + j * amp;
			R = x * x + y * y;
			R = sqrt(R);
			theta = atan(y / x);
			if (x < 0 && y < 0)
			{
				theta = theta - PI;
			}
			else if (x < 0 && y >= 0)
			{
				theta = theta + PI;
			}
			x = 260 + R * cos(theta + Roll);
			y = 205 + R * sin(theta + Roll);
			x1 = (int)(x + 0.5);
			y1 = (int)(y + 0.5);
			pDC->MoveTo(x1, y1);

			for (k = 1; k <= 30; k = k + 2)
			{
				x = 240 - k * 2 - 260;
				y = -a + j * amp;
				R = x * x + y * y;
				R = sqrt(R);
				theta = atan(y / x);
				if (x < 0 && y < 0)
				{
					theta = theta - PI;
				}
				else if (x < 0 && y >= 0)
				{
					theta = theta + PI;
				}
				x = 260 + R * cos(theta + Roll);
				y = 205 + R * sin(theta + Roll);
				x1 = (int)(x + 0.5);
				y1 = (int)(y + 0.5);
				pDC->LineTo(x1, y1);

				x = 240 - (k + 1) * 2 - 260;
				y = -a + j * amp;
				R = x * x + y * y;
				R = sqrt(R);
				theta = atan(y / x);
				if (x < 0 && y < 0)
				{
					theta = theta - PI;
				}
				else if (x < 0 && y >= 0)
				{
					theta = theta + PI;
				}
				x = 260 + R * cos(theta + Roll);
				y = 205 + R * sin(theta + Roll);
				x1 = (int)(x + 0.5);
				y1 = (int)(y + 0.5);
				pDC->MoveTo(x1, y1);
			}

			x = 180 - 260;
			y = -a + j * amp - 10;
			R = x * x + y * y;
			R = sqrt(R);
			theta = atan(y / x);
			if (x < 0 && y < 0)
			{
				theta = theta - PI;
			}
			else if (x < 0 && y >= 0)
			{
				theta = theta + PI;
			}
			x = 260 + R * cos(theta + Roll);
			y = 205 + R * sin(theta + Roll);
			x1 = (int)(x + 0.5);
			y1 = (int)(y + 0.5);
			pDC->LineTo(x1, y1);


			x = 280 - 260;
			y = -a + j * amp;
			R = x * x + y * y;
			R = sqrt(R);
			theta = atan(y / x);
			if (x < 0 && y < 0)
			{
				theta = theta - PI;
			}
			else if (x < 0 && y >= 0)
			{
				theta = theta + PI;
			}
			x = 260 + R * cos(theta + Roll);
			y = 205 + R * sin(theta + Roll);
			x1 = (int)(x + 0.5);
			y1 = (int)(y + 0.5);
			pDC->MoveTo(x1, y1);

			for (k = 1; k <= 30; k = k + 2)
			{
				x = 280 + k * 2 - 260;
				y = -a + j * amp;
				R = x * x + y * y;
				R = sqrt(R);
				theta = atan(y / x);
				if (x < 0 && y < 0)
				{
					theta = theta - PI;
				}
				else if (x < 0 && y >= 0)
				{
					theta = theta + PI;
				}
				x = 260 + R * cos(theta + Roll);
				y = 205 + R * sin(theta + Roll);
				x1 = (int)(x + 0.5);
				y1 = (int)(y + 0.5);
				pDC->LineTo(x1, y1);

				x = 280 + (k + 1) * 2 - 260;
				y = -a + j * amp;
				R = x * x + y * y;
				R = sqrt(R);
				theta = atan(y / x);
				if (x < 0 && y < 0)
				{
					theta = theta - PI;
				}
				else if (x < 0 && y >= 0)
				{
					theta = theta + PI;
				}
				x = 260 + R * cos(theta + Roll);
				y = 205 + R * sin(theta + Roll);
				x1 = (int)(x + 0.5);
				y1 = (int)(y + 0.5);
				pDC->MoveTo(x1, y1);
			}

			x = 340 - 260;
			y = -a + j * amp - 10;
			R = x * x + y * y;
			R = sqrt(R);
			theta = atan(y / x);
			if (x < 0 && y < 0)
			{
				theta = theta - PI;
			}
			else if (x < 0 && y >= 0)
			{
				theta = theta + PI;
			}
			x = 260 + R * cos(theta + Roll);
			y = 205 + R * sin(theta + Roll);
			x1 = (int)(x + 0.5);
			y1 = (int)(y + 0.5);
			pDC->LineTo(x1, y1);
		}
		itoa(FYJ_cas + j, c, 10);

		x = 145 - 260;
		y = -a + j * amp - text_offset;
		R = x * x + y * y;
		R = sqrt(R);
		theta = atan(y / x);
		if (x < 0 && y < 0)
		{
			theta = theta - PI;
		}
		else if (x < 0 && y >= 0)
		{
			theta = theta + PI;
		}
		x = 260 + R * cos(theta + Roll);
		y = 205 + R * sin(theta + Roll);
		x1 = (int)(x + 0.5);
		y1 = (int)(y + 0.5);
		pDC->TextOutA(x1, y1, c);

		x = 350 - 260;
		y = -a + j * amp - text_offset;
		R = x * x + y * y;
		R = sqrt(R);
		theta = atan(y / x);
		if (x < 0 && y < 0)
		{
			theta = theta - PI;
		}
		else if (x < 0 && y >= 0)
		{
			theta = theta + PI;
		}
		x = 260 + R * cos(theta + Roll);
		y = 205 + R * sin(theta + Roll);
		x1 = (int)(x + 0.5);
		y1 = (int)(y + 0.5);
		pDC->TextOutA(x1, y1, c);
	}
	pDC->SelectObject(poldPen);
}
