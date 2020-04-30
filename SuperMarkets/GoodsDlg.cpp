// GoodsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "supermarkets.h"
#include "GoodsDlg.h"
#include "adoconn.h"
#include "newgoodsdlg.h"
#include "userdlg.h"
#include "StorageDlg.h"
#include "Ticketdlg.h"
#include "settlementdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGoodsDlg dialog


CGoodsDlg::CGoodsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGoodsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGoodsDlg)
	m_info = _T("");
	m_opStr = _T("");
	//}}AFX_DATA_INIT
}


void CGoodsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGoodsDlg)
	DDX_Control(pDX, IDC_COMBO2, m_opType);
	DDX_Control(pDX, IDC_COMBO1, m_index);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_INFO, m_info);
	DDX_CBString(pDX, IDC_COMBO2, m_opStr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGoodsDlg, CDialog)
	//{{AFX_MSG_MAP(CGoodsDlg)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_MODFY, OnModfy)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_COMMAND(IDUM_USER,OnUser)
	ON_COMMAND(IDUM_STORAGE,OnStorage)
	ON_COMMAND(IDUM_TICKET,OnTicket)
	ON_COMMAND(IDUM_COUNT,OnCount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoodsDlg message handlers

BOOL CGoodsDlg::OnInitDialog() 
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



	m_list.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0,"商品编号",LVCFMT_LEFT,120,1);
	m_list.InsertColumn(1,"商品名称",LVCFMT_LEFT,120,4);
	m_list.InsertColumn(2,"条形码",LVCFMT_LEFT,120,6);   
	m_list.InsertColumn(3,"销售单价",LVCFMT_LEFT,120,5);

	m_index.InsertString(0,"商品编号");
	m_index.InsertString(1,"商品名称");
	m_index.InsertString(2,"条形码");
	m_index.InsertString(3,"销售价格");

	m_index.SetCurSel(0);

	m_opType.InsertString(0,"  >  ");
	m_opType.InsertString(1,"  >= ");
	m_opType.InsertString(2,"  =  ");
	m_opType.InsertString(3,"  <= ");
	m_opType.InsertString(4,"  <  ");
	m_opType.SetCurSel(2);
	SetopTypeEnable();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGoodsDlg::OnSelect() 
{
	// TODO: Add your control notification handler code here
	m_list.DeleteAllItems();
	CString sql;
	UpdateData(true);
	double value = 0;
	int index = m_index.GetCurSel();
	switch(index)
	{
	case 0:
		sql.Format("select * from GOODS where GoodsID %s '%s'",m_opStr,m_info);
		break;
	case 1:
		sql.Format("select * from GOODS where GoodsName %s '%s'",m_opStr,m_info);
		break;
	case 2:
		sql.Format("select * from GOODS where GoodsBarCode %s '%s'",m_opStr,m_info);
		break;
	case 3:
		value = atof(m_info);
		sql.Format("select * from GOODS where GoodsValue %s %.2f",m_opStr,value);
		break;
	}
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	CString workid,name,Permissions,sex,id,phone,address,pwd;
	int i = 0;
	while(!adoConn.m_pRecordset->adoEOF)
	{
		m_list.InsertItem(i,"");
		m_list.SetItemText(i,0,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsID"));
		m_list.SetItemText(i,1,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsName"));
		m_list.SetItemText(i,2,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsBarCode"));
		m_list.SetItemText(i,3,(char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsValue"));
		adoConn.m_pRecordset->MoveNext();
	}
}

void CGoodsDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	CString goodsid = GetGoodsID();
	CNewGoodsDlg dlg;
	dlg.m_goodsid = goodsid;

ERROR_END:
	if(dlg.DoModal() ==  IDOK)
	{
		if((dlg.m_goodsname == "" || dlg.m_barcode == "" || dlg.m_goodsvalue == 0) )
		{
				MessageBox("新增商品信息不完备，请检查！");
				goto ERROR_END;
		}
		else
		{
			ADOConn adoConn;
			adoConn.OnInitADOConn();
			CString sql;
			sql.Format("insert into GOODS(GoodsID,GoodsName,GoodsBarCode,GoodsValue)\
			values('%s','%s','%s',%.2f)",dlg.m_goodsid,dlg.m_goodsname,dlg.m_barcode,dlg.m_goodsvalue);
			adoConn.ExecuteSQL((_bstr_t)sql);

			sql.Format("Insert into GOODSPACK(GoodsID ,PackMain,PackParts,PackAnnotation) values('%s','%s','%s','%s')",\
				dlg.m_goodsid,dlg.m_main,dlg.m_part,dlg.m_info);
			adoConn.ExecuteSQL((_bstr_t)sql);
			adoConn.ExitConnect();
		
		}
	}
}

void CGoodsDlg::OnModfy() 
{
	// TODO: Add your control notification handler code here
	CNewGoodsDlg dlg;
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	CString sql;
	sql.Format("select * from GOODSPACK where GoodsID = '%s'",m_list.GetItemText(m_listIndex,0));
	adoConn.m_pRecordset = adoConn.GetRecordSet((bstr_t)sql);
	if(!adoConn.m_pRecordset->adoEOF)
	{
		dlg.m_main = (char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("PackMain");
		dlg.m_part = (char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("PackParts");
		dlg.m_info = (char *)(_bstr_t)adoConn.m_pRecordset->GetCollect("PackAnnotation");
	}

	dlg.m_goodsid		=	m_list.GetItemText(m_listIndex,0);
	dlg.m_goodsname		=	m_list.GetItemText(m_listIndex,1);
	dlg.m_barcode		=	m_list.GetItemText(m_listIndex,2);
	dlg.m_goodsvalue	=	atof(m_list.GetItemText(m_listIndex,3));
	if(dlg.DoModal() ==  IDOK)
	{
		sql.Format("UPDATE GOODS set GoodsName ='%s', GoodsBarCode='%s', GoodsValue =%.2f where GoodsID = '%s'",\
			dlg.m_goodsname,dlg.m_barcode,dlg.m_goodsvalue,dlg.m_goodsid);
		adoConn.ExecuteSQL((_bstr_t)sql);
	

		if(CheckExitPack("GoodsID",dlg.m_goodsid,"GOODSPACK"))
		{
			sql.Format("UPDATE GOODSPACK set PackMain ='%s' , PackParts='%s' ,PackAnnotation ='%s' where GoodsID = '%s'",\
				dlg.m_main,dlg.m_part,dlg.m_info,dlg.m_goodsid);
			adoConn.ExecuteSQL((_bstr_t)sql);
		}
		else
		{
			sql.Format("Insert into GOODSPACK(GoodsID ,PackMain,PackParts,PackAnnotation) values('%s','%s','%s','%s')",\
				dlg.m_goodsid,dlg.m_main,dlg.m_part,dlg.m_info);
			adoConn.ExecuteSQL((_bstr_t)sql);
		}
			adoConn.ExitConnect();
	}
	OnSelect();
}

void CGoodsDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	CString msg;
	msg.Format("真的要删除商品：%s",m_list.GetItemText(m_listIndex,1));
	if(MessageBox(msg,"删除商品",MB_OKCANCEL) != 1)
		return;
	
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	CString goodsID = m_list.GetItemText(m_listIndex,0);
	CString sql;
	sql.Format("delete * from GOODS where GoodsID = '%s'",goodsID);
	
	adoConn.ExecuteSQL((_bstr_t)sql);
	adoConn.ExitConnect();	
	OnSelect();
}

void CGoodsDlg::SetopTypeEnable()
{
	if(m_index.GetCurSel() != 1)
	{
		m_opType.EnableWindow(true);
	}
	else
	{
		m_opType.EnableWindow(false);
		m_opType.SetCurSel(2);
	}
}

void CGoodsDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	SetopTypeEnable();
}

CString CGoodsDlg::GetGoodsID()
{
	CTime time = CTime::GetCurrentTime();
	CString infoStart,infoEnd;
	infoStart.Format("GS%s0001",time.Format("%y%m%d"));
	infoEnd.Format("GS%s9999",time.Format("%y%m%d"));
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	CString sql,goodsID,temp;
	sql.Format("select * from GOODS where GoodsID >= '%s' and GoodsID <=  '%s'", infoStart,infoEnd);
	adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	goodsID = temp = "0";
	if(!adoConn.m_pRecordset->adoEOF)
	{
		while(!adoConn.m_pRecordset->adoEOF)
		{
			temp = (char*)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsID");
			adoConn.m_pRecordset->MoveNext();
		}
		if(temp.Compare(goodsID) > 0)
		{
			goodsID = temp;
		}
		goodsID.Format("GS%s%04d",time.Format("%y%m%d"),atoi(goodsID.Right(4))+1);
	}
	else
	{
		goodsID.Format("GS%s0001",time.Format("%y%m%d"));
	}
	adoConn.ExitConnect();
	return goodsID;

}

void CGoodsDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_listIndex =	m_list.GetSelectionMark();
	*pResult = 0;
}
void CGoodsDlg::OnUser()
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

void CGoodsDlg::OnStorage()
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

void CGoodsDlg::OnTicket()
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

void CGoodsDlg::OnCount()
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


bool CGoodsDlg::CheckExitPack(CString index, CString value, CString table)
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
	
}
