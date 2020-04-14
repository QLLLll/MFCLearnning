#pragma once
#include "Pic.h"
#include "resource.h"
#include <afxwin.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib" )

#define play	0
#define score	1
#define none	2

class Button
{
public:
	int kind;//种类
	int play_y,score_y;//位置
	bool move;//晃动按钮标记
public:
	Button();
	void click(CPoint &point);
	void logic(int &game_state);
	void draw(Pic &All,CDC* To,CDC* From);
	BOOL LoadFromResource(UINT nRes);//加载HTML资源
};

