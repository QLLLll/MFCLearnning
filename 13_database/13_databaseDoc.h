
// 13_databaseDoc.h : CMy13_databaseDoc 类的接口
//


#pragma once
#include"13_databaseSet.h"

class CMy13_databaseDoc : public CDocument
{
protected: // 仅从序列化创建
	CMy13_databaseDoc();
	DECLARE_DYNCREATE(CMy13_databaseDoc)

// 特性
public:

// 操作
public:
	CMy13_databaseSet *GetSet() {
		return &pSet;
	}

private:
	CMy13_databaseSet pSet;

// 重写
public:
	virtual BOOL OnNewDocument();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMy13_databaseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
