// pro2_1View.cpp : implementation of the CPro2_1View class
//

#include "stdafx.h"
#include "pro2_1.h"

#include "pro2_1Doc.h"
#include "pro2_1View.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro2_1View

IMPLEMENT_DYNCREATE(CPro2_1View, CView)

BEGIN_MESSAGE_MAP(CPro2_1View, CView)
	//{{AFX_MSG_MAP(CPro2_1View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro2_1View construction/destruction

CPro2_1View::CPro2_1View()
{
	// TODO: add construction code here

}

CPro2_1View::~CPro2_1View()
{
}

BOOL CPro2_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPro2_1View drawing

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
int match_hor[2][2] = {0,0, 0,1};
int match_ver[2][2] = {0,0, 1,0};

double value[GRID_SIZE + 1][GRID_SIZE + 1]; //������valueֵ
int hor[GRID_SIZE][GRID_SIZE + 1][2]; //ˮƽ�߶��ϵĵ�ֵ������
int ver[GRID_SIZE + 1][GRID_SIZE][2]; //��ֱ�߶��ϵĵ�ֵ������

//�߶����˵㺯��ֵ�ֱ�Ϊx,y�����ظ��߶����Ƿ���ڵ�ֵ��
bool valid(double x, double y) {
	return (x - CON) * (y - CON) < EPS;
}

//����һ����Χ��[0,1.0]��α���С��
double generate() {
	//return (rand() % 10) / 9.0;
	return rand() / RAND_RANGE;
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
	//����ֵ�ߣ���������ÿ������
	//��ÿ������
	//�����ڶ����ԣ���������ĵ㺯��ֵ�����Ƶظ�һ�£�
	//�������ڶ����ԣ�ֻ��Ҫ˳ʱ��ؿ����������߽�����Ӽ��ɣ�������=>
	//1. hor[i][j] <--> ver[i][j]|ver[i+1][j]��hor[i][j+1] <--> ver[i][j]|ver[i+1][j]������
	//2. hor[i][j] <--> hor[i][j+1] �� ver[i][j] <--> ver[i+1][j]������
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			/* ����(i,j)�������߽�ֱ�Ϊhor[i][j], ver[i+1][j], hor[i][j+1], ver[i][j] */
			if (ambiguous(hor[i][j][0], ver[i + 1][j][0], hor[i][j + 1][0], ver[i][j][0])) {
				//���ڶ�����
				//std::cout << "(" << i << ", " << j << ") ";
				//std::cout.flush();
				double value_center = (value[i][j] + value[i + 1][j] + value[i][j + 1] + value[i + 1][j + 1]) * 0.25;
				if ((value_center - CON) * (value[i][j] - CON) > EPS) {
					//���ĵ�����ϽǶ��㡢���½Ƕ��㡰ͬ�š��������߾���������ֵCON���߾�С��CON
					//����hor[i][j]��ver[i+1][j]���Լ�hor[i][j+1]��ver[i][j]
					pDC->MoveTo(hor[i][j][0], hor[i][j][1]);
					pDC->LineTo(ver[i + 1][j][0], ver[i + 1][j][1]);
					pDC->MoveTo(hor[i][j + 1][0], hor[i][j + 1][1]);
					pDC->LineTo(ver[i][j][0], ver[i][j][1]);
				} else {
					//���ĵ�����ϽǶ��㡢���½Ƕ��㡰ͬ�š�
					//����hor[i][j]��ver[i][j]���Լ�hor[i][j+1]��ver[i+1][j]
					pDC->MoveTo(hor[i][j][0], hor[i][j][1]);
					pDC->LineTo(ver[i][j][0], ver[i][j][1]);
					pDC->MoveTo(hor[i][j + 1][0], hor[i][j + 1][1]);
					pDC->LineTo(ver[i + 1][j][0], ver[i + 1][j][1]);
				}
			} else {
				//�����ڶ�����
				int ih, jh, iv, jv;
				for (int idx_hor = 0; idx_hor < 2; ++idx_hor) {
					ih = i + match_hor[idx_hor][0];
					jh = j + match_hor[idx_hor][1];
					if (hor[ih][jh][0] == -1) continue;
					for (int idx_ver = 0; idx_ver < 2; ++idx_ver) {
						iv = i + match_ver[idx_ver][0];
						jv = j + match_ver[idx_ver][1];
						if (ver[iv][jv][0] == -1) continue;
						pDC->MoveTo(hor[ih][jh][0], hor[ih][jh][1]);
						pDC->LineTo(ver[iv][jv][0], ver[iv][jv][1]);
					}
				}
				if ((~hor[i][j][0]) && (~hor[i][j + 1][0])) {
					pDC->MoveTo(hor[i][j][0], hor[i][j][1]);
					pDC->LineTo(hor[i][j + 1][0], hor[i][j + 1][1]);
				}
				if ((~ver[i][j][0]) && (~ver[i + 1][j][0])) {
					pDC->MoveTo(ver[i][j][0], ver[i][j][1]);
					pDC->LineTo(ver[i + 1][j][0], ver[i + 1][j][1]);
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

void CPro2_1View::OnDraw(CDC* pDC)
{
	CPro2_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	//add draw code for na	tive data here
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
// CPro2_1View printing

BOOL CPro2_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPro2_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPro2_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPro2_1View diagnostics

#ifdef _DEBUG
void CPro2_1View::AssertValid() const
{
	CView::AssertValid();
}

void CPro2_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPro2_1Doc* CPro2_1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPro2_1Doc)));
	return (CPro2_1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro2_1View message handlers
