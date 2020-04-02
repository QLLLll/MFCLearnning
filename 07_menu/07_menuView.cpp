
// 07_menuView.cpp : CMy07_menuView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "07_menu.h"
#endif

#include "07_menuDoc.h"
#include "07_menuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy07_menuView

IMPLEMENT_DYNCREATE(CMy07_menuView, CView)

BEGIN_MESSAGE_MAP(CMy07_menuView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMy07_menuView 构造/析构

CMy07_menuView::CMy07_menuView()
{
	// TODO: 在此处添加构造代码

}

CMy07_menuView::~CMy07_menuView()
{
}

BOOL CMy07_menuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy07_menuView 绘制

void CMy07_menuView::OnDraw(CDC* /*pDC*/)
{
	CMy07_menuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMy07_menuView 打印

BOOL CMy07_menuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy07_menuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy07_menuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy07_menuView 诊断

#ifdef _DEBUG
void CMy07_menuView::AssertValid() const
{
	CView::AssertValid();
}

void CMy07_menuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy07_menuDoc* CMy07_menuView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy07_menuDoc)));
	return (CMy07_menuDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy07_menuView 消息处理程序


int CMy07_menuView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CMy07_menuView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	//这里不能用getMenu()因为它将获得的菜单是属于Frame的，而我们操作的区域是在View上，
	//所以要在View上加载一个菜单。


	CMenu menu;

	menu.LoadMenuW(IDR_MAINFRAME);

	CMenu *subMenu = menu.GetSubMenu(0);

	ClientToScreen(&point);

	subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON,
		point.x, point.y, this);

	CView::OnLButtonDown(nFlags, point);
}
