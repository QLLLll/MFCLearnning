// InOutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "supermarkets.h"
#include "InOutDlg.h"
#include "adoconn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInOutDlg dialog


CInOutDlg::CInOutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInOutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInOutDlg)
	m_goosid = _T("");
	m_num = 0;
	m_supplier = _T("");
	m_value = 0.0f;
	//}}AFX_DATA_INIT
}


void CInOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInOutDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_COMBO1, m_comb);
	DDX_CBString(pDX, IDC_COMBO1, m_goosid);
	DDX_Text(pDX, IDC_NUM, m_num);
	DDX_Text(pDX, IDC_SUPPLIER, m_supplier);
	DDX_Text(pDX, IDC_VALUE, m_value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInOutDlg, CDialog)
	//{{AFX_MSG_MAP(CInOutDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInOutDlg message handlers

BOOL CInOutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_list.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0,"货物编号",LVCFMT_LEFT,101,1);
	m_list.InsertColumn(1,"货物条形码",LVCFMT_LEFT,101,1);
	m_list.InsertColumn(2,"货物名称",LVCFMT_LEFT,101,1);
	m_list.InsertColumn(3,"货物销售价格",LVCFMT_LEFT,101,1);

	
	CString sql;
	int index = 0;
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	sql = "select * from GOODS";
	adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	while(!adoConn.m_pRecordset->adoEOF)
	{
		m_comb.InsertString(index,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsID"));
		adoConn.m_pRecordset->MoveNext();
		index++;
	}
	adoConn.ExitConnect();
	m_comb.SetCurSel(0);
	OnSelchangeCombo1() ;
	if(!m_bIn)
	{
		GetDlgItem(IDC_INFO)->SetWindowText("出库信息：");
		GetDlgItem(IDC_WHO)->SetWindowText("提货商：");
		SetWindowText("出库管理");
	}
	else
	{
		GetDlgItem(IDC_INFO)->SetWindowText("入库信息：");
		GetDlgItem(IDC_WHO)->SetWindowText("供货商：");
		SetWindowText("入库管理");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInOutDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	m_list.DeleteAllItems();
	UpdateData(true);
	CString sql;
	int index = 0;
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	sql.Format("select * from GOODS where GoodsID ='%s'",m_goosid);
	adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	while(!adoConn.m_pRecordset->adoEOF)
	{
		m_list.InsertItem(index,"");
		m_list.SetItemText(index,0,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsID"));
		m_list.SetItemText(index,1,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsBarCode"));
		m_list.SetItemText(index,2,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsName"));
		m_list.SetItemText(index,3,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsValue"));
		adoConn.m_pRecordset->MoveNext();
		index++;
	}
	adoConn.ExitConnect();
}
