
// TestSRDllDlg.h : 头文件
//

#pragma once
#define FLAG 0
#include"tbl_dll.h"
#include"MyTestDLL.h"
#include"Interface.h"
# if FLAG
#include"MyTestDLL.h"
#pragma  comment(lib,"MyTestDLL")
#endif
// CTestSRDllDlg 对话框
class CTestSRDllDlg : public CDialogEx
{
// 构造
public:
	CTestSRDllDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTSRDLL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnClose();

private:
	Ctbl_dll *m_tbl;
public:
	afx_msg void OnBnClickedButton1();
private:
	CString m_path;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
