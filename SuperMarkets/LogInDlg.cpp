// LogInDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperMarkets.h"
#include "LogInDlg.h"
#include "adoconn.h"
#include "SuperMarketsDlg.h"
#include "SuperMarketsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CLogInDlg dialog


CLogInDlg::CLogInDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogInDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogInDlg)
	m_WorkID = _T("");
	m_PassWord = _T("");
	//}}AFX_DATA_INIT
	m_times = 0;
	m_type = 0;
}


void CLogInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogInDlg)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Text(pDX, IDC_ID, m_WorkID);
	DDX_Text(pDX, IDC_PW, m_PassWord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogInDlg, CDialog)
	//{{AFX_MSG_MAP(CLogInDlg)
	ON_EN_CHANGE(IDC_ID, OnChangeId)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogInDlg message handlers

BOOL CLogInDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_LBUTTONDOWN )
	{
		CRect rect,rc;
		m_OK.GetWindowRect(&rect);
		m_Cancel.GetWindowRect(&rc);
		CPoint point;
		GetCursorPos(&point);
		if(rect.PtInRect(point))
		{
			UpdateData(TRUE);
			if(m_WorkID.IsEmpty() || m_PassWord.IsEmpty())
			{
				MessageBox("用户名或密码不能为空");
				return FALSE;
			}
			m_times++;
			ADOConn m_AdoConn;
			m_AdoConn.OnInitADOConn();
			CString sql;
			sql.Format("select * from worker where WorkerID='%s'  and PWD='%s'",
				m_WorkID,m_PassWord);
			m_AdoConn.m_pRecordset = m_AdoConn.GetRecordSet((_bstr_t)sql);
			if(!m_AdoConn.m_pRecordset->adoEOF)
			{
				CString str;
				str = (char *)(_bstr_t)m_AdoConn.m_pRecordset->GetCollect("Permissions");
				m_type = atoi(str);
				CDialog::OnOK();
				m_AdoConn.ExitConnect();
			}
			else
			{
				if(m_times == 3)
				{
					MessageBox("密码不正确已达3次，系统将自动退出！");
					CDialog::OnCancel();
					m_AdoConn.ExitConnect();
				}
				else
				{
					CString str ;
					str.Format("用户名或密码不正确，您还可以输入%d次！",3 - m_times);
					MessageBox(str);
					m_WorkID = "";
					m_PassWord = "";
					UpdateData(FALSE);
				}
			}
				
		}
		if(rc.PtInRect(point))
		{
			CDialog::OnCancel();
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}



void CLogInDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CLogInDlg::OnChangeId() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CLogInDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
