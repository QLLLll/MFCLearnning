
// 08_HuanDengPianDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMy08_HuanDengPianDlg 对话框
class CMy08_HuanDengPianDlg : public CDialogEx
{
// 构造
public:
	CMy08_HuanDengPianDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY08_HUANDENGPIAN_DIALOG };
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
	virtual void OnOK();
private:
	CStatic m_image;
	int m_w;
	int m_h;
public:
	afx_msg void OnBnClickedButton1();
private:
	bool m_isAuto;
	CButton m_preImg;
	CButton m_nextImg;
	CButton m_autoImg;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
