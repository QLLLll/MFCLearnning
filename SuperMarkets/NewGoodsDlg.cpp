// NewGoodsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "supermarkets.h"
#include "NewGoodsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewGoodsDlg dialog


CNewGoodsDlg::CNewGoodsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewGoodsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewGoodsDlg)
	m_goodsid = _T("");
	m_goodsname = _T("");
	m_goodsvalue = 0.0;
	m_barcode = _T("");
	m_main = _T("");
	m_part = _T("");
	m_info = _T("");
	//}}AFX_DATA_INIT
}


void CNewGoodsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewGoodsDlg)
	DDX_Text(pDX, IDC_GoodsID, m_goodsid);
	DDX_Text(pDX, IDC_GoodsName, m_goodsname);
	DDX_Text(pDX, IDC_VALUE, m_goodsvalue);
	DDX_Text(pDX, IDC_BARCODE, m_barcode);
	DDX_Text(pDX, IDC_EDIT1, m_main);
	DDX_Text(pDX, IDC_EDIT2, m_part);
	DDX_Text(pDX, IDC_EDIT3, m_info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewGoodsDlg, CDialog)
	//{{AFX_MSG_MAP(CNewGoodsDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewGoodsDlg message handlers
