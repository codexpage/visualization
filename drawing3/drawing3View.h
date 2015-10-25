// drawing3View.h : interface of the CDrawing3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWING3VIEW_H__0A70EC1B_EA5C_4384_87E3_D4D5B23E4EBB__INCLUDED_)
#define AFX_DRAWING3VIEW_H__0A70EC1B_EA5C_4384_87E3_D4D5B23E4EBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDrawing3View : public CView
{
protected: // create from serialization only
	CDrawing3View();
	DECLARE_DYNCREATE(CDrawing3View)

// Attributes
public:
	int gridwidth;
	int gridx;
	int gridy;
	
	CDrawing3Doc* GetDocument();
	//void drawline(int x1, int y1,int x2,int y2,CDC* pDC);
	void drawline(int x1, int y1,int x2,int y2,CDC* pDC,int RGB);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawing3View)
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
	virtual ~CDrawing3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawing3View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in drawing3View.cpp
inline CDrawing3Doc* CDrawing3View::GetDocument()
   { return (CDrawing3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWING3VIEW_H__0A70EC1B_EA5C_4384_87E3_D4D5B23E4EBB__INCLUDED_)
