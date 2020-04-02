
// 07_menuView.h : CMy07_menuView 类的接口
//

#pragma once


class CMy07_menuView : public CView
{
protected: // 仅从序列化创建
	CMy07_menuView();
	DECLARE_DYNCREATE(CMy07_menuView)

// 特性
public:
	CMy07_menuDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy07_menuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 07_menuView.cpp 中的调试版本
inline CMy07_menuDoc* CMy07_menuView::GetDocument() const
   { return reinterpret_cast<CMy07_menuDoc*>(m_pDocument); }
#endif

