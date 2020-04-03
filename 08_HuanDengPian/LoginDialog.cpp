// LoginDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "08_HuanDengPian.h"
#include "LoginDialog.h"
#include "afxdialogex.h"


// CLoginDialog 对话框

IMPLEMENT_DYNAMIC(CLoginDialog, CDialogEx)

CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_userName(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDialog::~CLoginDialog()
{
}

void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_userName);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDialog::OnBnClickedButton1)
	ON_WM_CLOSE()
//	ON_WM_CHAR()
END_MESSAGE_MAP()


// CLoginDialog 消息处理程序


void CLoginDialog::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(1);
}

//登录按钮
void CLoginDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	if (m_userName ==TEXT("L")&&m_pwd == TEXT("L")) {
		CDialogEx::OnOK();

	}
	else {

		MessageBox(TEXT("用户名或密码错误"));

	}
}


void CLoginDialog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDialog::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	exit(1);
}


//void CLoginDialog::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	if (nChar == VK_RETURN) {
//
//		OnBnClickedButton1();
//	}
//
//
//	CDialogEx::OnChar(nChar, nRepCnt, nFlags);
//}


BOOL CLoginDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN) {

		if (pMsg->wParam == VK_RETURN)
		{
			OnBnClickedButton1();
		}
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}
