
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
	, m_fileName(_T(""))
	, m_findOpen(FALSE)
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
	ON_COMMAND(ID_32771, &CMyNoteDlg::OnNewFile)
	ON_COMMAND(ID_32773, &CMyNoteDlg::OnSaveFile)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_32774, &CMyNoteDlg::OnSaveAs)
	ON_COMMAND(ID_32776, &CMyNoteDlg::OnFind)
	ON_COMMAND(ID_32780, &CMyNoteDlg::OnFont)
	ON_COMMAND(ID_32777, &CMyNoteDlg::OnInsertDate)
	ON_MESSAGE(WM_FIND_EVENT, OnFindStr)
	ON_COMMAND(ID_32781, &CMyNoteDlg::OnCopyOther)
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

LRESULT CMyNoteDlg::OnFindStr(WPARAM wParam, LPARAM iParam)
{
	CEdit *edit = (CEdit*)GetDlgItem(IDC_EDIT1);	
	edit->SetSel((int)wParam, (int)iParam);
	edit->SetFocus();

	return 0;
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

	if (fDiaLog.DoModal() == IDOK) {
		CString pName = fDiaLog.GetPathName();
		m_fileName = pName;
		SetTitle();
		CFile file;
		char buffer[256];
		if (file.Open(pName, CFile::modeReadWrite, NULL)) {
			
			if (file.Read(buffer, 2) == 2)
			{
				switch (buffer[0])
				{
				case 0xBBEF:
					ReadUTF8(file);
					return;
				case 0xFFFE:
					ReadUnicode(file);
					return;
				}
			}
			ReadAnsi(file);
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


void CMyNoteDlg::OnNewFile()
{
	// TODO: 在此添加命令处理程序代码

	SetWindowText(_T(""));

	CString txt;
	GetDlgItemText(IDC_EDIT1, txt);

	if (!m_fileName.IsEmpty() || !txt.IsEmpty()) {
		if (MessageBox(_T("是否保存"), _T("是否保存"), MB_OKCANCEL) == IDOK) {
			OnSaveFile();
			txt.Empty();
			SetDlgItemText(IDC_EDIT1, txt);
			m_fileName.Empty();
		}
		else {
			
			txt.Empty();
			SetDlgItemText(IDC_EDIT1, txt);
			m_fileName.Empty();
		}


	}


}


void CMyNoteDlg::OnSaveFile()
{
	CString txt;

	GetDlgItemText(IDC_EDIT1, txt);

	if (!m_fileName.IsEmpty())
	{
		CStdioFile file;
		if (file.Open(m_fileName, CFile::modeCreate|CFile::modeReadWrite, NULL) == TRUE) {
			
			char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));

			setlocale(LC_CTYPE, "chs");//设定

			file.WriteString(txt);
			file.Close();
		}
	}
	else if (m_fileName.IsEmpty()) {
		
		CFileDialog fDiaLog(FALSE, TEXT("*.txt"), _T("新建文件"),
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			_T("txt Files (*.txt)|*.txt|cs Files (*.cs)|*.cs|Data Files (*.ini)|*.ini|All Files (*.*)|*.*||"), NULL);

		if (fDiaLog.DoModal() == IDOK) {
			CString pName = fDiaLog.GetPathName();
			m_fileName = pName;

			CStdioFile file;
			if (file.Open(pName, CFile::modeCreate|CFile::modeWrite, NULL)) {
			
				char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));

				setlocale(LC_CTYPE, "chs");//设定

				file.WriteString(txt);
				file.Close();
			
			}
		}

	}

}


void CMyNoteDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值v
	CDialogEx::OnDropFiles(hDropInfo);
	TCHAR sFile[256];
	int nCount = DragQueryFile(hDropInfo, 0, sFile, _countof(sFile));
	CFile file;
	if (!file.Open(sFile, CFile::modeRead))
	{//文件在拖动过程被删除了，或者文件被占用
		AfxMessageBox(_T("打开文件时失败！请检查文件名称是否正确！"));
		return;
	}
	if (file.Read(sFile, 2) == 2)
	{
		switch (sFile[0])
		{
		case 0xBBEF:
			ReadUTF8(file);
			return;
		case 0xFFFE:
			ReadUnicode(file);
			return;
		}
	}
	ReadAnsi(file);
	
	
}
void CMyNoteDlg::ReadAnsi(CFile& file)//读取方式1：ANSI //传对象传引用
{
	file.Seek(0, CFile::begin);//回到头开始
	char buff[1024];
	UINT nRet = 0;//三种文件：ANSI:窄字符集 Unicode:宽字符集也叫UTF-16 UTF-8:窄字符集：属于Unicode 
	CString str;
	while (nRet = file.Read(buff, sizeof(buff) - 1))//nRet != 0
	{
		buff[nRet] = _T('\0');
		str += buff;
	}
	SetDlgItemText(IDC_EDIT1, str);
}

void CMyNoteDlg::ReadUTF8(CFile& file)//UTF-8文件编码读取
{
	file.Seek(3, CFile::begin);//向后移动三个字节
	LONGLONG nLen = file.GetLength();//64位操作系统
	char* p = new char[nLen + 1];
	nLen = file.Read(p, nLen);
	p[nLen] = '\0';
	TCHAR* pText = new TCHAR[nLen / 2 + 2];//防止不够 + 2
	nLen = MultiByteToWideChar(CP_UTF8, NULL, p, -1, pText, nLen / 2 + 2);//代入p 传出 pText
	SetDlgItemText(IDC_EDIT1, pText);
	delete[] p;
	delete[] pText;
}

void CMyNoteDlg::ReadUnicode(CFile& file)//Unicode文件编码获取
{
	file.Seek(2, CFile::begin);//向后移动三个字节
	LONGLONG nLen = file.GetLength();//64位操作系统
	TCHAR* pText = new TCHAR[nLen / 2 + 1];//防止不够 + 1
	nLen = file.Read(pText, nLen);
	pText[nLen / 2] = _T('\0');
	SetDlgItemText(IDC_EDIT1, pText);
	delete[] pText;
}

void CMyNoteDlg::OnSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	CString txt;
	GetDlgItemText(IDC_EDIT1, txt);

	CFileDialog fDiaLog(FALSE, TEXT("*.txt"), _T("新建文件"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("txt Files (*.txt)|*.txt|cs Files (*.cs)|*.cs|Data Files (*.ini)|*.ini|All Files (*.*)|*.*||"), NULL);

	if (fDiaLog.DoModal() == IDOK) {
		CString pName = fDiaLog.GetPathName();
		m_fileName = pName;

		CStdioFile file;
		if (file.Open(pName, CFile::modeCreate | CFile::modeWrite, NULL)) {

			char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));

			setlocale(LC_CTYPE, "chs");//设定

			file.WriteString(txt);
			file.Close();

		}
	}
}


void CMyNoteDlg::OnFind()
{
	// TODO: 在此添加命令处理程序代码
	/*CEdit *edit = (CEdit*)GetDlgItem(IDC_EDIT1);
	CString str;
	GetDlgItemText(IDC_EDIT1, str);

	int index=str.Find(_T("abc"), 0);
	edit->SetSel(index, index + 3);*/
	if (!m_findOpen||m_diaFind.m_isClose==TRUE) {
		m_findOpen=m_diaFind.Create(IDD_DIALOG_FIND, this);
		m_diaFind.ShowWindow(SW_SHOWNORMAL);
		m_diaFind.m_isClose = FALSE;
		GetDlgItemText(IDC_EDIT1, m_diaFind.m_totalStr);
	}
	
	
}


void CMyNoteDlg::OnFont()
{
	CFont* pFont = GetDlgItem(IDC_EDIT1)->GetFont();
	LOGFONT lf;
	pFont->GetLogFont(&lf);//获得当前CFont对象的LOGFONT结构体的拷贝
	CFontDialog fd(&lf);//构造字体对话框，初始选择字体为当前CFont对象的字体

	if (IDCANCEL == fd.DoModal())
		return;
	m_font.DeleteObject();//如果m_font已经关联了一个字体资源对象，则释放它
	m_font.CreateFontIndirect(fd.m_cf.lpLogFont);//使用选定字体的LOGFONT创建新的字体 
												 //	m_font.CreateFontIndirect(&lf);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_font);//选定字体
}

void CMyNoteDlg::SetTitle()
{
	CString str;
	if (m_fileName.IsEmpty())
		str = "无标题";
	else
		str = m_fileName;

	int i = str.ReverseFind('\\'); //反向找到 \\
								   	if(i > 0)
	str = str.Mid(i + 1); //从\\位置处 截出str后面的内容

	SetWindowText(str);
}


void CMyNoteDlg::OnInsertDate()
{
	// TODO: 在此添加命令处理程序代码
	COleDateTime time = COleDateTime::GetCurrentTime();
	CString str = time.Format(_T("%Y-%m-%d %H:%M"));
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit->ReplaceSel(str);//选中插入

}


void CMyNoteDlg::OnCopyOther()
{
	// TODO: Add your command handler code here

	//HWND	m_qqhWnd = ::FindWindow(_T("TXGuiFoundation"), _T("QQ"));
	HWND	padWnd = ::FindWindow(_T("Notepad"), NULL);
	if (padWnd)

	{

		//获取窗口句柄

		CRect rect;

		::GetWindowRect(padWnd, rect);

		CString str;

		CPoint user_pt;

		//将user_pt点定位到编辑框框内
		user_pt.x = rect.left + 63;

		user_pt.y = rect.top + 89;

		//获取edit句柄句柄
		HWND editWnd = ::WindowFromPoint(user_pt);
		
		//获取文字长度
		LRESULT res = ::SendMessage(editWnd, WM_GETTEXTLENGTH, 0, 0);
		int len = (int)res;
		TCHAR *buf=new TCHAR[len+1];
		
		::SendMessage(editWnd, WM_GETTEXT, (WPARAM)res, (LPARAM)buf);
		buf[len] = '/0';
		SetDlgItemText(IDC_EDIT1, buf);
			
		delete[]buf;
	}
	else
		MessageBox(_T("查找窗口失败！"));
	
}
