// drawing4View.h : interface of the CDrawing4View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWING4VIEW_H__22155594_2862_4298_BD41_CC7C61D19228__INCLUDED_)
#define AFX_DRAWING4VIEW_H__22155594_2862_4298_BD41_CC7C61D19228__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDrawing4View : public CView
{
protected: // create from serialization only
	CDrawing4View();
	DECLARE_DYNCREATE(CDrawing4View)

// Attributes
public:

	int gridwidth;
	int gridx;
	int gridy;
	void drawline(int x1, int y1,int x2,int y2,CDC* pDC,int RGB);
	CDrawing4Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawing4View)
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
	virtual ~CDrawing4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawing4View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in drawing4View.cpp
inline CDrawing4Doc* CDrawing4View::GetDocument()
   { return (CDrawing4Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWING4VIEW_H__22155594_2862_4298_BD41_CC7C61D19228__INCLUDED_)
