
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "LearningFlyBird.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 创建一个视图以占用框架的工作区
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("未能创建视图窗口\n");
		return -1;
	}
	CRect rect(0, 0, 286, 512);       //理想客户区窗口矩形形状
	CalcWindowRect(&rect);            //根据分辨率、菜单...计算窗口矩形大小（必须在窗口创建后调用）

	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(),
		SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW);

	CDC *cDC = this->GetDC();
	GetClientRect(&m_client);   //获得窗口的尺寸
	m_cacheDC.CreateCompatibleDC(cDC);
	m_bgcDC.CreateCompatibleDC(cDC);
	m_tempcDC.CreateCompatibleDC(cDC);
	m_tempBitmap.CreateCompatibleBitmap(cDC, m_client.Width(), m_client.Height());
	m_bgBitmap.LoadBitmap(IDB_BITMAP1);
	m_cacheDC.SelectObject(&m_tempBitmap);
	ReleaseDC(cDC);

	SetTimer(1, 60, NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
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

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 将焦点前移到视图窗口
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 让视图第一次尝试该命令
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 否则，执行默认处理
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CMainFrame::OnTimer(UINT_PTR nID)
{
	CDC *cDC = this->GetDC();//获得当前窗口的DC   
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static int x;
	x = (x + 4) % 51;
		bg_state = 0;
		m_bgcDC.SelectObject(&m_bgBitmap);
		//pic.bg[bg_state].TBlt(0, 0, &m_cacheDC, &m_bgcDC);//背景
		pic.bg[bg_state].TBlt(0, 0, &m_cacheDC, &m_bgcDC);//背景
		//pipe.draw(pic, &m_cacheDC, &m_bgcDC);//所有柱子
		//land.draw(pic, &m_cacheDC, &m_bgcDC);//道路
		//bird.paint(&m_cacheDC, &m_tempcDC);
		pic.pipe2_up.TBlt(0, 0, &m_cacheDC, &m_bgcDC);
		m_cacheDC.TransparentBlt(0, 400, 288, pic.land.y, &m_bgcDC, pic.land.pos_x * 1024 + x, pic.land.pos_y * 1024, 288, pic.land.y, RGB(0, 0, 0));
	m_cacheDC.SelectObject(&m_tempBitmap);
	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_cacheDC, 0, 0, SRCCOPY);

	ReleaseDC(cDC);
	CFrameWnd::OnTimer(nID);
}
