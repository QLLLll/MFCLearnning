
// 13_databaseView.h : CMy13_databaseView 类的接口
//

#pragma once


class CMy13_databaseView : public CFormView
{
protected: // 仅从序列化创建
	CMy13_databaseView();
	DECLARE_DYNCREATE(CMy13_databaseView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MY13_DATABASE_FORM };
#endif

// 特性
public:
	CMy13_databaseDoc* GetDocument() const;

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
	virtual ~CMy13_databaseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
private:
	int m_uiId;
	CString m_uiName;
	int m_uiAge;
	float m_uiScore;
public:
	afx_msg void OnBnClickedButton1();
};

#ifndef _DEBUG  // 13_databaseView.cpp 中的调试版本
inline CMy13_databaseDoc* CMy13_databaseView::GetDocument() const
   { return reinterpret_cast<CMy13_databaseDoc*>(m_pDocument); }
#endif

