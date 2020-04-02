
// 06_timerView.h : CMy06_timerView 类的接口
//

#pragma once


class CMy06_timerView : public CView
{
protected: // 仅从序列化创建
	CMy06_timerView();
	DECLARE_DYNCREATE(CMy06_timerView)

// 特性
public:
	CMy06_timerDoc* GetDocument() const;

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
	virtual ~CMy06_timerView();
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	int w1=0;
	int w2=0;
	int w3=0;
	int w4=0;
	int imgW=100;
	int imgH = 100;
	void RectMove(CClientDC& dc, CBrush *brush2, int x, int y, int step,int wWith,int& w, COLORREF color);
};

#ifndef _DEBUG  // 06_timerView.cpp 中的调试版本
inline CMy06_timerDoc* CMy06_timerView::GetDocument() const
   { return reinterpret_cast<CMy06_timerDoc*>(m_pDocument); }
#endif

