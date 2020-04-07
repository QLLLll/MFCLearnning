
// 11_documentView.h : CMy11_documentView 类的接口
//

#pragma once


class CMy11_documentView : public CView
{
protected: // 仅从序列化创建
	CMy11_documentView();
	DECLARE_DYNCREATE(CMy11_documentView)

// 特性
public:
	CMy11_documentDoc* GetDocument() const;

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
	virtual ~CMy11_documentView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 11_documentView.cpp 中的调试版本
inline CMy11_documentDoc* CMy11_documentView::GetDocument() const
   { return reinterpret_cast<CMy11_documentDoc*>(m_pDocument); }
#endif

