
// ListDirectoryFilesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ListDirectoryFiles.h"
#include "ListDirectoryFilesDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CListDirectoryFilesDlg 对话框



CListDirectoryFilesDlg::CListDirectoryFilesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTDIRECTORYFILES_DIALOG, pParent)
	, m_dirPath(_T(""))
	, m_logIsShow(FALSE)
	, m_chanPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListDirectoryFilesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_BTN_BACK, m_btnBack);
	DDX_Control(pDX, IDC_BTN_FWARD, m_btnFward);
	DDX_Control(pDX, IDC_BTN_DOWN, m_btnDown);
	DDX_Control(pDX, IDC_BTN_UP, m_btnUp);
	DDX_Control(pDX, IDC_LIST_LOGPATH, m_logPath);
}

BEGIN_MESSAGE_MAP(CListDirectoryFilesDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SEARCH, &CListDirectoryFilesDlg::OnBnClickedSearch)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CListDirectoryFilesDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BTN_DOWN, &CListDirectoryFilesDlg::OnBnClickedBtnDown)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CListDirectoryFilesDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CListDirectoryFilesDlg 消息处理程序
int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {

	int row1 = (int)lParam1;//这里的参数实际是SetItemData函数设置的值，比较的第一列
	int row2 = (int)lParam2;//这里的参数实际是SetItemData函数设置的值，比较的第二列
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString s1 = lc->GetItemText(row1, 2);
	CString s2 = lc->GetItemText(row2, 2);
	
	// 比较，对不同的列，不同比较，注意记录前一次排序方向，下一次要相反排序		 
	if(s1.Compare(_T("文件夹"))==0)
		return  -1;
	
	else
	{
		return  1;
	}
	

}

BOOL CListDirectoryFilesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_logIsShow = 0;
	m_logPath.ShowWindow(FALSE);
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_list.InsertColumn(0, _T("名称"), LVCFMT_LEFT, 340);
	m_list.InsertColumn(1, _T("修改日期"), LVCFMT_LEFT, 180);
	m_list.InsertColumn(2, _T("类型"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T("大小"), LVCFMT_LEFT,100);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT
		| LVS_EX_GRIDLINES);
	SetDlgItemText(IDC_PATH, _T("d:"));

	ListFiles(_T("d:\\*.*"));
	for (int i = 0; i < m_list.GetItemCount(); i++)
	{

		m_list.SetItemData(i, i);//在排序前一定用这个函数设置每行值，类似于自定义索引

	}
	m_list.SortItems(CompareFunc, (DWORD)&m_list);
	
	m_btnUp.EnableWindow(FALSE);
	m_btnBack.EnableWindow(FALSE);
	m_btnFward.EnableWindow(FALSE);
	m_btnDown.EnableWindow(FALSE);

	if (m_logPh == NULL) {
		m_logPh = new CLogPath();
		m_logPh->Create(IDD_LOG_PATH, AfxGetApp()->GetMainWnd());
	}

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CListDirectoryFilesDlg::ListFiles(CString  path) {



	CFileFind ff;

	if(path.IsEmpty())
	{
		path = _T("c:\\*.*");
	}

	BOOL bworking = ff.FindFile(path);

	if (bworking)
	{
		m_list.DeleteAllItems();
	}

	CString fileName, fileLen, lastTime, fileType;
	int i = 0;
	while (bworking) {

		bworking = ff.FindNextFileW();

		if (ff.IsHidden()||ff.IsSystem()) {
			continue;
		}

		fileName = ff.GetFileName();
		if (fileName == _T(".") || fileName == _T("..")) {
			continue;
		}
		if (ff.IsDirectory()) {
			fileType = _T("文件夹");
			fileLen = _T("");
		}
		else {
			int dot = ff.GetFilePath().ReverseFind('.');
			fileType = ff.GetFilePath().Mid(dot);
			ULONGLONG	size = ff.GetLength();
			fileLen.Format(_T("%dKB"), size/1024+1);
		}

		
		
		CTime time;
		ff.GetLastWriteTime(time);

		lastTime = time.Format(_T("%y-%m-%d %H:%M:%S"));
		
		m_list.InsertItem(i, fileName);
		m_list.SetItemText(i, 1, lastTime);
		m_list.SetItemText(i, 2, fileType);
		m_list.SetItemText(i, 3, fileLen);


	}

}

void CListDirectoryFilesDlg::OnPaint()
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
HCURSOR CListDirectoryFilesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CListDirectoryFilesDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CListDirectoryFilesDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void CListDirectoryFilesDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	DestroyWindow();

	//CDialogEx::OnClose();
}


void CListDirectoryFilesDlg::OnBnClickedSearch()
{
	CString path;
	GetDlgItemText(IDC_PATH, path);

	ListFiles(path + _T("//*.*"));

	for (int i = 0; i < m_list.GetItemCount(); i++)
	{

		m_list.SetItemData(i, i);//在排序前一定用这个函数设置每行值，类似于自定义索引

	}
	m_list.SortItems(CompareFunc, (DWORD)&m_list);


}


//void CListDirectoryFilesDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}


void CListDirectoryFilesDlg::OnBnClickedBtnDown()
{
	CRect rec;

	m_btnDown.GetWindowRect(rec);
	if (m_logIsShow==0)
	{
		if (m_logPh == NULL) {
			m_logPh = new CLogPath();
			m_logPh->Create(IDD_LOG_PATH, AfxGetApp()->GetMainWnd());
			m_logPh->ShowWindow(SW_NORMAL);
			m_logPh->SetWindowPos(&this->wndTopMost, rec.left - 70, rec.top + 40, 160, 250, SWP_SHOWWINDOW);

		}
		else {
			m_logPh->ShowWindow(SW_NORMAL);
			m_logPh->SetWindowPos(&this->wndTopMost, rec.left - 70, rec.top + 40, 160, 250, SWP_SHOWWINDOW);
		}
		m_logIsShow = 1;
	}
	else  {
		if (m_logPh != NULL) {

			m_logIsShow = m_logPh->ShowWindow(SW_HIDE);
			m_logIsShow = 0;
		}
	}

	
}


void CListDirectoryFilesDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE active = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	CString str1;
	CString str2;
	//str.Format(L"%d,%d", active->iItem, active->iSubItem);
	//MessageBox(str);
	if (active->iSubItem == 0) {

		int row = active->iItem;

		str1=m_list.GetItemText(row, 0);
		str2 = m_list.GetItemText(row, 2);
	}

	if (str2.Compare(_T("文件夹")) == 0) {
		CString oPath;
		GetDlgItemText(IDC_PATH, oPath);
		m_chanPath = oPath + _T("//") + str1;
		SetDlgItemText(IDC_PATH, m_chanPath);
		
		m_logPh->m_listBox.AddString(oPath);

	}
	int m = m_logPh->m_listBox.GetCount();
	if (m > 0) {
		m_btnDown.EnableWindow(TRUE);
	}
	else {
		m_btnDown.EnableWindow(FALSE);

	}


	*pResult = 0;
}
