#if !defined(AFX_NEWGOODSDLG_H__09EC00A0_9B29_472B_A838_E88DB96B3717__INCLUDED_)
#define AFX_NEWGOODSDLG_H__09EC00A0_9B29_472B_A838_E88DB96B3717__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewGoodsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewGoodsDlg dialog

class CNewGoodsDlg : public CDialog
{
// Construction
public:
	CNewGoodsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewGoodsDlg)
	enum { IDD = IDD_NEWGOODS_DIALOG };
	CString	m_goodsid;
	CString	m_goodsname;
	double	m_goodsvalue;
	CString	m_barcode;
	CString	m_main;
	CString	m_part;
	CString	m_info;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewGoodsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewGoodsDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWGOODSDLG_H__09EC00A0_9B29_472B_A838_E88DB96B3717__INCLUDED_)
