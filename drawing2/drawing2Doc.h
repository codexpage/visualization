// drawing2Doc.h : interface of the CDrawing2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWING2DOC_H__AE485595_FDB8_49F3_BF87_428852C016E0__INCLUDED_)
#define AFX_DRAWING2DOC_H__AE485595_FDB8_49F3_BF87_428852C016E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDrawing2Doc : public CDocument
{
protected: // create from serialization only
	CDrawing2Doc();
	DECLARE_DYNCREATE(CDrawing2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawing2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawing2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawing2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWING2DOC_H__AE485595_FDB8_49F3_BF87_428852C016E0__INCLUDED_)
