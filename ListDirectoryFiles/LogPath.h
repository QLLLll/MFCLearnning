#pragma once
#include "afxwin.h"
#define WM_SENDPATH WM_USER+134

// CLogPath 对话框

class CLogPath : public CDialogEx
{
	DECLARE_DYNAMIC(CLogPath)

public:
	CLogPath(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogPath();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOG_PATH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listBox;
	afx_msg void OnLbnSelchangeList1();
};
