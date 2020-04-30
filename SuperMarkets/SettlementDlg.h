#if !defined(AFX_SETTLEMENTDLG_H__C0082338_8CBD_4863_80BE_4F6BE9FC17C6__INCLUDED_)
#define AFX_SETTLEMENTDLG_H__C0082338_8CBD_4863_80BE_4F6BE9FC17C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettlementDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettlementDlg dialog

class CSettlementDlg : public CDialog
{
// Construction
public:
	CSettlementDlg(CWnd* pParent = NULL);   // standard constructor
	int m_WorkType;
// Dialog Data
	//{{AFX_DATA(CSettlementDlg)
	enum { IDD = IDD_SETTLEMENT_DIALOG };
	CComboBox	m_comb;
	CListCtrl	m_countList;
	CListCtrl	m_checkList;
	CString	m_opType;
	CTime	m_checkTime;
	int		m_info;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettlementDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBar   m_ToolBar;
	CImageList m_ImageList;
	void OnNGoods();
	void OnTicket();
	void OnStorage();
	void OnUser();
	// Generated message map functions
	//{{AFX_MSG(CSettlementDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelect();
	afx_msg void OnCount();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTLEMENTDLG_H__C0082338_8CBD_4863_80BE_4F6BE9FC17C6__INCLUDED_)
