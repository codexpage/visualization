// pro1_1View.cpp : implementation of the CPro1_1View class
//

#include "stdafx.h"
#include "pro1_1.h"

#include "pro1_1Doc.h"
#include "pro1_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro1_1View

IMPLEMENT_DYNCREATE(CPro1_1View, CView)

BEGIN_MESSAGE_MAP(CPro1_1View, CView)
	//{{AFX_MSG_MAP(CPro1_1View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro1_1View construction/destruction

CPro1_1View::CPro1_1View()
{
	// TODO: add construction code here

}

CPro1_1View::~CPro1_1View()
{
}

BOOL CPro1_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPro1_1View drawing

const double CON = 5.0; //������ĵ�ֵ
const double EPS = 1e-8; //����

//�߶����˵㺯��ֵ�ֱ�Ϊx,y�����ظ��߶����Ƿ���ڵ�ֵ��
bool valid(double x, double y) {
	return (x - CON) * (y - CON) < EPS;
}

//����һ�������ı��ϵ�ֵ��ĺ�����(������Ϊ-1)�����ظ������Ƿ���ڶ�����
bool ambiguous(int x1, int x2, int x3, int x4) {
	return (~x1) && (~x2) && (~x3) && (~x4);
}

void CPro1_1View::OnDraw(CDC* pDC)
{
	CPro1_1Doc* pDoc = GetDocument();
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
	const int SCREEN_WIDTH = GetSystemMetrics(SM_CXFULLSCREEN); //��Ļ���(����ֱ���)
	const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYFULLSCREEN); //��Ļ�߶�(����ֱ���)
	const int INC = min(SCREEN_WIDTH, SCREEN_HEIGHT) / (SIZE + 5);
	const double INC_DB = (double)INC;
	
	/* ���������� */
	int pos[SIZE + 1][SIZE + 1][2], i, j;

	for (i = 0; i <= SIZE; ++i) {
		for (j = 0; j <= SIZE; ++j) {
			pos[i][j][0] = LEFT_TOP_X + INC * i;
			pos[i][j][1] = LEFT_TOP_Y + INC * j;
		}
	}

	for (i = 0; i <= SIZE; ++i) {
		pDC->MoveTo(LEFT_TOP_X + INC * i, LEFT_TOP_Y);
		pDC->LineTo(LEFT_TOP_X + INC * i, LEFT_TOP_Y + INC * SIZE);
		pDC->MoveTo(LEFT_TOP_X, LEFT_TOP_Y + INC * i);
		pDC->LineTo(LEFT_TOP_X + INC * SIZE, LEFT_TOP_Y + INC * i);
	}

	//������valueֵ
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
			str.Format("%.0f", value[i][j]); //�˴���ʽ��ģʽӦƥ��value����������(int?float?)
			pDC->TextOut(pos[i][j][0] - RDU_X, pos[i][j][1] - RDU_Y, str);
		}
	}

	//������߽�ĵ�ֵ��(��ֵ�ߺ����񽻵�)���꣬ӳ���ϵΪpoint=>cordination
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

	//������ɫ����= =
	CPen myPen2;
	myPen2.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pDC->SelectObject(&myPen2);

	//����ֵ�ߣ���������ÿ������
	//��ÿ������
	//�����ڶ����ԣ���������ĵ㺯��ֵ�����Ƶظ�һ�£�
	//�������ڶ����ԣ�ֻ��Ҫ˳ʱ��ؿ����������߽�����Ӽ��ɣ�������
	//1. hor[i][j] => ver[i][j]|ver[i+1][j]��hor[i][j+1] => ver[i][j]|ver[i+1][j]������
	//2. hor[i][j] => hor[i][j+1] �� ver[i][j] => ver[i+1][j]������
	int match_hor[2][2] = {0,0, 0,1};
	int match_ver[2][2] = {0,0, 1,0};
	//freopen("stdout.txt", "w", stdout);
	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			/* ����(i,j)�������߽�ֱ�Ϊhor[i][j], ver[i+1][j], hor[i][j+1], ver[i][j] */
			if (ambiguous(hor[i][j][0], ver[i + 1][j][0], hor[i][j + 1][0], ver[i][j][0])) {
				//���ڶ�����
				//std::cout << "(" << i << ", " << j << ") ";
				//std::cout.flush();
				double value_center = (value[i][j] + value[i + 1][j] + value[i][j + 1] + value[i + 1][j + 1]) * 0.25;
				if ((value_center - CON) * (value[i][j] - CON) < EPS) {
					//���ĵ�����ϽǶ��㡢���½Ƕ��㡰ͬ�š��������߾����������ֵCON���߾�С��CON
					//����hor[i][j]��ver[i+1][j]���Լ�hor[i][j+1]��ver[i][j]
					pDC->MoveTo(hor[i][j][0], hor[i][j][1]);
					pDC->LineTo(ver[i + 1][j][0], ver[i + 1][j][1]);
					pDC->MoveTo(hor[i][j + 1][0], hor[i][j + 1][1]);
					pDC->LineTo(ver[i][j][0], ver[i][j][1]);
				} else {
					//���ĵ�����ϽǶ��㡢���½Ƕ��㡰ͬ�š�
					//����hor[i][j]��ver[i][j]���Լ�hor[i][j+1]��hor[i+1][j]
					pDC->MoveTo(hor[i][j][0], hor[i][j][1]);
					pDC->LineTo(ver[i][j][0], ver[i][j][1]);
					pDC->MoveTo(hor[i][j + 1][0], hor[i][j + 1][1]);
					pDC->LineTo(hor[i + 1][j][0], hor[i + 1][j][1]);
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

/////////////////////////////////////////////////////////////////////////////
// CPro1_1View printing

BOOL CPro1_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPro1_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPro1_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPro1_1View diagnostics

#ifdef _DEBUG
void CPro1_1View::AssertValid() const
{
	CView::AssertValid();
}

void CPro1_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPro1_1Doc* CPro1_1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPro1_1Doc)));
	return (CPro1_1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro1_1View message handlers
