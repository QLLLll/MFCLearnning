
// MyNoteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyNote.h"
#include "MyNoteDlg.h"
#include "afxdialogex.h"
#include<string>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyNoteDlg 对话框



CMyNoteDlg::CMyNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYNOTE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyNoteDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_COMMAND(ID_32772, &CMyNoteDlg::OnOpenFile)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMyNoteDlg 消息处理程序

BOOL CMyNoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyNoteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyNoteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyNoteDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void CMyNoteDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}

//窗口改变时改变控件大小
void CMyNoteDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rec;
	GetClientRect(&rec);
	
	CEdit *edit = (CEdit*)GetDlgItem(IDC_EDIT1);
	if(edit!=NULL)
	edit->MoveWindow(rec);


}


void CMyNoteDlg::OnOpenFile()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog fDiaLog(TRUE, TEXT("*.txt"), _T("新建文件"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("txt Files (*.txt)|*.txt|cs Files (*.cs)|*.cs|Data Files (*.ini)|*.ini|All Files (*.*)|*.*||"),NULL);

	//CEdit *edit = (CEdit*)GetDlgItem(IDC_EDIT1);

	if (fDiaLog.DoModal() == IDOK) {
		CString pName = fDiaLog.GetPathName();

		CFile file;
		if (file.Open(pName, CFile::modeReadWrite, NULL)) {


			char *pBuf;
			char *copy;

			pBuf = new char[1024];
			int n = 0;
			CString  str;
			DWORD len = file.GetLength();
			int max = 0;
			while ((n=file.Read(pBuf,1024))>0) {
				max += n;
				


				copy = new  char[n+2];
				//strcpy_s(copy, n, pBuf);
				strncpy_s(copy,n+1, pBuf, n);
					//copy[n+1] = '/0';
				

				CString str1 = CA2W(pBuf, CP_UTF8); //Utf8格式文件用此方法
				delete[] copy;
				str += str1;
				if (max >= len) {
					break;
				}
			}
			SetDlgItemText(IDC_EDIT1, str);
			file.Close();
		}
		else {
			MessageBox(_T("打开文件失败！"));
		}

	}

}


void CMyNoteDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	exit(1);
	CDialogEx::OnClose();
}
