
// TestSRDllDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSRDll.h"
#include "TestSRDllDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestSRDllDlg 对话框



CTestSRDllDlg::CTestSRDllDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTSRDLL_DIALOG, pParent)
	, m_path(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestSRDllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestSRDllDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestSRDllDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestSRDllDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestSRDllDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CTestSRDllDlg 消息处理程序

BOOL CTestSRDllDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	if (m_tbl == NULL)
	{
		m_tbl = new Ctbl_dll();
		
	}
	if (m_tbl->IsOpen() == FALSE) {
		BOOL isOpen = m_tbl->Open(CRecordset::dynaset);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestSRDllDlg::OnPaint()
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
HCURSOR CTestSRDllDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestSRDllDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CTestSRDllDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void CTestSRDllDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	this->DestroyWindow();
	delete m_tbl;
	m_tbl = NULL;
}

//打开
void CTestSRDllDlg::OnBnClickedButton1()
{
	CFileDialog fDiaLog(TRUE, TEXT("*.txt"),NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("txt Files (*.dll)|*.dll|All Files (*.*)|*.*||"), NULL);
	CString path;
	if (fDiaLog.DoModal() == IDOK)
	{
		m_path = fDiaLog.GetPathName();
		SetDlgItemText(IDC_EDIT1, m_path);
	}
	else {
		return;
	}


}


void CTestSRDllDlg::OnBnClickedButton2()
{

	if (m_path.IsEmpty()) {
		return;
	}

	CFile file;
	CFileStatus filestatus;
	file.Open(m_path, CFile::modeRead);
	file.GetStatus(filestatus);
	m_tbl->AddNew();
	m_tbl->m_m_data.m_dwDataLength = filestatus.m_size;
	HGLOBAL hGlobal = GlobalAlloc(GPTR, filestatus.m_size);
	m_tbl->m_m_data.m_hData = GlobalLock(hGlobal);
	file.Read(m_tbl->m_m_data.m_hData, filestatus.m_size);	
	m_tbl->SetFieldDirty(&m_tbl->m_m_data);
	m_tbl->SetFieldNull(&m_tbl->m_m_data, FALSE);
	BOOL flag=m_tbl->Update();
	GlobalUnlock(hGlobal);
	if (flag == TRUE) {
		MessageBox(_T("保存成功"));
	}
	file.Close();
}


void CTestSRDllDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	CFileDialog fDiaLog(FALSE, TEXT("*.dll"), TEXT("New.dll"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("txt Files (*.dll)|*.dll|All Files (*.*)|*.*||"), NULL);
	CString path;
	if (fDiaLog.DoModal() == IDOK)
	{
		m_path = fDiaLog.GetPathName();
		SetDlgItemText(IDC_EDIT1, m_path);
	}
	else {
		return;
	}

	CFile file;
	CFileStatus filestatus;
	file.Open(m_path, CFile::modeCreate|CFile::modeWrite);

	m_tbl->MoveFirst();

	BYTE * byt = (BYTE*)GlobalLock(m_tbl->m_m_data.m_hData);

	file.Write(byt, m_tbl->m_m_data.m_dwDataLength);
	file.Close();
	GlobalUnlock(m_tbl->m_m_data.m_hData);
}
