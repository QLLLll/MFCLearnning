// MyButton.cpp : 实现文件
//

#include "stdafx.h"
#include "09_逃跑的按钮.h"
#include "MyButton.h"


// MyButton

IMPLEMENT_DYNAMIC(MyButton, CButton)

MyButton::MyButton()
{

}

MyButton::~MyButton()
{
}


BEGIN_MESSAGE_MAP(MyButton, CButton)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// MyButton 消息处理程序




void MyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int x = rand() % (m_w-100);

	int y = rand() % (m_h-100);

	CPoint pt(x, y);

	this->MoveWindow(pt.x, pt.y, 100, 100);


	CButton::OnMouseMove(nFlags, point);
}
