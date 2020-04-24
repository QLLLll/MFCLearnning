// DialogFind.cpp : 实现文件
//

#include "stdafx.h"
#include "MyNote.h"
#include "DialogFind.h"
#include "afxdialogex.h"


// CDialogFind 对话框

IMPLEMENT_DYNAMIC(CDialogFind, CDialogEx)

CDialogFind::CDialogFind(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FIND, pParent)
	, m_isClose(FALSE)
	, m_findIndex(0)
	, m_isIgnoreCase(false)
	, m_isFindNext(false)
	, m_isLoop(false)
	, m_totalStr(_T(""))
{

}

CDialogFind::~CDialogFind()
{
}

void CDialogFind::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogFind, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO1, &CDialogFind::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDialogFind::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_CHECK1, &CDialogFind::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDialogFind::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogFind::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogFind::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CDialogFind::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CDialogFind 消息处理程序


void CDialogFind::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


void CDialogFind::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void CDialogFind::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_isClose = TRUE;
	this->DestroyWindow();

	//CDialogEx::OnClose();
}


void CDialogFind::PreInitDialog()
{
	// TODO: 在此添加专用代码和/或调用基类

	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
	m_isFindNext = true;

	CWnd *btn = GetDlgItem(IDC_BUTTON1);
	btn->EnableWindow(FALSE);
	m_findIndex = 0;
	m_isIgnoreCase = false;	
	 m_isLoop = false;
	 m_totalStr = _T("");
	CDialogEx::PreInitDialog();
}


void CDialogFind::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_isFindNext = false;
}


void CDialogFind::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_isFindNext = true;
}


void CDialogFind::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_isIgnoreCase = !m_isIgnoreCase;
}


void CDialogFind::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_isLoop = !m_isLoop;
}


void CDialogFind::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_isClose = TRUE;
	this->DestroyWindow();
}


void CDialogFind::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_totalStr.IsEmpty()) {
		return;
	}
	WPARAM a = 8;
	LPARAM b = 9;
	HWND hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	
	CString str;
	GetDlgItemText(IDC_EDIT1, str);
	
	if (m_isFindNext) {


		if (!m_isIgnoreCase)
		{
			int n = m_totalStr.Find(str, m_findIndex);
			if ((n>=0||m_findIndex >= m_totalStr.GetLength())||(n==-1&&m_findIndex>0)) {
				if (m_isLoop) {
					
						m_findIndex = 0;
						n = m_totalStr.Find(str, m_findIndex);
						if (n != -1)
							::SendMessage(hWnd, WM_FIND_EVENT, n, n + str.GetLength());
						m_findIndex = n + str.GetLength();
					
				}
					else {
						if (m_findIndex >= m_totalStr.GetLength()) {
							m_findIndex = m_totalStr.GetLength();
						}
						n = m_totalStr.Find(str, m_findIndex);
						if (n != -1)
						{
							::SendMessage(hWnd, WM_FIND_EVENT, n, n + str.GetLength());
							m_findIndex = n + str.GetLength();
						}
					}
			}
		}
	}


}


void CDialogFind::OnEnChangeEdit1()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);
	CWnd *btn = GetDlgItem(IDC_BUTTON1);
	if (str.IsEmpty()) {
		btn->EnableWindow(FALSE);
	}
	else {
		btn->EnableWindow(TRUE);

	}
}
