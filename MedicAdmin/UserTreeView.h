#pragma once


// CUserTreeView 视图
#include"MedicAdminDoc.h"
#include"UserSet.h"
#include<map>
#include<vector>
#include"UserA.h"
using namespace std;
class CUserTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CUserTreeView)

protected:
	CUserTreeView();           // 动态创建所使用的受保护的构造函数
	virtual ~CUserTreeView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
private:
	CImageList imageList;
	vector<map<CString, vector<CUserA>>> m_vecTreeList;
public:
	afx_msg void OnUserAdd();
	afx_msg void OnPwdChange();
private:
	vector<CString> m_vecRoots;
public:
	afx_msg void OnUserQuery();
};


