// SetUp.cpp : implementation file
//

#include "stdafx.h"
#include "windows.h"
#include "windowsx.h"
#include "APP429.h"
#include "SetUp.h"
#include "DLL429D42_lib.h"
#include "cusfunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LABELDLG_BASE 205
#define LABELDLG_BASE_XL 225
#define LABELDLG_BASE_YL 110
#define LABELDLG_BASE_WIDTHL 16
#define LABELDLG_BASE_HEIGHL 16
#define LABELDLG_BASE_XB 225
#define LABELDLG_BASE_YB 110
#define LABELDLG_BASE_WIDTHB 16
#define LABELDLG_BASE_HEIGHB 16

extern HANDLE hCard;
extern TriggerDepth_STRUCT stTriggerLevel;
extern LabelTable_STRUCT stLabelTable;
extern BOOL blFilter[CHNO_RMAX];
extern STCOMMUNICATION stComm[CHNO_TMAX];
extern WORD wdMode;
extern BOOL blTimeTag[CHNO_RMAX];
extern WORD wdBInterval[CHNO_TMAX];
extern WORD wdSInterval[CHNO_TMAX];
extern SYSTEMTIME stSysTime;
extern DWORD dwTime;

TriggerDepth_STRUCT tpstTriggerLevel;
LabelTable_STRUCT tpstLabelTable;
BOOL tpblFilter[CHNO_RMAX];
STCOMMUNICATION tpstComm[CHNO_TMAX];
WORD tpwdMode;
BOOL tpblTimeTag[CHNO_RMAX];
WORD tpwdBInterval[CHNO_TMAX];
WORD tpwdSInterval[CHNO_TMAX];
HWND hwButton_Label[256];
HWND hwStatic_LRName[2][16];

int oldsd;
/////////////////////////////////////////////////////////////////////////////
// CSetUp dialog


CSetUp::CSetUp(CWnd* pParent /*=NULL*/)
	: CDialog(CSetUp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetUp)
	//}}AFX_DATA_INIT
}


void CSetUp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetUp)
	DDX_Control(pDX, IDC_COMBO_SD, m_combo_sd);
	DDX_Control(pDX, IDC_TAB_CONFIGURE, m_tab_configure);
	DDX_Control(pDX, IDC_EDIT_STRIDEP, m_edit_stridep);
	DDX_Control(pDX, IDC_EDIT_STINTERVAL, m_edit_stinterval);
	DDX_Control(pDX, IDC_EDIT_RTRIDEP, m_edit_rtridep);
	DDX_Control(pDX, IDC_EDIT_BTINTERVAL, m_edit_btinterval);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_combo_parity);
	DDX_Control(pDX, IDC_COMBO_BRATE, m_combo_brate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetUp, CDialog)
	//{{AFX_MSG_MAP(CSetUp)
	ON_BN_CLICKED(IDC_BUTTON_LOADCONF, OnButtonLoadconf)
	ON_BN_CLICKED(IDC_BUTTON_SAVECONF, OnButtonSaveconf)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONFIGURE, OnSelchangeTabConfigure)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_CONFIGURE, OnSelchangingTabConfigure)
	ON_EN_CHANGE(IDC_EDIT_BTINTERVAL, OnChangeEditBtinterval)
	ON_EN_CHANGE(IDC_EDIT_RTRIDEP, OnChangeEditRtridep)
	ON_EN_CHANGE(IDC_EDIT_STINTERVAL, OnChangeEditStinterval)
	ON_EN_CHANGE(IDC_EDIT_STRIDEP, OnChangeEditStridep)
	ON_WM_CREATE()
	ON_EN_KILLFOCUS(IDC_EDIT_BTINTERVAL, OnKillfocusEditBtinterval)
	ON_EN_KILLFOCUS(IDC_EDIT_RTRIDEP, OnKillfocusEditRtridep)
	ON_EN_KILLFOCUS(IDC_EDIT_STINTERVAL, OnKillfocusEditStinterval)
	ON_EN_KILLFOCUS(IDC_EDIT_STRIDEP, OnKillfocusEditStridep)
	ON_CBN_SELCHANGE(IDC_COMBO_SD, OnSelchangeComboSd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetUp message handlers
int CSetUp::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	int i=0, j=0;
	char c[80];

	//  Create Label filter Windows

	// static labels
	for (i=0; i<16; i++)
	{
		// X
		hwStatic_LRName[0][i] = ::CreateWindow("STATIC", NULL,
									SS_CENTER | WS_CHILD,
									LABELDLG_BASE_XL + i*LABELDLG_BASE_WIDTHL,
									93,
									LABELDLG_BASE_WIDTHL,
									LABELDLG_BASE_HEIGHL,
									this->m_hWnd,
									NULL,
									0,
									0);
		::ShowWindow(hwStatic_LRName[0][i], SW_SHOW);
		::UpdateWindow(hwStatic_LRName[0][i]);
		itoa(i, c, 16);
		::SetWindowText(hwStatic_LRName[0][i], c);
		//Y
		hwStatic_LRName[1][i] = ::CreateWindow("STATIC", NULL, 
									SS_CENTER | WS_CHILD,
									LABELDLG_BASE,
									LABELDLG_BASE_YL + i*LABELDLG_BASE_HEIGHL,
									LABELDLG_BASE_WIDTHL,
									LABELDLG_BASE_HEIGHL,
									this->m_hWnd,
									NULL,
									0,
									0);
		::ShowWindow(hwStatic_LRName[1][i], SW_SHOW);
		::UpdateWindow(hwStatic_LRName[1][i]);
		itoa(i, c, 16);
		::SetWindowText(hwStatic_LRName[1][i], c);
	}
	// check button
	for (i=0; i<16; i++)
	{
		for (j=0; j<16; j++)
		{
			hwButton_Label[i*16+j] = ::CreateWindow("BUTTON", NULL, 
									BS_AUTOCHECKBOX | WS_CHILD,
									LABELDLG_BASE_XB + j*LABELDLG_BASE_WIDTHB,
									LABELDLG_BASE_YB + i*LABELDLG_BASE_HEIGHB,
									LABELDLG_BASE_WIDTHB,
									LABELDLG_BASE_HEIGHB,
									this->m_hWnd,
									NULL,
									0,
									0);
			::ShowWindow(hwButton_Label[i*16+j], SW_SHOW);
			::UpdateWindow(hwButton_Label[i*16+j]);
		}
	}
			
	return 0;
}

BOOL CSetUp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//init variables
	tpstTriggerLevel=stTriggerLevel;
	tpstLabelTable = stLabelTable;
	tpwdMode = wdMode;

	for (int i=0; i<CHNO_RMAX; i++)
	{
		tpblFilter[i] = blFilter[i];
		tpblTimeTag[i] = blTimeTag[i];
	}
	for (i=0; i<CHNO_TMAX; i++)
	{
		tpstComm[i] = stComm[i];
		tpwdBInterval[i] = wdBInterval[i];
		tpwdSInterval[i] = wdSInterval[i];
	}
	
	//  init edit control
	//
	this->m_edit_rtridep.LimitText(3);
	this->m_edit_stridep.LimitText(3);
	this->m_edit_btinterval.LimitText(5);
	this->m_edit_stinterval.LimitText(5);

	//	init tab control
	//
	this->m_tab_configure.InsertItem(0, "配置 [1]");
	this->m_tab_configure.InsertItem(1, "配置 [2]");
	this->m_tab_configure.InsertItem(2, "配置 [3]");
	this->m_tab_configure.InsertItem(3, "配置 [4]");
	this->m_tab_configure.SetCurSel(0);

	//  Init bits rate & parity combo box
	//
	this->m_combo_brate.ResetContent();
	this->m_combo_brate.AddString(TEXT("100"));
	this->m_combo_brate.AddString(TEXT("48"));
	this->m_combo_brate.AddString(TEXT("12.5"));
	this->m_combo_parity.ResetContent();
	this->m_combo_parity.AddString(TEXT("奇校验"));
	this->m_combo_parity.AddString(TEXT("偶校验"));
	this->m_combo_parity.AddString(TEXT("无"));

	//  Init SD selection combo box
	//
	this->m_combo_sd.ResetContent();
	this->m_combo_sd.AddString(TEXT("0"));
	this->m_combo_sd.AddString(TEXT("1"));
	this->m_combo_sd.AddString(TEXT("2"));
	this->m_combo_sd.AddString(TEXT("3"));
	this->m_combo_sd.SetCurSel(0);
	oldsd = 0;

	this->ResumeConfig(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetUp::ResumeConfig(int idx)
{
	// TODO: resume configuration
	int i=idx;
	char c[80];
	int j=0, sd=0;
	
	//  bps
	//
	this->m_combo_brate.SetCurSel(tpstComm[i/2].iSelBR);

	//  parity
	//
	this->m_combo_parity.SetCurSel(tpstComm[i/2].iSelParity);

	//  Tx Interval
	//
	sprintf(c, "%ld", tpwdBInterval[i/2]);
	this->m_edit_btinterval.SetWindowText(c);
	sprintf(c, "%ld", tpwdSInterval[i/2]);
	this->m_edit_stinterval.SetWindowText(c);

	//  Time Tag
	//
	if (tpblTimeTag[i])
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TIMETAG), BST_CHECKED); //this->m_check_timetag.SetCheck(1); // need Time Tag
	}
	else
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TIMETAG), BST_UNCHECKED); //this->m_check_timetag.SetCheck(0); // don't need Time Tag
	}
	
	//  Rx Trigger Level
	//
	switch (i)
	{
		case 0:
			itoa(tpstTriggerLevel.Chan0Depth_I, c, 10);
			break;
		case 1:
			itoa(tpstTriggerLevel.Chan1Depth_I, c, 10);
			break;
		case 2:
			itoa(tpstTriggerLevel.Chan2Depth_I, c, 10);
			break;
		case 3:
			itoa(tpstTriggerLevel.Chan3Depth_I, c, 10);
			break;
	}
	this->m_edit_rtridep.SetWindowText(c);

	//  Tx Trigger Level
	//
	switch (i/2)
	{
		case 0:
			itoa(tpstTriggerLevel.Chan0Depth_O, c, 10);
			break;
		case 1:
			itoa(tpstTriggerLevel.Chan1Depth_O, c, 10);
			break;
	}
	this->m_edit_stridep.SetWindowText(c);
	
	//  Label Filter
	//
	if (tpblFilter[i])
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_ENLABLEFIL), BST_CHECKED);//this->m_check_enlabelfil.SetCheck(1); // need label filter
	}
	else
	{
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_ENLABLEFIL), BST_UNCHECKED); // don't need label filter
	}

	sd = this->m_combo_sd.GetCurSel(); // get SD num

	for (j=0; j<LABEL_MAX; j++) // save label table with SD num
	{
		switch (i)
		{
			case 0:
				if (tpstLabelTable.LabFilterChan0[sd][j] == 1)
				{
					Button_SetCheck(hwButton_Label[j], BST_CHECKED);
				}
				else
				{
					Button_SetCheck(hwButton_Label[j], BST_UNCHECKED);
				}
				break;
			case 1:
				if (tpstLabelTable.LabFilterChan1[sd][j] == 1)
				{
					Button_SetCheck(hwButton_Label[j], BST_CHECKED);
				}
				else
				{
					Button_SetCheck(hwButton_Label[j], BST_UNCHECKED);
				}
				break;
			case 2:
				if (tpstLabelTable.LabFilterChan2[sd][j] == 1)
				{
					Button_SetCheck(hwButton_Label[j], BST_CHECKED);
				}
				else
				{
					Button_SetCheck(hwButton_Label[j], BST_UNCHECKED);
				}
				break;
			case 3:
				if (tpstLabelTable.LabFilterChan3[sd][j] == 1)
				{
					Button_SetCheck(hwButton_Label[j], BST_CHECKED);
				}
				else
				{
					Button_SetCheck(hwButton_Label[j], BST_UNCHECKED);
				}
				break;
		} // end of switch
	} // end of for (...
	
	//  Work Mode
	//
	if (tpwdMode == C429_NORMAL)
	{ // normal mode
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_SELFLOOP), BST_UNCHECKED); // selftest radio
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_NORMAL), BST_CHECKED); // normal radio
	}
	else
	{ // selftest mode
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_SELFLOOP), BST_CHECKED); // selftest radio
		Button_SetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_NORMAL), BST_UNCHECKED); // normal radio
	}
}

void CSetUp::StoreConfig(int idx)
{
	// TODO: save configuration
	int i=idx;
	char c[80];
	int j=0, sd=0;
	
	//  bps
	//
	tpstComm[i/2].iSelBR = this->m_combo_brate.GetCurSel();

	//  parity
	//
	tpstComm[i/2].iSelParity = this->m_combo_parity.GetCurSel();

	//  Tx Interval
	//
	this->m_edit_btinterval.GetWindowText(c, sizeof(c));
	tpwdBInterval[i/2] = (WORD) atoi(c);
	this->m_edit_stinterval.GetWindowText(c, sizeof(c));
	tpwdSInterval[i/2] = (WORD) atoi(c);	
	//  Time Tag
	//
	if (Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_TIMETAG))== BST_UNCHECKED)
	{
		tpblTimeTag[i] = FALSE; // don't need Time Tag
	}
	else
	{
		tpblTimeTag[i] = TRUE; // need Time Tag
	}
	
	//  Rx Trigger Level
	//
	this->m_edit_rtridep.GetWindowText(c, sizeof(c));
	switch (i)
	{
		case 0:
			tpstTriggerLevel.Chan0Depth_I = (BYTE) atoi(c);
			break;
		case 1:
			tpstTriggerLevel.Chan1Depth_I = (BYTE) atoi(c);
			break;
		case 2:
			tpstTriggerLevel.Chan2Depth_I = (BYTE) atoi(c);
			break;
		case 3:
			tpstTriggerLevel.Chan3Depth_I = (BYTE) atoi(c);
			break;
	}

	//  Tx Trigger Level
	//
	this->m_edit_stridep.GetWindowText(c, sizeof(c));
	switch (i/2)
	{
		case 0:
			tpstTriggerLevel.Chan0Depth_O = (BYTE) atoi(c);
			break;
		case 1:
			tpstTriggerLevel.Chan1Depth_O = (BYTE) atoi(c);
			break;
	}
	
	//  Label Filter
	//
	if (Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_CHECK_ENLABLEFIL)) == BST_UNCHECKED) // check Label switch
	{
		tpblFilter[i] = FALSE; // don't need label filter
	}
	else
	{
		tpblFilter[i] = TRUE; // need label filter
	}

	sd = this->m_combo_sd.GetCurSel(); // get SD num

	for (j=0; j<LABEL_MAX; j++) // save label table with SD num
	{
		if (Button_GetCheck(hwButton_Label[j]) == BST_CHECKED)
		{
			switch (i)
			{
				case 0:
					tpstLabelTable.LabFilterChan0[sd][j] = 1;
					break;
				case 1:
					tpstLabelTable.LabFilterChan1[sd][j] = 1;
					break;
				case 2:
					tpstLabelTable.LabFilterChan2[sd][j] = 1;
					break;
				case 3:
					tpstLabelTable.LabFilterChan3[sd][j] = 1;
					break;
			}
		}
		else
		{
			switch (i)
			{
				case 0:
					tpstLabelTable.LabFilterChan0[sd][j] = 0;
					break;
				case 1:
					tpstLabelTable.LabFilterChan1[sd][j] = 0;
					break;
				case 2:
					tpstLabelTable.LabFilterChan2[sd][j] = 0;
					break;
				case 3:
					tpstLabelTable.LabFilterChan3[sd][j] = 0;
					break;
			}
		} // end of if (...
	} // end of for (...
	
	//  Work Mode
	//
	if (Button_GetCheck(::GetDlgItem(this->m_hWnd, IDC_RADIO_SELFLOOP))==BST_UNCHECKED) // check selftest mode button
	{
		tpwdMode = C429_NORMAL; // work on normal mode
	}
	else
	{
		tpwdMode = C429_SELFTEST; // work on selftest mode
	}
}
void CSetUp::OnButtonLoadconf() 
{
	// TODO: Add your control notification handler code here
	// TODO: load configuring file
	char path[MAX_PATH];
	int i=0;
	char section[80];

	//  Load configuration from fym429cfg.ini
	//
	memset(path, 0, sizeof(path));
	if (::GetCurrentDirectory(sizeof(path), path)==0)
	{
		return;
	}
	strcat(path, "\\fym429cfg.ini");

	//  workmode
	//
	tpwdMode = GetPrivateProfileInt("WM", "workmode", wdMode, path);

	//  label table
	//
	GetPrivateProfileStruct("LT", "LabelTable", &tpstLabelTable, sizeof(LabelTable_STRUCT), path);

	//  load Rx configuration
	//
	for (i=0; i<CHNO_RMAX; i++)
	{
		memset(section, 0, sizeof(section));
		sprintf(section, "RxCONFIG_%d", i);

		switch (i) // Rx trigger level
		{
			case 0:
				tpstTriggerLevel.Chan0Depth_I = GetPrivateProfileInt(section, "RxTL", stTriggerLevel.Chan0Depth_I, path);
				break;
			case 1:
				tpstTriggerLevel.Chan1Depth_I = GetPrivateProfileInt(section, "RxTL", stTriggerLevel.Chan1Depth_I, path);
				break;
			case 2:
				tpstTriggerLevel.Chan2Depth_I = GetPrivateProfileInt(section, "RxTL", stTriggerLevel.Chan2Depth_I, path);
				break;
			case 3:
				tpstTriggerLevel.Chan3Depth_I = GetPrivateProfileInt(section, "RxTL", stTriggerLevel.Chan3Depth_I, path);
				break;
		}

		tpblTimeTag[i] = GetPrivateProfileInt(section, "TimeTag", blTimeTag[i], path); // time tag

		tpblFilter[i] = GetPrivateProfileInt(section, "LabelTableEN", blFilter[i], path); // Enable label table
	} // end of for (i=0; i<CHNO_RMAX; i++)...

	//  load Tx configuration
	//
	for (i=0; i<CHNO_TMAX; i++)
	{
		memset(section, 0, sizeof(section));
		sprintf(section, "TxCONFIG_%d", i);

		tpstComm[i].iSelBR = GetPrivateProfileInt(section, "bps", stComm[i].iSelBR, path); // bps

		tpstComm[i].iSelParity = GetPrivateProfileInt(section, "parity", stComm[i].iSelParity, path); // parity

		switch (i) // Tx trigger level
		{
			case 0:
				tpstTriggerLevel.Chan0Depth_O = GetPrivateProfileInt(section, "TxTL", stTriggerLevel.Chan0Depth_O, path);
				break;
			case 1:
				tpstTriggerLevel.Chan1Depth_O = GetPrivateProfileInt(section, "TxTL", stTriggerLevel.Chan1Depth_O, path);
				break;
		}

		tpwdBInterval[i] = GetPrivateProfileInt(section, "BInterval", wdBInterval[i], path); // BInterval
		tpwdSInterval[i] = GetPrivateProfileInt(section, "SInterval", wdSInterval[i], path); // SInterval
	} // end of for (i=0; i<CHNO_TMAX; i++)

	i = this->m_tab_configure.GetCurSel();
	this->ResumeConfig(i);	
}

void CSetUp::OnButtonSaveconf() 
{
	// TODO: Add your control notification handler code here
	char path[MAX_PATH];
	int i=0;
	char c[80];
	char section[80];
	BOOL status=FALSE;

	//  Load configuration from fym429cfg.ini
	//
	memset(path, 0, sizeof(path));
	if (::GetCurrentDirectory(sizeof(path), path)==0)
	{
		return;
	}
	strcat(path, "\\fym429cfg.ini");

	i = this->m_tab_configure.GetCurSel();
	this->StoreConfig(i);

	//  workmode
	//
	memset(c, 0, sizeof(c));
	itoa(tpwdMode, c, 10);
	status = WritePrivateProfileString("WM", "workmode", c, path); // work mode
	if (!status)
	{
		return;
	}

	//  label table
	//
	status = WritePrivateProfileStruct("LT", "LabelTable", &tpstLabelTable, sizeof(LabelTable_STRUCT), path);
	if (!status)
	{
		return;
	}

	//  save Rx configuration
	//
	for (i=0; i<CHNO_RMAX; i++)
	{
		memset(section, 0, sizeof(section));
		sprintf(section, "RxCONFIG_%d", i);

		memset(c, 0, sizeof(c));
		switch (i)
		{
			case 0:
				itoa(tpstTriggerLevel.Chan0Depth_I, c, 10);
				break;
			case 1:
				itoa(tpstTriggerLevel.Chan1Depth_I, c, 10);
				break;
			case 2:
				itoa(tpstTriggerLevel.Chan2Depth_I, c, 10);
				break;
			case 3:
				itoa(tpstTriggerLevel.Chan3Depth_I, c, 10);
				break;
		}
		status = WritePrivateProfileString(section, "RxTL", c, path); // Rx trigger level
		if (!status)
		{
			return;
		}

		memset(c, 0, sizeof(c));
		itoa(tpblTimeTag[i], c, 10);
		status = WritePrivateProfileString(section, "TimeTag", c, path); // time tag
		if (!status)
		{
			return;
		}

		memset(c, 0, sizeof(c));
		itoa(tpblFilter[i], c, 10);
		status = WritePrivateProfileString(section, "LabelTableEN", c, path); // Enable label table
		if (!status)
		{
			return;
		}
	} // end of for (i=0; i<CHNO_RMAX; i++)...

	//  save Tx configuration
	//
	for (i=0; i<CHNO_TMAX; i++)
	{
		memset(section, 0, sizeof(section));
		sprintf(section, "TxCONFIG_%d", i);

		memset(c, 0, sizeof(c));
		itoa(tpstComm[i].iSelBR, c, 10);
		status = WritePrivateProfileString(section, "bps", c, path); // bps
		if (!status)
		{
			return;
		}

		memset(c, 0, sizeof(c));
		itoa(tpstComm[i].iSelParity, c, 10);
		status = WritePrivateProfileString(section, "parity", c, path); // parity
		if (!status)
		{
			return;
		}

		memset(c, 0, sizeof(c));
		switch (i)
		{
			case 0:
				itoa(tpstTriggerLevel.Chan0Depth_O, c, 10);
				break;
			case 1:
				itoa(tpstTriggerLevel.Chan1Depth_O, c, 10);
				break;
		}
		status = WritePrivateProfileString(section, "TxTL", c, path); // Tx trigger level
		if (!status)
		{
			return;
		}

		memset(c, 0, sizeof(c));
		itoa(tpwdBInterval[i], c, 10);
		status = WritePrivateProfileString(section, "BInterval", c, path); // BInterval
		if (!status)
		{
			return;
		}
		memset(c, 0, sizeof(c));
		itoa(tpwdSInterval[i], c, 10);
		status = WritePrivateProfileString(section, "SInterval", c, path); // SInterval
		if (!status)
		{
			return;
		}
	} // end of for (i=0; i<CHNO_TMAX; i++)	
}

void CSetUp::OnSelchangeTabConfigure(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i=0;

	i = this->m_tab_configure.GetCurSel();
	this->ResumeConfig(i);
	
	*pResult = 0;
}

void CSetUp::OnSelchangingTabConfigure(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i=0;

	i = this->m_tab_configure.GetCurSel();
	this->StoreConfig(i);
	
	*pResult = 0;
}

void CSetUp::OnChangeEditBtinterval() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80];
	int i=0;

	this->m_edit_btinterval.GetWindowText(c, sizeof(c));

	i = atoi(c);

	if (i>INTERVAL_MAX)
	{
		MessageBox(TEXT("输入值超出范围!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		itoa(INTERVAL_MAX, c, 10);
		this->m_edit_btinterval.SetWindowText(c);
		this->m_edit_btinterval.SetSel(this->m_edit_btinterval.LineLength(-1), this->m_edit_btinterval.LineLength(-1), FALSE);
		this->m_edit_btinterval.SetFocus();
	}	
}

void CSetUp::OnChangeEditRtridep() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80];
	int i=0;

	this->m_edit_rtridep.GetWindowText(c, sizeof(c));

	i = atoi(c);

	if (i>TRIGGER_RMAX)
	{
		MessageBox(TEXT("输入值超出范围!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		itoa(TRIGGER_RMAX, c, 10);
		this->m_edit_rtridep.SetWindowText(c);
		this->m_edit_rtridep.SetSel(this->m_edit_rtridep.LineLength(-1), this->m_edit_rtridep.LineLength(-1), FALSE);
		this->m_edit_rtridep.SetFocus();
	}	
}

void CSetUp::OnChangeEditStinterval() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80];
	int i=0;

	this->m_edit_stinterval.GetWindowText(c, sizeof(c));

	i = atoi(c);

	if (i>INTERVAL_MAX)
	{
		MessageBox(TEXT("输入值超出范围!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		itoa(INTERVAL_MAX, c, 10);
		this->m_edit_stinterval.SetWindowText(c);
		this->m_edit_stinterval.SetSel(this->m_edit_stinterval.LineLength(-1), this->m_edit_stinterval.LineLength(-1), FALSE);
		this->m_edit_stinterval.SetFocus();
	}	
}

void CSetUp::OnChangeEditStridep() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80];
	int i=0;

	this->m_edit_stridep.GetWindowText(c, sizeof(c));

	i = atoi(c);

	if (i>TRIGGER_TMAX)
	{
		MessageBox(TEXT("输入值超出范围!"), TEXT("警告"), MB_OK | MB_ICONWARNING);
		itoa(TRIGGER_TMAX, c, 10);
		this->m_edit_stridep.SetWindowText(c);
		this->m_edit_stridep.SetSel(this->m_edit_stridep.LineLength(-1), this->m_edit_stridep.LineLength(-1), FALSE);
		this->m_edit_stridep.SetFocus();
	}	
}

void CSetUp::OnKillfocusEditBtinterval() 
{
	// TODO: Add your control notification handler code here
	if (this->m_edit_btinterval.LineLength(-1)==0)
	{
		this->m_edit_btinterval.SetWindowText(TEXT("0"));
	}	
}

void CSetUp::OnKillfocusEditRtridep() 
{
	// TODO: Add your control notification handler code here
	if (this->m_edit_rtridep.LineLength(-1)==0)
	{
		this->m_edit_rtridep.SetWindowText(TEXT("0"));
	}	
}

void CSetUp::OnKillfocusEditStinterval() 
{
	// TODO: Add your control notification handler code here
	if (this->m_edit_stinterval.LineLength(-1)==0)
	{
		this->m_edit_stinterval.SetWindowText(TEXT("0"));
	}	
}

void CSetUp::OnKillfocusEditStridep() 
{
	// TODO: Add your control notification handler code here
	if (this->m_edit_stridep.LineLength(-1)==0)
	{
		this->m_edit_stridep.SetWindowText(TEXT("0"));
	}	
}

void CSetUp::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CSetUp::OnOK() 
{
	// TODO: Add extra validation here
	int i=0;
	WORD wd=0;
	BOOL needTT=FALSE;

	i = this->m_tab_configure.GetCurSel();
	this->StoreConfig(i);

	//  save variables
	//
	stTriggerLevel = tpstTriggerLevel;
	stLabelTable = tpstLabelTable;
	wdMode = tpwdMode;
	for (i=0; i<CHNO_RMAX; i++)
	{
		blFilter[i] = tpblFilter[i];
		blTimeTag[i] = tpblTimeTag[i];
	}
	for (i=0; i<CHNO_TMAX; i++)
	{
		stComm[i] = tpstComm[i];
		wdBInterval[i] = tpwdBInterval[i];
		wdSInterval[i] = tpwdSInterval[i];
	}

	#ifndef CARD_DEBUG
	//	Try to Open card and setting up the card with default configuration
	//
	
	//  0. check card's handle
	//
	if (hCard==NULL)
	{
		MessageBox(TEXT("程序找不到板卡, 无法完成设置操作!\n\n(板卡句柄获取失败)"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return; // quit program
	}

	//  1. reset card
	//
	if (!ResetCard(hCard)) // reset Card
	{
		MessageBox(TEXT("复位板卡失败,无法完成设置操作!\n\n(ResetCard函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
		if (!Card_Close(hCard))
		{
			MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
		}
		return; // quit program
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
			MessageBox(TEXT("配置硬件出错,无法完成设置操作!\n\n(SetConfigureWord函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
			if (!Card_Close(hCard))
			{
				MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
			}
			return; // quit program
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
				MessageBox(TEXT("添加标号过滤功能出错,无法完成设置操作!\n\n(StartLabelFilter函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				if (!Card_Close(hCard))
				{
					MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				}
				return; // quit program
			}
		}
		else
		{
			if (!StartLabelFilter(hCard, (BYTE)(i), FALSE))
			{
				MessageBox(TEXT("取消标号过滤功能出错,无法完成设置操作!\n\n(StartLabelFilter函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				if (!Card_Close(hCard))
				{
					MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				}
				return; // quit program
			}
		}
	}

	//  5. configuring Time Tag
	//
	for (i=0; i<CHNO_RMAX; i++)
	{
		if (blTimeTag[i])
		{
			needTT = TRUE;
			if (!AddTimeTag(hCard, (BYTE)(i), TRUE))
			{
				MessageBox(TEXT("添加时间标签功能出错,无法完成设置操作!\n\n(AddTimeTag函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				if (!Card_Close(hCard))
				{
					MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				}
				return; // quit program
			}
		}
		else
		{
			if (!AddTimeTag(hCard, (BYTE)(i), FALSE))
			{
				MessageBox(TEXT("取消时间标签功能出错,无法完成设置操作!\n\n(AddTimeTag函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				if (!Card_Close(hCard))
				{
					MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
				}
				return;
			}
		}
	}
	if (needTT)
	{
		StartTimeTag(hCard, TRUE, &stSysTime); // enable time tag
		if ((stSysTime.wHour + 8) > 24)
		{
			stSysTime.wHour = stSysTime.wHour + 8 - 24;
		}
		else
		{
			stSysTime.wHour = stSysTime.wHour + 8;
		}
		dwTime = stSysTime.wHour*3600000 + stSysTime.wMinute*60000 + stSysTime.wSecond*1000 + stSysTime.wMilliseconds;
	}
	else
	{
		StartTimeTag(hCard, FALSE, &stSysTime); // disable time tag
		dwTime = 0;
	}

	
	//  6. setting up Tx Timer Interval
	//
	for (i=0; i<CHNO_TMAX; i++)
	{
		if (!SetTimerIntervalB(hCard, (BYTE)(i), wdBInterval[i]))
		{
			MessageBox(TEXT("设置群定时发送功能出错,无法完成设置操作!\n\n(SetTimerIntervalB函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
			if (!Card_Close(hCard))
			{
				MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
			}
			return;
		}
		if (!SetTimerIntervalS(hCard, (BYTE)(i), wdSInterval[i]))
		{
			MessageBox(TEXT("设置群定时发送功能出错,无法完成设置操作!\n\n(SetTimerIntervalS函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
			if (!Card_Close(hCard))
			{
				MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
			}
			return;
		}
		if (wdBInterval[i]>0)
		{
			StartTimerB(hCard, (BYTE)(i), TRUE); // enable BTx Timer
		}
		else
		{
			StartTimerB(hCard, (BYTE)(i), FALSE); // disable BTx Timer
		}
		if (wdSInterval[i]>0)
		{
			StartTimerS(hCard, (BYTE)(i), TRUE); // enable STx Timer
		}
		else
		{
			StartTimerS(hCard, (BYTE)(i), FALSE); // disable STx Timer
		}
	}

	if(!Enable_R(hCard,TRUE))//使能接收，在复位板卡时禁止了接收
	{
		MessageBox(TEXT("使能接收失败"), TEXT("错误"), MB_OK | MB_ICONERROR);
	}
#endif
	
	CDialog::OnOK();
}

void CSetUp::OnSelchangeComboSd() 
{
	// TODO: Add your control notification handler code here
	int j=0, i=0, sd=0;

	i = this->m_tab_configure.GetCurSel();

	//  store Label table
	//
	sd = oldsd;
	for (j=0; j<LABEL_MAX; j++) // save label table with SD num
	{
		if (Button_GetCheck(hwButton_Label[j]) == BST_CHECKED)
		{
			switch (i)
			{
				case 0:
					tpstLabelTable.LabFilterChan0[sd][j] = 1;
					break;
				case 1:
					tpstLabelTable.LabFilterChan1[sd][j] = 1;
					break;
				case 2:
					tpstLabelTable.LabFilterChan2[sd][j] = 1;
					break;
				case 3:
					tpstLabelTable.LabFilterChan3[sd][j] = 1;
					break;
			}
		}
		else
		{
			switch (i)
			{
				case 0:
					tpstLabelTable.LabFilterChan0[sd][j] = 0;
					break;
				case 1:
					tpstLabelTable.LabFilterChan1[sd][j] = 0;
					break;
				case 2:
					tpstLabelTable.LabFilterChan2[sd][j] = 0;
					break;
				case 3:
					tpstLabelTable.LabFilterChan3[sd][j] = 0;
					break;
			}
		} // end of if (...
	} // end of for (...

	//  resume Label table
	//
	sd = this->m_combo_sd.GetCurSel();
	for (j=0; j<LABEL_MAX; j++) // save label table with SD num
	{
		switch (i)
		{
			case 0:
				if (tpstLabelTable.LabFilterChan0[sd][j] == 1)
				{
					Button_SetCheck(hwButton_Label[j], BST_CHECKED);
				}
				else
				{
					Button_SetCheck(hwButton_Label[j], BST_UNCHECKED);
				}
				break;
			case 1:
				if (tpstLabelTable.LabFilterChan1[sd][j] == 1)
				{
					Button_SetCheck(hwButton_Label[j], BST_CHECKED);
				}
				else
				{
					Button_SetCheck(hwButton_Label[j], BST_UNCHECKED);
				}
				break;
			case 2:
				if (tpstLabelTable.LabFilterChan2[sd][j] == 1)
				{
					Button_SetCheck(hwButton_Label[j], BST_CHECKED);
				}
				else
				{
					Button_SetCheck(hwButton_Label[j], BST_UNCHECKED);
				}
				break;
			case 3:
				if (tpstLabelTable.LabFilterChan3[sd][j] == 1)
				{
					Button_SetCheck(hwButton_Label[j], BST_CHECKED);
				}
				else
				{
					Button_SetCheck(hwButton_Label[j], BST_UNCHECKED);
				}
				break;
		} // end of switch
	} // end of for (...

	oldsd = sd;	
}
