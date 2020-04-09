// MedicListView.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicAdmin.h"
#include "MedicListView.h"
#include"MedicAdminDoc.h"
#include"MedicSet.h"

// CMedicListView

IMPLEMENT_DYNCREATE(CMedicListView, CListView)

CMedicListView::CMedicListView()
{

}

CMedicListView::~CMedicListView()
{
}

BEGIN_MESSAGE_MAP(CMedicListView, CListView)
END_MESSAGE_MAP()


// CMedicListView 诊断

#ifdef _DEBUG
void CMedicListView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CMedicListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMedicListView 消息处理程序


void CMedicListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CListCtrl & listCtrl = this->GetListCtrl();

	listCtrl.ModifyStyle(0, LVS_REPORT);

	listCtrl.SetExtendedStyle(listCtrl.GetExtendedStyle()
		|| LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	CString head[] = {
		TEXT("药品代号"),TEXT("药品名称"),TEXT("药品类别"),
	TEXT("库存数目"),TEXT("出厂公司"),TEXT("产地"),
	TEXT("出厂时间"),TEXT("保质期(月)"),TEXT("单价(元)")
	};

	int n = sizeof(head) / sizeof(head[0]);

	for (int  i = 0; i < n; i++)
	{
		listCtrl.InsertColumn(i, head[i], LVCFMT_CENTER, 130);
	}

	CMedicAdminDoc *pDoc = (CMedicAdminDoc*)GetDocument();
	CMedicSet *pMySet = pDoc->GetMedicSet();

	if (pMySet->IsOpen() == FALSE) {
		pMySet->Open(CRecordset::dynaset);
	}

	pMySet->MoveFirst();
	
	/*CStringA	m_id;
	CStringA	m_name;
	CStringA	m_classification;
	CTime	m_produceDate;
	CStringA	m_producePlace;
	CStringA	m_discription;
	CStringA	m_produceCompany;
	long	m_quelityAssurance;
	long	m_unitPrice;
	long	m_number;*/
	int i = 0;
	while (!pMySet->IsEOF()) {
		
		listCtrl.InsertItem(i, CString(pMySet->m_id));
		
		int j = 1;

		listCtrl.SetItemText(i, j++, CString(pMySet->m_name));
		listCtrl.SetItemText(i, j++, CString(pMySet->m_classification));

		CString strNum;
		strNum.Format(TEXT("%d"), pMySet->m_number);
		listCtrl.SetItemText(i, j++, strNum);
		listCtrl.SetItemText(i, j++, CString(pMySet->m_produceCompany));
		listCtrl.SetItemText(i, j++, CString(pMySet->m_producePlace));
		
		/*CString strTime;
		strTime.Format(TEXT("%d年%d月%d日"), 
			pMySet->m_produceDate.GetYear(), 
			pMySet->m_produceDate.GetMonth(), 
			pMySet->m_produceDate.GetDay());*/

		listCtrl.SetItemText(i, j++, pMySet->m_produceDate.Format(TEXT("%Y-%m-%d")));

		CString strQulityAss;
		strQulityAss.Format(TEXT("%d"), pMySet->m_quelityAssurance);
		listCtrl.SetItemText(i, j++, strQulityAss);

		CString strUnit;
		strUnit.Format(TEXT("%d"), pMySet->m_unitPrice);
		listCtrl.SetItemText(i, j++, strUnit);

		i++;
		pMySet->MoveNext();
	}
	UpdateData(FALSE);

}
