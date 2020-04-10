
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "MedicAdmin.h"

#include "MainFrm.h"
#include"UserLogin.h"
#include"UserDelete.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CString G_LoginName = TEXT("");
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_32776, &CMainFrame::On32776)
	ON_COMMAND(ID_32774, &CMainFrame::On32774)
	ON_COMMAND(ID_32778, &CMainFrame::OnExit)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	SetMenu(NULL);

	CMenu menu;
	menu.LoadMenuW(IDR_MENU1);
	
	SetMenu(&menu);
	menu.Detach();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	

	



	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	CUserLogin userLogin;
	userLogin.DoModal();
	G_LoginName = userLogin.GetLoginUserName();


	m_sWnd.CreateStatic(this,1,2, WS_CHILD | WS_VISIBLE, AFX_IDW_PANE_FIRST);
	m_sWnd.CreateView(0, 0, RUNTIME_CLASS(CUserTreeView), CSize(230, 600), pContext);
	m_sWnd.CreateView(0, 1, RUNTIME_CLASS(CMedicListView), CSize(720, 600), pContext);


	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::On32776()
{
	// TODO: 在此添加命令处理程序代码
	CUserDelete deleteDialog;

	deleteDialog.DoModal();
}

//更换用户
void CMainFrame::On32774()
{
	// TODO: 在此添加命令处理程序代码
	//程序重启
	wchar_t pBuf[MAX_PATH];
	//获取应用程序完全路径，比 GetCurrentDirectory 好用多了
	GetModuleFileName(NULL, pBuf, MAX_PATH);

	STARTUPINFO startupinfo;
	PROCESS_INFORMATION proc_info;
	memset(&startupinfo, 0, sizeof(STARTUPINFO));
	startupinfo.cb = sizeof(STARTUPINFO);
	// 最重要的地方
	::CreateProcess(pBuf, NULL, NULL, NULL, FALSE,
		NORMAL_PRIORITY_CLASS, NULL, NULL, &startupinfo, &proc_info);

	PostMessage(WM_QUIT);
}

//退出系统
void CMainFrame::OnExit()
{
	// TODO: 在此添加命令处理程序代码
	PostMessage(WM_QUIT);
}
