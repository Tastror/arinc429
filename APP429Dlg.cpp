// APP429Dlg.cpp : implementation file
//

#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include "APP429.h"
#include "APP429Dlg.h"
#include "CardSel.h"
#include "SetUp.h"
#include "cusfunc.h"
#include "DLL429D42_lib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	THREAD_EXITCODE		0

int iTabID=0;

BYTE btCardId=0;
HANDLE hCard=NULL;
TriggerDepth_STRUCT stTriggerLevel={0};
LabelTable_STRUCT stLabelTable={0};
BOOL blFilter[CHNO_RMAX];
STCOMMUNICATION stComm[CHNO_TMAX];
SYSTEMTIME stSysTime={0};
WORD wdMode=C429_NORMAL;
BOOL blTimeTag[CHNO_RMAX];
DWORD dwTime=0;
WORD wdBInterval[CHNO_TMAX];
WORD wdSInterval[CHNO_TMAX];

BOOL isNeedThread=FALSE;
HANDLE hThread=NULL; // handle to thread function
DWORD dwThreadId=0;

BOOL blRxNow=FALSE;
HWND ghWnd=NULL;

DWORD dwTxBuf[FIFO_TMAX];
WORD wdTxBufLen=0;

DWORD WINAPI ThreadFunc(LPVOID lpParam); // thread function
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
// CAPP429Dlg dialog

CAPP429Dlg::CAPP429Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAPP429Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAPP429Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAPP429Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAPP429Dlg)
	DDX_Control(pDX, IDC_CHECK_SL2, m_check_sl2);
	DDX_Control(pDX, IDC_CHECK_SL1, m_check_sl1);
	DDX_Control(pDX, IDC_LIST_SL, m_list_sl);
	DDX_Control(pDX, IDC_EDIT_SENDCOUNT, m_edit_sendcount);
	DDX_Control(pDX, IDC_BUTTON_STARTREV, m_button_startrev);
	DDX_Control(pDX, IDC_EDIT_SENDDATA, m_edit_senddata);
	DDX_Control(pDX, IDC_TAB_REV, m_tab_rev);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAPP429Dlg, CDialog)
	//{{AFX_MSG_MAP(CAPP429Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CLR, OnButtonClr)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_LOADF, OnButtonLoadf)
	ON_BN_CLICKED(IDC_BUTTON_SAVEF, OnButtonSavef)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_STARTREV, OnButtonStartrev)
	ON_BN_CLICKED(IDC_BUTTON_STOPTIMERTRA, OnButtonStoptimertra)
	ON_EN_CHANGE(IDC_EDIT_SENDDATA, OnChangeEditSenddata)
	ON_EN_KILLFOCUS(IDC_EDIT_SENDDATA, OnKillfocusEditSenddata)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_REV, OnSelchangeTabRev)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_REV, OnSelchangingTabRev)
	ON_COMMAND(IDM_SETUP, OnSetup)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAPP429Dlg message handlers

BOOL CAPP429Dlg::OnInitDialog()
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
	CCardSel dlgCardSel;
	int i=0, j=0;
	char c[80];
	WORD wd=0;

	ghWnd = this->m_hWnd;
	
	if (dlgCardSel.DoModal()!=IDOK)
	{
		ExitProcess(0);
		return FALSE;
	}

	//  Init Tab Control
	//
	for (i=0; i<CHNO_RMAX; i++)
	{
		sprintf(c, "第%d路", i+1);
		this->m_tab_rev.InsertItem(i, TEXT(c));
	}
	this->m_tab_rev.SetCurSel(0);

	//  Init Rx ListBox
	//
	for (i=0; i<CHNO_RMAX; i++)
	{
		ListBox_ResetContent(::GetDlgItem(this->m_hWnd, IDC_LIST_RL1+i));
		::SetWindowText(::GetDlgItem(this->m_hWnd, IDC_EDIT_REVCOUNT1+i), TEXT("0"));
		if (i>0)
		{
			::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_LIST_RL1+i), SW_HIDE);
			::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_EDIT_REVCOUNT1+i), SW_HIDE);
		}
	}

	//  Init other windows
	//
	for (i=0; i<CHNO_TMAX; i++)
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_SL1+i), BST_CHECKED);
	}

	this->m_edit_sendcount.SetWindowText(TEXT("0"));
	this->m_edit_senddata.LimitText(8);
	this->m_edit_senddata.SetWindowText(TEXT("0"));

	//  Init Global Variables
	//

	stTriggerLevel.Chan0Depth_I = 0; // default Trigger Level
	stTriggerLevel.Chan1Depth_I = 0;
	stTriggerLevel.Chan2Depth_I = 0; 
	stTriggerLevel.Chan3Depth_I = 0;
	stTriggerLevel.Chan0Depth_O = 0;
	stTriggerLevel.Chan1Depth_O = 0;

	for (i=0; i<SD_MAX; i++) // default Label Filter
	{
		for (j=0; j<LABEL_MAX; j++)
		{
			stLabelTable.LabFilterChan0[i][j]=0;
			stLabelTable.LabFilterChan1[i][j]=0;
			stLabelTable.LabFilterChan2[i][j]=0;
			stLabelTable.LabFilterChan3[i][j]=0;
		}
	}
	
	for (i=0; i<CHNO_TMAX; i++) // bits rate & parity
	{ // followed definitions can be found in cusfunc.h
		stComm[i].iSelBR = C429_BITRATE100K; // 0: 100k    1: 48k    2: 12.5k
		stComm[i].iSelParity = C429_PARITY_NONE; // 0: odd    1: even    2: none
		wdBInterval[i] = 0;
		wdSInterval[i] = 0;
	}

	for (i=0; i<CHNO_RMAX; i++)
	{
		blFilter[i] = FALSE;  // disable label filter function
		blTimeTag[i] = FALSE;  // disable Time Tag function
	}

	wdMode=C429_NORMAL; // Normal work mode

#ifndef CARD_DEBUG
	//	Try to Open card and setting up the card with default configuration
	//

	//  0. open card
	//
	if (!Card_Open(&hCard, btCardId))
	{
		MessageBox(TEXT("程序找不到板卡,即将退出!\n\n(Card_Open函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
		ExitProcess(0);
		return FALSE; // quit program
	}
	if (hCard==NULL)
	{
		MessageBox(TEXT("程序找不到板卡,即将退出!\n\n(板卡句柄获取失败)"), TEXT("错误"), MB_OK | MB_ICONERROR);
		ExitProcess(0);
		return FALSE; // quit program
	}

	//  1. reset card
	//
	if (!ResetCard(hCard)) // reset Card
	{
		MessageBox(TEXT("复位板卡失败,即将退出程序!\n\n(ResetCard函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
		if (!Card_Close(hCard))
		{
			MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
		}
		ExitProcess(0);
		return FALSE; // quit program
	}

	//  2. setting up configure word for communication
	//
	for (i=0; i<CHNO_TMAX; i++)
	{
		wd = ::Get429ConfigureWord(stComm[i].iSelBR, stComm[i].iSelParity, wdMode);
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
		if (SetConfigureWord(hCard, (BYTE)(i), wd))
		{
			if (stComm[i].iSelBR == C429_BITRATE48K) // enable 48k function
			{
				EnableBaudrate_48K(hCard, (BYTE)(i), TRUE);
			}
			else
			{
				EnableBaudrate_48K(hCard, (BYTE)(i), FALSE);
			}
		}
		else
		{
			MessageBox(TEXT("配置硬件出错,即将退出程序!\n\n(SetConfigureWord函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
			if (!Card_Close(hCard))
			{
				MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
			}
			ExitProcess(0);
			return FALSE; // quit program
		}
	}

	//  3. configuring Trigger Level
	//
	SetTriggerDepth(hCard, &stTriggerLevel);

	//  4. setting up Label Filter
	//
	SetLabelFilter(hCard, &stLabelTable);
	for (i=0; i<CHNO_RMAX; i++)
	{
		if (blFilter[i])
		{
			if (!StartLabelFilter(hCard, (BYTE)(i), TRUE))
			{
				MessageBox(TEXT("添加标号过滤功能出错,即将退出程序!\n\n(StartLabelFilter函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				if (!Card_Close(hCard))
				{
					MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				}
				ExitProcess(0);
				return FALSE; // quit program
			}
		}
		else
		{
			if (!StartLabelFilter(hCard, (BYTE)(i), FALSE))
			{
				MessageBox(TEXT("取消标号过滤功能出错,即将退出程序!\n\n(StartLabelFilter函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				if (!Card_Close(hCard))
				{
					MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				}
				ExitProcess(0);
				return FALSE; // quit program
			}
		}
	}

	//  5. configuring Time Tag
	//
	for (i=0; i<CHNO_RMAX; i++)
	{
		if (blTimeTag[i])
		{
			if (!AddTimeTag(hCard, (BYTE)(i), TRUE))
			{
				MessageBox(TEXT("添加时间标签功能出错,即将退出程序!\n\n(AddTimeTag函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				if (!Card_Close(hCard))
				{
					MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				}
				ExitProcess(0);
				return FALSE; // quit program
			}
		}
		else
		{
			if (!AddTimeTag(hCard, (BYTE)(i), FALSE))
			{
				MessageBox(TEXT("取消时间标签功能出错,即将退出程序!\n\n(AddTimeTag函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				if (!Card_Close(hCard))
				{
					MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				}
				ExitProcess(0);
				return FALSE; // quit program
			}
		}
	}
	StartTimeTag(hCard, FALSE, &stSysTime); // disable time tag
	dwTime = 0;
	
	//  6. setting up Tx Timer Interval
	//
	for (i=0; i<CHNO_TMAX; i++)
	{
		if (!SetTimerIntervalB(hCard, (BYTE)(i), wdBInterval[i]))
		{
			MessageBox(TEXT("设置群定时发送功能出错,即将退出程序!\n\n(SetTimerIntervalB函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
			if (!Card_Close(hCard))
			{
				MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
			}
			ExitProcess(0);
			return FALSE; // quit program
		}

		if (!SetTimerIntervalS(hCard, (BYTE)(i), wdSInterval[i]))
		{
			MessageBox(TEXT("设置字定时发送功能出错,即将退出程序!\n\n(SetTimerIntervalS函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
			if (!Card_Close(hCard))
			{
				MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
			}
			ExitProcess(0);
			return FALSE; // quit program
		}

		if (wdBInterval[i]>0)
		{
			StartTimerB(hCard, (BYTE)(i), TRUE);// enable Tx Timer
		}
		else
		{
			StartTimerB(hCard, (BYTE)(i), FALSE);// disable Tx Timer
		}

		if (wdSInterval[i]>0)
		{
			StartTimerS(hCard, (BYTE)(i), TRUE);// enable Tx Timer
		}
		else
		{
			StartTimerS(hCard, (BYTE)(i), FALSE);// disable Tx Timer
		}
	}

	if(!Enable_R(hCard,TRUE))//使能接收，在复位板卡时禁止了接收
	{
		MessageBox(TEXT("使能接收失败"), TEXT("错误"), MB_OK | MB_ICONERROR);
	}
#endif	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAPP429Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAPP429Dlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAPP429Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAPP429Dlg::OnSetup() 
{
	// TODO: Add your command handler code here
	if (blRxNow)
	{
		//  wait thread to terminated
		//
		this->OnButtonStartrev();
	}

	//  show setup dialog
	//
	{
		CSetUp dlgSetup;
		dlgSetup.DoModal();
	}	
}

void CAPP429Dlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add data into Tx List
	int i=0;
	char c[80];
	DWORD dw=0;

	if (this->m_edit_senddata.LineLength(-1)==0)
	{
		MessageBox(TEXT("请先填写将要发送的数据!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return;
	}

	if ((this->m_list_sl.GetCount())<FIFO_TMAX)
	{
		this->m_edit_senddata.GetWindowText(c, sizeof(c));
		dw = HEXS(c);
		sprintf(c, "%08x", dw);
		this->m_list_sl.AddString(c);
	}

	i = this->m_list_sl.GetCount();
	sprintf(c, "%ld", i);
	this->m_edit_sendcount.SetWindowText(c);	
}

void CAPP429Dlg::OnButtonClr() 
{
	// TODO: Add your control notification handler code here
	// TODO: clear Tx list's content
	int i=0;
	char c[80];

	this->m_list_sl.ResetContent();
	i = this->m_list_sl.GetCount();
	sprintf(c, "%ld", i);
	this->m_edit_sendcount.SetWindowText(c);	
}

void CAPP429Dlg::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	int i=0;
	char c[80];

	i = this->m_list_sl.GetCurSel();
	if (i!=LB_ERR)
	{ // one item was selected
		this->m_list_sl.DeleteString(i);
	}
	else
	{ // no item was selected
		if ((this->m_list_sl.GetCount())>0)
		this->m_list_sl.DeleteString(this->m_list_sl.GetCount()-1);
	}

	i = this->m_list_sl.GetCount();
	sprintf(c, "%ld", i);
	this->m_edit_sendcount.SetWindowText(c);	
}

void CAPP429Dlg::OnButtonLoadf() 
{
	// TODO: Add your control notification handler code here
	// TODO: load Tx data from specify .sdt file
	char path[MAX_PATH];
	FILE *pf;
	char c[80];
	int i=0, l=0;
	DWORD dw=0;

	//  checking amount of Tx Data
	//
	i = this->m_list_sl.GetCount();
	if (i>=FIFO_TMAX)
	{
		MessageBox(TEXT("发送数据列表中的数据已经达到最大限!\n\n请适当地删除发送列表窗口中的数据!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		return;
	}
	l = i;

	//  show open file dialog
	//
	CFileDialog dlgOpenFile(TRUE, ".sdt", NULL, 
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						"sdt file(*.sdt)|*.sdt||", NULL);
	if ((dlgOpenFile.DoModal())!=IDOK)
	{
		return;
	}

	//	Get File Name
	//
	if ((dlgOpenFile.GetPathName()).GetLength()>=MAX_PATH)
	{
		MessageBox(TEXT("所选文件路径长度超出指定范围,请选择一个较短的路径名称!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return;
	}
	memset(path, 0, sizeof(path));
	strcpy(path, (dlgOpenFile.GetPathName()).GetBuffer((dlgOpenFile.GetPathName()).GetLength()));

	//	Open File
	//
	pf = fopen(path, "r+");
	if (pf == NULL)
	{
		MessageBox(TEXT("加载数据文件失败!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return;
	}

	//	Read Data
	//
	while ((feof(pf)==0)&&(l<FIFO_TMAX))
	{
		strcpy(c, "");
		fscanf(pf, "%s\n", c);
		dw = HEXS(c);
		sprintf(c, "%08x", dw);
		this->m_list_sl.AddString(c);
		l++;
	}

	fclose(pf); // Close File

	if (i==l)
	{
		MessageBox(TEXT("数据文件为空,请先对发送列表中的数据进行保存!"), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
	}

	sprintf(c, "%ld", this->m_list_sl.GetCount());
	this->m_edit_sendcount.SetWindowText(c);	
}

void CAPP429Dlg::OnButtonSavef() 
{
	// TODO: Add your control notification handler code here
	// TODO: save Tx list into file
	char path[MAX_PATH];
	FILE *pf;
	char c[80];
	int i=0, l=0;

	//  checking amount of Tx Data
	//
	i = this->m_list_sl.GetCount();
	if (i==0)
	{
		MessageBox(TEXT("发送数据列表不能为空!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		return;
	}
	l = i;

	//  show save file dialog
	//
	CFileDialog dlgSaveFile(FALSE, ".sdt", NULL, 
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						"sdt file(*.sdt)|*.sdt||", NULL);
	if ((dlgSaveFile.DoModal())!=IDOK)
	{
		return;
	}

	//	Get File Name
	//
	if ((dlgSaveFile.GetPathName()).GetLength()>=MAX_PATH)
	{
		MessageBox(TEXT("所选文件路径长度超出指定范围,请选择一个较短的路径名称!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return;
	}
	memset(path, 0, sizeof(path));
	strcpy(path, (dlgSaveFile.GetPathName()).GetBuffer((dlgSaveFile.GetPathName()).GetLength()));
	
	//	Open File
	//
	pf = fopen(path, "w+");
	if (pf == NULL)
	{
		MessageBox(TEXT("创建数据文件失败!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return;
	}

	//	Write Data
	//
	for (i=0; i<l; i++)
	{
		memset(c, 0, sizeof(c));
		this->m_list_sl.GetText(i, c);
		fprintf(pf, "%s\n", c);
	}

	fclose(pf); // Close File	
}

void CAPP429Dlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	int i=0, l=0;
	char c[128];

	//  get Tx data
	//
	wdTxBufLen = 0;
	memset(dwTxBuf, 0, sizeof(DWORD)*FIFO_TMAX);
	l = this->m_list_sl.GetCount();
	if (l==0)
	{
		MessageBox(TEXT("发送数据列表不能为空!"), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	if (l>FIFO_TMAX)
		l = FIFO_TMAX;

	//  fill Tx Buffer
	//
	i = 0;
	while (i<l)
	{
		this->m_list_sl.GetText(i, c);
		dwTxBuf[wdTxBufLen] = HEXS(c);
		wdTxBufLen++;
		i++;
	}

#ifndef CARD_DEBUG
	//  data transmission
	//
	for (i=0; i<CHNO_TMAX; i++)
	{
		if (Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_SL1+i))==BST_CHECKED)
		{
			// we must stop the Tx timer before we want to write data to Tx FIFO
			//
			if (wdBInterval[i]>0)
			{
				if (!StartTimerB(hCard, i, FALSE))
				{
					sprintf(c, "第[%d]路终止群定时发送功能出错!\n\n(StartTimerB函数返回值为[0])", i+1);
					MessageBox(TEXT(c), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
				}
			}

			if (wdSInterval[i]>0)
			{
				if (!StartTimerS(hCard, i, FALSE))
				{
					sprintf(c, "第[%d]路终止字定时发送功能出错!\n\n(StartTimerS函数返回值为[0])", i+1);
					MessageBox(TEXT(c), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
				}
			}

			//start the Tx timer
			//
			if (wdBInterval[i]>0)
			{
				if (!StartTimerB(hCard, i, TRUE))
				{
					sprintf(c, "第[%d]路开启群定时发送功能出错!\n\n(StartTimerB函数返回值为[0])", i+1);
					MessageBox(TEXT(c), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
				}
			}

			if (wdSInterval[i]>0)
			{
				if (!StartTimerS(hCard, i, TRUE))
				{
					sprintf(c, "第[%d]路开启字定时发送功能出错!\n\n(StartTimerS函数返回值为[0])", i+1);
					MessageBox(TEXT(c), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
				}
			}

			if(ReadFIFOStatus_S(hCard, i)!=FIFOFull)
			{
				if (!SendData(hCard, i, (BYTE) wdTxBufLen, dwTxBuf))
				{
					sprintf(c, "第[%d]路发送数据出错!\n\n(SendData函数返回值为[0])", i+1);
					MessageBox(TEXT(c), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
				}					
			}
			else
			{ // Tx FIFO is not empty
				sprintf(c, "第[%d]路硬件缓冲区已满!\n\n(ReadFIFOStatus_S函数返回值为[0x12])", i+1);
				MessageBox(TEXT(c), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
			}
		}
	} // end of for (...
#endif	
}

void CAPP429Dlg::OnButtonStoptimertra() 
{
	// TODO: Add your control notification handler code here
	int i=0;
#ifndef CARD_DEBUG
	char c[128];

	for (i=0; i<CHNO_TMAX; i++)
	{
		if (!StartTimerB(hCard, i, FALSE))
		{
			sprintf(c, "第[%d]路终止定时发送功能出错!\n\n(StartTimerB函数返回值为[0])", i+1);
			MessageBox(TEXT(c), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
		}

		if (!StartTimerS(hCard, i, FALSE))
		{
			sprintf(c, "第[%d]路终止定时发送功能出错!\n\n(StartTimerS函数返回值为[0])", i+1);
			MessageBox(TEXT(c), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
		}
	}
#endif	
}

void CAPP429Dlg::OnChangeEditSenddata() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	// TODO: limited Tx Data
	char c[80], s[80];
	char tc='\0';
	int i=0;
	int l=0, j=0;
	int nStart=0, nEnd=0;
	BOOL isErr=FALSE;
	DWORD dw=0;

	l = this->m_edit_senddata.LineLength(-1);
	if (l==0)
		return;

	memset(s, 0, sizeof(s));
	memset(c, 0, sizeof(c));

	dw = this->m_edit_senddata.GetSel();

	this->m_edit_senddata.GetWindowText(c, sizeof(c)); // get data string with HEX

	//  analyze data string with HEX
	//
	j=0;
	for (i=0; i<l; i++)
	{
		tc = c[i];
		if (((tc>='a')&&(tc<='f'))||((tc>='0')&&(tc<='9'))||((tc>='A')&&(tc<='F')))
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
	this->m_edit_senddata.SetWindowText(s);
	this->m_edit_senddata.SetSel(HIWORD(dw)-1, HIWORD(dw)-1, FALSE);	
}

void CAPP429Dlg::OnKillfocusEditSenddata() 
{
	// TODO: Add your control notification handler code here
	if (this->m_edit_senddata.LineLength(-1)==0)
	{
		this->m_edit_senddata.SetWindowText(TEXT("0"));
	}	
}

void CAPP429Dlg::OnSelchangeTabRev(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_LIST_RL1+iTabID), SW_HIDE);
	::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_EDIT_REVCOUNT1+iTabID), SW_HIDE);

	iTabID = this->m_tab_rev.GetCurSel();
	::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_LIST_RL1+iTabID), SW_SHOW);
	::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_EDIT_REVCOUNT1+iTabID), SW_SHOW);

	::ShowWindow(::GetDlgItem(this->m_hWnd, IDC_BUTTON_STARTREV), SW_SHOW);
	
	*pResult = 0;
}

void CAPP429Dlg::OnSelchangingTabRev(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	iTabID = this->m_tab_rev.GetCurSel();
	
	*pResult = 0;
}

void CAPP429Dlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (MessageBox(TEXT("您确定要退出吗?"), TEXT("退出提示"), MB_YESNO | MB_ICONQUESTION)!=IDYES)
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
			MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
		}
	}
	
	CDialog::OnClose();
}

void CAPP429Dlg::OnButtonStartrev() 
{
	// TODO: Add your control notification handler code here
	int i=0;

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

		this->m_button_startrev.SetWindowText(TEXT("开始接收"));
		blRxNow = FALSE;
	}
	else
	{
		//  Init Rx ListBox
		//
		for (i=0; i<CHNO_RMAX; i++)
		{
			ListBox_ResetContent(::GetDlgItem(this->m_hWnd, IDC_LIST_RL1+i));
			::SetWindowText(::GetDlgItem(this->m_hWnd, IDC_EDIT_REVCOUNT1+i), TEXT("0"));
		}

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
			MessageBox(TEXT("无法创建接收线程,请重新启动应用程序!"), TEXT("错误"), MB_OK | MB_ICONERROR);
			return;
		}

		this->m_button_startrev.SetWindowText(TEXT("停止接收"));
		blRxNow = TRUE;
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
DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	char c[80];
	HWND hWnd=(HWND)lpParam;
	DWORD d=0;
	DWORD dwRxCnt[CHNO_RMAX];
	BYTE chno=0;
	BYTE btTriggerLevel=0;

	memset(dwRxCnt, 0, sizeof(DWORD)*CHNO_RMAX);

	while (isNeedThread)
	{
#ifndef CARD_DEBUG
		chno = 0;
		while ((chno<CHNO_RMAX)&&(isNeedThread))
		{
			//  Get trigger level
			//
			switch (chno)
			{	
				case 0:
					btTriggerLevel = stTriggerLevel.Chan0Depth_I;
					break;
				case 1:
					btTriggerLevel = stTriggerLevel.Chan1Depth_I;
					break;
				case 2:
					btTriggerLevel = stTriggerLevel.Chan2Depth_I;
					break;
				case 3:
					btTriggerLevel = stTriggerLevel.Chan3Depth_I;
					break;
			}
			
			//  Rx channel 1~CHNO_RMAX
			// ----------------------------------------------------------------
			if (btTriggerLevel>0) // triggered
			{
				if (IsFIFOTriggered_R(hCard, chno))
				{
					EnablReadFIFO(hCard,chno);//使能读FIFO数据
					while ((ReadFIFOStatus_R(hCard, chno) != FIFOEmpty)&&(ReadFIFOStatus_R(hCard, chno) != FIFOError))
					{
						d = ReceiveData(hCard, chno);
						if ((wdMode==C429_SELFTEST)&&(stComm[chno/2].iSelParity==C429_PARITY_NONE)) // resume 429 Word
						{
							d = Resume429Word(d);
						}
						sprintf(c, "%08x", d);
						if (blTimeTag[chno])
						{
							d = ReceiveData(hCard, chno); // receive time tag
							CHTIME(dwTime, d, c);
						}
						ListBox_AddString(::GetDlgItem(hWnd, IDC_LIST_RL1+chno), c);
						dwRxCnt[chno]++;
					}
					ultoa(dwRxCnt[chno], c, 10);
					::SetWindowText(::GetDlgItem(hWnd, IDC_EDIT_REVCOUNT1+chno), c);
					
					DisablReadFIFO(hCard);//禁止读FIFO数据
				}
			}
			else // untriggered
			{
				if ((ReadFIFOStatus_R(hCard, chno) != FIFOEmpty)&&(ReadFIFOStatus_R(hCard, chno) != FIFOError))
				{
					EnablReadFIFO(hCard,chno);//使能读FIFO数据
					d = ReceiveData(hCard, chno);
					if ((wdMode==C429_SELFTEST)&&(stComm[chno/2].iSelParity==C429_PARITY_NONE)) // resume 429 Word
					{
						d = Resume429Word(d);
					}
					sprintf(c, "%08x", d);
					if (blTimeTag[chno])
					{
						d = ReceiveData(hCard, chno); // receive time tag
						CHTIME(dwTime, d, c);
					}
					ListBox_AddString(::GetDlgItem(hWnd, IDC_LIST_RL1+chno), c);
					dwRxCnt[chno]++;
					ultoa(dwRxCnt[chno], c, 10);
					::SetWindowText(::GetDlgItem(hWnd, IDC_EDIT_REVCOUNT1+chno), c);
				}
				
				DisablReadFIFO(hCard);//禁止读FIFO数据
			} // end of if (btTriggerLevel...
			chno++;
		} // end of while ((chno<CHNO_RMAX...
#else
		chno = 0;
		while ((chno<CHNO_RMAX)&&(isNeedThread))
		{
			Sleep(10);
			//  Rx channel 1~CHNO_RMAX
			// ----------------------------------------------------------------
			d = rand()*345;
			sprintf(c, "%08x", d);
			d = 1234567; // receive time tag
			CHTIME(dwTime, d, c);
			ListBox_AddString(::GetDlgItem(hWnd, IDC_LIST_RL1+chno), c);
			dwRxCnt[chno]++;
			ultoa(dwRxCnt[chno], c, 10);
			::SetWindowText(::GetDlgItem(hWnd, IDC_EDIT_REVCOUNT1+chno), c);
			chno++;
		} // end of while ((chno<CHNO_RMAX...
#endif
	} // end of while (...
	
	ExitThread(THREAD_EXITCODE);
	return 0;
}
