#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include"UserSet.h"

// CUserDelete 对话框

class CUserDelete : public CDialogEx
{
	DECLARE_DYNAMIC(CUserDelete)

public:
	CUserDelete(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserDelete();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_userType;
	CString m_userCount;
	CListCtrl m_listUser;
	CUserSet m_userSet;
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
};
