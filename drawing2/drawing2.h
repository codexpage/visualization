// drawing2.h : main header file for the DRAWING2 application
//

#if !defined(AFX_DRAWING2_H__B894AAD2_2B5D_4454_9F77_107FA13F54AE__INCLUDED_)
#define AFX_DRAWING2_H__B894AAD2_2B5D_4454_9F77_107FA13F54AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDrawing2App:
// See drawing2.cpp for the implementation of this class
//

class CDrawing2App : public CWinApp
{
public:
	CDrawing2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawing2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDrawing2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWING2_H__B894AAD2_2B5D_4454_9F77_107FA13F54AE__INCLUDED_)
