
// MyNoteDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include"DialogFind.h"


// CMyNoteDlg 对话框
class CMyNoteDlg : public CDialogEx
{
// 构造
public:
	CMyNoteDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYNOTE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnFindStr(WPARAM wParam, LPARAM iParam);
	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnOpenFile();
	afx_msg void OnClose();
	afx_msg void OnNewFile();
private:
	CString m_fileName;
	CDialogFind m_diaFind;
public:
	afx_msg void OnSaveFile();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	void ReadAnsi(CFile & file);
	void ReadUTF8(CFile & file);
	void ReadUnicode(CFile & file);
	afx_msg void OnSaveAs();
	afx_msg void OnFind();
	afx_msg void OnFont();
	void SetTitle();
private:
	CFont m_font;
public:
	afx_msg void OnInsertDate();
private:
	BOOL m_findOpen;
public:
	afx_msg void OnCopyOther();
};
