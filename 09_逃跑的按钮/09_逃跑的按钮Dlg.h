
// 09_逃跑的按钮Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "MyButton.h"


// CMy09_逃跑的按钮Dlg 对话框
class CMy09_逃跑的按钮Dlg : public CDialogEx
{
// 构造
public:
	CMy09_逃跑的按钮Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY09__DIALOG };
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
	CButton m_btn;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	MyButton m_myBtn;
	int m_w;
	int m_h;
};
