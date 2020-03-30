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

MyFrame::MyFrame()
{
	Create(NULL, TEXT("MFC"));
}
