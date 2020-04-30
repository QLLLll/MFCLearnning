// TicketDlg.cpp : implementation file
//

#include "stdafx.h"
#include "supermarkets.h"
#include "TicketDlg.h"
#include "adoconn.h"
#include "userdlg.h"
#include "StorageDlg.h"
#include "Goodsdlg.h"
#include "settlementdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTicketDlg dialog


CTicketDlg::CTicketDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTicketDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTicketDlg)
	m_info = _T("");
	m_time = 0;
	//}}AFX_DATA_INIT
}


void CTicketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTicketDlg)
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_cTime);
	DDX_Control(pDX, IDC_INFO, m_eInfo);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_INDEX, m_combIndex);
	DDX_Control(pDX, IDC_TYPE, m_combType);
	DDX_Text(pDX, IDC_INFO, m_info);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTicketDlg, CDialog)
	//{{AFX_MSG_MAP(CTicketDlg)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_CBN_SELCHANGE(IDC_INDEX, OnSelchangeIndex)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_DELETEALL, OnDeleteall)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_COMMAND(IDUM_USER,OnUser)
	ON_COMMAND(IDUM_STORAGE,OnStorage)
	ON_COMMAND(IDUM_GOODS,OnNGoods)
	ON_COMMAND(IDUM_COUNT,OnCount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTicketDlg message handlers

BOOL CTicketDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
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



	InitControl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTicketDlg::InitControl()
{
	m_list.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0,"票据编号",LVCFMT_LEFT,100,500);
	m_list.InsertColumn(1,"商品编号",LVCFMT_LEFT,100,500);
	m_list.InsertColumn(2,"数量",LVCFMT_LEFT,86,500);
	m_list.InsertColumn(3,"价格",LVCFMT_LEFT,80,500);
	m_list.InsertColumn(4,"日期",LVCFMT_LEFT,100,500);
	m_list.InsertColumn(5,"时间",LVCFMT_LEFT,100,500);

	m_combType.InsertString(0,"销售小票");
	m_combType.InsertString(1,"入库票务");
	m_combType.InsertString(2,"出库票务");
	m_combType.SetCurSel(0);

	m_combIndex.InsertString(0,"票据编号");
	m_combIndex.InsertString(1,"商品编号");
	m_combIndex.InsertString(2,"日期");
	m_combIndex.SetCurSel(0);
}

void CTicketDlg::OnSelect() 
{
	// TODO: Add your control notification handler code here
	m_list.DeleteAllItems();
	int utype = m_combType.GetCurSel();
	int uindex = m_combIndex.GetCurSel();
	UpdateData(true);
	CString sql,index,table;
	int InOrOut = 0;
	switch(utype)
	{
	case 0:
		table = "TICKET";
		break;
	case 1:
		table = "STORAGEINFO";
		InOrOut = ~0;
		break;
	case 2:
		table = "STORAGEINFO";
		InOrOut = 0;
		break;
	}
	switch(uindex)
	{
	case 0:
		index = "TicketID";
		if(utype)
			sql.Format("select * from %s where %s = '%s' AND InOrOut = %d",table,index,m_info,InOrOut);
		else
			sql.Format("select * from %s where %s = '%s'",table,index,m_info);
		break;
	case 1:
		index = "GoodsID";
		if(utype)
			sql.Format("select * from %s where %s = '%s' AND InOrOut = %d",table,index,m_info,InOrOut);
		else
			sql.Format("select * from %s where %s = '%s'",table,index,m_info);
		break;
	default:
		if(utype)
		{
			index = "OpDate";
			sql.Format("select * from %s where %s = #%s# AND InOrOut = %d",table,index,m_time.Format("%Y-%m-%d"),InOrOut);
		}
		else
		{
			index = "SaleDate";
			sql.Format("select * from %s where %s = #%s#",table,index,m_time.Format("%Y-%m-%d"));
		}
	}
	int i = 0;
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	while(!adoConn.m_pRecordset->adoEOF)
	{
		m_list.InsertItem(i,"");
		m_list.SetItemText(i,0,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("TicketID"));
		m_list.SetItemText(i,1,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsID"));
		
		m_list.SetItemText(i,3,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsValue"));
		if(utype)
		{
			m_list.SetItemText(i,2,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("Num"));
			m_list.SetItemText(i,4,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("OpDate"));
			m_list.SetItemText(i,5,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("OpTime"));
		}
		else
		{
			m_list.SetItemText(i,2,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("SaleNum"));
			m_list.SetItemText(i,4,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("SaleDate"));
			m_list.SetItemText(i,5,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("SaleTime"));
		}

		adoConn.m_pRecordset->MoveNext();
		i++;
	}
	if(i == 0)
	{
		MessageBox("没有满足条件的票据！");
	}
	adoConn.ExitConnect();
}



BOOL CTicketDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_LBUTTONDOWN )
	{

	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CTicketDlg::OnSelchangeIndex() 
{
	// TODO: Add your control notification handler code here
	if(m_combIndex.GetCurSel() == 2)
	{
		m_cTime.ShowWindow(SW_SHOW);
		m_eInfo.ShowWindow(SW_HIDE);
		m_time = CTime::GetCurrentTime();
		UpdateData(false);
	}
	else
	{
		m_cTime.ShowWindow(SW_HIDE);
		m_eInfo.ShowWindow(SW_SHOW);
	}
}

void CTicketDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	CString msg;
	msg.Format("真的要销毁票号为：%s的票据？",m_list.GetItemText(m_listIndex,0));
	if(MessageBox(msg,"销毁票据",MB_OKCANCEL) != 1)
		return;

	CString sql;
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	CString ticketid = m_list.GetItemText(m_listIndex,0);
	if(m_combType.GetCurSel())
	{
		sql.Format("delete * from STORAGEINFO where TicketID = '%s'",ticketid );
	}
	else
	{
		sql.Format("delete * from Ticket where TicketID = '%s'",ticketid );
	}
	
	adoConn.ExecuteSQL((_bstr_t)sql);
	adoConn.ExitConnect();	
	OnSelect();	
}

void CTicketDlg::OnDeleteall() 
{
	CString msg;
	msg.Format("真的要销毁当前查询的所有票据？");
	if(MessageBox(msg,"销毁票据",MB_OKCANCEL) != 1)
		return;

	CString sql,ticketid;
	ADOConn adoConn;
	adoConn.OnInitADOConn();

	for(int i=0;i<m_list.GetItemCount();i++)
	{
		ticketid = m_list.GetItemText(i,0);
		if(m_combType.GetCurSel())
		{
			sql.Format("delete * from STORAGEINFO where TicketID = '%s'",ticketid );
		}
		else
		{
			sql.Format("delete * from Ticket where TicketID = '%s'",ticketid );
		}
		adoConn.ExecuteSQL((_bstr_t)sql);
	}
	adoConn.ExitConnect();	
	m_list.DeleteAllItems();
}

void CTicketDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_listIndex =	m_list.GetSelectionMark();
	*pResult = 0;
}
void CTicketDlg::OnUser()
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

void CTicketDlg::OnStorage()
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

void CTicketDlg::OnNGoods()
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

void CTicketDlg::OnCount()
{
	if(m_WorkType  < 6)
	{
		MessageBox("您没有权限访问这个模块");
		return;
	}
	OnOK();
	CSettlementDlg dlg;
	dlg.m_WorkType = m_WorkType;
	dlg.DoModal();
}
