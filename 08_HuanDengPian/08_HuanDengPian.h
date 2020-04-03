
// 08_HuanDengPian.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CMy08_HuanDengPianApp: 
// 有关此类的实现，请参阅 08_HuanDengPian.cpp
//

class CMy08_HuanDengPianApp : public CWinApp
{
public:
	CMy08_HuanDengPianApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMy08_HuanDengPianApp theApp;