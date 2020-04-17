
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "LearningFlyBird.h"
#include"Resource.h"

#include "MainFrm.h"
#define PI 3.1415926

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
	for (int i = 0; i < 1; i++)
	{
		Pipe temp;
		pipes.AddHead(temp);
	}
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

	bird[0][0].LoadBitmap(IDB_BITMAP2);
	bird[0][1].LoadBitmap(IDB_BITMAP3);
	bird[0][2].LoadBitmap(IDB_BITMAP4);
	bird[1][0].LoadBitmap(IDB_BITMAP5);
	bird[1][1].LoadBitmap(IDB_BITMAP6);
	bird[1][2].LoadBitmap(IDB_BITMAP7);
	bird[2][0].LoadBitmap(IDB_BITMAP8);
	bird[2][1].LoadBitmap(IDB_BITMAP9);
	bird[2][2].LoadBitmap(IDB_BITMAP10);

	SetTimer(1, 60, NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
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
	static int x, y, dis_state = 2;;
	static double Time = 0;
	static int fly_state = 0;
	x = (x + 4) % 51;
	bg_state = 0;
	m_bgcDC.SelectObject(&m_bgBitmap);
	//pic.bg[bg_state].TBlt(0, 0, &m_cacheDC, &m_bgcDC);//背景
	pic.bg[bg_state].TBlt(0, 0, &m_cacheDC, &m_bgcDC);//背景
	//pipe.draw(pic, &m_cacheDC, &m_bgcDC);//所有柱子
	//land.draw(pic, &m_cacheDC, &m_bgcDC);//道路
	//bird.paint(&m_cacheDC, &m_tempcDC);
	//pic.pipe2_up.TBlt(0, 0, &m_cacheDC, &m_bgcDC);

	m_cacheDC.TransparentBlt(0, 400, 288, pic.land.y, &m_bgcDC, pic.land.pos_x * 1024 + x, pic.land.pos_y * 1024, 288, pic.land.y, RGB(0, 0, 0));

	m_tempcDC.SelectObject(&bird[0][fly_state]);
	m_cacheDC.TransparentBlt(65, 230 + y, 48, 48, &m_tempcDC, 9.936, 9.936 + dis_state * 48, 48, 48, RGB(0, 0, 0));

	y = 4 * sin(Time*PI);
	Time += 0.25;
	fly_state = (fly_state + 1) % 3;
	int copy = goals, wei = 1;//显示分数
	int this_wei, first_pos = 142 - 12 * wei - wei / 2;
	pic.font[0].TBlt(first_pos + wei * 25, 60, &m_cacheDC, &m_bgcDC);//分数



	//pic.text_ready.TBlt(50, 140, &m_cacheDC, &m_bgcDC);//ready图标
	//pic.tutorial.TBlt(85, 220, &m_cacheDC, &m_bgcDC);//指示pic.font[this_wei].TBlt(first_pos+wei*25,60,&m_cacheDC,&m_bgcDC);//分数



	//pic.text_ready.TBlt(50, 140, &m_cacheDC, &m_bgcDC);//ready图标
	//pic.tutorial.TBlt(85, 220, &m_cacheDC, &m_bgcDC);//指示


	piepeMove(pic, &m_cacheDC, &m_bgcDC);


	m_cacheDC.SelectObject(&m_tempBitmap);
	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_cacheDC, 0, 0, SRCCOPY);

	ReleaseDC(cDC);
	CFrameWnd::OnTimer(nID);
}

void CMainFrame::piepeMove(Pic &All, CDC* To, CDC* From) {//绘制函数
	int count = pipes.GetCount();
	for (int i = 0; i<count; i++) {
		Pipe temp = pipes.GetHead();
		pipes.RemoveHead();
		temp.logic();
		

		if (temp.pos_x < -60) {
			temp.pos_x = 300;
		}

		pipes.AddTail(temp);
		All.pipe_down.TBlt(temp.pos_x, temp.pos_y, To, From);//上柱子
		All.pipe_up.TBlt(temp.pos_x, temp.pos_y + 420, To, From);//下柱子
	}
}
