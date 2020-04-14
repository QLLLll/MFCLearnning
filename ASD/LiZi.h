#pragma once
#include "resource.h"
#include "Pic.h"
#include "PipeList.h"
#include "Land.h"
#include "Bird.h"
#include "Panel.h"
#include "Button.h"
#include <afxwin.h>
#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )



class CMyApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
};


class CMainWindow:public CFrameWnd
{
public:
	int bg_state,game_state,last_state;//背景切换2，游戏状态,最后gameover状态

	int goals,best_goals;//分数

	CRect m_client;
	CBitmap m_bgBitmap,m_tempBitmap;
	CDC m_cacheDC;   //缓冲DC  
	CDC m_bgcDC,m_tempcDC;

	Pic pic;//所有图片
	PipeList pipe;//柱子
	Land land;//路
	Bird bird;//鸟
	Panel panel;//计分板
    Button button;//按钮
public:
	CMainWindow ();
	
	void draw();
	void restart();
	void screenShot(CRect rect,int left,int top,char *name);
protected:
	afx_msg int  OnCreate (LPCREATESTRUCT lpcs);      
    afx_msg void OnTimer (UINT nTimerID);              
    afx_msg void OnClose ();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP();
	
};

