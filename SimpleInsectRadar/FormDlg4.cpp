// FormDlg4.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimpleInsectRadar.h"
#include "FormDlg4.h"
#include "afxdialogex.h"


// CFormDlg4 �Ի���

IMPLEMENT_DYNAMIC(CFormDlg4, CDialogEx)

CFormDlg4::CFormDlg4(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFormDlg4::IDD, pParent)
	//, m_chart1(0)
	//, m_chart2(0)
	//, m_chart3(0)
	//, m_chart4(0)
{

}

CFormDlg4::~CFormDlg4()
{
}

void CFormDlg4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_TCHART1, m_chart1);
	//DDX_Control(pDX, IDC_TCHART3, m_chart2);
	//DDX_Control(pDX, IDC_TCHART2, m_chart3);
	//DDX_Control(pDX, IDC_TCHART5, m_chart4);
	DDX_Control(pDX, IDC_CHARTCTRL1, m_ChartCtrl_1);
	DDX_Control(pDX, IDC_CHARTCTRL2, m_ChartCtrl_2);
	DDX_Control(pDX, IDC_CHARTCTRL4, m_ChartCtrl_3);
	DDX_Control(pDX, IDC_CHARTCTRL5, m_ChartCtrl_4);
	DDX_Control(pDX, IDC_CHARTCTRL6, m_ChartCtrl_6);
}


BEGIN_MESSAGE_MAP(CFormDlg4, CDialogEx)
	ON_MESSAGE(WM_USER+121, &CFormDlg4::OnUser121)
	ON_MESSAGE(WM_USER+122, &CFormDlg4::OnUser122)
	ON_MESSAGE(WM_USER+123, &CFormDlg4::OnUser123)
	ON_MESSAGE(WM_USER+124, &CFormDlg4::OnUser124)
	ON_MESSAGE(WM_USER+125, &CFormDlg4::OnUser125)

END_MESSAGE_MAP()


// CFormDlg4 ��Ϣ�������


BOOL CFormDlg4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	InitChartCtrl();

	//DrawChart_1();

	//DrawChart_2();

	//DrawChart_3();

	//DrawChart_4();
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CFormDlg4::InitChartCtrl()
{
	//����������
	CChartStandardAxis* m_pBottomAxis_Chart_1 =  m_ChartCtrl_1.CreateStandardAxis(CChartCtrl::BottomAxis);
	//pBottomAxis->SetMinMax(0, 0);
	m_pBottomAxis_Chart_1->SetAutomatic(true);
	CChartStandardAxis* m_pLeftAxis_Chart_1   =  m_ChartCtrl_1.CreateStandardAxis(CChartCtrl::LeftAxis);
	//pLeftAxis->SetMinMax(0, 0);
	m_pLeftAxis_Chart_1->SetAutomatic(true);

	CChartStandardAxis* m_pBottomAxis_Chart_2 =  m_ChartCtrl_2.CreateStandardAxis(CChartCtrl::BottomAxis);
	m_pBottomAxis_Chart_2->SetAutomatic(true);
	CChartStandardAxis* m_pLeftAxis_Chart_2   =  m_ChartCtrl_2.CreateStandardAxis(CChartCtrl::LeftAxis);
	m_pLeftAxis_Chart_2->SetAutomatic(true);

	CChartStandardAxis* m_pBottomAxis_Chart_3 =  m_ChartCtrl_3.CreateStandardAxis(CChartCtrl::BottomAxis);
	m_pBottomAxis_Chart_3->SetAutomatic(true);
	CChartStandardAxis* m_pLeftAxis_Chart_3   =  m_ChartCtrl_3.CreateStandardAxis(CChartCtrl::LeftAxis);
	m_pLeftAxis_Chart_3->SetAutomatic(true);

	CChartStandardAxis* m_pBottomAxis_Chart_4 =  m_ChartCtrl_4.CreateStandardAxis(CChartCtrl::BottomAxis);
	m_pBottomAxis_Chart_4->SetAutomatic(true);
	CChartStandardAxis* m_pLeftAxis_Chart_4   =  m_ChartCtrl_4.CreateStandardAxis(CChartCtrl::LeftAxis);
	m_pLeftAxis_Chart_4->SetAutomatic(true);

	CChartStandardAxis* m_pBottomAxis_Chart_6 =  m_ChartCtrl_6.CreateStandardAxis(CChartCtrl::BottomAxis);
	m_pBottomAxis_Chart_6->SetAutomatic(true);
	CChartStandardAxis* m_pLeftAxis_Chart_6   =  m_ChartCtrl_6.CreateStandardAxis(CChartCtrl::LeftAxis);
	m_pLeftAxis_Chart_6->SetAutomatic(true);

	//���������
	//m_pPointsSeries_1 = m_ChartCtrl_1.CreatePointsSerie();
	m_pLinesSeries_1 = m_ChartCtrl_1.CreateLineSerie();	// �ܶ�����
	m_pPointsSeries_2 = m_ChartCtrl_2.CreatePointsSerie();	// ����ֲ�
	m_pPointsSeries_3 = m_ChartCtrl_3.CreatePointsSerie();	// �峤�ֲ�
	m_pPointsSeries_3->SetPointType(CChartPointsSerie::ptRectangle);
	m_pPointsSeries    = m_ChartCtrl_4.CreatePointsSerie();	// ���Ƶ�ʷֲ�
	//m_pLinesSeries    = m_ChartCtrl_4.CreateLineSerie();	// ���Ƶ�ʷֲ�
	m_pLinesSeries_6  = m_ChartCtrl_6.CreatePointsSerie();	// ���طֲ�

	m_ChartCtrl_1.GetTitle()->AddString(_T("�ܶ�����"));
	m_ChartCtrl_2.GetTitle()->AddString(_T("����ֲ�"));
	m_ChartCtrl_3.GetTitle()->AddString(_T("�峤�ֲ�"));
	m_ChartCtrl_4.GetTitle()->AddString(_T("���Ƶ�ʷֲ�"));
	m_ChartCtrl_6.GetTitle()->AddString(_T("���طֲ�"));


}

// �ܶ�����
void CFormDlg4::DrawChart_1()
{
	CChartStandardAxis* pBottomAxis =  m_ChartCtrl_1.CreateStandardAxis(CChartCtrl::BottomAxis);
	//pBottomAxis->SetMinMax(0, 0);
	pBottomAxis->SetAutomatic(true);
	CChartStandardAxis* pLeftAxis   =  m_ChartCtrl_1.CreateStandardAxis(CChartCtrl::LeftAxis);
	//pLeftAxis->SetMinMax(0, 0);
	pLeftAxis->SetAutomatic(true);

	CChartPointsSerie *pPointsSeries = m_ChartCtrl_1.CreatePointsSerie();		//�������㡱����;

	HANDLE hx = CreateFile(_T("x.bin"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hy = CreateFile(_T("y.bin"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	const UINT N = 596;

	double *pXValues = new double[N];
	double *pYValues = new double[N];

	DWORD dwReadBytes = 0;
	ReadFile(hx, pXValues, N*8, &dwReadBytes, NULL);
	ReadFile(hy, pYValues, N*8, &dwReadBytes, NULL);
	CloseHandle(hx);
	CloseHandle(hy);

	pPointsSeries->SetPoints(pXValues, pYValues, N);
}

void CFormDlg4::DrawChart_2()
{
	CChartStandardAxis* pBottomAxis =  m_ChartCtrl_2.CreateStandardAxis(CChartCtrl::BottomAxis);
	//pBottomAxis->SetMinMax(0, 0);
	pBottomAxis->SetAutomatic(true);
	CChartStandardAxis* pLeftAxis   =  m_ChartCtrl_2.CreateStandardAxis(CChartCtrl::LeftAxis);
	//pLeftAxis->SetMinMax(0, 0);
	pLeftAxis->SetAutomatic(true);

	CChartPointsSerie *pPointsSeries = m_ChartCtrl_2.CreatePointsSerie();		//�������㡱����;

	HANDLE hx = CreateFile(_T("fig3x.bin"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hy = CreateFile(_T("fig3y.bin"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	const UINT N = 869;

	double *pXValues = new double[N];
	double *pYValues = new double[N];

	DWORD dwReadBytes = 0;
	ReadFile(hx, pXValues, N*8, &dwReadBytes, NULL);
	ReadFile(hy, pYValues, N*8, &dwReadBytes, NULL);
	CloseHandle(hx);
	CloseHandle(hy);
	
	pPointsSeries->SetPoints(pXValues, pYValues, N);
}

// ��������ͼ
void CFormDlg4::DrawChart_3()
{
	//����������
	CChartStandardAxis* pBottomAxis = m_ChartCtrl_3.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetAutomatic(true);
	CChartStandardAxis* pLeftAxis = m_ChartCtrl_3.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAutomatic(true);

	//�������ݳ���
	const UINT N = 6;

	//���������ڴ�ռ�
	double XValues[N] = {2.5, 6, 7, 7, 8, 9 };
	double YValues[N] = {380, 220, 220, 410, 550, 550};

	//��������
	CChartPointsSerie *pPointsSeries = m_ChartCtrl_3.CreatePointsSerie();
	pPointsSeries->SetPointType(CChartPointsSerie::ptRectangle);
	pPointsSeries->SetPoints(XValues, YValues, N);
}

// ���Ƶ��
void CFormDlg4::DrawChart_4()
{
	//����������
	CChartStandardAxis* pBottomAxis = m_ChartCtrl_4.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetAutomatic(true);
	//pBottomAxis->SetMinMax(0, 10);
	CChartStandardAxis* pLeftAxis = m_ChartCtrl_4.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAutomatic(true);

	const UINT N = 5;

	DWORD rgElements[] = {N};

	//���������ڴ�ռ�
	double XValues[N] = {1.0, 2.0, 1.0, 2.0, 3.0};
	//double XValues[N] = {1.0, 2.0, 3.0, 4.0, 1.0};

	double YValues[N] ={650, 550, 450, 300, 100};

	//��������
	CChartLineSerie *pLinesSeries = m_ChartCtrl_4.CreateLineSerie();
	
	//pLinesSeries->SetSeriesOrdering(poXOrdering);
	//pLinesSeries->SetPoints(XValues, YValues, N);
	pLinesSeries->SetSeriesOrdering(poNoOrdering);

	for (int i=0; i<N; i++)
	{
		pLinesSeries->AddPoint(XValues[i], YValues[i]);
	}

	COLORREF BackColor = RGB(0,50,0);
	COLORREF GridColor = RGB(0,180,0);
	COLORREF TextColor = RGB(0,180,0);
	COLORREF SerieColor = RGB(0,255,0);

	// Specifies a sunken border for the control
	m_ChartCtrl_4.SetEdgeType(EDGE_SUNKEN);

	// Sets the color of the border and the back color
	m_ChartCtrl_4.SetBorderColor(TextColor);
	m_ChartCtrl_4.SetBackColor(BackColor);

	//Sets the color of the different elements of the bottom axis
	m_ChartCtrl_4.GetBottomAxis()->SetAxisColor(TextColor);
	m_ChartCtrl_4.GetBottomAxis()->SetTextColor(TextColor);
	m_ChartCtrl_4.GetBottomAxis()->GetGrid()->SetColor(GridColor);

	// Sets the color of the different elements of the left axis
	m_ChartCtrl_4.GetLeftAxis()->SetAxisColor(TextColor);
	m_ChartCtrl_4.GetLeftAxis()->SetTextColor(TextColor);
	m_ChartCtrl_4.GetLeftAxis()->GetGrid()->SetColor(GridColor);

	// Sets the color of the title, change the font to Times New Roman
	// and add a string
	m_ChartCtrl_4.GetTitle()->SetColor(TextColor);
	m_ChartCtrl_4.GetTitle()->SetFont(140,_T("Times New Roman"));
	m_ChartCtrl_4.GetTitle()->AddString(_T("An example of oscilloscope"));

	// Change the color of the line series
	pLinesSeries->SetColor(SerieColor);
}


//��ͼ
// �ܶ�����
afx_msg LRESULT CFormDlg4::OnUser121(WPARAM wParam, LPARAM lParam)
{
	UINT nCount = *((UINT*)(lParam));
	UINT nLen = nCount * 2;

	double *pValueArray = new double[nLen];

	memcpy(pValueArray, (double*)wParam, nLen*8);


	m_pLinesSeries_1->ClearSerie();
	m_pLinesSeries_1->SetPoints(pValueArray, (pValueArray+nCount), nCount);


	delete []pValueArray;
	return 0;
}

// ����ֲ�
afx_msg LRESULT CFormDlg4::OnUser122(WPARAM wParam, LPARAM lParam) 
{
	UINT nCount = *((UINT*)(lParam));
	UINT nLen = nCount * 2;

	double *pValueArray = new double[nLen];

	memcpy(pValueArray, (double*)wParam, nLen*8);


	m_pPointsSeries_2->ClearSerie();
	m_pPointsSeries_2->SetPoints(pValueArray, (pValueArray+nCount), nCount);


	delete []pValueArray;
	return 0;
}

// �峤�ֲ�
afx_msg LRESULT CFormDlg4::OnUser123(WPARAM wParam, LPARAM lParam)
{
	UINT nCount = *((UINT*)(lParam));
	UINT nLen = nCount * 2;
	double *p = (double*)wParam;

	double *pValueArray = new double[nLen];

	memcpy(pValueArray, (double*)wParam, nLen*8);


	m_pPointsSeries_3->ClearSerie();
	m_pPointsSeries_3->SetPoints(pValueArray, (pValueArray+nCount), nCount);


	delete []pValueArray;
	delete []p;
	return 0;
}


// ���Ƶ�ʷֲ�
afx_msg LRESULT CFormDlg4::OnUser124(WPARAM wParam, LPARAM lParam)
{
	UINT nCount = *((UINT*)(lParam));
	UINT nLen = nCount * 2;

	double *pValueArray = new double[nLen];

	memcpy(pValueArray, (double*)wParam, nLen*8);


	m_pPointsSeries->ClearSerie();
	m_pPointsSeries->SetPoints(pValueArray, (pValueArray+nCount), nCount);


	delete []pValueArray;
	return 0;
}

// ���طֲ�
afx_msg LRESULT CFormDlg4::OnUser125(WPARAM wParam, LPARAM lParam)
{
	UINT nCount = *((UINT*)(lParam));
	UINT nLen = nCount * 2;
	double *p = (double*)wParam;

	double *pValueArray = new double[nLen];

	memcpy(pValueArray, (double*)wParam, nLen*8);


	m_pLinesSeries_6->ClearSerie();
	m_pLinesSeries_6->SetPoints(pValueArray, (pValueArray+nCount), nCount);


	delete []pValueArray;
	delete []p;
	return 0;
}



//afx_msg LRESULT CFormDlg4::OnUser124(WPARAM wParam, LPARAM lParam)
//{
//	UINT nCount = *((UINT*)(lParam));
//	UINT nLen = nCount * 2;
//	double *p = (double*)wParam;
//
//	double *pValueArray = new double[nLen];
//
//	memcpy(pValueArray, (double*)wParam, nLen*8);
//
//
//	m_pLinesSeries->ClearSerie();
//	m_pLinesSeries->SetPoints(pValueArray, (pValueArray+nCount), nCount);
//	
//
//	delete []pValueArray;
//
//	delete []p;
//
//	return 0;
//}