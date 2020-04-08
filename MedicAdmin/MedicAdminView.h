
// MedicAdminView.h : CMedicAdminView 类的接口
//

#pragma once


class CMedicAdminView : public CFormView
{
protected: // 仅从序列化创建
	CMedicAdminView();
	DECLARE_DYNCREATE(CMedicAdminView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MEDICADMIN_FORM };
#endif

// 特性
public:
	CMedicAdminDoc* GetDocument() const;

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
	virtual ~CMedicAdminView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MedicAdminView.cpp 中的调试版本
inline CMedicAdminDoc* CMedicAdminView::GetDocument() const
   { return reinterpret_cast<CMedicAdminDoc*>(m_pDocument); }
#endif

