// UserLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicAdmin.h"
#include "UserLogin.h"
#include "afxdialogex.h"


// CUserLogin 对话框

IMPLEMENT_DYNAMIC(CUserLogin, CDialogEx)

CUserLogin::CUserLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_uName(_T(""))
	, m_uPwd(_T(""))
{

}

CUserLogin::~CUserLogin()
{
}

void CUserLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_userClassify);
	DDX_Text(pDX, IDC_EDIT1, m_uName);
	DDX_Text(pDX, IDC_EDIT2, m_uPwd);
}


BEGIN_MESSAGE_MAP(CUserLogin, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, &CUserLogin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserLogin::OnBnClickedButton1)
END_MESSAGE_MAP()


// CUserLogin 消息处理程序


void CUserLogin::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CUserLogin::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	exit(1);
	CDialogEx::OnClose();
}


void CUserLogin::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(1);
}
BOOL CUserLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_userClassify.InsertString(0, TEXT("管理员"));
	m_userClassify.InsertString(1, TEXT("医生"));
	m_userClassify.InsertString(2, TEXT("售药员"));
	m_userClassify.SetCurSel(1);

	m_uName = TEXT("令狐冲");
	m_uPwd = TEXT("123456");
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CUserLogin::OnBnClickedButton1()
{
	UpdateData(true);

	CString filter;

	CString type;
	m_userClassify.GetLBText(m_userClassify.GetCurSel(), type);

	filter.Format(TEXT("name='%s' and password='%s' and classification='%s'"), m_uName, m_uPwd, type);
	
	if (userSet.IsOpen() == FALSE) {
		userSet.Open();
	}
	userSet.m_strFilter = filter;

	userSet.Requery();

	if (userSet.GetRecordCount() == 1) {
		CDialogEx::OnOK();
	}
	else {
		MessageBox(TEXT("登录失败"));
		m_uName = TEXT("");
		m_uPwd = TEXT("");
		UpdateData(FALSE);
	}

}



