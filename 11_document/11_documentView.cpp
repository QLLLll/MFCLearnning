
// 11_documentView.cpp : CMy11_documentView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "11_document.h"
#endif

#include "11_documentDoc.h"
#include "11_documentView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy11_documentView

IMPLEMENT_DYNCREATE(CMy11_documentView, CView)

BEGIN_MESSAGE_MAP(CMy11_documentView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMy11_documentView 构造/析构

CMy11_documentView::CMy11_documentView()
{
	// TODO: 在此处添加构造代码

}

CMy11_documentView::~CMy11_documentView()
{
}

BOOL CMy11_documentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy11_documentView 绘制

void CMy11_documentView::OnDraw(CDC* pDC)
{
	CMy11_documentDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	
	for (int i = 0; i < pDoc->m_num; i++)
	{
		CPoint pt = pDoc->m_point[i];

		pDC->Ellipse(pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);
	}

}


// CMy11_documentView 打印

BOOL CMy11_documentView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy11_documentView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy11_documentView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy11_documentView 诊断

#ifdef _DEBUG
void CMy11_documentView::AssertValid() const
{
	CView::AssertValid();
}

void CMy11_documentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy11_documentDoc* CMy11_documentView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy11_documentDoc)));
	return (CMy11_documentDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy11_documentView 消息处理程序


void CMy11_documentView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CMy11_documentDoc* pDoc = GetDocument();

	if (pDoc->m_num > 199) {
		pDoc->m_num = 200;
		return;
	}

	pDoc->m_point[pDoc->m_num++] = point;

	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}
