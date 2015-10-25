// drawing2View.h : interface of the CDrawing2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWING2VIEW_H__114A85A9_8B9D_445C_A756_231C2A6F494F__INCLUDED_)
#define AFX_DRAWING2VIEW_H__114A85A9_8B9D_445C_A756_231C2A6F494F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDrawing2View : public CView
{
protected: // create from serialization only
	CDrawing2View();
	DECLARE_DYNCREATE(CDrawing2View)

// Attributes
public:
	CDrawing2Doc* GetDocument();
		void drawline(int x1, int y1,int x2,int y2,CDC* pDC);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawing2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawing2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawing2View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in drawing2View.cpp
inline CDrawing2Doc* CDrawing2View::GetDocument()
   { return (CDrawing2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWING2VIEW_H__114A85A9_8B9D_445C_A756_231C2A6F494F__INCLUDED_)
