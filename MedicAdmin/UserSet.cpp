// UserSet.h : CUserSet 类的实现



// CUserSet 实现

// 代码生成在 2020年4月8日, 15:20

#include "stdafx.h"
#include "UserSet.h"
IMPLEMENT_DYNAMIC(CUserSet, CRecordset)

CUserSet::CUserSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_account = "";
	m_password = "";
	m_name = "";
	m_classification = "";
	m_nFields = 4;
	m_nDefaultType = snapshot;
}
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CUserSet::GetDefaultConnect()
{
	return _T("Description=MEdicODBC;DRIVER=SQL Server;SERVER=COMP-02-2433\\SQLEXPRESS;UID=sa;PWD=940619.lq;APP=Microsoft? Visual Studio? 2015;WSID=COMP-02-2433;DATABASE=medicine");
	//  return _T("Description=MEdicODBC;DRIVER=SQL Server;SERVER=DESKTOP-I7LA8BS;UID=sa;PWD=940619.lq;APP=Microsoft? Visual Studio? 2015;WSID=COMP-02-2433;DATABASE=medicine");

}

CString CUserSet::GetDefaultSQL()
{
	return _T("[dbo].[user]");
}

void CUserSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[account]"), m_account);
	RFX_Text(pFX, _T("[password]"), m_password);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[classification]"), m_classification);

}
/////////////////////////////////////////////////////////////////////////////
// CUserSet 诊断

#ifdef _DEBUG
void CUserSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUserSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


