
// 10_ListControl练习Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMy10_ListControl练习Dlg 对话框
class CMy10_ListControl练习Dlg : public CDialogEx
{
// 构造
public:
	CMy10_ListControl练习Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY10_LISTCONTROL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	// 男
//	CButton m_rcMan;
	CString m_check;
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
private:
	CComboBox m_people;
	
	CListCtrl m_list;
public:
	afx_msg void OnBnClickedButton1();
private:
public:
//	CString m_age;
private:
	int m_age;
public:
	afx_msg void OnBnClickedButton2();
};
