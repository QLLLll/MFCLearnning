// SuperMarkets.h : main header file for the SUPERMARKETS application
//

#if !defined(AFX_SUPERMARKETS_H__230EA553_8FD4_48AE_8DC9_FB4C7E93BE00__INCLUDED_)
#define AFX_SUPERMARKETS_H__230EA553_8FD4_48AE_8DC9_FB4C7E93BE00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSuperMarketsApp:
// See SuperMarkets.cpp for the implementation of this class
//

class CSuperMarketsApp : public CWinApp
{
public:
	CSuperMarketsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperMarketsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSuperMarketsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERMARKETS_H__230EA553_8FD4_48AE_8DC9_FB4C7E93BE00__INCLUDED_)
