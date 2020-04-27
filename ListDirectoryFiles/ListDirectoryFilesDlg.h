
// ListDirectoryFilesDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include"LogPath.h"
#include<vector>
#include<iterator>
using namespace std;
// CListDirectoryFilesDlg 对话框
class CListDirectoryFilesDlg : public CDialogEx
{
// 构造
public:
	CListDirectoryFilesDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTDIRECTORYFILES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg
		void ListFiles(CString path);
	void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnClose();
	void ShowList();
private:
	CListCtrl m_list;
public:
	afx_msg void OnBnClickedSearch();
private:	
	CButton m_btnBack;
	CButton m_btnFward;
	CButton m_btnDown;
	CButton m_btnUp;
	CLogPath *m_logPh=NULL;
	vector<CString>m_vecPath;
	CString m_chanPath;
	BOOL m_logIsShow;	
public:
	afx_msg void OnBnClickedBtnDown();
	afx_msg LRESULT OnGetPath(WPARAM wParam, LPARAM iParam);	
public:
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnBack();
	void SetBtnEnable(int index, int total);
	afx_msg void OnBnClickedBtnFward();
	afx_msg void OnEnChangePath();
	afx_msg void OnBnClickedBtnUp();
};
