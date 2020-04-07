
// 12_FormViewView.cpp : CMy12_FormViewView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "12_FormView.h"
#endif

#include "12_FormViewDoc.h"
#include "12_FormViewView.h"
#include"Student.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy12_FormViewView

IMPLEMENT_DYNCREATE(CMy12_FormViewView, CFormView)

BEGIN_MESSAGE_MAP(CMy12_FormViewView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy12_FormViewView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_RADIO1, &CMy12_FormViewView::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMy12_FormViewView::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy12_FormViewView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy12_FormViewView::OnBnClickedButton2)
END_MESSAGE_MAP()

// CMy12_FormViewView 构造/析构

CMy12_FormViewView::CMy12_FormViewView()
	: CFormView(IDD_MY12_FORMVIEW_FORM)
	, m_xuehao(_T(""))
	, m_xm(_T(""))
	, m_age(0)
	, m_cj(0)
{
	// TODO: 在此处添加构造代码

}

CMy12_FormViewView::~CMy12_FormViewView()
{
}

void CMy12_FormViewView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_buttonPre);
	DDX_Control(pDX, IDC_BUTTON2, m_buttonNext);
	DDX_Text(pDX, IDC_EDIT1, m_xuehao);
	DDX_Text(pDX, IDC_EDIT4, m_xm);
	DDX_Text(pDX, IDC_EDIT3, m_age);
	DDX_Text(pDX, IDC_EDIT2, m_cj);
	DDX_Control(pDX, IDC_BUTTON3, m_buttonAdd);
}

BOOL CMy12_FormViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CMy12_FormViewView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);

	m_buttonPre.EnableWindow(FALSE);
	m_buttonNext.EnableWindow(FALSE);
	m_buttonAdd.EnableWindow(TRUE);

	m_age = 0;
	m_xuehao = TEXT("");
	m_cj = 0.0;
	m_xm = TEXT("");
	UpdateData(FALSE);

}


// CMy12_FormViewView 诊断

#ifdef _DEBUG
void CMy12_FormViewView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy12_FormViewView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy12_FormViewDoc* CMy12_FormViewView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy12_FormViewDoc)));
	return (CMy12_FormViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy12_FormViewView 消息处理程序

//添加修改
void CMy12_FormViewView::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CMy12_FormViewDoc* pDoc = GetDocument();

	UpdateData(true);

	CStudent stu;



	stu.m_xuehao = m_xuehao;
	stu.m_xm = m_xm;
	stu.m_age = m_age;
	stu.m_cj = m_cj;

	pDoc->m_list.AddTail(stu);

	pDoc->m_pos = pDoc->m_list.GetTailPosition();

	m_xuehao = TEXT("");
	m_xm = TEXT("");
	m_age = 0;
	m_cj = 0.0;
	UpdateData(FALSE);
}


void CMy12_FormViewView::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_buttonAdd.EnableWindow(TRUE);
}


void CMy12_FormViewView::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_buttonPre.EnableWindow(TRUE);
	m_buttonNext.EnableWindow(TRUE);
	m_buttonAdd.EnableWindow(FALSE);
}


void CMy12_FormViewView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CMy12_FormViewDoc* pDoc = GetDocument();

	if (pDoc->m_list.GetTailPosition() == NULL) {
		return;
	}


	if (pDoc->m_pos < pDoc->m_list.GetHeadPosition()|| pDoc->m_pos == NULL) {

		pDoc->m_pos = pDoc->m_list.GetTailPosition();

	}

	CStudent stu = pDoc->m_list.GetPrev(pDoc->m_pos);

	m_age = stu.m_age;
	m_xuehao = stu.m_xuehao;
	m_cj = stu.m_cj;
	m_xm = stu.m_xm;

	UpdateData(FALSE);

}


void CMy12_FormViewView::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CMy12_FormViewDoc* pDoc = GetDocument();

	if (pDoc->m_list.GetHeadPosition() == NULL) {
		return;
	}

	if (pDoc->m_pos > pDoc->m_list.GetTailPosition()||pDoc->m_pos==NULL) {

		pDoc->m_pos = pDoc->m_list.GetHeadPosition();

	}

	CStudent stu = pDoc->m_list.GetNext(pDoc->m_pos);

	m_age = stu.m_age;
	m_xuehao = stu.m_xuehao;
	m_cj = stu.m_cj;
	m_xm = stu.m_xm;

	UpdateData(FALSE);
}
