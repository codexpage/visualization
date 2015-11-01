// pro1_2View.cpp : implementation of the CPro1_2View class
//

#include "stdafx.h"
#include "pro1_2.h"

#include "pro1_2Doc.h"
#include "pro1_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro1_2View

IMPLEMENT_DYNCREATE(CPro1_2View, CView)

BEGIN_MESSAGE_MAP(CPro1_2View, CView)
	//{{AFX_MSG_MAP(CPro1_2View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro1_2View construction/destruction

CPro1_2View::CPro1_2View()
{
	// TODO: add construction code here

}

CPro1_2View::~CPro1_2View()
{
}

BOOL CPro1_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPro1_2View drawing
const double CON = 5.0; //������ĵ�ֵ
const double EPS = 1e-8; //����,precision

//�߶����˵㺯��ֵ�ֱ�Ϊx,y�����ظ��߶����Ƿ���ڵ�ֵ��
bool valid(double x, double y) {
	return (x - CON) * (y - CON) < EPS;
}

void CPro1_2View::OnDraw(CDC* pDC)
{
	CPro1_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//add draw code for native data here
	CPen myPen1;
	myPen1.CreatePen(PS_SOLID, 1, RGB(31, 197, 183));
	pDC->SelectObject(&myPen1);
		
	//��������
	/* ���ϽǶ������� */
	const int LEFT_TOP_X = 100;
	const int LEFT_TOP_Y = 100;

	/* �����ģΪSIZE x SIZE */
	const int SIZE = 4;
	
	/* �����С����������Ϊ(��Ļ��/��Ľ�С��)����(����������5) */
	const int SCREEN_WIDTH = GetSystemMetrics(SM_CXFULLSCREEN);
	const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYFULLSCREEN);
	const int INC = min(SCREEN_WIDTH, SCREEN_HEIGHT) / (SIZE + 5);
	const double INC_DB = (double)INC;
	
	/* ���������� */
	int pos[SIZE + 1][SIZE + 1][2], i, j;
	
	//������������
	for (i = 0; i <= SIZE; ++i) {
		for (j = 0; j <= SIZE; ++j) {
			pos[i][j][0] = LEFT_TOP_X + INC * i;
			pos[i][j][1] = LEFT_TOP_Y + INC * j;
		}
	}
	//��������
	for (i = 0; i <= SIZE; ++i) {
		pDC->MoveTo(LEFT_TOP_X + INC * i, LEFT_TOP_Y);
		pDC->LineTo(LEFT_TOP_X + INC * i, LEFT_TOP_Y + INC * SIZE);
		pDC->MoveTo(LEFT_TOP_X, LEFT_TOP_Y + INC * i);
		pDC->LineTo(LEFT_TOP_X + INC * SIZE, LEFT_TOP_Y + INC * i);
	}

	//�����㺯��ֵ
	double value[SIZE + 1][SIZE + 1] = {
		{0, 1, 3, 2, 1},
		{1, 3, 7, 7, 2},
		{1, 6, 9, 8, 3},
		{3, 6, 7, 6, 4},
		{2, 3, 3, 2, 3}
	};

	//�궥����ֵ
	/* ��ʾ�����ַ���������Զ�Ӧ����ƫ������������ʾ���ı����ͷֱ��ʿ�����Ҫ΢��RDU_X��RDU_Y */
	const int RDU_X = 10;
	const int RDU_Y = 17;
	CString str; //���ڸ�ʽ������, ת����integer => QString
	for (i = 0; i <= SIZE; ++i) {
		for (j = 0; j <= SIZE; ++j) {
			str.Format("%.0f", value[i][j]);
			pDC->TextOut(pos[i][j][0] - RDU_X, pos[i][j][1] - RDU_Y, str);
		}
	}

	//���������߽�ĵ�ֵ��(��ֵ�ߺ����񽻵�)���꣬ӳ���ϵΪpoint=>cordination
	int hor[SIZE][SIZE + 1][2]; //ˮƽ�߶�
	int ver[SIZE + 1][SIZE][2]; //��ֱ�߶�
	for (i = 0; i <= SIZE; ++i) {
		for (j = 0; j <= SIZE; ++j) {
			if (i < SIZE) {
				if (valid(value[i][j], value[i + 1][j])) {
					hor[i][j][0] = pos[i][j][0];
					hor[i][j][1] = pos[i][j][1];
					hor[i][j][0] += (int)(INC_DB * (CON - value[i][j]) / (value[i + 1][j] - value[i][j]));
				} else {
					hor[i][j][0] = hor[i][j][1] = -1;
				}
			}
			if (j < SIZE) {
				if (valid(value[i][j], value[i][j + 1])) {
					ver[i][j][0] = pos[i][j][0];
					ver[i][j][1] = pos[i][j][1];
					ver[i][j][1] += (int)(INC_DB * (CON - value[i][j]) / (value[i][j + 1] - value[i][j]));
				} else {
					ver[i][j][0] = ver[i][j][1] = -1;
				}
			}
		}
	}

	//���ǻ��֣���������ĵ㺯��ֵ�����꣬���������ĵ����ĸ������߶��Ͽ��ܵĵ�ֵ������
	int pos_center[SIZE][SIZE][2]; //���ĵ�����
	double value_center[SIZE][SIZE]; //���ĵ㺯��ֵ
	int center[SIZE][SIZE][4][2]; //���ĵ����ĸ������߶��ϵĵ�ֵ�����꣬ע�⵽ÿ�������������߶�
	/*******************************************************
	 * ����ƫ�����������ĵ�Ϊ(x,y)�����ĸ�����pos�����Ӧ�±�ֱ�Ϊ
	 * ����(x,y), ����(x+1,y), ����(x,y+1), ����(x+1,y+1)
	 *******************************************************/
	int dd[4][2] = {0,0, 1,0, 1,1, 0,1};

	//freopen("error.txt", "w", stdout);
	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			/* �������ĵ����� */
			pos_center[i][j][0] = (pos[i][j][0] + pos[i + 1][j][0]) >> 1;
			pos_center[i][j][1] = (pos[i][j][1] + pos[i][j + 1][1]) >> 1;
	
			/* �������ĵ㺯��ֵ */
			value_center[i][j] = 0.0;
			for (int k = 0; k < 4; ++k) {
				value_center[i][j] += value[i + dd[k][0]][j + dd[k][1]]; //�ĸ������
			}
			value_center[i][j] *= 0.25;//ȡ�ĸ���ƽ��ֵ
			//std::cout << value_center[i][j] << " ";

			/* ���ĵ����ĸ������ߵ�ֵ������ */
			for (k = 0; k < 4; ++k) {
				pDC->MoveTo(pos_center[i][j][0], pos_center[i][j][1]);
				pDC->LineTo(pos[i+dd[k][0]][j+dd[k][1]][0], pos[i+dd[k][0]][j+dd[k][1]][1]);

				if (valid(value_center[i][j], value[i + dd[k][0]][j + dd[k][1]])) {
					//���ڵ�ֵ��
					int dx = pos_center[i][j][0] - pos[i + dd[k][0]][j + dd[k][1]][0];
					int dy = pos_center[i][j][1] - pos[i + dd[k][0]][j + dd[k][1]][1];
					center[i][j][k][0] = pos[i + dd[k][0]][j + dd[k][1]][0];
					center[i][j][k][0] += dx * (CON - value[i + dd[k][0]][j + dd[k][1]])
						/ (value_center[i][j] - value[i + dd[k][0]][j + dd[k][1]]);
					center[i][j][k][1] = pos[i + dd[k][0]][j + dd[k][1]][1];
					center[i][j][k][1] += dy * (CON - value[i + dd[k][0]][j + dd[k][1]])
						/ (value_center[i][j] - value[i + dd[k][0]][j + dd[k][1]]);
				} else {
					//�����ڵ�ֵ��
					center[i][j][k][0] = center[i][j][k][1] = -1;
				}
				//std::cout << "center[" << i << "][" << j << "][" << k << "] = " << center[i][j][k][0] << ", " << center[i][j][k][1] << std::endl;
			}
		}
		//std::cout << std::endl;
	}	

	CPen myPen2;
	myPen2.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pDC->SelectObject(&myPen2);

	/* ����ֵ�ߣ����ǵ��κ�һ�ε�ֵ�߶������漰һ��б�߶Σ�����ֻ������4xSIZExSIZE��б�߶� */
	/* б�߶ι�����ˮƽ&��ֱ�߶� */
	int con_hor[4][2] = {0,0, 0,0, 0,1, 0,1};
	int con_ver[4][2] = {0,0, 1,0, 1,0, 0,0};
	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			for (int k = 0; k < 4; ++k) {
				if (center[i][j][k][0] == -1) continue;
				if (~center[i][j][(k + 1) % 4][0]) {
					pDC->MoveTo(center[i][j][k][0], center[i][j][k][1]);
					pDC->LineTo(center[i][j][(k+1)%4][0], center[i][j][(k+1)%4][1]);
				}
				int xx = i + con_hor[k][0];
				int yy = j + con_hor[k][1];
				if (~hor[xx][yy][0]) {
					pDC->MoveTo(center[i][j][k][0], center[i][j][k][1]);
					pDC->LineTo(hor[xx][yy][0], hor[xx][yy][1]);
				}
				xx = i + con_ver[k][0];
				yy = j + con_ver[k][1];
				if (~ver[xx][yy][0]) {
					pDC->MoveTo(center[i][j][k][0], center[i][j][k][1]);
					pDC->LineTo(ver[xx][yy][0], ver[xx][yy][1]);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPro1_2View printing

BOOL CPro1_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPro1_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPro1_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPro1_2View diagnostics

#ifdef _DEBUG
void CPro1_2View::AssertValid() const
{
	CView::AssertValid();
}

void CPro1_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPro1_2Doc* CPro1_2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPro1_2Doc)));
	return (CPro1_2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro1_2View message handlers
