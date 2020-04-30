#if !defined(AFX_ADMINDLG_H__38639D7C_8293_494F_827D_2668376A075E__INCLUDED_)
#define AFX_ADMINDLG_H__38639D7C_8293_494F_827D_2668376A075E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdminDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdminDlg dialog

class CAdminDlg : public CDialog
{
// Construction
public:
	CAdminDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAdminDlg)
	enum { IDD = IDD_ADMIN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdminDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBar   m_ToolBar;
	CImageList m_ImageList;
	// Generated message map functions
	//{{AFX_MSG(CAdminDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void OnCount();
	void OnNGoods();
	void OnTicket();
	void OnStorage();
	void OnUser();
	CString m_WorkID;
	int m_WorkType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADMINDLG_H__38639D7C_8293_494F_827D_2668376A075E__INCLUDED_)
