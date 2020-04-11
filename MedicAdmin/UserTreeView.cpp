// UserTreeView.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicAdmin.h"
#include "UserTreeView.h"
#include"Resource.h"
#include"UserAdd.h"
#include"UserA.h"
#include"PwdChange.h"
#include<iterator>
#include"UserQuery.h"


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
	ON_COMMAND(ID_32775, &CUserTreeView::OnUserAdd)
	ON_COMMAND(ID_32773, &CUserTreeView::OnPwdChange)
	ON_COMMAND(ID_32777, &CUserTreeView::OnUserQuery)
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



	imageList.Create(30, 30, ILC_COLOR32, 4, 4);


	CBitmap bitmap[4];

	bitmap[0].LoadBitmapW(IDB_BITMAP_DOCTOR);
	bitmap[1].LoadBitmapW(IDB_BITMAP_MANAGER);
	bitmap[2].LoadBitmapW(IDB_BITMAP_SAL);
	bitmap[3].LoadBitmapW(IDB_BITMAP_NORMAL);

	imageList.Add(&bitmap[0], RGB(0, 0, 0));
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
	//TODO:改成读xml生成treeView的根节点
	CString root[3] = {
		TEXT("医生"),TEXT("管理员"),TEXT("售药员")
	};

	int n = sizeof(root) / sizeof(root[0]);

	for (int i = 0; i < n; i++)
	{
		map<CString, vector<CUserA>> mapVec;
		vector<CUserA> vecUser;

		HTREEITEM item1 = treeCtrl.InsertItem(root[i], 3, 3, NULL);

		m_vecRoots.push_back(root[i]);

		CString filter;
		filter.Format(TEXT("classification='%s'"), root[i]);


		userSet->m_strFilter = filter;
		userSet->Requery();
		userSet->MoveFirst();

		while (!userSet->IsEOF())
		{
			CString addNode;

			addNode.Format(TEXT("%s(%s)"), CString(userSet->m_name), CString(userSet->m_account));

			if (G_LoginName == CString(userSet->m_name)) {

				CString str;

				str.Format(TEXT("[已登录] %s"), addNode);

				treeCtrl.InsertItem(str, i, i, item1);
			}
			else {
				treeCtrl.InsertItem(addNode, i, i, item1);
			}
			CUserA userA;

			userA.m_type = root[i];
			userA.m_userAccount = userSet->m_account;
			userA.m_userName = userSet->m_name;
			userA.m_userPwd = userSet->m_password;

			vecUser.push_back(userA);
			userSet->MoveNext();
		}
		mapVec.insert(make_pair(root[i], vecUser));
		m_vecTreeList.push_back(mapVec);
	}

}

//添加用戶
void CUserTreeView::OnUserAdd()
{
	// TODO: 在此添加命令处理程序代码
	CUserAdd userAddDia;
	userAddDia.DoModal();

	if (userAddDia.m_isAdd) {

		POSITION pos = userAddDia.listUser.GetHeadPosition();

		while (pos != NULL) {

			CUserA u = userAddDia.listUser.GetAt(pos);

			CString userType = u.m_type;
			CString userName = u.m_userName;
			CString userAcount = u.m_userAccount;

			for (size_t m = 0; m < m_vecTreeList.size(); m++)
			{
				map<CString, vector<CUserA>>::iterator iter = m_vecTreeList[m].find(userType);
				if (iter != m_vecTreeList[m].end()) {

					iter->second.push_back(u);
					break;
				}
			}

			CString addNode;
			addNode.Format(TEXT("%s(%s)"), userName, userAcount);

			CTreeCtrl & treeCtrl = GetTreeCtrl();

			HTREEITEM item1 = treeCtrl.GetRootItem();
			CString strType = treeCtrl.GetItemText(item1);
			int i = 0;
			while (!strType.IsEmpty())
			{
				if (userType == strType) {

					treeCtrl.InsertItem(addNode, i, i, item1);

					break;
				}
				i++;
				item1 = treeCtrl.GetNextSiblingItem(item1);
				strType = treeCtrl.GetItemText(item1);

			}

			userAddDia.listUser.GetNext(pos);

		}
	}
}


void CUserTreeView::OnPwdChange()
{
	// TODO: 在此添加命令处理程序代码

	bool isAdmin = false;

	CUserA curUser;
	CPwdChange pwdCh;

	//判断登录用户是否是管理员
	for (size_t m = 0; m < m_vecTreeList.size(); m++)
	{
		map<CString, vector<CUserA>> mapVec = m_vecTreeList[m];


		bool flag = false;
		for (map<CString, vector<CUserA>>::iterator iter = mapVec.begin(); iter != mapVec.end(); iter++) {
			{

				vector <CUserA>tempVec = iter->second;

				for (size_t i = 0; i < tempVec.size(); i++)
				{
					CUserA tempUser = tempVec[i];

					if (tempUser.m_userName.Compare(G_LoginName) == 0) {

						if (iter->first.Compare(CString(TEXT("管理员"))) == 0) {

							isAdmin = true;
						}
						else {
							curUser.m_type = tempUser.m_type;
							curUser.m_userAccount = tempUser.m_userAccount;
							curUser.m_userName = tempUser.m_userName;
							curUser.m_userPwd = tempUser.m_userPwd;
						}
						flag = true;
						break;
					}
				}
				if (flag) {
					break;
				}
			}
		}

		if (flag) {
			break;
		}
	}

	CTreeCtrl& treeCtrl = GetTreeCtrl();
	//管理员可以更改所有人的密码，否则只能更改自己的密码
	if (isAdmin) {
		HTREEITEM selItem = treeCtrl.GetSelectedItem();
		CString selText = treeCtrl.GetItemText(selItem);

		HTREEITEM parentItem = treeCtrl.GetParentItem(selItem);
		CString paText = treeCtrl.GetItemText(parentItem);
		CUserA u;

		for (size_t m = 0; m < m_vecTreeList.size(); m++)
		{
			map<CString, vector<CUserA>>::iterator iter = m_vecTreeList[m].find(paText);
			if (iter != m_vecTreeList[m].end()) {

				//iter->second.push_back(u);

				vector < CUserA>tempVec = iter->second;

				for (size_t i = 0; i < tempVec.size(); i++)
				{
					CUserA tempU = tempVec[i];

					CString text;
					text.Format(_T("%s(%s)"), tempU.m_userName, tempU.m_userAccount);
					CString text2;
					text2.Format(_T("[已登录] %s(%s)"), tempU.m_userName, tempU.m_userAccount);
					if (text.Compare(selText) == 0 || text2.Compare(selText) == 0) {

						u.m_type = tempU.m_type;
						u.m_userAccount = tempU.m_userAccount;
						u.m_userName = tempU.m_userName;
						u.m_userPwd = tempU.m_userPwd;

						break;
					}
				}
				break;
			}
		}



		pwdCh.SetName(u.m_userName);
		pwdCh.SetAccount(u.m_userAccount);
		pwdCh.SetPwd(u.m_userPwd);
	}
	else {
		pwdCh.SetName(curUser.m_userName);
		pwdCh.SetAccount(curUser.m_userAccount);
		pwdCh.SetPwd(curUser.m_userPwd);
	}

	pwdCh.DoModal();

	//程序重启
	wchar_t pBuf[MAX_PATH];
	//获取应用程序完全路径，比 GetCurrentDirectory 好用多了
	GetModuleFileName(NULL, pBuf, MAX_PATH);

	STARTUPINFO startupinfo;
	PROCESS_INFORMATION proc_info;
	memset(&startupinfo, 0, sizeof(STARTUPINFO));
	startupinfo.cb = sizeof(STARTUPINFO);
	// 最重要的地方
	::CreateProcess(pBuf, NULL, NULL, NULL, FALSE,
		NORMAL_PRIORITY_CLASS, NULL, NULL, &startupinfo, &proc_info);

	PostMessage(WM_QUIT);
}


void CUserTreeView::OnUserQuery()
{
	// TODO: 在此添加命令处理程序代码
	CUserQuery userQuery;
	CString condition;
	if (userQuery.DoModal() == IDOK) {
		condition = userQuery.GetCondition();

		int markRoot = 0, markChild = 0;
		CString strRoot, strChild;
		//查找用戶
		for (size_t m = 0; m < m_vecTreeList.size(); m++)
		{
			map<CString, vector<CUserA>> mapVec = m_vecTreeList[m];


			bool flag = false;
			for (map<CString, vector<CUserA>>::iterator iter = mapVec.begin(); iter != mapVec.end(); iter++) {
				{

					vector <CUserA>tempVec = iter->second;

					for (size_t i = 0; i < tempVec.size(); i++)
					{
						CUserA tempUser = tempVec[i];
						//查找到了
						if (tempUser.m_userName.Find(condition, 0) != -1 || tempUser.m_userAccount.Find(condition, 0) != -1) {
							markRoot = m;
							markChild = i;

							flag = true;
							break;
						}
					}
					if (flag) {
						break;
					}
				}
			}

			if (flag) {
				break;
			}
		}

		CTreeCtrl & treeCtrl = GetTreeCtrl();

		HTREEITEM node;
		HTREEITEM nextNode;
		
		//获取第一个根节点
		node = treeCtrl.GetRootItem();
		nextNode = node;
		
		/*
		*获取每个根节点的所有下层的第一个节点
		*/
		vector<HTREEITEM>vecItem;

		while (nextNode != NULL) {

			//获取所有下层节点中的第一个节点
			while (node != NULL) {

				vecItem.push_back(node);
				node = treeCtrl.GetChildItem(node);
			}
			//从最末端节点开始，获取它的所有兄弟节点，然后退回到上一层重复这个操作
			for (int q = (int)vecItem.size() - 1; q > -1; q--)
			{

				HTREEITEM endItem = vecItem[q];

				HTREEITEM endItemSbiling = endItem;

				while (endItemSbiling != NULL) {

					CString itemText = treeCtrl.GetItemText(endItemSbiling);

					if (itemText.Find(condition) != -1) {

						treeCtrl.SelectItem(endItemSbiling);
						treeCtrl.Expand(endItemSbiling, TVM_EXPAND);
						vecItem.clear();
						return;

					}

					endItemSbiling = treeCtrl.GetNextItem(endItemSbiling, TVGN_NEXT);

				}
			}
			//每完成一层就清空
			vecItem.clear();

			//顶层根节点的兄弟节点
			nextNode = treeCtrl.GetNextItem(nextNode, TVGN_NEXT);
			node = nextNode;
		}
	}
}