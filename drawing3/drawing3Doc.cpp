// drawing3Doc.cpp : implementation of the CDrawing3Doc class
//

#include "stdafx.h"
#include "drawing3.h"

#include "drawing3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawing3Doc

IMPLEMENT_DYNCREATE(CDrawing3Doc, CDocument)

BEGIN_MESSAGE_MAP(CDrawing3Doc, CDocument)
	//{{AFX_MSG_MAP(CDrawing3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawing3Doc construction/destruction

CDrawing3Doc::CDrawing3Doc()
{
	// TODO: add one-time construction code here

}

CDrawing3Doc::~CDrawing3Doc()
{
}

BOOL CDrawing3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDrawing3Doc serialization

void CDrawing3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDrawing3Doc diagnostics

#ifdef _DEBUG
void CDrawing3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawing3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawing3Doc commands
