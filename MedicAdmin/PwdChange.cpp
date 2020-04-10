// PwdChange.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicAdmin.h"
#include "PwdChange.h"
#include "afxdialogex.h"


// CPwdChange 对话框

IMPLEMENT_DYNAMIC(CPwdChange, CDialogEx)

CPwdChange::CPwdChange(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CHAN_PWD, pParent)
	, m_uName(_T(""))
	, m_uAccount(_T(""))
	, m_uPwd(_T(""))
	, m_newPwd(_T(""))
	, m_uYzm(0)
	, m_yzm2(0)
{

}

CPwdChange::~CPwdChange()
{
}

void CPwdChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_uName);
	DDX_Text(pDX, IDC_EDIT2, m_uAccount);
	DDX_Text(pDX, IDC_EDIT3, m_uPwd);
	DDX_Text(pDX, IDC_EDIT4, m_newPwd);
	//  DDX_Text(pDX, IDC_EDIT6, m_uYzm);
	DDX_Control(pDX, IDC_BUTTON4, m_btnYzm);
	DDX_Text(pDX, IDC_EDIT6, m_yzm2);
}


BEGIN_MESSAGE_MAP(CPwdChange, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &CPwdChange::OnBnClickedButton4)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON5, &CPwdChange::OnBnClickedButton5)
END_MESSAGE_MAP()


// CPwdChange 消息处理程序


BOOL CPwdChange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(FALSE);
	
	//打开的时候产生验证码
	//每次启动生成的随机数都是一样的，根本不随机
	m_uYzm =123456+ rand()%10000;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPwdChange::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//发送验证码
	typedef int(__stdcall*pSend)(LPCSTR sCmd);
	HINSTANCE hdll;
	pSend mySend;
	hdll = LoadLibrary(TEXT("blat32/blat.dll"));
	mySend = (pSend)GetProcAddress(hdll, "Send");
	//int x = mySend(cmd);

	CString yzm;
	yzm.Format(TEXT("验证码:%d"),m_uYzm);

	CString cmd2;// = TEXT("-to kwjf11@sina.com -subject 更改密码 -body '%s' -u 576484879@qq.com -pw lakqyyyykfnrbehi -charset utf-8");
	cmd2.Format(TEXT("-to kwjf11@sina.com -subject 更改密码 -body %s -u 576484879@qq.com -pw lakqyyyykfnrbehi -charset utf-8"), yzm);
	wchar_t *sBuf = cmd2.AllocSysString();
	DWORD dBufSize = WideCharToMultiByte(CP_OEMCP, 0, sBuf, -1, NULL, 0, NULL, FALSE);

	//分配目标缓存
	char *dBuf = new char[dBufSize];
	memset(dBuf, 0, dBufSize);

	//转换
	int nRet = WideCharToMultiByte(CP_OEMCP, 0, sBuf, -1, dBuf, dBufSize, NULL, FALSE);


	int x = mySend(dBuf);

	m_btnYzm.EnableWindow(FALSE);

	SetTimer(1, 1000, NULL);

}


void CPwdChange::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	static int i = 60;

	if (nIDEvent == 1) {

		if (i-- >=1) {
			CString str;
			str.Format(TEXT("剩余：%ds"), i);

			m_btnYzm.SetWindowTextW(str);

		}
		else {

			i = 60;
			
			CString str= TEXT("获取验证码");
			m_btnYzm.EnableWindow(TRUE);
			m_btnYzm.SetWindowTextW(str);

			KillTimer(1);

			m_uYzm = 654321 + rand() % 10000;

		}

	}


	CDialogEx::OnTimer(nIDEvent);
}


void CPwdChange::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_yzm2 < 10000 || m_yzm2 != m_uYzm) {
		MessageBox(_T("验证码输入不正确，请在60秒内重写输入"));
		return;
	}
	else {
		//TODO: 更改密码
		//MessageBox(_T("更改密码"));
		if (m_userSet.IsOpen() == FALSE) {
			m_userSet.Open(CRecordset::dynaset);
		}

		CString filter;
		filter.Format(TEXT("account='%s'"), m_uAccount);
		m_userSet.m_strFilter = filter;
		m_userSet.Requery();

		m_userSet.Edit();

		m_userSet.m_password = m_newPwd;

		m_userSet.Update();
		MessageBox(TEXT("修改成功"));

		CDialogEx::OnOK();
	}
}
