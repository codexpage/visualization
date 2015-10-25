// drawing3.h : main header file for the DRAWING3 application
//

#if !defined(AFX_DRAWING3_H__4A6AE189_DD67_4386_A962_CE02E29534CE__INCLUDED_)
#define AFX_DRAWING3_H__4A6AE189_DD67_4386_A962_CE02E29534CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDrawing3App:
// See drawing3.cpp for the implementation of this class
//

class CDrawing3App : public CWinApp
{
public:
	CDrawing3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawing3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDrawing3App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWING3_H__4A6AE189_DD67_4386_A962_CE02E29534CE__INCLUDED_)
