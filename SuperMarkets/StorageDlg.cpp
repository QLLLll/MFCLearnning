// StorageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "supermarkets.h"
#include "StorageDlg.h"
#include "adoconn.h"
#include "inoutdlg.h"
#include "userdlg.h"
#include "Ticketdlg.h"
#include "Goodsdlg.h"
#include "settlementdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStorageDlg dialog


CStorageDlg::CStorageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStorageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStorageDlg)
	m_id = 0;
	m_info = _T("");
	m_goodsid = _T("");
	//}}AFX_DATA_INIT
}


void CStorageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStorageDlg)
	DDX_Control(pDX, IDC_INFO, m_infoComb);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_COMBO1, m_comb);
	DDX_Radio(pDX, IDC_ID, m_id);
	DDX_CBString(pDX, IDC_INFO, m_info);
	DDX_CBString(pDX, IDC_COMBO1, m_goodsid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStorageDlg, CDialog)
	//{{AFX_MSG_MAP(CStorageDlg)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_BN_CLICKED(IDC_INSTORAGE, OnInstorage)
	ON_BN_CLICKED(IDC_OUTSTORAGE, OnOutstorage)
	ON_BN_CLICKED(IDC_ID, OnId)
	ON_BN_CLICKED(IDC_LEFT, OnLeft)
	ON_BN_CLICKED(IDC_SALE, OnSale)
	ON_COMMAND(IDUM_USER,OnUser)
	ON_COMMAND(IDUM_TICKET,OnTicket)
	ON_COMMAND(IDUM_GOODS,OnNGoods)
	ON_COMMAND(IDUM_COUNT,OnCount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStorageDlg message handlers

BOOL CStorageDlg::OnInitDialog() 
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


	m_list.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0,"货物编号",LVCFMT_LEFT,101,1);
	m_list.InsertColumn(1,"剩余数量",LVCFMT_LEFT,99,4);
	m_list.InsertColumn(2,"销售数量",LVCFMT_LEFT,99,6);  
	
	SetControl();
	m_comb.InsertString(0,"   >   ");
	m_comb.InsertString(1,"   >=  ");
	m_comb.InsertString(2,"   =   ");
	m_comb.InsertString(3,"   <=  ");
	m_comb.InsertString(4,"   <   ");
	m_comb.SetCurSel(2);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStorageDlg::OnSelect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_list.DeleteAllItems();
	CString type_index,type_symbols;
	switch(m_id)
	{
	case 0:
		type_index = "GoodsID";
		break;
	case 1:
		type_index = "GoodsLeftNum";
		break;
	case 2:
		type_index = "GoodsSaleNum";
		break;
	}
	switch(m_comb.GetCurSel())
	{
	case 0:
		type_symbols = ">";
		break;
	case 1:
		type_symbols = ">=";
		break;
	case 2:
		type_symbols = "=";
		break;
	case 3:
		type_symbols = "<=";
		break;
	case 4:
		type_symbols = "<";
		break;
	}
	CString sql;
	int index = 0;
	if(!m_id)
	{
		sql.Format("select * from STORAGE where GoodsID ='%s' ",m_info);
	}
	else
	{
		int num = atoi(m_info);
		sql.Format("select * from STORAGE where %s %s%d",type_index,type_symbols,num);
	}
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	while(!adoConn.m_pRecordset->adoEOF)
	{
		m_list.InsertItem(index,"");
		m_list.SetItemText(index,0,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsID"));
		m_list.SetItemText(index,1,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsLeftNum"));
		m_list.SetItemText(index,2,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsSaleNum"));
		adoConn.m_pRecordset->MoveNext();
		index++;
	}
}

void CStorageDlg::OnInstorage() 
{
	// TODO: Add your control notification handler code here
	CInOutDlg dlg;
	dlg.m_bIn = true;

ERROR_DEEL:
	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_num == 0 || dlg.m_value == 0 || dlg.m_supplier == "")
		{
			MessageBox("入库货物信息不完备，请检查！\r\n \r\n价格与数量不能为0，需要添加进货商信息！");
			goto ERROR_DEEL;
		}
		CString sql;
		ADOConn adoConn;
		adoConn.OnInitADOConn();
		if(CheckExit("GoodsID",dlg.m_goosid,"STORAGE"))
		{
			sql.Format("UPDATE STORAGE SET GoodsLeftNum = GoodsLeftNum + %d where GoodsID ='%s'",dlg.m_num,dlg.m_goosid);
			adoConn.ExecuteSQL((_bstr_t)sql);
			adoConn.ExitConnect();
		}
		else
		{
			sql.Format("insert into STORAGE(GoodsID,GoodsLeftNum,GoodsSaleNum) \
			values('%s',%d,%d)",dlg.m_goosid,dlg.m_num,0);
			adoConn.ExecuteSQL((_bstr_t)sql);
			adoConn.ExitConnect();
			m_comb.InsertString(m_comb.GetCount()+1,dlg.m_goosid);
			m_comb.SetCurSel(m_comb.GetCount());
			OnSelect();
		}
		CString ticketid;
		CTime time = CTime::GetCurrentTime();
		ticketid = GetTicketID(time);
		adoConn.OnInitADOConn();
		sql.Format("insert into STORAGEINFO(TicketID,GoodsID,Num,GoodsValue,InOrOut,Info,OpDate,OpTime)\
			values('%s','%s',%d,%.2f,%d,'%s',#%s#,#%s#)",ticketid,dlg.m_goosid,dlg.m_num,dlg.m_value,1,dlg.m_supplier,\
			time.Format("%Y-%m-%d"),time.Format("%H:%M:%S"));
		adoConn.ExecuteSQL((_bstr_t)sql);


	}
}

void CStorageDlg::OnOutstorage() 
{
	// TODO: Add your control notification handler code here
	CInOutDlg dlg;
	dlg.m_bIn = false;

ERROR_DEEL:
	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_num == 0 || dlg.m_value == 0 || dlg.m_supplier == "")
		{
			MessageBox("出库货物信息不完备，请检查！\r\n \r\n价格与数量不能为0，需要添提进货商信息！");
			goto ERROR_DEEL;
		}
		
		if(CheckExit("GoodsID",dlg.m_goosid,"STORAGE"))
		{
			if(CheckNum("GoodsID",dlg.m_goosid,"STORAGE",dlg.m_num) < 0)
			{
				MessageBox("库存不足，请核实出库数量！");
				goto ERROR_DEEL;
			}
			CString sql;
			ADOConn adoConn;
			adoConn.OnInitADOConn();
			sql.Format("UPDATE STORAGE SET GoodsLeftNum = GoodsLeftNum - %d where GoodsID ='%s'",dlg.m_num,dlg.m_goosid);
			adoConn.ExecuteSQL((_bstr_t)sql);
			adoConn.ExitConnect();

			CString ticketid;
			CTime time = CTime::GetCurrentTime();
			ticketid = GetTicketID(time);
			adoConn.OnInitADOConn();
			sql.Format("insert into STORAGEINFO(TicketID,GoodsID,Num,GoodsValue,InOrOut,Info,OpDate,OpTime)\
				values('%s','%s',%d,%.2f,%d,'%s',#%s#,#%s#)",ticketid,dlg.m_goosid,dlg.m_num,dlg.m_value,0,dlg.m_supplier,\
				time.Format("%Y-%m-%d"),time.Format("%H:%M:%S"));
			adoConn.ExecuteSQL((_bstr_t)sql);
		}
		else
		{
			MessageBox("此种商品尚未入库，请查询！");
			return;
		}
	}
}

void CStorageDlg::SetControl()
{
	if(m_id == 0)
	{
		m_comb.SetCurSel(2);
		m_comb.EnableWindow(false);
		
		int index = 0;
		CString sql;
		sql.Format("select * from GOODS ");
		ADOConn adoConn;
		adoConn.OnInitADOConn();
		adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
		while(!adoConn.m_pRecordset->adoEOF)
		{
			m_infoComb.InsertString(index,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsID"));
			adoConn.m_pRecordset->MoveNext();
			index++;
		}
		m_infoComb.SetCurSel(0);
	}
	else 
	{
		m_comb.EnableWindow(true);
		int index = m_infoComb.GetCount();
		while(index >= 0)
		{
			m_infoComb.DeleteString(index);
			index--;
		}
		m_info = "";
		UpdateData(false);
	}
}

void CStorageDlg::OnId() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	SetControl();
}

void CStorageDlg::OnLeft() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	SetControl();
}

void CStorageDlg::OnSale() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	SetControl();
}

bool CStorageDlg::CheckExit(CString index, CString value, CString table)
{
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	CString sql;
	sql.Format("select * from %s where %s = '%s'",table,index,value);
		adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	if(!adoConn.m_pRecordset->adoEOF)
	{
		adoConn.ExitConnect();
		return true;
	}
	else
	{
		adoConn.ExitConnect();
		return false;
	}
	adoConn.ExitConnect();
}

int CStorageDlg::CheckNum(CString index, CString value, CString table, int num)
{
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	CString sql;
	sql.Format("select * from %s where %s = '%s'",table,index,value);
		adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	if(!adoConn.m_pRecordset->adoEOF)
	{
		CString str = (char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsLeftNum");
		adoConn.ExitConnect();
		return atoi(str) -  num ;
	}
	else
	{
		adoConn.ExitConnect();
		return -1;
	}

}

CString CStorageDlg::GetTicketID(CTime time)
{
	CString sql,ph,ticketID;
	sql.Format("select * from STORAGEINFO where OpDate=#%s#",time.Format("%Y-%m-%d"));
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	ticketID = ph ="0";
	if(!adoConn.m_pRecordset->adoEOF)
	{
		while(!adoConn.m_pRecordset->adoEOF)
		{
			ph = (char*)(_bstr_t)adoConn.m_pRecordset->GetCollect("TicketID");
			adoConn.m_pRecordset->MoveNext();
			if(ph.Compare(ticketID) > 0)
			{
				ticketID = ph;
			}
		}
		ticketID.Format("STOR%s%04d",time.Format("%y%m%d"),atoi(ticketID.Right(4))+1);
	}
	else
	{
		ticketID.Format("STOR%s0001",time.Format("%y%m%d"));
	}
	adoConn.ExitConnect();
	return ticketID;

}
void CStorageDlg::OnUser()
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


void CStorageDlg::OnTicket()
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

void CStorageDlg::OnNGoods()
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

void CStorageDlg::OnCount()
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
