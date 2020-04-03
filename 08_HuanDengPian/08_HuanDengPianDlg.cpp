
// 08_HuanDengPianDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "08_HuanDengPian.h"
#include "08_HuanDengPianDlg.h"
#include "afxdialogex.h"
#include"resource.h"
#define HBMP(filepath,width,height) (HBITMAP)LoadImage(AfxGetInstanceHandle(),filepath,IMAGE_BITMAP,width,height,LR_LOADFROMFILE|LR_CREATEDIBSECTION)
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


// CMy08_HuanDengPianDlg 对话框



CMy08_HuanDengPianDlg::CMy08_HuanDengPianDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY08_HUANDENGPIAN_DIALOG, pParent)
	, m_w(0)
	, m_h(0)
	, m_isAuto(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy08_HuanDengPianDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BMP, m_image);
	DDX_Control(pDX, IDC_BUTTON2, m_preImg);
	DDX_Control(pDX, IDC_BUTTON3, m_nextImg);
	DDX_Control(pDX, IDC_BUTTON1, m_autoImg);
}

BEGIN_MESSAGE_MAP(CMy08_HuanDengPianDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy08_HuanDengPianDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMy08_HuanDengPianDlg 消息处理程序

BOOL CMy08_HuanDengPianDlg::OnInitDialog()
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

	m_image.ModifyStyle(0xf,SS_BITMAP | SS_CENTERIMAGE);

	CRect rect;
	
	m_image.GetWindowRect(&rect);

	m_w = rect.Width();
	m_h = rect.Height();

	m_image.SetBitmap(HBMP(TEXT("../image/1.bmp"), m_w, m_h));

	m_isAuto = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy08_HuanDengPianDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy08_HuanDengPianDlg::OnPaint()
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
HCURSOR CMy08_HuanDengPianDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy08_HuanDengPianDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


void CMy08_HuanDengPianDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_isAuto = !m_isAuto;

	if (m_isAuto) {

		SetTimer(1, 1200, NULL);

		
		m_preImg.EnableWindow(FALSE);
		m_nextImg.EnableWindow(FALSE);
	}
	else {
		
		m_preImg.EnableWindow(TRUE);
		m_nextImg.EnableWindow(TRUE);
		KillTimer(1);
	}

}


void CMy08_HuanDengPianDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	static int i = 1;

	if (nIDEvent == 1) {

		i++;

		if (i > 24) {
			i = 1;
		}
		CString str;
		str.Format(TEXT("../image/%d.bmp"), i);

			m_image.SetBitmap(HBMP(str, m_w, m_h));
	}


	CDialogEx::OnTimer(nIDEvent);
}
