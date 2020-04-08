#pragma once


// CUserLogin 对话框
#include"UserSet.h"
#include "afxwin.h"
class CUserLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CUserLogin)

public:
	CUserLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserLogin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	
	

	virtual void OnOK();
public:
	afx_msg void OnClose();

	// TODO: 在此添加专用代码和/或调用基类
	

	
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
private:
	CComboBox m_userClassify;
	CString m_uName;
	CString m_uPwd;
	CUserSet userSet;

public:
	CString GetLoginUserName() {
		return m_uName;
	}
};
