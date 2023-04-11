// CardSel.cpp : implementation file
//

#include "stdafx.h"
#include "APP429.h"
#include "CardSel.h"
#include "DLL429D42_lib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BYTE btCardId;
/////////////////////////////////////////////////////////////////////////////
// CCardSel dialog


CCardSel::CCardSel(CWnd* pParent /*=NULL*/)
	: CDialog(CCardSel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCardSel)
	//}}AFX_DATA_INIT
}


void CCardSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCardSel)
	DDX_Control(pDX, IDC_EDIT_CARDSEL, m_edit_cardsel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCardSel, CDialog)
	//{{AFX_MSG_MAP(CCardSel)
	ON_EN_CHANGE(IDC_EDIT_CARDSEL, OnChangeEditCardsel)
	ON_EN_KILLFOCUS(IDC_EDIT_CARDSEL, OnKillfocusEditCardsel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCardSel message handlers
BOOL CCardSel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char c[80];
	this->m_edit_cardsel.LimitText(3);
	itoa(btCardId,c,10);
	this->m_edit_cardsel.SetWindowText(c);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCardSel::OnOK() 
{
	// TODO: Add extra validation here
	char c[80];
	this->m_edit_cardsel.GetWindowText(c,sizeof(c));
	btCardId=(BYTE)atoi(c);

	CDialog::OnOK();
}

void CCardSel::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}



void CCardSel::OnChangeEditCardsel() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char c[80];
	int i=0;

	this->m_edit_cardsel.GetWindowText(c,sizeof(c));
	i=(BYTE)atoi(c);

	if(i>CARDID_MAX)
	{
		MessageBox(TEXT("输入值超出范围!"),TEXT("警告"),MB_OK|MB_ICONWARNING);
		itoa(CARDID_MAX,c,10);
		m_edit_cardsel.SetWindowText(TEXT(c));
		m_edit_cardsel.SetSel(this->m_edit_cardsel.LineLength(-1),this->m_edit_cardsel.LineLength(-1),FALSE);//???
		m_edit_cardsel.SetFocus();
	}	
}

void CCardSel::OnKillfocusEditCardsel() 
{
	// TODO: Add your control notification handler code here
	if(this->m_edit_cardsel.LineLength(-1)==0)
	{
		this->m_edit_cardsel.SetWindowText(TEXT("0"));
	}	
}
