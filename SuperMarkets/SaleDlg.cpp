// SaleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperMarkets.h"
#include "SaleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaleDlg dialog


CSaleDlg::CSaleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaleDlg)
	m_goods = _T("");
	m_num = 0;
	//}}AFX_DATA_INIT
}


void CSaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaleDlg)
	DDX_Control(pDX, IDC_COMTYPE, m_type);
	DDX_Text(pDX, IDC_GOODS, m_goods);
	DDX_Text(pDX, IDC_NUM, m_num);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaleDlg, CDialog)
	//{{AFX_MSG_MAP(CSaleDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaleDlg message handlers

BOOL CSaleDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_type.InsertString(0,"商品编号");
	m_type.InsertString(1,"商品条形码");
	m_type.SetCurSel(m_uType);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
