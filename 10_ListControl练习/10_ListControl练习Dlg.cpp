
// 10_ListControl练习Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "10_ListControl练习.h"
#include "10_ListControl练习Dlg.h"
#include "afxdialogex.h"
#include"People.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy10_ListControl练习Dlg 对话框



CMy10_ListControl练习Dlg::CMy10_ListControl练习Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY10_LISTCONTROL_DIALOG, pParent)
	, m_check(_T(""))
	, m_age(0)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy10_ListControl练习Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BUTTON1, m_rcMan);
	DDX_Control(pDX, IDC_COMBO1, m_people);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//  DDX_Control(pDX, IDC_EDIT1, m_age);
	//  DDX_Text(pDX, IDC_EDIT1, m_age);
	DDX_Text(pDX, IDC_EDIT1, m_age);
}

BEGIN_MESSAGE_MAP(CMy10_ListControl练习Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CMy10_ListControl练习Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMy10_ListControl练习Dlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy10_ListControl练习Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy10_ListControl练习Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMy10_ListControl练习Dlg 消息处理程序

BOOL CMy10_ListControl练习Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);

	CString people[10] = { TEXT("王一"),TEXT("李二"), TEXT("张三"), TEXT("钱五"), TEXT("孙八"),
		TEXT("周周"), TEXT("刘六"), TEXT("赵七"), TEXT("吴五"), TEXT("贺三三") };

	for (int i = 0; i < 10; i++)
	{
		m_people.InsertString(i, people[i]);

	}
	m_people.SetCurSel(0);

	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_list.InsertColumn(0, TEXT("姓名"),LVCFMT_LEFT,50);
	m_list.InsertColumn(1, TEXT("性别"),LVCFMT_LEFT,50); 
	m_list.InsertColumn(2, TEXT("年龄"),LVCFMT_LEFT,50);

	m_check = TEXT("男");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy10_ListControl练习Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy10_ListControl练习Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy10_ListControl练习Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy10_ListControl练习Dlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_check = TEXT("男");
}


void CMy10_ListControl练习Dlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_check = TEXT("女");
}


void CMy10_ListControl练习Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	static int i = 0;

	CString strName;

	m_people.GetLBText(m_people.GetCurSel(), strName);
	m_list.InsertItem(i, strName);
	int j = 1;
	m_list.SetItemText(i, j++, m_check);
	CString strNum;
	strNum.Format(TEXT("%d"), m_age);
	m_list.SetItemText(i++, j, strNum);
}


void CMy10_ListControl练习Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

		if (m_list.GetSelectedCount() > 0) {

		POSITION pos=	m_list.GetFirstSelectedItemPosition();

		while (pos)
		{
			int nSelected = m_list.GetNextSelectedItem(pos); //获取选中行的索引
			m_list.DeleteItem(nSelected); //根据索引删除
			pos = m_list.GetFirstSelectedItemPosition();
		}

		}

}
