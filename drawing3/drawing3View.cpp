// drawing3View.cpp : implementation of the CDrawing3View class
//

#include "stdafx.h"
#include "drawing3.h"

#include<time.h>

#include "drawing3Doc.h"
#include "drawing3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawing3View

IMPLEMENT_DYNCREATE(CDrawing3View, CView)

BEGIN_MESSAGE_MAP(CDrawing3View, CView)
	//{{AFX_MSG_MAP(CDrawing3View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawing3View construction/destruction
	


static const int r=50,c=50;
/*static double mat[50][50]={
		{0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2},
		{1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3},
		{3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3},
		{2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2},
		{1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3},
		{0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2},
		{1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3},
		{3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3},
		{2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2},
		{1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3},
		{0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2},
		{1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3},
		{3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3},
		{2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2},
		{1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3},
		{0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2},
		{1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3},
		{3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3},
		{2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2},
		{1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3},
		{0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2},
		{1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3},
		{3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3},
		{2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2},
		{1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3},
		{0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2},
		{1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3},
		{3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3},
		{2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2},
		{1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3},
		{0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2},
		{1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3},
		{3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3},
		{2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2},
		{1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3},
		{0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2},
		{1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3},
		{3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3},
		{2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2},
		{1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3},
		{0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2},
		{1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3},
		{3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3},
		{2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2},
		{1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3},
		{0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2,0,1,1,3,2},
		{1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3,1,3,6,6,3},
		{3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3,3,7,9,7,3},
		{2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2,2,7,8,6,2},
		{1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3,1,2,3,4,3}
	};
*/

CDrawing3View::CDrawing3View():gridwidth(13),gridx(3),gridy(3)
{
	// TODO: add construction code here

	
}

CDrawing3View::~CDrawing3View()
{
}

BOOL CDrawing3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawing3View drawing

void CDrawing3View::OnDraw(CDC* pDC)
{
	CDrawing3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	srand(time(0));
	double matbak[r][c];
	int ii,jj;
	for(ii=0;ii<r;ii++){
		for(jj=0;jj<c;jj++){
			matbak[ii][jj]=(double)rand()/RAND_MAX;
		}
	}

	//draw the grid
	int i=0;
	for( i=0;i<c;i++){
		drawline(gridx+i*gridwidth,gridy,gridx+i*gridwidth,gridy+(r-1)*gridwidth,pDC,000);//vertical
		
	}

	for(i=0;i<r;i++){
		drawline(gridx,gridy+i*gridwidth,gridx+(c-1)*gridwidth,gridy+i*gridwidth,pDC,000);//horizontal
	}

	

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
int t=0;
double set[]={0.4,0.6};
int color[]={001,100};


for(t=0;t<2;t++){


	double value=set[t];
	double mat[r][c];
	for(j=0;j<r;j++)
	{
		for( k=0;k<c;k++)
		{
			mat[j][k]=matbak[j][k]-value;
		}
	}


	CString str;
	for( j=0;j<r;j++)
	{
		for( k=0;k<c;k++)
		{
			str.Format("%.1f",mat[j][k]);
			//TextOut(pDC->GetSafeHdc(),100,100,str,2);
		//	pDC->TextOut(gridx-15+k*gridwidth,gridy-20+j*gridwidth,str);	
		}
	}

	for( j=0;j<r-1;j++)
	{
		for( k=0;k<c-1;k++)
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
						
						//pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.5)*gridwidth,"左下");
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

						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
					else{
						//右上
							//pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.5)*gridwidth,"右上");

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

						drawline(x1,y1,x2,y2,pDC,color[t]);

					}
				}
				else{
					if(mat[j][k]*mat[j][k+1]>0){
					    //右下
						//pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.5)*gridwidth,"右下");

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

						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
					else{
						//左上
					//	pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.5)*gridwidth,"左上");

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

						drawline(x1,y1,x2,y2,pDC,color[t]);
					}
				}

			}
			if(cnt==2){
				
				if(mat[j][k]*mat[j+1][k+1]>0){
					//pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.5)*gridwidth,"歧义");
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

						drawline(x1,y1,x2,y2,pDC,color[t]);
						
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

						drawline(x3,y3,x4,y4,pDC,color[t]);
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

						drawline(x1,y1,x2,y2,pDC,color[t]);
						
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

						drawline(x3,y3,x4,y4,pDC,color[t]);
					}
				}
				else{
					//pDC->TextOut(gridx+(k+0.5)*gridwidth,gridy+(j+0.5)*gridwidth,"二分");
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

						drawline(x1,y1,x2,y2,pDC,color[t]);
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

						drawline(x1,y1,x2,y2,pDC,color[t]);						
					}

				}
			}
		}
	}
	
	

}//2 loop 


	//===========









}

/*
void CDrawing3View::drawline(int x1,int y1,int x2, int y2,CDC* pDC){
	CPen myPen2;
	myPen2.CreatePen(PS_SOLID,1,RGB(0,0,0));
	CPen *pOldPen=pDC->SelectObject(&myPen2);
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
}
*/

void CDrawing3View::drawline(int x1,int y1,int x2, int y2,CDC* pDC,int RGB){
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
// CDrawing3View printing

BOOL CDrawing3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawing3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawing3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDrawing3View diagnostics

#ifdef _DEBUG
void CDrawing3View::AssertValid() const
{
	CView::AssertValid();
}

void CDrawing3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawing3Doc* CDrawing3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawing3Doc)));
	return (CDrawing3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawing3View message handlers
