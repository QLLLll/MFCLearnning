
// 06_timerView.cpp : CMy06_timerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "06_timer.h"
#endif

#include "06_timerDoc.h"
#include "06_timerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy06_timerView

IMPLEMENT_DYNCREATE(CMy06_timerView, CView)

BEGIN_MESSAGE_MAP(CMy06_timerView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMy06_timerView 构造/析构

CMy06_timerView::CMy06_timerView()
{
	// TODO: 在此处添加构造代码

}

CMy06_timerView::~CMy06_timerView()
{
}

BOOL CMy06_timerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy06_timerView 绘制

void CMy06_timerView::OnDraw(CDC* /*pDC*/)
{
	CMy06_timerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMy06_timerView 打印

BOOL CMy06_timerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy06_timerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy06_timerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy06_timerView 诊断

#ifdef _DEBUG
void CMy06_timerView::AssertValid() const
{
	CView::AssertValid();
}

void CMy06_timerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy06_timerDoc* CMy06_timerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy06_timerDoc)));
	return (CMy06_timerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy06_timerView 消息处理程序


int CMy06_timerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	SetTimer(1, 500, NULL);

	return 0;
}


void CMy06_timerView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static int w = 0;
	int imgW = 100, imgH = 100;
	if (nIDEvent == 1) {

		CClientDC dc(this);
		COLORREF  bkColor = dc.GetBkColor();
		CBrush *brush2 = new CBrush(bkColor);

		//获得客户区宽度
		CRect rec;
		GetClientRect(&rec);
		int wWith = rec.Width();

		int x = 10, y = 10;

		COLORREF color1 = RGB(255, 0, 0);
		COLORREF color2 = RGB(100, 0, 0);
		COLORREF color3 = RGB(200, 110, 0);
		COLORREF color4 = RGB(100, 100, 100);

		RectMove(dc, brush2, 10, 10, imgW, wWith, w1,color1);
		RectMove(dc, brush2, 40, 120, imgW, wWith, w2,color2);
		RectMove(dc, brush2, 70, 240, imgW, wWith, w3, color3);
		RectMove(dc, brush2, 100, 360, imgW, wWith, w4, color4);


	}


	CView::OnTimer(nIDEvent);
}

void CMy06_timerView::RectMove(CClientDC & dc, CBrush * brush2, int x, int y, int step,int wWith,int& w,COLORREF color)
{
	CBrush *brush = new CBrush(color);
	dc.SelectObject(brush);
	dc.Rectangle(x + w, y, x + step + w, y + imgH);


	dc.SelectObject(brush2);
	if (w != 0)
		dc.FillRect(new CRect(x + w - step, y, x + w, y + imgH), brush2);

	w += step;
	if (w > wWith) {
		dc.FillRect(new CRect(x + w - step, y, x + w, y + imgH), brush2);
		w = 0;
	}
}
