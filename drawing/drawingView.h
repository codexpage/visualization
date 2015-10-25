// drawingView.h : interface of the CDrawingView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWINGVIEW_H__D6FDEE40_C5B4_416F_A59F_28286EC66FA0__INCLUDED_)
#define AFX_DRAWINGVIEW_H__D6FDEE40_C5B4_416F_A59F_28286EC66FA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDrawingView : public CView
{
protected: // create from serialization only
	CDrawingView();
	DECLARE_DYNCREATE(CDrawingView)

// Attributes
public:
	CDrawingDoc* GetDocument();
	void drawline(int x1, int y1,int x2,int y2,CDC* pDC);
	//void draw(int J,int K,int gridx,int gridy,int gridwidth, CDC* pDC,double mat[][5]);


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawingView)
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
	virtual ~CDrawingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawingView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in drawingView.cpp
inline CDrawingDoc* CDrawingView::GetDocument()
   { return (CDrawingDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWINGVIEW_H__D6FDEE40_C5B4_416F_A59F_28286EC66FA0__INCLUDED_)
