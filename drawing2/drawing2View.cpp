// drawing2View.cpp : implementation of the CDrawing2View class
//

#include "stdafx.h"
#include "drawing2.h"

#include "drawing2Doc.h"
#include "drawing2View.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawing2View

IMPLEMENT_DYNCREATE(CDrawing2View, CView)

BEGIN_MESSAGE_MAP(CDrawing2View, CView)
	//{{AFX_MSG_MAP(CDrawing2View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawing2View construction/destruction

CDrawing2View::CDrawing2View()
{
	// TODO: add construction code here

}

CDrawing2View::~CDrawing2View()
{
}

BOOL CDrawing2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawing2View drawing

void CDrawing2View::OnDraw(CDC* pDC)
{
	CDrawing2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

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

	double mid[4][4];
	for( j=0;j<4;j++)
	{
		for( k=0;k<4;k++)
		{
			mid[j][k]=(mat[j][k]+mat[j+1][k]+mat[j][k+1]+mat[j+1][k+1])/4;	
			drawline(gridx+gridwidth*k,gridy+gridwidth*j,gridx+gridwidth*(k+1),gridy+gridwidth*(j+1),pDC);
			drawline(gridx+gridwidth*(k+1),gridy+gridwidth*j,gridx+gridwidth*k,gridy+gridwidth*(j+1),pDC);
			CString str;
			str.Format("%.1f",mid[j][k]);
			pDC->TextOut(gridx-15+(k+0.5)*gridwidth,gridy-20+(j+0.5)*gridwidth,str);

			
			mid[2][3]+=0.1;//·ÀÖ¹³ýÁã´íÎó

			int cnt=0;
			if(mat[j][k]>0) cnt++;
			if(mat[j][k+1]>0) cnt++;
			if(mid[j][k]>0) cnt++;
			if(cnt==1||cnt==2){

			if(mat[j][k]*mid[j][k]>0){//ÓÒµ×½Ç
			
				
				int x1=gridx+gridwidth*k;
				int y1=gridy+gridwidth*j;
				int x2=x1+gridwidth;
				int y2=y1;

				double ratio=-1*mat[j][k]/mat[j][k+1];
				double percent=ratio/(ratio+1);
				x1+=gridwidth*percent;
				
	
				double ratio2=-1*mat[j][k+1]/mid[j][k];
				double percent2=ratio2/(ratio2+1);
				x2-=gridwidth*percent2/2;
				y2+=gridwidth*percent2/2;

	

				drawline(x1,y1,x2,y2,pDC);
			}
			else if(mat[j][k+1]*mid[j][k]>0){//×óµ×½Ç
				int x1=gridx+gridwidth*k;
				int y1=gridy+gridwidth*j;
				int x2=x1;
				int y2=y1;

				double ratio=-1*mat[j][k]/mat[j][k+1];
				double percent=ratio/(ratio+1);
				x1+=gridwidth*percent;
				
				double ratio2=-1*mat[j][k]/mid[j][k];
				double percent2=ratio2/(ratio2+1);
				x2+=gridwidth*percent2/2;
				y2+=gridwidth*percent2/2;

				drawline(x1,y1,x2,y2,pDC);
			}
			else{//ÏÂ¶¥½Ç
				int x1=gridx+gridwidth*k;
				int y1=gridy+gridwidth*j;
				int x2=x1+gridwidth;
				int y2=y1;

				double ratio=-1*mat[j][k]/mid[j][k];
				double percent=ratio/(ratio+1);
				x1+=gridwidth*percent/2;
				y1+=gridwidth*percent/2;
				
				double ratio2=-1*mat[j][k+1]/mid[j][k];
				double percent2=ratio2/(ratio2+1);
				x2-=gridwidth*percent2/2;
				y2+=gridwidth*percent2/2;

				drawline(x1,y1,x2,y2,pDC);
			}

			}
			//2


			int cnt2=0;
			if(mat[j][k+1]>0) cnt2++;
			if(mat[j+1][k+1]>0) cnt2++;
			if(mid[j][k]>0) cnt2++;
			if(cnt2==1||cnt2==2){

			if(mat[j][k+1]*mid[j][k]>0){//ÏÂµ×½Ç
				//pDC->TextOut(gridx+(k+0.75)*gridwidth,gridy+(j+0.5)*gridwidth,"ÏÂµ×½Ç");
				int x1=gridx+gridwidth*(k+1);
				int y1=gridy+gridwidth*j;
				int x2=x1;
				int y2=y1+gridwidth;

				
				double ratio=-1*mat[j][k+1]/mat[j+1][k+1];
				double percent=ratio/(ratio+1);
				y1+=gridwidth*percent;
				
				//pDC->TextOut(x1,y1,"¡õ");
				double ratio2=-1*mat[j+1][k+1]/mid[j][k];
				double percent2=ratio2/(ratio2+1);
				x2-=gridwidth*percent2/2;
				y2-=gridwidth*percent2/2;

				drawline(x1,y1,x2,y2,pDC);
			}
			else if(mat[j+1][k+1]*mid[j][k]>0){//ÉÏµ×½Ç
				int x1=gridx+gridwidth*(k+1);
				int y1=gridy+gridwidth*j;
				int x2=x1;
				int y2=y1;

				double ratio=-1*mat[j][k+1]/mat[j+1][k+1];
				double percent=ratio/(ratio+1);
				y1+=gridwidth*percent;
				
				double ratio2=-1*mat[j][k+1]/mid[j][k];
				double percent2=ratio2/(ratio2+1);
				x2-=gridwidth*percent2/2;
				y2+=gridwidth*percent2/2;

				drawline(x1,y1,x2,y2,pDC);
			}
			else{//×ó¶¥½Ç
				int x1=gridx+gridwidth*(k+1);
				int y1=gridy+gridwidth*j;
				int x2=x1;
				int y2=y1+gridwidth;

				double ratio=-1*mat[j][k+1]/mid[j][k];
				double percent=ratio/(ratio+1);
				x1-=gridwidth*percent/2;
				y1+=gridwidth*percent/2;
				
				double ratio2=-1*mat[j+1][k+1]/mid[j][k];
				double percent2=ratio2/(ratio2+1);
				x2-=gridwidth*percent2/2;
				y2-=gridwidth*percent2/2;

				drawline(x1,y1,x2,y2,pDC);
			}

			}
			//3

			int cnt3=0;
			if(mat[j+1][k+1]>0) cnt3++;
			if(mat[j+1][k]>0) cnt3++;
			if(mid[j][k]>0) cnt3++;
			if(cnt3==1||cnt3==2){

				/*CString s;
				s.Format("%.1f",mat[j+1][k+1]*mid[j][k]);
				pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.75)*gridwidth,s);
*/
			if(mat[j+1][k+1]*mid[j][k]>0){//×óµ×½Ç
			
				CString s;
				s.Format("×ó£º%.1f",mat[j+1][k+1]*mid[j][k]);
				//pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.75)*gridwidth,s);
				int x1=gridx+gridwidth*k;
				int y1=gridy+gridwidth*(j+1);
				int x2=x1;
				int y2=y1;

				
				double ratio=-1*mat[j+1][k]/mat[j+1][k+1];
				double percent=ratio/(ratio+1);
				x1+=gridwidth*percent;
				
				//pDC->TextOut(x1,y1,"¡õ");
				double ratio2=-1*mat[j+1][k]/mid[j][k];
				double percent2=ratio2/(ratio2+1);
				x2+=gridwidth*percent2/2;
				y2-=gridwidth*percent2/2;

				drawline(x1,y1,x2,y2,pDC);
			}
			else if(mat[j+1][k]*mid[j][k]>0){//ÓÒµ×½Ç
				//pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.75)*gridwidth,"ÓÒ");
				int x1=gridx+gridwidth*k;
				int y1=gridy+gridwidth*(j+1);
				int x2=x1+gridwidth;
				int y2=y1;

				double ratio=-1*mat[j+1][k]/mat[j+1][k+1];
				double percent=ratio/(ratio+1);
				x1+=gridwidth*percent;
				
				double ratio2=-1*mat[j+1][k+1]/mid[j][k];
				double percent2=ratio2/(ratio2+1);
				x2-=gridwidth*percent2/2;
				y2-=gridwidth*percent2/2;

				drawline(x1,y1,x2,y2,pDC);
			}
			else{//ÉÏ¶¥½Ç

				int x1=gridx+gridwidth*k;
				int y1=gridy+gridwidth*(j+1);
				int x2=x1+gridwidth;
				int y2=y1;

				double ratio=-1*mat[j+1][k]/mid[j][k];
				double percent=ratio/(ratio+1);
				x1+=gridwidth*percent/2;
				y1-=gridwidth*percent/2;
				
				double ratio2=-1*mat[j+1][k+1]/mid[j][k];
				double percent2=ratio2/(ratio2+1);
				x2-=gridwidth*percent2/2;
				y2-=gridwidth*percent2/2;

				drawline(x1,y1,x2,y2,pDC);
			}

			}

			//4
			int cnt4=0;
			if(mat[j][k]>0) cnt4++;
			if(mat[j+1][k]>0) cnt4++;
			if(mid[j][k]>0) cnt4++;
			if(cnt4==1||cnt4==2){

				CString s;
				s.Format("%d",cnt4);
				//pDC->TextOut(gridx+(k+0.25)*gridwidth,gridy+(j+0.5)*gridwidth,s);

			if(mat[j+1][k]*mid[j][k]>0){//ÉÏµ×½Ç
			
				CString s;
				s.Format("×ó£º%.1f",mat[j+1][k+1]*mid[j][k]);
				//pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.75)*gridwidth,s);
				int x1=gridx+gridwidth*k;
				int y1=gridy+gridwidth*j;
				int x2=x1;
				int y2=y1;

				
				double ratio=-1*mat[j][k]/mat[j+1][k];
				double percent=ratio/(ratio+1);
				y1+=gridwidth*percent;
				
				//pDC->TextOut(x1,y1,"¡õ");
				double ratio2=-1*mat[j][k]/mid[j][k];
				double percent2=ratio2/(ratio2+1);
				x2+=gridwidth*percent2/2;
				y2+=gridwidth*percent2/2;

				drawline(x1,y1,x2,y2,pDC);
			}
			else if(mat[j][k]*mid[j][k]>0){//ÏÂµ×½Ç
				//pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.75)*gridwidth,"ÏÂ");
				int x1=gridx+gridwidth*k;
				int y1=gridy+gridwidth*j;
				int x2=x1;
				int y2=y1+gridwidth;

				double ratio=-1*mat[j][k]/mat[j+1][k];
				double percent=ratio/(ratio+1);
				y1+=gridwidth*percent;
				
				double ratio2=-1*mat[j+1][k]/mid[j][k];
				double percent2=ratio2/(ratio2+1);
				x2+=gridwidth*percent2/2;
				y2-=gridwidth*percent2/2;

				drawline(x1,y1,x2,y2,pDC);
			}
			else{//ÓÒ¶¥½Ç

				int x1=gridx+gridwidth*k;
				int y1=gridy+gridwidth*j;
				int x2=x1;
				int y2=y1+gridwidth;

				double ratio=-1*mat[j][k]/mid[j][k];
				double percent=ratio/(ratio+1);
				x1+=gridwidth*percent/2;
				y1+=gridwidth*percent/2;
				
				double ratio2=-1*mat[j+1][k]/mid[j][k];
				double percent2=ratio2/(ratio2+1);
				x2+=gridwidth*percent2/2;
				y2-=gridwidth*percent2/2;

				drawline(x1,y1,x2,y2,pDC);
			}

			}
			
		}

	}





}




void CDrawing2View::drawline(int x1,int y1,int x2, int y2,CDC* pDC){
	CPen myPen2;
	myPen2.CreatePen(PS_SOLID,1,RGB(0,0,0));
	CPen *pOldPen=pDC->SelectObject(&myPen2);
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawing2View printing

BOOL CDrawing2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawing2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawing2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDrawing2View diagnostics

#ifdef _DEBUG
void CDrawing2View::AssertValid() const
{
	CView::AssertValid();
}

void CDrawing2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawing2Doc* CDrawing2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawing2Doc)));
	return (CDrawing2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawing2View message handlers
