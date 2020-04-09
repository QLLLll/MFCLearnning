// UserTreeView.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicAdmin.h"
#include "UserTreeView.h"
#include"Resource.h"

extern CString G_LoginName;
// CUserTreeView

IMPLEMENT_DYNCREATE(CUserTreeView, CTreeView)

CUserTreeView::CUserTreeView()
{

}

CUserTreeView::~CUserTreeView()
{
}

BEGIN_MESSAGE_MAP(CUserTreeView, CTreeView)
END_MESSAGE_MAP()


// CUserTreeView 诊断

#ifdef _DEBUG
void CUserTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserTreeView 消息处理程序


void CUserTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	

	imageList.Create(30,30,ILC_COLOR32,4,4);


	CBitmap bitmap[4];

	bitmap[0].LoadBitmapW(IDB_BITMAP_DOCTOR);
	bitmap[1].LoadBitmapW(IDB_BITMAP_MANAGER);
	bitmap[2].LoadBitmapW(IDB_BITMAP_SAL);
	bitmap[3].LoadBitmapW(IDB_BITMAP_NORMAL);

	imageList.Add(&bitmap[0],RGB(0,0,0));
	imageList.Add(&bitmap[1], nullptr);
	imageList.Add(&bitmap[2], nullptr);
	imageList.Add(&bitmap[3], nullptr);


	CTreeCtrl & treeCtrl = GetTreeCtrl();
	treeCtrl.SetImageList(&imageList, TVSIL_NORMAL);

	//treeCtrl.InsertItem(TEXT("text"), 0, 0, NULL);

	CMedicAdminDoc *pDoc = (CMedicAdminDoc *)GetDocument();
	CUserSet * userSet = pDoc->GetUserSet();

	if (userSet->IsOpen() == FALSE) {
		userSet->Open(CRecordset::dynaset);
	}

	CString root[3] = {
		TEXT("医生"),TEXT("管理员"),TEXT("售药员")
	};

	int n = sizeof(root) / sizeof(root[0]);

	for (int  i = 0; i < n; i++)
	{
		HTREEITEM item1=treeCtrl.InsertItem(root[i], 3, 3, NULL);

		CString filter;
		filter.Format(TEXT("classification='%s'"), root[i]);

		userSet->m_strFilter = filter;
		userSet->Requery();
		userSet->MoveFirst();

		while (!userSet->IsEOF())
		{
			if (G_LoginName == CString(userSet->m_name)) {

				CString str;

				str.Format(TEXT("[已登录] %s"), CString(userSet->m_name));

				treeCtrl.InsertItem(str, i, i, item1);
			}
			else {
				treeCtrl.InsertItem(CString(userSet->m_name), i, i, item1);
			}
			userSet->MoveNext();
		}

	}

}
