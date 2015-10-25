// drawing4Doc.cpp : implementation of the CDrawing4Doc class
//

#include "stdafx.h"
#include "drawing4.h"

#include "drawing4Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawing4Doc

IMPLEMENT_DYNCREATE(CDrawing4Doc, CDocument)

BEGIN_MESSAGE_MAP(CDrawing4Doc, CDocument)
	//{{AFX_MSG_MAP(CDrawing4Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawing4Doc construction/destruction

CDrawing4Doc::CDrawing4Doc()
{
	// TODO: add one-time construction code here

}

CDrawing4Doc::~CDrawing4Doc()
{
}

BOOL CDrawing4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDrawing4Doc serialization

void CDrawing4Doc::Serialize(CArchive& ar)
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
// CDrawing4Doc diagnostics

#ifdef _DEBUG
void CDrawing4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawing4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawing4Doc commands
