
// MedicAdminDoc.h : CMedicAdminDoc 类的接口
//


#pragma once
#include"MedicSet.h"
#include"UserSet.h"

class CMedicAdminDoc : public CDocument
{
protected: // 仅从序列化创建
	CMedicAdminDoc();
	DECLARE_DYNCREATE(CMedicAdminDoc)

// 特性
public:
	CMedicSet * GetMedicSet() {
		return &m_pMySet;
	}
	CUserSet *GetUserSet() {
		return &m_pUserSet;
	}

// 操作
private:
	CMedicSet m_pMySet;
	CUserSet m_pUserSet;

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMedicAdminDoc();
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
