// NewUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "supermarkets.h"
#include "NewUserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewUserDlg dialog


CNewUserDlg::CNewUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewUserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewUserDlg)
	m_adress = _T("");
	m_id = _T("");
	m_male = -1;
	m_name = _T("");
	m_phone = _T("");
	m_position = _T("");
	m_pwd = _T("");
	m_workerid = _T("");
	//}}AFX_DATA_INIT
}


void CNewUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewUserDlg)
	DDX_Control(pDX, IDC_COMBO1, m_comb);
	DDX_Text(pDX, IDC_ADDRESS, m_adress);
	DDX_Text(pDX, IDC_ID, m_id);
	DDX_Radio(pDX, IDC_MALE, m_male);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_PHONE, m_phone);
	DDX_Text(pDX, IDC_POSITION, m_position);
	DDX_Text(pDX, IDC_PWD, m_pwd);
	DDX_Text(pDX, IDC_WORKID, m_workerid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewUserDlg, CDialog)
	//{{AFX_MSG_MAP(CNewUserDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewUserDlg message handlers

BOOL CNewUserDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comb.InsertString(0,"1");
	m_comb.InsertString(1,"2");
	m_comb.InsertString(2,"3");
	m_comb.InsertString(3,"4");
	m_comb.InsertString(4,"5");
	m_comb.SetCurSel(m_Permissions - 1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CNewUserDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	m_Permissions = m_comb.GetCurSel() + 1;
}
