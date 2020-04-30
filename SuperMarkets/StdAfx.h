// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__3B5A520C_71DF_41D4_8170_A0FB28D24FB3__INCLUDED_)
#define AFX_STDAFX_H__3B5A520C_71DF_41D4_8170_A0FB28D24FB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define IDUM_USER		9000
#define IDUM_STORAGE	9001
#define IDUM_TICKET		9002
#define IDUM_GOODS		9003
#define IDUM_COUNT		9005

#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")   

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__3B5A520C_71DF_41D4_8170_A0FB28D24FB3__INCLUDED_)
