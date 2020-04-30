#if !defined(AFX_GOODSDLG_H__73F4972C_75ED_46FB_A6A6_75ACA7396A70__INCLUDED_)
#define AFX_GOODSDLG_H__73F4972C_75ED_46FB_A6A6_75ACA7396A70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GoodsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGoodsDlg dialog

class CGoodsDlg : public CDialog
{
// Construction
public:
	bool CheckExitPack(CString index, CString value,CString table);
	CString GetGoodsID();
	void SetopTypeEnable();
	CGoodsDlg(CWnd* pParent = NULL);   // standard constructor
	int m_WorkType;
// Dialog Data
	//{{AFX_DATA(CGoodsDlg)
	enum { IDD = IDD_GOODS_DIALOG };
	CComboBox	m_opType;
	CComboBox	m_index;
	CListCtrl	m_list;
	CString	m_info;
	CString	m_opStr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGoodsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBar   m_ToolBar;
	CImageList m_ImageList;
	int m_listIndex;
	void OnCount();
	void OnTicket();
	void OnStorage();
	void OnUser();
	
	// Generated message map functions
	//{{AFX_MSG(CGoodsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelect();
	afx_msg void OnAdd();
	afx_msg void OnModfy();
	afx_msg void OnDelete();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOODSDLG_H__73F4972C_75ED_46FB_A6A6_75ACA7396A70__INCLUDED_)
