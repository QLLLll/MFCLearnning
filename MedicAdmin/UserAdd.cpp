// UserAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicAdmin.h"
#include "UserAdd.h"
#include "afxdialogex.h"



// CUserAdd 对话框

IMPLEMENT_DYNAMIC(CUserAdd, CDialogEx)

CUserAdd::CUserAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADDUSER, pParent)
	, m_uName(_T(""))
	, m_uAccount(_T(""))
	, m_uPwd(_T(""))
{

}

CUserAdd::~CUserAdd()
{
}

void CUserAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_userType);
	DDX_Text(pDX, IDC_EDIT1, m_uName);
	DDX_Text(pDX, IDC_EDIT3, m_uAccount);
	DDX_Text(pDX, IDC_EDIT2, m_uPwd);
}


BEGIN_MESSAGE_MAP(CUserAdd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserAdd::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserAdd::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserAdd 消息处理程序

//退出
void CUserAdd::OnBnClickedButton3()
{
	
	CDialogEx::OnCancel();
}

//添加用户
void CUserAdd::OnBnClickedButton2()
{
	
	UpdateData(TRUE);

	if (m_uAccount.IsEmpty() || m_uName.IsEmpty() || m_uPwd.IsEmpty()) {
		MessageBox(_T("字段不能为空"));
		return;
	}


	//TODO:添加到数据库中
	if (m_userSet.IsOpen() == FALSE) {
		m_userSet.Open(CRecordset::dynaset);
	}

	//先查找账号是否存在
	CString sql;
	sql.Format(_T("account='%s'"), m_uAccount);

	m_userSet.m_strFilter = sql;

	m_userSet.Requery();

	if (m_userSet.GetRecordCount() >= 1) {
		MessageBox(TEXT("账户重复，请更改"));
		m_uAccount = _T("");
		UpdateData(FALSE);
		return;
	}



	m_userSet.AddNew();
	m_userType.GetLBText(m_userType.GetCurSel(), m_GetType);
	
	m_userSet.m_classification = m_GetType;

	m_userSet.m_account = m_uAccount;
	m_userSet.m_name = m_uName;
	m_userSet.m_password = m_uPwd;

	m_userSet.Update();
	m_userSet.Requery();
	CUserA user;

	user.m_type = m_GetType;
	user.m_userName = m_uName;
	user.m_userPwd = m_uPwd;
	user.m_userAccount = m_uAccount;
	
	listUser.AddTail(user);

	m_uAccount = _T("");
	m_uName = _T("");
	m_uPwd = _T("");
	UpdateData(FALSE);

	m_isAdd = true;
	
	


	//CDialogEx::OnOK();

}


BOOL CUserAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_userType.InsertString(0, TEXT("管理员"));
	m_userType.InsertString(1, TEXT("医生"));
	m_userType.InsertString(2, TEXT("售药员"));
	m_userType.SetCurSel(0);

	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
