#pragma once


// CUserQuery 对话框

class CUserQuery : public CDialogEx
{
	DECLARE_DYNAMIC(CUserQuery)

public:
	CUserQuery(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserQuery();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_USER_QUERY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_qCondtion;
public:
	afx_msg void OnBnClickedButton1();
	CString GetCondition() {
		return m_qCondtion;
	}
};
