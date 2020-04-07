
// 13_databaseView.cpp : CMy13_databaseView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "13_database.h"
#endif

#include "13_databaseDoc.h"
#include "13_databaseView.h"
#include"13_databaseSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy13_databaseView

IMPLEMENT_DYNCREATE(CMy13_databaseView, CFormView)

BEGIN_MESSAGE_MAP(CMy13_databaseView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy13_databaseView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy13_databaseView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy13_databaseView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy13_databaseView::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CMy13_databaseView::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMy13_databaseView::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMy13_databaseView::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON5, &CMy13_databaseView::OnBnClickedButton5)
END_MESSAGE_MAP()

// CMy13_databaseView 构造/析构

CMy13_databaseView::CMy13_databaseView()
	: CFormView(IDD_MY13_DATABASE_FORM)
	, m_uiId(0)
	, m_uiName(_T(""))
	, m_uiAge(0)
	, m_uiScore(0)
{
	// TODO: 在此处添加构造代码

}

CMy13_databaseView::~CMy13_databaseView()
{
}

void CMy13_databaseView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_uiId);
	DDX_Text(pDX, IDC_EDIT1, m_uiName);
	DDX_Text(pDX, IDC_EDIT3, m_uiAge);
	DDX_Text(pDX, IDC_EDIT4, m_uiScore);
}

BOOL CMy13_databaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CMy13_databaseView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CMy13_databaseDoc* pDoc = GetDocument();

	CMy13_databaseSet *pSet = pDoc->GetSet();

	if (pSet->IsOpen() == FALSE) {
		BOOL isOpen=pSet->Open(CRecordset::dynaset);
	}

}


// CMy13_databaseView 诊断

#ifdef _DEBUG
void CMy13_databaseView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy13_databaseView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy13_databaseDoc* CMy13_databaseView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy13_databaseDoc)));
	return (CMy13_databaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy13_databaseView 消息处理程序

//上一个
void CMy13_databaseView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CMy13_databaseDoc* pDoc = GetDocument();

	CMy13_databaseSet *pSet = pDoc->GetSet();

	//移动到上一个
	pSet->MovePrev();

	//头部的前一个
	if (pSet->IsBOF())
	{
		//尾部
		pSet->MoveLast();
	}
	m_uiId = pSet->m_id;
	m_uiName = pSet->m_userName;

	m_uiAge = pSet->m_userAge;
	m_uiScore = pSet->m_userScore;

	//MessageBox(m_uiName);

	UpdateData(FALSE);

}

//下一个
void CMy13_databaseView::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CMy13_databaseDoc* pDoc = GetDocument();

	CMy13_databaseSet *pSet = pDoc->GetSet();

	//移动到上一个
	pSet->MoveNext();

	//头部的前一个
	if (pSet->IsEOF())
	{
		//尾部
		pSet->MoveFirst();
	}
	m_uiId = pSet->m_id;
	m_uiName = pSet->m_userName;

	m_uiAge = pSet->m_userAge;
	m_uiScore = pSet->m_userScore;

	//MessageBox(m_uiName);

	UpdateData(FALSE);
}

//添加记录
void CMy13_databaseView::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CMy13_databaseDoc* pDoc = GetDocument();

	CMy13_databaseSet *pSet = pDoc->GetSet();
	
	//m_uiId = pSet->m_id;
	pSet->AddNew();

	  pSet->m_userName= m_uiName;

	 pSet->m_userAge= m_uiAge;
	 pSet->m_userScore= m_uiScore;
	 pSet->Update();
	 pSet->Requery();
	 m_uiName = TEXT("");
	 m_uiAge = 0;
	 m_uiScore = 0;
	 UpdateData(FALSE);

}


void CMy13_databaseView::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CMy13_databaseDoc* pDoc = GetDocument();

	CMy13_databaseSet *pSet = pDoc->GetSet();

	//TODO
	//先判断id是否存在
	pSet->Edit();
	pSet->m_userName = m_uiName;

	pSet->m_userAge = m_uiAge;
	pSet->m_userScore = m_uiScore;
	pSet->Update();
	pSet->Requery();
	m_uiName = TEXT("");
	m_uiAge = 0;
	m_uiScore = 0;
	UpdateData(FALSE);


}

//删除
void CMy13_databaseView::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CMy13_databaseDoc* pDoc = GetDocument();

	CMy13_databaseSet *pSet = pDoc->GetSet();

	if (pSet->IsEOF()) {
		MessageBox(TEXT("当前记录为空"));
		return;
	}

	pSet->Delete();
	if (pSet->IsEOF()) {
		pSet->MoveLast();
	}
	else {
		pSet->MoveNext();
		pSet->Requery();
		UpdateData(FALSE);

		MessageBox(TEXT("删除成功"));
	}

	OnBnClickedButton2();
}

//年龄大于50
void CMy13_databaseView::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sql = TEXT("userAge>50");
	CMy13_databaseDoc* pDoc = GetDocument();

	CMy13_databaseSet *pSet = pDoc->GetSet();

	pSet->m_strFilter = sql;
	pSet->Requery();
}


void CMy13_databaseView::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	CMy13_databaseDoc* pDoc = GetDocument();

	CMy13_databaseSet *pSet = pDoc->GetSet();
	
	pSet->m_strSort = TEXT("userAge desc");
	pSet->Requery();

}


void CMy13_databaseView::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CMy13_databaseDoc* pDoc = GetDocument();

	CMy13_databaseSet *pSet = pDoc->GetSet();

	pSet->m_strFilter = TEXT("1=1");
	pSet->Requery();
}
