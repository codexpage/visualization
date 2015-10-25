// drawingView.cpp : implementation of the CDrawingView class
//

#include "stdafx.h"
#include "drawing.h"

#include "drawingDoc.h"
#include "drawingView.h"

#include <iostream>


#include <conio.h>

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawingView

IMPLEMENT_DYNCREATE(CDrawingView, CView)

BEGIN_MESSAGE_MAP(CDrawingView, CView)
	//{{AFX_MSG_MAP(CDrawingView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawingView construction/destruction

CDrawingView::CDrawingView()
{
	// TODO: add construction code here

}

CDrawingView::~CDrawingView()
{
}

BOOL CDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawingView drawing

void CDrawingView::OnDraw(CDC* pDC)
{
	CDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//=============


	int gridwidth=90;
	int gridx=80;
	int gridy=80;

	//draw the grid
	int i=0;
	for( i=0;i<5;i++){
		drawline(gridx+i*gridwidth,gridy,gridx+i*gridwidth,gridy+4*gridwidth,pDC);//vertical
		drawline(gridx,gridy+i*gridwidth,gridx+4*gridwidth,gridy+i*gridwidth,pDC);//horizontal
	}

	double mat[5][5]={
		{0,1,1,3,2},
		{1,3,6,6,3},
		{3,7,9,7,3},
		{2,7,8,6,2},
		{1,2,3,4,3}
	};

	int j,k;

/*	CString str;
	for( j=0;j<5;j++)
	{
		for( k=0;k<5;k++)
		{
			str.Format("%.1f",mat[j][k]);
			//TextOut(pDC->GetSafeHdc(),100,100,str,2);
			pDC->TextOut(gridx-15+k*gridwidth,gridy-20+j*gridwidth,str);	
		}
	}
	*/


	

	double value=4.5;
	
	for(j=0;j<5;j++)
	{
		for( k=0;k<5;k++)
		{
			mat[j][k]-=value;
		}
	}


	CString str;
	for( j=0;j<5;j++)
	{
		for( k=0;k<5;k++)
		{
			str.Format("%.1f",mat[j][k]);
			//TextOut(pDC->GetSafeHdc(),100,100,str,2);
			pDC->TextOut(gridx-15+k*gridwidth,gridy-20+j*gridwidth,str);	
		}
	}

	for( j=0;j<4;j++)
	{
		for( k=0;k<4;k++)
		{
			int cnt=0;
			if(mat[j][k]>0) cnt++;
			if(mat[j+1][k]>0) cnt++;
			if(mat[j][k+1]>0) cnt++;
			if(mat[j+1][k+1]>0) cnt++;
			
			if(cnt==0||cnt==4) continue;

			if(cnt==1||cnt==3){
				

				if(mat[j][k]*mat[j+1][k+1]>0){
					if(mat[j][k+1]*mat[j][k]>0){
						//左下
						CString str;
						//str.Format("左下：%.1f*%.1f=%.1f_j=%d_k=%d",mat[j][k+1],mat[j][k],mat[j][k+1]*mat[j][k],j,k);
						pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.5)*gridwidth,"左下");
						int x1=gridx+gridwidth*k;
						int y1=gridy+gridwidth*j;
						int x2=x1;
						int y2=y1+gridwidth;

						double ratio=-1*mat[j][k]/mat[j+1][k];
						double percent=ratio/(ratio+1);
						y1+=gridwidth*percent;

						double ratio2=-1*mat[j+1][k]/mat[j+1][k+1];
						double percent2=ratio2/(ratio2+1);
						x2+=gridwidth*percent2;

						drawline(x1,y1,x2,y2,pDC);
					}
					else{
						//右上
							pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.5)*gridwidth,"右上");

						int x1=gridx+gridwidth*k;
						int y1=gridy+gridwidth*j;
						int x2=x1+gridwidth;
						int y2=y1;

						double ratio=-1*mat[j][k]/mat[j][k+1];
						double percent=ratio/(ratio+1);
						x1+=gridwidth*percent;

						double ratio2=-1*mat[j][k+1]/mat[j+1][k+1];
						double percent2=ratio2/(ratio2+1);
						y2+=gridwidth*percent2;

						drawline(x1,y1,x2,y2,pDC);

					}
				}
				else{
					if(mat[j][k]*mat[j][k+1]>0){
					    //右下
						pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.5)*gridwidth,"右下");

						int x1=gridx+gridwidth*(k+1);
						int y1=gridy+gridwidth*j;
						int x2=x1;
						int y2=y1+gridwidth;

						double ratio=-1*mat[j][k+1]/mat[j+1][k+1];
						double percent=ratio/(ratio+1);
						y1+=gridwidth*percent;

						double ratio2=-1*mat[j+1][k+1]/mat[j+1][k];
						double percent2=ratio2/(ratio2+1);
						x2-=gridwidth*percent2;

						drawline(x1,y1,x2,y2,pDC);
					}
					else{
						//左上
						pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.5)*gridwidth,"左上");

						int x1=gridx+gridwidth*k;
						int y1=gridy+gridwidth*j;
						int x2=x1;
						int y2=y1+gridwidth;

						double ratio=-1*mat[j][k]/mat[j][k+1];
						double percent=ratio/(ratio+1);
						x1+=gridwidth*percent;

						double ratio2=-1*mat[j+1][k]/mat[j][k];
						double percent2=ratio2/(ratio2+1);
						y2-=gridwidth*percent2;

						drawline(x1,y1,x2,y2,pDC);
					}
				}

			}
			if(cnt==2){
				
				if(mat[j][k]*mat[j+1][k+1]>0){
					pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.5)*gridwidth,"歧义");
					double mid=(mat[j][k]+mat[j][k+1]+mat[j+1][k]+mat[j+1][k+1])/4;
					if(mid*mat[j][k]>0)//正斜线
					{
						//line one
						int x1=gridx+gridwidth*k;
						int y1=gridy+gridwidth*j;
						int x2=x1;
						int y2=y1+gridwidth;

						double ratio=-1*mat[j][k]/mat[j+1][k];
						double percent=ratio/(ratio+1);
						y1+=gridwidth*percent;

						double ratio2=-1*mat[j+1][k]/mat[j+1][k+1];
						double percent2=ratio2/(ratio2+1);
						x2+=gridwidth*percent2;

						drawline(x1,y1,x2,y2,pDC);
						
						//line two
						int x3=gridx+gridwidth*k;
						int y3=gridy+gridwidth*j;
						int x4=x3+gridwidth;
						int y4=y3;

						double ratio3=-1*mat[j][k]/mat[j][k+1];
						double percent3=ratio3/(ratio3+1);
						x3+=gridwidth*percent3;

						double ratio4=-1*mat[j][k+1]/mat[j+1][k+1];
						double percent4=ratio4/(ratio4+1);
						y4+=gridwidth*percent4;

						drawline(x3,y3,x4,y4,pDC);
					}
					else{//反斜线
												//line one
						int x1=gridx+gridwidth*k;
						int y1=gridy+gridwidth*j;
						int x2=x1;
						int y2=y1+gridwidth;

						double ratio=-1*mat[j][k]/mat[j][k+1];
						double percent=ratio/(ratio+1);
						x1+=gridwidth*percent;

						double ratio2=-1*mat[j+1][k]/mat[j][k];
						double percent2=ratio2/(ratio2+1);
						y2-=gridwidth*percent2;

						drawline(x1,y1,x2,y2,pDC);
						
						//line two
						int x3=gridx+gridwidth*(k+1);
						int y3=gridy+gridwidth*j;
						int x4=x3;
						int y4=y3+gridwidth;

						double ratio3=-1*mat[j][k+1]/mat[j+1][k+1];
						double percent3=ratio3/(ratio3+1);
						y3+=gridwidth*percent3;

						double ratio4=-1*mat[j+1][k+1]/mat[j+1][k];
						double percent4=ratio4/(ratio4+1);
						x4-=gridwidth*percent4;

						drawline(x3,y3,x4,y4,pDC);
					}
				}
				else{
					pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.5)*gridwidth,"二分");
					if(mat[j][k]*mat[j][k+1]>0)//horizontal
					{
						int x1=gridx+gridwidth*k;
						int y1=gridy+gridwidth*j;
						int x2=x1+gridwidth;
						int y2=y1;

						double ratio=-1*mat[j][k]/mat[j+1][k];
						double percent=ratio/(ratio+1);
						y1+=gridwidth*percent;

						double ratio2=-1*mat[j][k+1]/mat[j+1][k+1];
						double percent2=ratio2/(ratio2+1);
						y2+=gridwidth*percent2;

						drawline(x1,y1,x2,y2,pDC);
					}
					else//vertical
					{
						int x1=gridx+gridwidth*k;
						int y1=gridy+gridwidth*j;
						int x2=x1;
						int y2=y1+gridwidth;

						double ratio=-1*mat[j][k]/mat[j][k+1];
						double percent=ratio/(ratio+1);
						x1+=gridwidth*percent;

						double ratio2=-1*mat[j+1][k]/mat[j+1][k+1];
						double percent2=ratio2/(ratio2+1);
						x2+=gridwidth*percent2;

						drawline(x1,y1,x2,y2,pDC);						
					}

				}
			}
		}
	}
	



	//===========
}



void CDrawingView::drawline(int x1,int y1,int x2, int y2,CDC* pDC){
	CPen myPen2;
	myPen2.CreatePen(PS_SOLID,1,RGB(0,0,0));
	CPen *pOldPen=pDC->SelectObject(&myPen2);
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawingView printing

BOOL CDrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDrawingView diagnostics

#ifdef _DEBUG
void CDrawingView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawingDoc* CDrawingView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawingDoc)));
	return (CDrawingDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawingView message handlers
