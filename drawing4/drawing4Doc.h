// drawing4Doc.h : interface of the CDrawing4Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWING4DOC_H__37C79CE0_2916_44E7_A353_5F6EA94B75DC__INCLUDED_)
#define AFX_DRAWING4DOC_H__37C79CE0_2916_44E7_A353_5F6EA94B75DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDrawing4Doc : public CDocument
{
protected: // create from serialization only
	CDrawing4Doc();
	DECLARE_DYNCREATE(CDrawing4Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawing4Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawing4Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawing4Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWING4DOC_H__37C79CE0_2916_44E7_A353_5F6EA94B75DC__INCLUDED_)
