#include "mfc.h"
MyApp myApp;
BOOL MyApp::InitInstance()
{
	MyFrame *frame = new MyFrame;

	frame->ShowWindow(SW_SHOWNORMAL);

	frame->UpdateWindow();

	m_pMainWnd = frame;

	return TRUE;
}

BEGIN_MESSAGE_MAP(MyFrame, CFrameWnd)

	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()

END_MESSAGE_MAP()



MyFrame::MyFrame()
{
	Create(NULL, TEXT("MFC"));
}

afx_msg void MyFrame::OnLButtonDown(UINT i, CPoint pt) {

	CString str;
	
	str.Format(TEXT("点击坐标：%d,%d"), pt.x, pt.y);

	MessageBox(str);

}
afx_msg void MyFrame::OnPaint() {

	CPaintDC cdc(this);//只能在Onpaint里使用，CClientDC可以在客户区使用。



	TextOut(cdc, 0, 0, TEXT("hello MFC"), lstrlenW(TEXT("hello MFC")));


}