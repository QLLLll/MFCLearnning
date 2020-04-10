// UserQuery.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicAdmin.h"
#include "UserQuery.h"
#include "afxdialogex.h"


// CUserQuery 对话框

IMPLEMENT_DYNAMIC(CUserQuery, CDialogEx)

CUserQuery::CUserQuery(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_USER_QUERY, pParent)
	, m_qCondtion(_T(""))
{

}

CUserQuery::~CUserQuery()
{
}

void CUserQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_qCondtion);
}


BEGIN_MESSAGE_MAP(CUserQuery, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserQuery::OnBnClickedButton1)
END_MESSAGE_MAP()


// CUserQuery 消息处理程序

//查询
void CUserQuery::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
