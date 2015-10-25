// drawing2Doc.cpp : implementation of the CDrawing2Doc class
//

#include "stdafx.h"
#include "drawing2.h"

#include "drawing2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawing2Doc

IMPLEMENT_DYNCREATE(CDrawing2Doc, CDocument)

BEGIN_MESSAGE_MAP(CDrawing2Doc, CDocument)
	//{{AFX_MSG_MAP(CDrawing2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawing2Doc construction/destruction

CDrawing2Doc::CDrawing2Doc()
{
	// TODO: add one-time construction code here

}

CDrawing2Doc::~CDrawing2Doc()
{
}

BOOL CDrawing2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDrawing2Doc serialization

void CDrawing2Doc::Serialize(CArchive& ar)
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
// CDrawing2Doc diagnostics

#ifdef _DEBUG
void CDrawing2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawing2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawing2Doc commands
