// SuperMarketsDlg.h : header file
//

#if !defined(AFX_SUPERMARKETSDLG_H__C42E344A_115F_4779_AEAF_B43074C05FFC__INCLUDED_)
#define AFX_SUPERMARKETSDLG_H__C42E344A_115F_4779_AEAF_B43074C05FFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSuperMarketsDlg dialog

class CSuperMarketsDlg : public CDialog
{
// Construction
public:
	CString GetTicketID(CTime time);
	void PrintTicket();
	void InitSaleControl();
	void InitListControl();
	void InitDialogShow();
	CString m_WorkID;
	void ShowUser();
	CString numTostring(int num);
	void DrawBackGround(CDC *pDc);
	void DrawTitle(CDC *pDc);
	CSuperMarketsDlg(CWnd* pParent = NULL);	// standard constructor
	CRect m_clientRect;
// Dialog Data
	//{{AFX_DATA(CSuperMarketsDlg)
	enum { IDD = IDD_SUPERMARKETS_DIALOG };
	CButton	m_Statistics;
	CButton	m_cTicket;
	CStatic	m_sShould;
	CStatic	m_sChange;
	CStatic	m_sActual;
	CEdit	m_eShould;
	CEdit	m_eChange;
	CEdit	m_eActual;
	CButton	m_bSale;
	CButton	m_bCheck;
	CListCtrl	m_goodsTail;
	CListCtrl	m_goods;
	double	m_actual;
	double	m_should;
	double	m_change;
	BOOL	m_bTicket;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperMarketsDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CString m_GoodsID;
	int		m_GoodsValue;
	int		m_SaleNum;
	int m_type;
	// Generated message map functions
	//{{AFX_MSG(CSuperMarketsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSale();
	afx_msg void OnCheck();
	afx_msg void OnChangeEact();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERMARKETSDLG_H__C42E344A_115F_4779_AEAF_B43074C05FFC__INCLUDED_)
