// pro2_2View.cpp : implementation of the CPro2_2View class
//

#include "stdafx.h"
#include "pro2_2.h"

#include "pro2_2Doc.h"
#include "pro2_2View.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro2_2View

IMPLEMENT_DYNCREATE(CPro2_2View, CView)

BEGIN_MESSAGE_MAP(CPro2_2View, CView)
	//{{AFX_MSG_MAP(CPro2_2View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro2_2View construction/destruction

CPro2_2View::CPro2_2View()
{
	// TODO: add construction code here

}

CPro2_2View::~CPro2_2View()
{
}

BOOL CPro2_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPro2_2View drawing

static double CON = 0.4; //������ĵ�ֵ
const double EPS = 1e-8; //����
const double RAND_RANGE = RAND_MAX - 1.0; //�������Χӳ��[0,RAND_RANGE] => [0,1]

/* ���ϽǶ��������Ļ���Ͻ�ƫ��λ�� */
const int LEFT_TOP_X = 10;
const int LEFT_TOP_Y = 10;

/* �����ģΪGRID_SIZE x GRID_SIZE */
const int GRID_SIZE = 50;

/* �����С����������Ϊ(��Ļ��/��Ľ�С��)����(����������5) */
const int SCREEN_WIDTH = GetSystemMetrics(SM_CXFULLSCREEN);
const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYFULLSCREEN);
const int INC = min(SCREEN_WIDTH, SCREEN_HEIGHT) / (GRID_SIZE + 5);
const double INC_DB = (double)INC;

/* ���������� */
int pos[GRID_SIZE + 1][GRID_SIZE + 1][2];

/* ���������ڣ����߶μ���±�������ĵ������ƫ�ƹ�ϵ */
static const int match_hor[2][2] = {0,0, 0,1};
static const int match_ver[2][2] = {0,0, 1,0};

/* ���������ڣ��ĸ�����������ĵ������ƫ���� */
static const int dd[4][2] = {0,0, 1,0, 1,1, 0,1};

double value[GRID_SIZE + 1][GRID_SIZE + 1]; //������valueֵ
int hor[GRID_SIZE][GRID_SIZE + 1][2]; //ˮƽ�߶��ϵĵ�ֵ������
int ver[GRID_SIZE + 1][GRID_SIZE][2]; //��ֱ�߶��ϵĵ�ֵ������

/* ���ǻ��ֲ��� */
int pos_center[GRID_SIZE][GRID_SIZE][2]; //���ĵ�����
double value_center[GRID_SIZE][GRID_SIZE]; //���ĵ㺯��ֵ
int center[GRID_SIZE][GRID_SIZE][4][2]; //���ĵ����ĸ������߶��ϵĵ�ֵ�����꣬ע�⵽ÿ�������������߶�

//�߶����˵㺯��ֵ�ֱ�Ϊx,y�����ظ��߶����Ƿ���ڵ�ֵ��
bool valid(double x, double y) {
	return (x - CON) * (y - CON) < EPS;
}

//����һ����Χ��[0,1.0]��α���С��
double generate() {
	return (rand() % 10) / 9.0;
	//return rand() / RAND_RANGE;
}

//����һ�������ı��ϵ�ֵ��ĺ�����(������Ϊ-1)�����ظ������Ƿ���ڶ�����
bool ambiguous(int x1, int x2, int x3, int x4) {
	return (~x1) && (~x2) && (~x3) && (~x4);
}

//���Ƶ�ֵ��
void flush(CDC* pDC = NULL) {
	if (pDC == NULL) {
		return;
	}
	
	//���ǻ��֣���������ĵ㺯��ֵ�����꣬���������ĵ����ĸ������߶��Ͽ��ܵĵ�ֵ������
	/*******************************************************
	 * ����ƫ�����������ĵ�Ϊ(x,y)�����ĸ�����pos�����Ӧ�±�ֱ�Ϊ
	 * ����(x,y), ����(x+1,y), ����(x,y+1), ����(x+1,y+1)
	 *******************************************************/
	//freopen("error.txt", "w", stdout);
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {	
			/* �������ĵ㺯��ֵ */
			value_center[i][j] = 0.0;
			for (int k = 0; k < 4; ++k) {
				value_center[i][j] += value[i + dd[k][0]][j + dd[k][1]]; //�ĸ������
			}
			value_center[i][j] *= 0.25;//ȡ�ĸ���ƽ��ֵ
			//std::cout << value_center[i][j] << " ";

			/* ���ĵ����ĸ������ߵ�ֵ������ */
			for (k = 0; k < 4; ++k) {
				if (valid(value_center[i][j], value[i + dd[k][0]][j + dd[k][1]])) {
					//���ڵ�ֵ��
					int dx = pos_center[i][j][0] - pos[i + dd[k][0]][j + dd[k][1]][0];
					int dy = pos_center[i][j][1] - pos[i + dd[k][0]][j + dd[k][1]][1];
					center[i][j][k][0] = pos[i + dd[k][0]][j + dd[k][1]][0];
					center[i][j][k][0] += (int)(dx * (CON - value[i + dd[k][0]][j + dd[k][1]])
						/ (value_center[i][j] - value[i + dd[k][0]][j + dd[k][1]]));
					center[i][j][k][1] = pos[i + dd[k][0]][j + dd[k][1]][1];
					center[i][j][k][1] += (int)(dy * (CON - value[i + dd[k][0]][j + dd[k][1]])
						/ (value_center[i][j] - value[i + dd[k][0]][j + dd[k][1]]));
				} else {
					//�����ڵ�ֵ��
					center[i][j][k][0] = center[i][j][k][1] = -1;
				}
				//std::cout << "center[" << i << "][" << j << "][" << k << "] = " << center[i][j][k][0] << ", " << center[i][j][k][1] << std::endl;
			}
		}
		//std::cout << std::endl;
	}

	/* ����ֵ�ߣ����ǵ��κ�һ�ε�ֵ�߶������漰һ��б�߶Σ�����ֻ������4xSIZExSIZE��б�߶� */
	/* б�߶ι�����ˮƽ&��ֱ�߶� */
	int con_hor[4][2] = {0,0, 0,0, 0,1, 0,1};
	int con_ver[4][2] = {0,0, 1,0, 1,0, 0,0};
	for (i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
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

void calculate(CDC* pDC, double _con) {
	CON = _con;
	//������߽�ĵ�ֵ��(��ֵ�ߺ����񽻵�)���꣬ӳ���ϵΪpoint=>cordination
	for (int i = 0; i <= GRID_SIZE; ++i) {
		for (int j = 0; j <= GRID_SIZE; ++j) {
			if (i < GRID_SIZE) {
				if (valid(value[i][j], value[i + 1][j])) {
					hor[i][j][0] = pos[i][j][0];
					hor[i][j][1] = pos[i][j][1];
					hor[i][j][0] += (int)(INC_DB * (CON - value[i][j]) / (value[i + 1][j] - value[i][j]));
				} else {
					hor[i][j][0] = hor[i][j][1] = -1;
				}
			}
			if (j < GRID_SIZE) {
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
	flush(pDC); //���Ƶ�ֵ��
}

void CPro2_2View::OnDraw(CDC* pDC)
{
	CPro2_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//��������
	//CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	//pMain->ActivateFrame(SW_SHOWMAXIMIZED); //���������

	//add draw code for native data here
	CPen myPen1;
	//myPen1.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	myPen1.CreatePen(PS_SOLID, 1, RGB(25, 193, 242));
	CPen* oldPen = pDC->SelectObject(&myPen1);
	//pDC->SelectObject(oldPen);
	
	//��������
	int i, j;
	for (i = 0; i <= GRID_SIZE; ++i) {
		for (j = 0; j <= GRID_SIZE; ++j) {
			pos[i][j][0] = LEFT_TOP_X + INC * i;
			pos[i][j][1] = LEFT_TOP_Y + INC * j;
		}
	}
	for (i = 0; i <= GRID_SIZE; ++i) {
		pDC->MoveTo(LEFT_TOP_X + INC * i, LEFT_TOP_Y);
		pDC->LineTo(LEFT_TOP_X + INC * i, LEFT_TOP_Y + INC * GRID_SIZE);
		pDC->MoveTo(LEFT_TOP_X, LEFT_TOP_Y + INC * i);
		pDC->LineTo(LEFT_TOP_X + INC * GRID_SIZE, LEFT_TOP_Y + INC * i);
	}
	
	for (i = 0; i < GRID_SIZE; ++i) {
		for (j = 0; j < GRID_SIZE; ++j) {
			/* �����������ĵ����� */
			pos_center[i][j][0] = (pos[i][j][0] + pos[i + 1][j][0]) >> 1;
			pos_center[i][j][1] = (pos[i][j][1] + pos[i][j + 1][1]) >> 1;
			for (int k = 0; k < 4; ++k) {
				pDC->MoveTo(pos_center[i][j][0], pos_center[i][j][1]);
				pDC->LineTo(pos[i+dd[k][0]][j+dd[k][1]][0], pos[i+dd[k][0]][j+dd[k][1]][1]);
			}
		}
	}

	//���ɸ�����valueֵ
	srand(time(0));
	for (i = 0; i <= GRID_SIZE; ++i) {
		for (j = 0; j <= GRID_SIZE; ++j) {
			value[i][j] = generate(); //�����������ֵ[0,1.0]
		}
	}

	//�궥����ֵ
	/* ��ʾ�����ַ���������Զ�Ӧ����ƫ������������ʾ���ı����ͷֱ��ʿ�����Ҫ΢��RDU_X��RDU_Y */
	/*
	const int RDU_X = 1;
	const int RDU_Y = 1;
	CString str; //���ڸ�ʽ������, ת����integer => QString
	for (i = 0; i <= GRID_SIZE; ++i) {
		for (j = 0; j <= GRID_SIZE; ++j) {
			str.Format(".%.0f", 10.0 * value[i][j]); //�˴���ʽ��ģʽӦƥ��value����������(int?float?)
			pDC->TextOut(pos[i][j][0] - RDU_X, pos[i][j][1] - RDU_Y, str);
		}
	}
	*/

	//��ɫ����
	CPen myPen2;
	myPen2.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldPen = pDC->SelectObject(&myPen2);

	calculate(pDC, 0.4); //���������߽��ֵ�㣬��ֵΪCON=0.4�������Ƶ�ֵ��

	//��ɫ����
	CPen myPen3;
	//myPen3.CreatePen(PS_SOLID, 1, RGB(6, 189, 19));
	myPen3.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	oldPen = pDC->SelectObject(&myPen3);
	
	calculate(pDC, 0.6); //����������ֵΪCON=0.6�ĵ�ֵ�㲢���Ƶ�ֵ��
}

/////////////////////////////////////////////////////////////////////////////
// CPro2_2View printing

BOOL CPro2_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPro2_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPro2_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPro2_2View diagnostics

#ifdef _DEBUG
void CPro2_2View::AssertValid() const
{
	CView::AssertValid();
}

void CPro2_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPro2_2Doc* CPro2_2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPro2_2Doc)));
	return (CPro2_2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro2_2View message handlers
