// AdminDlg.cpp : implementation file
//

#include "stdafx.h"
#include "supermarkets.h"
#include "AdminDlg.h"
#include "userdlg.h"
#include "StorageDlg.h"
#include "Ticketdlg.h"
#include "Goodsdlg.h"
#include "settlementdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdminDlg dialog


CAdminDlg::CAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdminDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdminDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdminDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdminDlg, CDialog)
	//{{AFX_MSG_MAP(CAdminDlg)
	ON_COMMAND(IDUM_USER,OnUser)
	ON_COMMAND(IDUM_STORAGE,OnStorage)
	ON_COMMAND(IDUM_TICKET,OnTicket)
	ON_COMMAND(IDUM_GOODS,OnNGoods)
	ON_COMMAND(IDUM_COUNT,OnCount)

	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdminDlg message handlers

BOOL CAdminDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
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
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAdminDlg::OnUser()
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

void CAdminDlg::OnStorage()
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

void CAdminDlg::OnTicket()
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

void CAdminDlg::OnNGoods()
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

void CAdminDlg::OnCount()
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
