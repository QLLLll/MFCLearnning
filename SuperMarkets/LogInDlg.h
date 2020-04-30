#if !defined(AFX_LOGINDLG_H__A18C84EF_E9D9_4D65_B822_A7472CB3BF6F__INCLUDED_)
#define AFX_LOGINDLG_H__A18C84EF_E9D9_4D65_B822_A7472CB3BF6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogInDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogInDlg dialog

class CLogInDlg : public CDialog
{
// Construction
public:

	CLogInDlg(CWnd* pParent = NULL);   // standard constructor
	int m_times;
	int m_type;
// Dialog Data
	//{{AFX_DATA(CLogInDlg)
	enum { IDD = IDD_LOGIN_DIALOG };
	CButton	m_OK;
	CButton	m_Cancel;
	CString	m_WorkID;
	CString	m_PassWord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogInDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogInDlg)
	virtual void OnCancel();
	afx_msg void OnChangeId();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__A18C84EF_E9D9_4D65_B822_A7472CB3BF6F__INCLUDED_)
