#if !defined(AFX_INOUTDLG_H__8BCB85C7_2303_4994_B171_8E566D99E337__INCLUDED_)
#define AFX_INOUTDLG_H__8BCB85C7_2303_4994_B171_8E566D99E337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InOutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInOutDlg dialog

class CInOutDlg : public CDialog
{
// Construction
public:
	bool m_bIn;
	CInOutDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInOutDlg)
	enum { IDD = IDD_INOROUTSTORAGE_DIALOG };
	CListCtrl	m_list;
	CComboBox	m_comb;
	CString	m_goosid;
	int		m_num;
	CString	m_supplier;
	float	m_value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInOutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInOutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INOUTDLG_H__8BCB85C7_2303_4994_B171_8E566D99E337__INCLUDED_)
