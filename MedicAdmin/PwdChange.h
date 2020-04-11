#pragma once


// CPwdChange 对话框
#include"UserSet.h"
#include "afxwin.h"
#include"blat32/blatdll.h"
#pragma  comment(lib,"blat")
class CPwdChange : public CDialogEx
{
	DECLARE_DYNAMIC(CPwdChange)

public:
	CPwdChange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPwdChange();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHAN_PWD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_uName;
	CString m_uAccount;
	CString m_uPwd;
	CString m_newPwd;
	int m_uYzm;//生成的验证码
	int m_yzm2;//输入的验证码
	CUserSet m_userSet;

public:
	void SetName(CString uName) {
		this->m_uName = uName;
	}
	void SetAccount(CString uAccount) {
		this->m_uAccount = uAccount;
	}
	void SetPwd(CString uPwd) {
		this->m_uPwd = uPwd;
	}

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton4();
private:
	CButton m_btnYzm;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton5();
	
};
