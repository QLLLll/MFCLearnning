// SuperMarketsDlg.cpp : implementation file
//
#include <string.h>
#include "stdafx.h"
#include "SuperMarkets.h"
#include "SuperMarketsDlg.h"
#include "logindlg.h"
#include "adoconn.h"
#include "SaleDlg.h"
#include "admindlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperMarketsDlg dialog

CSuperMarketsDlg::CSuperMarketsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSuperMarketsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSuperMarketsDlg)
	m_actual = 0.0;
	m_should = 0.0;
	m_change = 0.0;
	m_bTicket = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_type = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSuperMarketsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuperMarketsDlg)
	DDX_Control(pDX, IDC_STATISTICS, m_Statistics);
	DDX_Control(pDX, IDC_TICKET, m_cTicket);
	DDX_Control(pDX, IDC_SSHOULD, m_sShould);
	DDX_Control(pDX, IDC_SCHANGE, m_sChange);
	DDX_Control(pDX, IDC_SACT, m_sActual);
	DDX_Control(pDX, IDC_ESHOLD, m_eShould);
	DDX_Control(pDX, IDC_ECHANGE, m_eChange);
	DDX_Control(pDX, IDC_EACT, m_eActual);
	DDX_Control(pDX, IDC_BSALE, m_bSale);
	DDX_Control(pDX, IDC_BCHECK, m_bCheck);
	DDX_Control(pDX, IDC_LIST2, m_goodsTail);
	DDX_Control(pDX, IDC_LIST1, m_goods);
	DDX_Text(pDX, IDC_EACT, m_actual);
	DDX_Text(pDX, IDC_ESHOLD, m_should);
	DDX_Text(pDX, IDC_ECHANGE, m_change);
	DDX_Check(pDX, IDC_TICKET, m_bTicket);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSuperMarketsDlg, CDialog)
	//{{AFX_MSG_MAP(CSuperMarketsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BSALE, OnSale)
	ON_BN_CLICKED(IDC_BCHECK, OnCheck)
	ON_EN_CHANGE(IDC_EACT, OnChangeEact)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperMarketsDlg message handlers

BOOL CSuperMarketsDlg::OnInitDialog()
{	
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	// TODO: Add extra initialization here
	
	SetTimer(1,1000,NULL);

	CLogInDlg dlg;
	if(dlg.DoModal() != IDOK)
	{
		CDialog::OnCancel();
	}
	else
	{
		if(dlg.m_type > 1)
		{
			CAdminDlg dlgM;
			dlgM.m_WorkID =   dlg.m_WorkID;
			dlgM.m_WorkType = dlg.m_type;
			dlgM.DoModal();
			OnOK();
		}
		else if(dlg.m_type < 1)
		{
			CDialog::OnCancel();
		}
		
		m_WorkID = dlg.m_WorkID;
	}
	int x,y;
	x = GetSystemMetrics(SM_CXSCREEN);
	y = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(NULL,0,0,x,y,SWP_NOMOVE);
	GetClientRect(&m_clientRect);
	InitDialogShow();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSuperMarketsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSuperMarketsDlg::OnPaint() 
{
	CClientDC dc(this);
	CDialog::OnPaint();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSuperMarketsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSuperMarketsDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	SYSTEMTIME time;
	GetLocalTime(&time);
	int num[6];
	num[0] = time.wYear;
	num[1] = time.wMonth;
	num[2] = time.wDay;
	num[3] = time.wHour;
	num[4] = time.wMinute;
	num[5] = time.wSecond;
	CString string[6];
	for(int i = 0; i < 6; i++)
	{
		string[i] = numTostring(num[i]);
	}

	CString sdate,stime;
	sdate.Format("%s年%s月%s日",string[0],string[1],string[2]);
	GetDlgItem(IDC_DATE)->SetWindowText(sdate);
	stime.Format("%s:%s:%s",string[3],string[4],string[5]);
	GetDlgItem(IDC_TIME)->SetWindowText(stime);
}

CString CSuperMarketsDlg::numTostring(int num)
{
	CString str;
	
	if(num <10)
	{
		str.Format("0%d",num);
	}
	else
	{
		str.Format("%d",num);
	}
	return str;
}

void CSuperMarketsDlg::ShowUser()
{
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	CString sql;
	sql.Format("select * from worker where WorkerID='%s'",m_WorkID);
	adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
	if(!(adoConn.m_pRecordset->adoEOF))
	{
		CString str;
		str = (char*)(_bstr_t)adoConn.m_pRecordset->GetCollect("Name");
		GetDlgItem(IDC_WORKERNAME)->SetWindowText(str);
	}
}

void CSuperMarketsDlg::InitDialogShow()
{
	ShowUser();
	InitListControl();
	InitSaleControl();
}

void CSuperMarketsDlg::InitListControl()
{
	m_goods.MoveWindow(10,60,m_clientRect.Width()-20,m_clientRect.Height()/2 - 30);
	//设置列表视图的扩展风格
	m_goods.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	//设置表头
	m_goods.InsertColumn(0,"商品编号",LVCFMT_LEFT,150,0);
	m_goods.InsertColumn(1,"条 形 码",LVCFMT_LEFT,200,4);
	m_goods.InsertColumn(2,"商品单价",LVCFMT_LEFT,150,6);   
	m_goods.InsertColumn(3,"销售数量",LVCFMT_LEFT,200,5); 
	m_goods.InsertColumn(4,"商品名称",LVCFMT_LEFT,230,1);

	m_goodsTail.MoveWindow(10,m_clientRect.Height()/2 + 160,m_clientRect.Width()-20,m_clientRect.Height()/2-180);
	//设置列表视图的扩展风格
	m_goodsTail.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

		//设置表头
	m_goodsTail.InsertColumn(0,"商品编号",LVCFMT_LEFT,150,0); 
	m_goodsTail.InsertColumn(1,"主件",LVCFMT_LEFT,230,1); 
	m_goodsTail.InsertColumn(2,"附件",LVCFMT_LEFT,150,2); 
	m_goodsTail.InsertColumn(3,"说明",LVCFMT_LEFT,950,6); 
}

void CSuperMarketsDlg::InitSaleControl()
{
	m_Statistics.MoveWindow(10,m_clientRect.Height()/2 + 30 ,m_clientRect.Width() - 20,125);
	m_sShould.MoveWindow(m_clientRect.Width() - 1100,m_clientRect.Height()/2 + 80 ,40,30);
	m_eShould.MoveWindow(m_clientRect.Width() - 1050,m_clientRect.Height()/2 + 75 ,150,25);

	m_sActual.MoveWindow(m_clientRect.Width() - 850,m_clientRect.Height()/2 + 80 ,40,30);
	m_eActual.MoveWindow(m_clientRect.Width() - 800,m_clientRect.Height()/2 + 75 ,150,25);

	m_sChange.MoveWindow(m_clientRect.Width() - 600,m_clientRect.Height()/2 + 80 ,40,30);
	m_eChange.MoveWindow(m_clientRect.Width() - 550,m_clientRect.Height()/2 + 75 ,150,25);

	m_cTicket.MoveWindow(m_clientRect.Width() - 290,m_clientRect.Height()/2 + 100 ,100,25);

	m_bSale.MoveWindow(m_clientRect.Width() - 190,m_clientRect.Height()/2 + 60 ,80,25);
	m_bCheck.MoveWindow(m_clientRect.Width() - 190,m_clientRect.Height()/2 + 100 ,80,25);
}

BOOL CSuperMarketsDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN )
	if(	pMsg->wParam == VK_RETURN)
	{
		pMsg->lParam = VK_TAB;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CSuperMarketsDlg::OnSale() 
{
	// TODO: Add your control notification handler code here
	CSaleDlg dlg;
	dlg.m_uType = m_type;
	int i = 0;
	if(dlg.DoModal() == IDOK)
	{
		CString Text,sql,field;
		Text		= dlg.m_goods;
		m_type		= dlg.m_uType;
		m_SaleNum   = dlg.m_num;
		switch(m_type)
		{
		case 0:
			field = "GoodsID";
			break;
		case 1:
			field = "GoodsBarCode";
			break;
		}
		sql.Format("select * from GOODS where %s='%s'",field,Text);
		ADOConn adoConn;
		adoConn.OnInitADOConn();
		adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
		if(!(adoConn.m_pRecordset->adoEOF))
		{
			CString str,sNum,sum;
			str = (char*)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsValue");
			m_GoodsID = (char*)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsID");
			sNum.Format("%d",m_SaleNum);
			m_should += m_SaleNum*atof(str)*1.0;
			str.Format("%.2f",atof(str));
			m_goods.InsertItem(i,"");
			m_goods.SetItemText(i,0,m_GoodsID);
			m_goods.SetItemText(i,1,(char*)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsBarCode"));
			m_goods.SetItemText(i,2,(char*)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsValue"));
			m_goods.SetItemText(i,3,sNum);
			m_goods.SetItemText(i,4,(char*)(_bstr_t)adoConn.m_pRecordset->GetCollect("GoodsName"));
			i++;
		}
		else
		{
			MessageBox("该商品不存在");
		}
		sql.Format("select * from GOODSPACK where GoodsID = '%s'",m_GoodsID);
		i = 0;
		adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
		if(!(adoConn.m_pRecordset->adoEOF))
		{
			m_goodsTail.InsertItem(i,"");
			m_goodsTail.SetItemText(i,0,m_GoodsID);
			m_goodsTail.SetItemText(i,1,(char*)(_bstr_t)adoConn.m_pRecordset->GetCollect("PackMain"));
			m_goodsTail.SetItemText(i,2,(char*)(_bstr_t)adoConn.m_pRecordset->GetCollect("PackParts"));
			m_goodsTail.SetItemText(i,3,(char*)(_bstr_t)adoConn.m_pRecordset->GetCollect("PackAnnotation"));
			i++;
		}
		adoConn.ExitConnect();
		UpdateData(false);
	}
}

void CSuperMarketsDlg::OnCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_should == 0 || m_actual == 0)
	{
		MessageBox("应收金额和实收金额不能为零！");
		return;
	}
	CString sql;
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	int num ;
	for(int i=0;i<m_goods.GetItemCount();i++)
	{
		num	= atoi(m_goods.GetItemText(i,3));
		sql.Format("UPDATE STORAGE SET GoodsLeftNum=GoodsLeftNum-%d,GoodsSaleNum=GoodsSaleNum+%d where GoodsID='%s'",
			num,num,m_goods.GetItemText(i,0));
		adoConn.ExecuteSQL((_bstr_t)sql);
	}
	adoConn.ExitConnect();

	PrintTicket();
	m_should = 0;
	m_actual = 0;
	m_change = 0;
	m_goods.DeleteAllItems();
	m_goodsTail.DeleteAllItems();
	UpdateData(false);
}

void CSuperMarketsDlg::OnChangeEact() 
{
	UpdateData(true);
	m_change = m_actual - m_should;
	CString str;

	str.Format("%.2f",m_change);
	GetDlgItem(IDC_ECHANGE)->SetWindowText(str);
}

void CSuperMarketsDlg::PrintTicket()
{
	int printx,printy;
	int screenx,screeny;
	double ratex,ratey;
	CFont pfont;
	CString str[100][7],sql;
	CTime time = CTime::GetCurrentTime();
	CString ticketID = GetTicketID(time);
		
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	/***插入新的销售小票***********/
	int i=0,n=0;
	CString goodsID,goodsCodeBar,goodsValue,saleNum,goodsName;
	for(i=0;i<m_goods.GetItemCount();i++)
	{
		goodsID			= m_goods.GetItemText(i,0);			// 商品编号
		goodsCodeBar	= m_goods.GetItemText(i,1);			// 商品条形码
		goodsValue		= m_goods.GetItemText(i,2);			// 商品定价
		saleNum			= m_goods.GetItemText(i,3);			// 商品数量
		goodsName		= m_goods.GetItemText(i,4);			// 商品名称

		sql.Format("insert into TICKET(TicketID,GoodsID,GoodsName,GoodsBarCode,SaleNum,GoodsValue,SaleDate,SaleTime)\
			values('%s','%s','%s','%s',%d,%f,#%s#,#%s#)",ticketID,goodsID,goodsName,goodsCodeBar,\
			atoi(saleNum),atof(goodsValue),time.Format("%Y-%m-%d"),time.Format(" %H:%M:%S"));
		adoConn.ExecuteSQL((_bstr_t)sql);
	}
	adoConn.ExitConnect();
	/***插入新的销售小票结束***********/
	if(m_bTicket)
	{
		/****************开始打印**********/
		m_should = 0;
		m_actual = 0;
		m_change = 0;
		i = 0;
		CDC* pDC = GetDC();
		screenx = pDC->GetDeviceCaps(LOGPIXELSX);
		screeny = pDC->GetDeviceCaps(LOGPIXELSY);
		CPrintDialog m_printdlg(FALSE);
		if (m_printdlg.DoModal()==IDOK)
		{
			CDC dc;	
			
			dc.Attach(m_printdlg.GetPrinterDC());

			printx = dc.GetDeviceCaps(LOGPIXELSX);
			printy = dc.GetDeviceCaps(LOGPIXELSY);
			ratex = (double)(printx)/screenx;
			ratey = (double)(printy)/screeny;
			
			i=0;
			str[i][0] = "商品编号";
			str[i][1] = "商品名称";
			str[i][2] = "销售数量";
			str[i][3] = "销售单价";
			str[i][4] = "销售金额";
			double sum  = 0;
			CString strsum = "";
			for(i=1;i<=m_goods.GetItemCount();i++)
			{
				str[i][0] = m_goods.GetItemText(i-1,0);
				str[i][1] = m_goods.GetItemText(i-1,1);
				str[i][2] = m_goods.GetItemText(i-1,5);
				str[i][3] = m_goods.GetItemText(i-1,6);
				str[i][4].Format("%0.2f",atoi(str[i][2])*atof(str[i][3]));
				strsum.Format("%0.2f",sum + atof(str[i][4]));
				sum = atof(str[i][4]);
			}
			CString tidStr;
			tidStr.Format("销售票号：%s", ticketID);
			dc.StartDoc("printstart");
			pfont.CreatePointFont(110,"宋体",&dc);
			dc.TextOut((int)ratex*5,(int)ratey*10,"XX超市");
			dc.TextOut((int)ratex*5,(int)ratey*30,tidStr);
			dc.TextOut((int)ratex*5,(int)ratey*50,"销售时间：");
			dc.TextOut((int)ratex*90,(int)ratey*50,time.Format("%Y-%m-%d %H:%M:%S"));
			dc.MoveTo((int)ratex*5,(int)ratey*72);
			dc.LineTo((int)ratex*220,(int)ratey*72);
			dc.MoveTo((int)ratex*5,(int)ratey*74);
			dc.LineTo((int)ratex*220,(int)ratey*74);
			for(int k=0;k<i;k++)
			{
				if(n >= 40)
				{
					n = 1;
					dc.EndPage();
					dc.StartPage();
				}
				for(int j=0;j<5;j++)
				{
					if(j<2)
						dc.TextOut((int)ratex*(5+j*80),(int)ratey*(80+n*20),str[k][j]);	
					else
						dc.TextOut((int)ratex*(5+(j-2)*80),(int)ratey*(80+(n+1)*20),str[k][j]);
				}
				n = n + 2;
			}
			
			dc.MoveTo((int)ratex*5,(int)ratey*(80+n*20));
			dc.LineTo((int)ratex*220,(int)ratey*(80+n*20));
			dc.MoveTo((int)ratex*5,(int)ratey*(82+n*20));
			dc.LineTo((int)ratex*220,(int)ratey*(82+n*20));
			dc.TextOut((int)ratex*5,(int)ratey*(90+n*20),"销售总额："+strsum);
			dc.EndDoc();
			pfont.DeleteObject();
		}
	}
}

CString CSuperMarketsDlg::GetTicketID(CTime time)
{
	CString sql,ph,ticketID;
	sql.Format("select * from TICKET where SaleDate=#%s#",time.Format("%Y-%m-%d"));
	ADOConn adoConn;
	adoConn.OnInitADOConn();
	adoConn.m_pRecordset = adoConn.GetRecordSet((_bstr_t)sql);
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
		ticketID.Format("XS%s%04d",time.Format("%y%m%d"),atoi(ticketID.Right(4))+1);
	}
	else
	{
		ticketID.Format("XS%s0001",time.Format("%y%m%d"));
	}
	adoConn.ExitConnect();
	return ticketID;
}

void CSuperMarketsDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
