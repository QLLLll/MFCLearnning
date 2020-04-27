// tbl_dll.h : Ctbl_dll 类的实现



// Ctbl_dll 实现

// 代码生成在 2020年4月27日, 20:25

#include "stdafx.h"
#include "tbl_dll.h"
IMPLEMENT_DYNAMIC(Ctbl_dll, CRecordset)

Ctbl_dll::Ctbl_dll(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_id = 0;
	m_m_data;
	m_nFields = 2;
	m_nDefaultType = snapshot;
}
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString Ctbl_dll::GetDefaultConnect()
{
	return _T("Description=\x6d4b\x8bd5\x8bfb\x53d6\x4e8c\x8fdb\x5236;DRIVER=SQL Server;SERVER=DESKTOP-I7LA8BS;UID=sa;PWD=940619.lq;APP=Microsoft? Visual Studio? 2015;WSID=DESKTOP-I7LA8BS;DATABASE=Learnning");
}

CString Ctbl_dll::GetDefaultSQL()
{
	return _T("[dbo].[tbl_dll]");
}

void Ctbl_dll::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_BigInt(pFX, _T("[id]"), m_id);
	RFX_LongBinary(pFX, _T("[m_data]"), m_m_data);

}
/////////////////////////////////////////////////////////////////////////////
// Ctbl_dll 诊断

#ifdef _DEBUG
void Ctbl_dll::AssertValid() const
{
	CRecordset::AssertValid();
}

void Ctbl_dll::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


