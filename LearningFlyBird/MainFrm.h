
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include"stdafx.h"
#include <afxwin.h>
#include"Pic.h"
#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 特性
public:
	int bg_state, game_state, last_state;//背景切换2，游戏状态,最后gameover状态

	int goals, best_goals;//分数

	CRect m_client;
	CBitmap m_bgBitmap, m_tempBitmap;
	CDC m_cacheDC;   //缓冲DC  
	CDC m_bgcDC, m_tempcDC;

	Pic pic;//所有图片
// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CChildView    m_wndView;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	CBitmap bird[3][3];

};


