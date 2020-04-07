
// 11_documentDoc.cpp : CMy11_documentDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "11_document.h"
#endif

#include "11_documentDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy11_documentDoc

IMPLEMENT_DYNCREATE(CMy11_documentDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy11_documentDoc, CDocument)
END_MESSAGE_MAP()


// CMy11_documentDoc 构造/析构

CMy11_documentDoc::CMy11_documentDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMy11_documentDoc::~CMy11_documentDoc()
{
}

BOOL CMy11_documentDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMy11_documentDoc 序列化

void CMy11_documentDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		ar << m_num;

		for (int i = 0; i < m_num; i++)
		{
			ar << m_point[i];
		}
	}
	else
	{
		// TODO: 在此添加加载代码
		ar >> m_num;
		for (int i = 0; i < m_num; i++)
		{
			ar >> m_point[i];
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMy11_documentDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMy11_documentDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMy11_documentDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy11_documentDoc 诊断

#ifdef _DEBUG
void CMy11_documentDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy11_documentDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy11_documentDoc 命令


void CMy11_documentDoc::DeleteContents()
{
	// TODO: 在此添加专用代码和/或调用基类

	m_num = 0;

	memset(&m_point, 0, sizeof(m_point));

	CDocument::DeleteContents();
}
