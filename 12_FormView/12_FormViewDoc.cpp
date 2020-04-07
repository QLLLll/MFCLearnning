
// 12_FormViewDoc.cpp : CMy12_FormViewDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "12_FormView.h"
#endif

#include "12_FormViewDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy12_FormViewDoc

IMPLEMENT_DYNCREATE(CMy12_FormViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy12_FormViewDoc, CDocument)
END_MESSAGE_MAP()


// CMy12_FormViewDoc 构造/析构

CMy12_FormViewDoc::CMy12_FormViewDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMy12_FormViewDoc::~CMy12_FormViewDoc()
{
}

BOOL CMy12_FormViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMy12_FormViewDoc 序列化

void CMy12_FormViewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMy12_FormViewDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMy12_FormViewDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMy12_FormViewDoc::SetSearchContent(const CString& value)
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

// CMy12_FormViewDoc 诊断

#ifdef _DEBUG
void CMy12_FormViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy12_FormViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy12_FormViewDoc 命令


void CMy12_FormViewDoc::DeleteContents()
{
	// TODO: 在此添加专用代码和/或调用基类
	/*while (m_list.GetHeadPosition() != NULL) {

		CStudent stu = m_list.RemoveHead();

	}
	m_pos = NULL;*/
	m_list.RemoveAll();
	m_pos = NULL;


	CDocument::DeleteContents();
}
