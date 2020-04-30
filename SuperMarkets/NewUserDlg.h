#if !defined(AFX_NEWUSERDLG_H__1B4E2258_C85F_46BB_82EE_43FA4A2D556A__INCLUDED_)
#define AFX_NEWUSERDLG_H__1B4E2258_C85F_46BB_82EE_43FA4A2D556A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewUserDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewUserDlg dialog

class CNewUserDlg : public CDialog
{
// Construction
public:
	CNewUserDlg(CWnd* pParent = NULL);   // standard constructor
	int m_Permissions;
// Dialog Data
	//{{AFX_DATA(CNewUserDlg)
	enum { IDD = IDD_NEW_USER_DIALOG };
	CComboBox	m_comb;
	CString	m_adress;
	CString	m_id;
	int		m_male;
	CString	m_name;
	CString	m_phone;
	CString	m_position;
	CString	m_pwd;
	CString	m_workerid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewUserDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWUSERDLG_H__1B4E2258_C85F_46BB_82EE_43FA4A2D556A__INCLUDED_)
