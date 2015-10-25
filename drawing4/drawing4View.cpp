// drawing4View.cpp : implementation of the CDrawing4View class
//

#include "stdafx.h"
#include "drawing4.h"
#include<time.h>

#include "drawing4Doc.h"
#include "drawing4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawing4View

IMPLEMENT_DYNCREATE(CDrawing4View, CView)

BEGIN_MESSAGE_MAP(CDrawing4View, CView)
	//{{AFX_MSG_MAP(CDrawing4View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawing4View construction/destruction

static const int r=50,c=50;

CDrawing4View::CDrawing4View():gridwidth(13),gridx(3),gridy(3)
{
	// TODO: add construction code here

}

CDrawing4View::~CDrawing4View()
{
}

BOOL CDrawing4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawing4View drawing

void CDrawing4View::OnDraw(CDC* pDC)
{
	CDrawing4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	//init the matbak
	srand(time(0));
	double matbak[r][c];
	int ii,jj;
	for(ii=0;ii<r;ii++){
		for(jj=0;jj<c;jj++){
			matbak[ii][jj]=(double)rand()/RAND_MAX;
		}
	}

	//draw the grid(black)
	int i=0;
	for( i=0;i<c;i++){
		drawline(gridx+i*gridwidth,gridy,gridx+i*gridwidth,gridy+(r-1)*gridwidth,pDC,000);//vertical		
	}

	for(i=0;i<r;i++){
		drawline(gridx,gridy+i*gridwidth,gridx+(c-1)*gridwidth,gridy+i*gridwidth,pDC,000);//horizontal
	}

	int t=0;
	double set[]={0.4,0.6};
	int color[]={001,100};
	for(t=0;t<2;t++){
	
		double value=set[t];
		double mat[r][c];
		int j,k;

		for(j=0;j<r;j++)
		{
			for( k=0;k<c;k++)
			{
				mat[j][k]=matbak[j][k]-value;
			}
		}

			//=====draw in a grid=======

		double mid[r-1][c-1];
		for( j=0;j<r-1;j++)
		{
			for( k=0;k<c-1;k++)
			{
				mid[j][k]=(mat[j][k]+mat[j+1][k]+mat[j][k+1]+mat[j+1][k+1])/4;	
				drawline(gridx+gridwidth*k,gridy+gridwidth*j,gridx+gridwidth*(k+1),gridy+gridwidth*(j+1),pDC,000);
				drawline(gridx+gridwidth*(k+1),gridy+gridwidth*j,gridx+gridwidth*k,gridy+gridwidth*(j+1),pDC,000);
				CString str;
				str.Format("%.1f",mid[j][k]);
				//pDC->TextOut(gridx-15+(k+0.5)*gridwidth,gridy-20+(j+0.5)*gridwidth,str);


				//mid[2][3]+=0.1;//??????

				//1
				int cnt=0;
				if(mat[j][k]>0) cnt++;
				if(mat[j][k+1]>0) cnt++;
				if(mid[j][k]>0) cnt++;
				if(cnt==1||cnt==2){

					if(mat[j][k]*mid[j][k]>0){//???

				
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



						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
					else if(mat[j][k+1]*mid[j][k]>0){//???
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
		
						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
					else{//???
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
		
						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
		
				}



				//2
				int cnt2=0;
				if(mat[j][k+1]>0) cnt2++;
				if(mat[j+1][k+1]>0) cnt2++;
				if(mid[j][k]>0) cnt2++;
				if(cnt2==1||cnt2==2){
		
					if(mat[j][k+1]*mid[j][k]>0){//???
						//pDC->TextOut(gridx+(k+0.75)*gridwidth,gridy+(j+0.5)*gridwidth,"???");
						int x1=gridx+gridwidth*(k+1);
						int y1=gridy+gridwidth*j;
						int x2=x1;
						int y2=y1+gridwidth;
		
						
						double ratio=-1*mat[j][k+1]/mat[j+1][k+1];
						double percent=ratio/(ratio+1);
						y1+=gridwidth*percent;
						
						//pDC->TextOut(x1,y1,"?");
						double ratio2=-1*mat[j+1][k+1]/mid[j][k];
						double percent2=ratio2/(ratio2+1);
						x2-=gridwidth*percent2/2;
						y2-=gridwidth*percent2/2;
		
						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
					else if(mat[j+1][k+1]*mid[j][k]>0){//???
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
		
						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
					else{//???
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
		
						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
				}
				
				//3
				int cnt3=0;
				if(mat[j+1][k+1]>0) cnt3++;
				if(mat[j+1][k]>0) cnt3++;
				if(mid[j][k]>0) cnt3++;
				if(cnt3==1||cnt3==2){
		
	
					if(mat[j+1][k+1]*mid[j][k]>0){//???

						CString s;
						s.Format("??%.1f",mat[j+1][k+1]*mid[j][k]);
						//pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.75)*gridwidth,s);
						int x1=gridx+gridwidth*k;
						int y1=gridy+gridwidth*(j+1);
						int x2=x1;
						int y2=y1;
		
						
						double ratio=-1*mat[j+1][k]/mat[j+1][k+1];
						double percent=ratio/(ratio+1);
						x1+=gridwidth*percent;
						
						//pDC->TextOut(x1,y1,"?");
						double ratio2=-1*mat[j+1][k]/mid[j][k];
						double percent2=ratio2/(ratio2+1);
						x2+=gridwidth*percent2/2;
						y2-=gridwidth*percent2/2;
		
						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
					else if(mat[j+1][k]*mid[j][k]>0){//???
						//pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.75)*gridwidth,"?");
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
		
						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
					else{//???

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
		
						drawline(x1,y1,x2,y2,pDC,color[t]);
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
		
					if(mat[j+1][k]*mid[j][k]>0){//???
		
						CString s;
						s.Format("??%.1f",mat[j+1][k+1]*mid[j][k]);
						//pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.75)*gridwidth,s);
						int x1=gridx+gridwidth*k;
						int y1=gridy+gridwidth*j;
						int x2=x1;
						int y2=y1;
		
						
						double ratio=-1*mat[j][k]/mat[j+1][k];
						double percent=ratio/(ratio+1);
						y1+=gridwidth*percent;
						
						//pDC->TextOut(x1,y1,"?");
						double ratio2=-1*mat[j][k]/mid[j][k];
						double percent2=ratio2/(ratio2+1);
						x2+=gridwidth*percent2/2;
						y2+=gridwidth*percent2/2;
		
						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
					else if(mat[j][k]*mid[j][k]>0){//???
						//pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.75)*gridwidth,"?");
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
		
						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
					else{//???

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
		
						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
		
				}//4 end 				
			
			}//loop k end

		}//loop j end
	}



}

void CDrawing4View::drawline(int x1,int y1,int x2, int y2,CDC* pDC,int RGB){
	CPen myPen2;
	switch(RGB){
		case 100:
		myPen2.CreatePen(PS_SOLID,1,RGB(255,0,0));
		break;
		case 010:
		myPen2.CreatePen(PS_SOLID,1,RGB(0,255,0));
		break;
		case 001:
		myPen2.CreatePen(PS_SOLID,1,RGB(0,0,255));
		break;
		case 000:
		myPen2.CreatePen(PS_SOLID,1,RGB(0,0,0));
		break;
	};
	
	CPen *pOldPen=pDC->SelectObject(&myPen2);
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
}


/////////////////////////////////////////////////////////////////////////////
// CDrawing4View printing

BOOL CDrawing4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawing4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawing4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDrawing4View diagnostics

#ifdef _DEBUG
void CDrawing4View::AssertValid() const
{
	CView::AssertValid();
}

void CDrawing4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawing4Doc* CDrawing4View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawing4Doc)));
	return (CDrawing4Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawing4View message handlers
