
// ForTreeCtrlDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CForTreeCtrlDlg 对话框
class CForTreeCtrlDlg : public CDialogEx
{
// 构造
public:
	CForTreeCtrlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORTREECTRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	void CForTreeCtrlDlg::func(HTREEITEM root, CString find);
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CTreeCtrl treeCtrl;
	CString m_find;
public:
	afx_msg void OnBnClickedButton1();
};
