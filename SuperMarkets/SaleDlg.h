#if !defined(AFX_SALEDLG_H__AF7BD941_A48F_4A13_A9BA_02867F201A42__INCLUDED_)
#define AFX_SALEDLG_H__AF7BD941_A48F_4A13_A9BA_02867F201A42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaleDlg dialog

class CSaleDlg : public CDialog
{
// Construction
public:
	CSaleDlg(CWnd* pParent = NULL);   // standard constructor
	int m_uType;
// Dialog Data
	//{{AFX_DATA(CSaleDlg)
	enum { IDD = IDD_SALE_DIALOG };
	CComboBox	m_type;
	CString	m_goods;
	int		m_num;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaleDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SALEDLG_H__AF7BD941_A48F_4A13_A9BA_02867F201A42__INCLUDED_)
