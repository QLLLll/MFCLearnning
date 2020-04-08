#pragma once


// CMedicListView 视图

class CMedicListView : public CListView
{
	DECLARE_DYNCREATE(CMedicListView)

protected:
	CMedicListView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMedicListView();

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
};


