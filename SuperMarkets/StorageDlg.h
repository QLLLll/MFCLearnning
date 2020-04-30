#if !defined(AFX_STORAGEDLG_H__4DE1A619_BE83_4C88_8BD1_AC6424535200__INCLUDED_)
#define AFX_STORAGEDLG_H__4DE1A619_BE83_4C88_8BD1_AC6424535200__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StorageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStorageDlg dialog

class CStorageDlg : public CDialog
{
// Construction
public:
	CString GetTicketID(CTime time);
	int CheckNum(CString index,CString value,CString table,int num);
	bool CheckExit(CString index, CString value, CString table);
	void SetControl();
	CStorageDlg(CWnd* pParent = NULL);   // standard constructor
	int m_WorkType;
// Dialog Data
	//{{AFX_DATA(CStorageDlg)
	enum { IDD = IDD_STORAGE_DIALOG };
	CComboBox	m_infoComb;
	CListCtrl	m_list;
	CComboBox	m_comb;
	int		m_id;
	CString	m_info;
	CString	m_goodsid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStorageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBar   m_ToolBar;
	CImageList m_ImageList;
	void OnCount();
	void OnNGoods();
	void OnTicket();
	void OnUser();
	// Generated message map functions
	//{{AFX_MSG(CStorageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelect();
	afx_msg void OnInstorage();
	afx_msg void OnOutstorage();
	afx_msg void OnId();
	afx_msg void OnLeft();
	afx_msg void OnSale();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STORAGEDLG_H__4DE1A619_BE83_4C88_8BD1_AC6424535200__INCLUDED_)
