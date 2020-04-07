
// 12_FormViewView.h : CMy12_FormViewView 类的接口
//

#pragma once
#include "afxwin.h"


class CMy12_FormViewView : public CFormView
{
protected: // 仅从序列化创建
	CMy12_FormViewView();
	DECLARE_DYNCREATE(CMy12_FormViewView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MY12_FORMVIEW_FORM };
#endif

// 特性
public:
	CMy12_FormViewDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CMy12_FormViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
private:
	CButton m_buttonPre;
	CButton m_buttonNext;
	CString m_xuehao;
	CString m_xm;
	int m_age;
	double m_cj;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedRadio1();
private:
	CButton m_buttonAdd;
public:
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};

#ifndef _DEBUG  // 12_FormViewView.cpp 中的调试版本
inline CMy12_FormViewDoc* CMy12_FormViewView::GetDocument() const
   { return reinterpret_cast<CMy12_FormViewDoc*>(m_pDocument); }
#endif

