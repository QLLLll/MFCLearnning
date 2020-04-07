
// 12_FormView.h : 12_FormView 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMy12_FormViewApp:
// 有关此类的实现，请参阅 12_FormView.cpp
//

class CMy12_FormViewApp : public CWinApp
{
public:
	CMy12_FormViewApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy12_FormViewApp theApp;
