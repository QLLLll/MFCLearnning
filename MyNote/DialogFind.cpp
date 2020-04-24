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
	, m_hasFind(false)
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
	m_isIgnoreCase = true;
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
	
	HWND hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();

	CString str;
	GetDlgItemText(IDC_EDIT1, str);
	CString str1 = str;
	CString strLower = str1.MakeLower();
	CString strUpper = str1.MakeUpper();
	int n = -1;
	CString s;

	s.Format(_T("未找到\"%s\""), str);

	if (m_isFindNext) {

		if (!m_isIgnoreCase)
		{
			n = m_totalStr.Find(str, m_findIndex);
			//循环查找
			if (m_isLoop) {
				if ((n >= 0 || m_findIndex >= m_totalStr.GetLength()) || (n == -1 && m_findIndex > 0)) {

					if (n == -1 && m_findIndex > 0)
					{
						m_findIndex = 0;
					}

					n = m_totalStr.Find(str, m_findIndex);
					if (n != -1)
					{
						::SendMessage(hWnd, WM_FIND_EVENT, n, n + str.GetLength());
						m_findIndex = n + str.GetLength();
						m_hasFind = true;
					}
				}
				else {
					MessageBox(s);
				}

			}//不循环
			else {
				if (m_findIndex >= m_totalStr.GetLength()) {
					m_findIndex = m_totalStr.GetLength();
				}
				n = m_totalStr.Find(str, m_findIndex);
				if (n != -1)
				{
					::SendMessage(hWnd, WM_FIND_EVENT, n, n + str.GetLength());
					m_findIndex = n + str.GetLength();
					m_hasFind = true;
				}
				else {

					MessageBox(s);
				}
			}
		}
		else {
			while (true) {
				int j = -1, u = -1;
				j = m_totalStr.Find(strLower.Left(1), m_findIndex);
				u = m_totalStr.Find(strUpper.Left(1), m_findIndex);

				n = (j > u ? j : u);

				if (n > -1 || (n == -1 && m_findIndex > 0)) {
					CString compStr;
					if (n > -1)
						compStr = m_totalStr.Mid(n, str.GetLength());

					if (m_isLoop) {
						m_findIndex = n + 1;
						if (n == -1 && m_findIndex > 0) {
							m_findIndex = 0;
							if (m_hasFind) {
								continue;
							}
						}
					}
					else {
						if (n > -1)
							m_findIndex = n + 1;
					}
					if (strLower.CompareNoCase(compStr) == 0) {
						::SendMessage(hWnd, WM_FIND_EVENT, n, n + str.GetLength());
						m_hasFind = true;
						break;
					}
					if (!m_isLoop) {
						if (m_findIndex > 0 && n == -1) {

							MessageBox(s);
							break;

						}
					}
					else {
						if (m_findIndex >0 && m_hasFind == false) {
							MessageBox(s);
							break;
						}
					}

				}
				else {
					MessageBox(s);
					break;
				}
			}
		}
	}
	else {
		CString copyStr = m_totalStr;
		if (n < -1) {
			n = -1;
		}
		while (true) {
			if (m_findIndex >=0)
				if (m_findIndex == 0 && m_isLoop) {
					m_findIndex = m_totalStr.GetLength();
					copyStr = m_totalStr;
				}
				else {
					copyStr = m_totalStr.Mid(0, m_findIndex);
				}
			else {
				copyStr = m_totalStr;
				m_findIndex = m_totalStr.GetLength();
			}
			int j = -1, u = -1;

			if (m_isIgnoreCase) {
				j = copyStr.ReverseFind(strLower[0]);
				u = copyStr.ReverseFind(strUpper[0]);
				n = (j > u ? j : u);
			}
			else {
				n= copyStr.ReverseFind(str[0]);
			}



			if (n > -1 || (n == -1 && m_findIndex > 0)) {
				CString compStr;
				if (n > -1)
					compStr = m_totalStr.Mid(n, str.GetLength());

				if (m_isLoop) {
					if (n > -1)
						m_findIndex = n;
					else
						m_findIndex -= 1;
					if (n == -1 && m_findIndex > 0) {
						m_findIndex = 0;
						if (m_hasFind) {
							continue;
						}
					}
				}
				else {
					if (n > -1)
						m_findIndex=n;
					else
						m_findIndex -= 1;
				}
				if (m_isIgnoreCase&&strLower.CompareNoCase(compStr) == 0) {
					::SendMessage(hWnd, WM_FIND_EVENT, n, n + str.GetLength());
					m_hasFind = true;
					break;
				}
				if (!m_isIgnoreCase&&str.Compare(compStr) == 0) {

					::SendMessage(hWnd, WM_FIND_EVENT, n, n + str.GetLength());
					m_hasFind = true;
					break;
				}

				if (!m_isLoop) {
					if (m_findIndex >= 0 && n == -1) {

						MessageBox(s);
						break;

					}
				}
				else {
					if (m_findIndex == 0 && m_hasFind == false) {
						MessageBox(s);
						break;
					}
				}
			}
			else {
				MessageBox(s);
				break;
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
		m_hasFind = false;

	}
}
