// ADOConn.cpp: implementation of the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOConn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADOConn::ADOConn()
{

}

ADOConn::~ADOConn()
{

}

void ADOConn::OnInitADOConn()
{
	try
	{
       m_pConnection.CreateInstance("ADODB.Connection");
	   m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=supermarket.mdb","","",adModeUnknown);///连接数据库
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		ExitConnect();
	}
}

BOOL ADOConn::ExecuteSQL(_bstr_t bstrSQL)
{
	try
	{
        if(m_pConnection==NULL)
	     	OnInitADOConn();
        m_pConnection->Execute(bstrSQL,NULL,adCmdText);
		return true;
	}
	catch(_com_error e)
	{
		if(m_hParent)
		{
			CString errormessage;
			errormessage.Format("Sql执行失败!\r\n错误信息:"+e.Description());
			AfxMessageBox(errormessage);///显示错误信息
			ExitConnect();
		}
		return false;
	}
}

void ADOConn::ExitConnect()
{
    if(m_pRecordset != NULL)
		m_pRecordset->Close();
	m_pConnection->Close();
}

_RecordsetPtr& ADOConn::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		if(m_pConnection==NULL)
              OnInitADOConn();
		m_pRecordset.CreateInstance(__uuidof(Recordset));
        m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
    catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		ExitConnect();
	}
	return m_pRecordset;
}

