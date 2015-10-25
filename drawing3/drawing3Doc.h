// drawing3Doc.h : interface of the CDrawing3Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWING3DOC_H__D6E13CAB_8E00_4C39_8062_849B1787950D__INCLUDED_)
#define AFX_DRAWING3DOC_H__D6E13CAB_8E00_4C39_8062_849B1787950D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDrawing3Doc : public CDocument
{
protected: // create from serialization only
	CDrawing3Doc();
	DECLARE_DYNCREATE(CDrawing3Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawing3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawing3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawing3Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWING3DOC_H__D6E13CAB_8E00_4C39_8062_849B1787950D__INCLUDED_)
