
// ForTreeCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ForTreeCtrl.h"
#include "ForTreeCtrlDlg.h"
#include "afxdialogex.h"
#include<vector>
using namespace std;

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


// CForTreeCtrlDlg 对话框



CForTreeCtrlDlg::CForTreeCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FORTREECTRL_DIALOG, pParent)
	, m_find(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CForTreeCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, treeCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_find);
}

BEGIN_MESSAGE_MAP(CForTreeCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CForTreeCtrlDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CForTreeCtrlDlg 消息处理程序

BOOL CForTreeCtrlDlg::OnInitDialog()
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
	CString root[2] = { TEXT("A"),TEXT("B") };

	for (int i=0;i<2;i++)
	{
		HTREEITEM r =treeCtrl.InsertItem(root[i], NULL);

		CString str;
		for (int j=0;j<3;j++)
		{
			str.Format(TEXT("%s%d"),root[i], j + 1);
			HTREEITEM j1 = treeCtrl.InsertItem(str, r);

			CString str1;
			for (int m = 0; m < 3; m++) {

				str1.Format(TEXT("%s%d%d"),  root[i], j + 1,m+1);
				HTREEITEM m1 = treeCtrl.InsertItem(str1, j1);

				CString str2;
				for (int q = 0; q < 3; q++) {

					str2.Format(TEXT("%s%d%d%d"), root[i], j + 1, m + 1,q+1);
					HTREEITEM q1 = treeCtrl.InsertItem(str2, m1);

					CString str3;
					for (int s = 0; s < 3; s++) {

						str3.Format(TEXT("%s%d%d%d%d"), root[i], j + 1, m + 1, q + 1,s+1);
						HTREEITEM s1 = treeCtrl.InsertItem(str3, q1);

					}

				}

			}
		}

	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CForTreeCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CForTreeCtrlDlg::OnPaint()
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
HCURSOR CForTreeCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CForTreeCtrlDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	vector<HTREEITEM>vecItem;
	HTREEITEM root = treeCtrl.GetRootItem();
	//第一层根节点
	while (root != NULL) {

		vecItem.push_back(root);
		root = treeCtrl.GetNextItem(root, TVGN_NEXT);
	}
	for (int q = (int)vecItem.size() - 1; q > -1; q--) {
		func(vecItem[q], m_find);
	}

}
void CForTreeCtrlDlg::func(HTREEITEM root,CString condition) {
	
	CString itemText = treeCtrl.GetItemText(root);

	if (itemText.Find(condition) != -1) {

		treeCtrl.SelectItem(root);
		treeCtrl.SetCheck(root, TRUE);
		treeCtrl.Expand(root, TVM_EXPAND);
		
		return;

	}
	//根节点的儿子节点
	HTREEITEM A1 = treeCtrl.GetChildItem(root);

	//儿子节点的兄弟节点
	vector<HTREEITEM>vecItem;

	while (A1 != NULL) {

		vecItem.push_back(A1);
		A1 = treeCtrl.GetNextItem(A1, TVGN_NEXT);
	}

	for (int q = (int)vecItem.size() - 1; q > -1; q--) {

		CString itemText = treeCtrl.GetItemText(vecItem[q]);

		if (itemText.Find(condition) != -1) {

			treeCtrl.SelectItem(vecItem[q]);
			treeCtrl.SetCheck(vecItem[q], TRUE);
			treeCtrl.Expand(vecItem[q], TVM_EXPAND);
			vecItem.clear();
			return;

		}
		else {
			//递归，儿子节点当作根节点遍历
			func(vecItem[q], condition);
		}

	}


}
