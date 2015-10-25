// drawing4.h : main header file for the DRAWING4 application
//

#if !defined(AFX_DRAWING4_H__CADEDA05_E50D_4B45_B525_61CB105B3DA2__INCLUDED_)
#define AFX_DRAWING4_H__CADEDA05_E50D_4B45_B525_61CB105B3DA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDrawing4App:
// See drawing4.cpp for the implementation of this class
//

class CDrawing4App : public CWinApp
{
public:
	CDrawing4App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawing4App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDrawing4App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWING4_H__CADEDA05_E50D_4B45_B525_61CB105B3DA2__INCLUDED_)
