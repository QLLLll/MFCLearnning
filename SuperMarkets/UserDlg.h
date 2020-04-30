#if !defined(AFX_USERDLG_H__D30C4B85_862E_4E2B_8142_F5D61B76453E__INCLUDED_)
#define AFX_USERDLG_H__D30C4B85_862E_4E2B_8142_F5D61B76453E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog

class CUserDlg : public CDialog
{
// Construction
public:
	CString CountWorkerID(CTime time);
	bool CheckExit(CString index,CString value,CString table);
	CUserDlg(CWnd* pParent = NULL);   // standard constructor
	int m_WorkType;
// Dialog Data
	//{{AFX_DATA(CUserDlg)
	enum { IDD = IDD_USER_DIALOG };
	CComboBox	m_index;
	CListCtrl	m_list;
	CString	m_info;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBar   m_ToolBar;
	CImageList m_ImageList;
	int m_listIndex;
	void OnCount();
	void OnNGoods();
	void OnTicket();
	void OnStorage();
	// Generated message map functions
	//{{AFX_MSG(CUserDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelect();
	afx_msg void OnAdd();
	afx_msg void OnModfy();
	afx_msg void OnDelete();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDLG_H__D30C4B85_862E_4E2B_8142_F5D61B76453E__INCLUDED_)
