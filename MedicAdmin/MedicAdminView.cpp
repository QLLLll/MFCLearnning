
// MedicAdminView.cpp : CMedicAdminView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MedicAdmin.h"
#endif

#include "MedicAdminDoc.h"
#include "MedicAdminView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMedicAdminView

IMPLEMENT_DYNCREATE(CMedicAdminView, CFormView)

BEGIN_MESSAGE_MAP(CMedicAdminView, CFormView)
END_MESSAGE_MAP()

// CMedicAdminView 构造/析构

CMedicAdminView::CMedicAdminView()
	: CFormView(IDD_MEDICADMIN_FORM)
{
	// TODO: 在此处添加构造代码

}

CMedicAdminView::~CMedicAdminView()
{
}

void CMedicAdminView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMedicAdminView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CMedicAdminView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CMedicAdminView 诊断

#ifdef _DEBUG
void CMedicAdminView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMedicAdminView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMedicAdminDoc* CMedicAdminView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMedicAdminDoc)));
	return (CMedicAdminDoc*)m_pDocument;
}
#endif //_DEBUG


// CMedicAdminView 消息处理程序
