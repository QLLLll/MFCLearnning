// SettlementDlg.cpp : implementation file
//

#include "stdafx.h"
#include "supermarkets.h"
#include "SettlementDlg.h"
#include "adoconn.h"
#include "userdlg.h"
#include "StorageDlg.h"
#include "Ticketdlg.h"
#include "Goodsdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettlementDlg dialog


CSettlementDlg::CSettlementDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettlementDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettlementDlg)
	m_opType = _T("");
	m_info = 0;
	//}}AFX_DATA_INIT

	m_checkTime = CTime::GetCurrentTime();
}


void CSettlementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettlementDlg)
	DDX_Control(pDX, IDC_COMBO1, m_comb);
	DDX_Control(pDX, IDC_LIST2, m_countList);
	DDX_Control(pDX, IDC_LIST1, m_checkList);
	DDX_CBString(pDX, IDC_COMBO1, m_opType);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_checkTime);
	DDX_Text(pDX, IDC_INFO, m_info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettlementDlg, CDialog)
	//{{AFX_MSG_MAP(CSettlementDlg)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_BN_CLICKED(IDC_COUNT, OnCount)
	ON_COMMAND(IDUM_USER,OnUser)
	ON_COMMAND(IDUM_STORAGE,OnStorage)
	ON_COMMAND(IDUM_TICKET,OnTicket)
	ON_COMMAND(IDUM_GOODS,OnNGoods)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettlementDlg message handlers

BOOL CSettlementDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// TODO: Add extra initialization here
	m_ImageList.Create(32,32,ILC_COLOR24|ILC_MASK,1,1);
	//向图像列表中添加图标
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_USER));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_STORAGE));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_SALE));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_GOODS));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_COUNT));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_EXIT));
	
	UINT array[8];
	for(int i=0;i<7;i++)
	{
		if(i==4 || i==6)
			array[i] = ID_SEPARATOR; //第3、6个按钮为分隔条
		else
			array[i] = i+IDUM_USER;
	}
	array[7] = IDOK;
	m_ToolBar.Create(this);
	m_ToolBar.SetButtons(array,8);
	//关联图像列表
	m_ToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);
	m_ToolBar.SetSizes(CSize(50,60),CSize(32,32)); //设置按钮和图标的大小
	//设置工具栏按钮的显示文本
	m_ToolBar.SetButtonText(0,"员工管理");
	m_ToolBar.SetButtonText(1,"仓库管理");
	m_ToolBar.SetButtonText(2,"票务管理");
	m_ToolBar.SetButtonText(3,"商品管理");
	m_ToolBar.SetButtonText(5,"营业统计");
	m_ToolBar.SetButtonText(7,"退出系统");
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);



	m_checkList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_checkList.InsertColumn(0,"商品编号",LVCFMT_LEFT,120,1);
	m_checkList.InsertColumn(1,"商品名称",LVCFMT_LEFT,120,4);
	m_checkList.InsertColumn(2,"销售数量",LVCFMT_LEFT,107,6);   
	m_checkList.InsertColumn(3,"销售单价",LVCFMT_LEFT,110,5);
	m_checkList.InsertColumn(4,"成本单价",LVCFMT_LEFT,110,5);

	m_countList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_countList.InsertColumn(0,"销售总数量",LVCFMT_LEFT,120,1);
	m_countList.InsertColumn(1,"商品总成本",LVCFMT_LEFT,120,4);
	m_countList.InsertColumn(2,"日销售额",LVCFMT_LEFT,107,6);   
	m_countList.InsertColumn(3,"日利润",LVCFMT_LEFT,110,5);

	m_comb.InsertString(0,"  >  ");
	m_comb.InsertString(1,"  >= ");
	m_comb.InsertString(2,"  =  ");
	m_comb.InsertString(3,"  <= ");
	m_comb.InsertString(4,"  <  ");
	m_comb.SetCurSel(2);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettlementDlg::OnSelect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_checkList.DeleteAllItems();
	CString sql,sql1,sql2;
	int index = 0;
	sql.Format("select * from TICKET where SaleDate = #%s# and SaleNum %s %d",m_checkTime.Format("%Y-%m-%d"),m_opType,m_info);
	ADOConn adoConn,adoConn1,adoConn2;
	adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	while(!adoConn.m_pRecordset->adoEOF)
	{
		m_checkList.InsertItem(index,"");
		m_checkList.SetItemText(index,0,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsID"));
		m_checkList.SetItemText(index,1,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsName"));
		adoConn1.OnInitADOConn();
		m_checkList.SetItemText(index,2,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("SaleNum"));
		m_checkList.SetItemText(index,3,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsValue"));
		adoConn.m_pRecordset->MoveNext();
		index++;
	}

	for(int i = 0; i < m_checkList.GetItemCount(); i++)
	{
		sql1.Format("select * from STORAGEINFO where GoodsID = '%s' AND InOrOut=%d",m_checkList.GetItemText(i,0),~0);
		adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql1);
		m_checkList.SetItemText(i,4,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsValue"));	
	}
	adoConn.ExitConnect();
}

void CSettlementDlg::OnCount() 
{
	// TODO: Add your control notification handler code here
	m_countList.DeleteAllItems();
	m_checkList.DeleteAllItems();
	m_opType = ">";
	m_info = 0;
	UpdateData(true);
	OnSelect();
	int num = 0 ;
	float turnover = 0,cost = 0,netprofits = 0;
	for(int i = 0; i < m_checkList.GetItemCount(); i++)
	{
		float temp1 = atof(m_checkList.GetItemText(i,2));
		float temp2 = atof(m_checkList.GetItemText(i,3));
		float temp3 = atof(m_checkList.GetItemText(i,4));
		
		num += temp1;
		turnover += temp1*temp2;
		cost += temp1*temp3;
		netprofits += temp1*(temp2 - temp3);
	}
	CString str;
	m_countList.InsertItem(0,"");
	str.Format("%d",num);
	m_countList.SetItemText(0,0,str);
	str.Format("%.2f",cost);
	m_countList.SetItemText(0,1,str);
	str.Format("%.2f",turnover);
	m_countList.SetItemText(0,2,str);
	str.Format("%.2f",netprofits);
	m_countList.SetItemText(0,3,str);
}
void CSettlementDlg::OnUser()
{
	if(m_WorkType != 5 && m_WorkType  < 6)
	{
		MessageBox("您没有权限访问这个模块");
		return;
	}
	OnOK();
	CUserDlg dlg;
	dlg.m_WorkType = m_WorkType;
	dlg.DoModal();
}

void CSettlementDlg::OnStorage()
{
	if(m_WorkType != 4 && m_WorkType  < 6)
	{
		MessageBox("您没有权限访问这个模块");
		return;
	}
	OnOK();
	CStorageDlg dlg;
	dlg.m_WorkType = m_WorkType;
	dlg.DoModal();
	
}

void CSettlementDlg::OnTicket()
{
	if(m_WorkType != 3 && m_WorkType  < 6)
	{
		MessageBox("您没有权限访问这个模块");
		return;
	}
	OnOK();
	CTicketDlg dlg;
	dlg.m_WorkType = m_WorkType;
	dlg.DoModal();
}

void CSettlementDlg::OnNGoods()
{
	if(m_WorkType != 2 && m_WorkType  < 6)
	{
		MessageBox("您没有权限访问这个模块");
		return;
	}
	OnOK();
	CGoodsDlg dlg;
	dlg.m_WorkType = m_WorkType;
	dlg.DoModal();
}

