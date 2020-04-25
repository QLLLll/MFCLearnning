
// QQMsgBoomDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQMsgBoom.h"
#include "QQMsgBoomDlg.h"
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


// CQQMsgBoomDlg 对话框



CQQMsgBoomDlg::CQQMsgBoomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_QQMSGBOOM_DIALOG, pParent)
	, m_boom_filePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQQMsgBoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CQQMsgBoomDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CQQMsgBoomDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CQQMsgBoomDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CQQMsgBoomDlg 消息处理程序

BOOL CQQMsgBoomDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQQMsgBoomDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CQQMsgBoomDlg::OnPaint()
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
HCURSOR CQQMsgBoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//打开文件
void CQQMsgBoomDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fDiaLog(TRUE, TEXT("*.txt"), NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("txt Files (*.txt)|*.txt|All Files (*.*)|*.*||"), NULL);

	if (fDiaLog.DoModal() == IDOK) {
		m_boom_filePath = fDiaLog.GetPathName();
		SetDlgItemText(IDC_BOOM_FILE, m_boom_filePath);
	}
}

void CQQMsgBoomDlg::OnBnClickedButton3()
{
	vector<CString> boomStr;
	boomStr.clear();
	boomStr.shrink_to_fit();

	CString qqNick;
	GetDlgItemText(IDC_QQ_NICK, qqNick);
	
	if (qqNick.IsEmpty()||m_boom_filePath.IsEmpty()) {
		AfxMessageBox(TEXT("qq昵称和文件路径不能为空"));
		return;
	}

	CString temp;
	GetDlgItemText(IDC_BOOM_TIMES, temp);//得到需要设置轰炸次数的字符串

	int times = _ttoi(temp);
	if (times <= 0) {
		return;
	}

	CString tempCString;
	CStdioFile filein;//声明文件操作对象
	if (filein.Open(m_boom_filePath, CFile::modeRead))//逐行读取boom文件中内容
	{
		while (filein.ReadString(tempCString))
		{
			boomStr.push_back(tempCString);//逐行压入m_BoomString容器中
		}
	}

	HWND hHandle = ::FindWindow(TEXT("TXGuiFoundation"), qqNick);//找到当前QQ窗口的句柄
	if (!hHandle) {
		AfxMessageBox(L"未找到窗口");
		return;
	}
	
	::ShowWindow(hHandle, 1);//显示窗口
	::SetForegroundWindow(hHandle);//将得到的窗口设置到前台并激活窗口
	
	for (int j = 0; j < times; ++j)
	{
		CString source;
		char * s = NULL;
		
		for (int i = 0; i < (int)boomStr.size(); ++i)
		{
			
			source = boomStr[i];
			if (s != NULL) {
				delete[] s;
				s = NULL;
			}

			int n = source.GetLength();
			
				//获取宽字节字符的大小，大小是按字节计算的
			 int len = WideCharToMultiByte(CP_ACP, 0, source, source.GetLength(), NULL, 0, NULL, NULL);
			
				 //为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小
				 s= new char[len + 1];   //以字节为单位
				 
				 WideCharToMultiByte(CP_ACP, 0, source, -1, s, len + 1, NULL, NULL);
				 
				 s[len] = '\0';
				
			if (OpenClipboard())//打开剪切板
			{
				
				 
				//TCHAR * buffer;//定义指向字符型的指针变量
				char* buffer;
				//定义一个HGLOBAL句柄变量用来指向分配的内存块
				HGLOBAL clipbuffer = GlobalAlloc(GHND, len+1);
				//在堆上分配可移动的内存块，程序返回一个内存句柄
				
				buffer = (char*)GlobalLock(clipbuffer);  //对分配的内存块进行加锁，将内存块句柄转化成一个指针,并将相应的引用计数器加1
								
				strcpy_s(buffer,len+1, s);  //将用户输入的数据复制到指针变量中，实际上就是复制到分配的内存块中
				
				BOOL flag=GlobalUnlock(clipbuffer);//数据写入完毕，进行解锁操作，并将引用计数器数字减1
				
				EmptyClipboard();//清空剪贴板 
				SetClipboardData(CF_TEXT, clipbuffer); //将存放有数据的内存块放入剪贴板的资源管理中
				CloseClipboard();    //关闭剪贴板，释放剪贴板资源的占用权
				
				::SendMessage(hHandle, WM_PASTE, 0, 0);//模拟粘贴操作
				Sleep(1000);
				::SendMessage(hHandle, WM_KEYDOWN, VK_RETURN, 0);//模拟回车按键操作，类似于点击了发送				
			}
		}
	}
}
