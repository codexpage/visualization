// drawing.h : main header file for the DRAWING application
//

#if !defined(AFX_DRAWING_H__E0DBF54E_A57B_4F20_8EF9_FC39DBE2B4C3__INCLUDED_)
#define AFX_DRAWING_H__E0DBF54E_A57B_4F20_8EF9_FC39DBE2B4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDrawingApp:
// See drawing.cpp for the implementation of this class
//

class CDrawingApp : public CWinApp
{
public:
	CDrawingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDrawingApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWING_H__E0DBF54E_A57B_4F20_8EF9_FC39DBE2B4C3__INCLUDED_)
