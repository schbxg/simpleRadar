// FormDlg5.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimpleInsectRadar.h"
#include "FormDlg5.h"
#include "afxdialogex.h"


// CFormDlg5 �Ի���

IMPLEMENT_DYNAMIC(CFormDlg5, CDialogEx)

CFormDlg5::CFormDlg5(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFormDlg5::IDD, pParent)
{

}

CFormDlg5::~CFormDlg5()
{
}

void CFormDlg5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHARTCTRL7, m_ChartCtrl_7);
	DDX_Control(pDX, IDC_CHARTCTRL8, m_ChartCtrl_8);
	DDX_Control(pDX, IDC_CHARTCTRL9, m_ChartCtrl_9);
}


BEGIN_MESSAGE_MAP(CFormDlg5, CDialogEx)
	ON_MESSAGE(WM_USER+126, &CFormDlg5::OnUser126)
	ON_MESSAGE(WM_USER+127, &CFormDlg5::OnUser127)
	ON_MESSAGE(WM_USER+128, &CFormDlg5::OnUser128)
END_MESSAGE_MAP()


// CFormDlg5 ��Ϣ�������


BOOL CFormDlg5::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	InitChartCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CFormDlg5::InitChartCtrl()
{
	//����������
	CChartStandardAxis* m_pBottomAxis_Chart_7 =  m_ChartCtrl_7.CreateStandardAxis(CChartCtrl::BottomAxis);
	//pBottomAxis->SetMinMax(0, 0);
	m_pBottomAxis_Chart_7->SetAutomatic(true);
	CChartStandardAxis* m_pLeftAxis_Chart_7   =  m_ChartCtrl_7.CreateStandardAxis(CChartCtrl::LeftAxis);
	//pLeftAxis->SetMinMax(0, 0);
	m_pLeftAxis_Chart_7->SetAutomatic(true);

	CChartStandardAxis* m_pBottomAxis_Chart_8 =  m_ChartCtrl_8.CreateStandardAxis(CChartCtrl::BottomAxis);
	m_pBottomAxis_Chart_8->SetAutomatic(true);
	CChartStandardAxis* m_pLeftAxis_Chart_8   =  m_ChartCtrl_8.CreateStandardAxis(CChartCtrl::LeftAxis);
	m_pLeftAxis_Chart_8->SetAutomatic(true);

	CChartStandardAxis* m_pBottomAxis_Chart_9 =  m_ChartCtrl_9.CreateStandardAxis(CChartCtrl::BottomAxis);
	m_pBottomAxis_Chart_9->SetAutomatic(true);
	CChartStandardAxis* m_pLeftAxis_Chart_9   =  m_ChartCtrl_9.CreateStandardAxis(CChartCtrl::LeftAxis);
	m_pLeftAxis_Chart_9->SetAutomatic(true);

	// ���������
	m_pPointsSeries_7 = m_ChartCtrl_7.CreatePointsSerie();
	m_pLinesSeries_8 = m_ChartCtrl_8.CreateLineSerie();
	//m_pLinesSeries_9 = m_ChartCtrl_9.CreateLineSerie();
	m_pPointsSeries_9 = m_ChartCtrl_9.CreatePointsSerie();

	m_ChartCtrl_7.GetTitle()->AddString(_T("�߶�-ʱ��ֲ�"));
	m_ChartCtrl_8.GetTitle()->AddString(_T("�������Ƶ��"));
	m_ChartCtrl_9.GetTitle()->AddString(_T("��������ͼ"));
	
}

// �߶�-ʱ��ֲ�
afx_msg LRESULT CFormDlg5::OnUser126(WPARAM wParam, LPARAM lParam)
{
	UINT nCount = *((UINT*)(lParam));
	UINT nLen = nCount * 2;
	double *p = (double*)wParam;

	double *pValueArray = new double[nLen];

	memcpy(pValueArray, (double*)wParam, nLen*8);


	m_pPointsSeries_7->ClearSerie();
	m_pPointsSeries_7->SetPoints(pValueArray, (pValueArray+nCount), nCount);


	delete []pValueArray;
	delete []p;
	return 0;
}

// �������Ƶ��
afx_msg LRESULT CFormDlg5::OnUser127(WPARAM wParam, LPARAM lParam)
{
	UINT nCount = *((UINT*)(lParam));
	UINT nLen = nCount * 2;
	double *p = (double*)wParam;

	double *pValueArray = new double[nLen];

	memcpy(pValueArray, (double*)wParam, nLen*8);


	m_pLinesSeries_8->ClearSerie();
	m_pLinesSeries_8->SetPoints(pValueArray, (pValueArray+nCount), nCount);


	delete []pValueArray;

	delete []p;

	return 0;
}

// ��������ͼ
afx_msg LRESULT CFormDlg5::OnUser128(WPARAM wParam, LPARAM lParam)
{
	UINT nCount = *((UINT*)(lParam));
	UINT nLen = nCount * 2;

	double *pValueArray = new double[nLen];

	memcpy(pValueArray, (double*)wParam, nLen*8);


	m_pPointsSeries_9->ClearSerie();
	m_pPointsSeries_9->SetPoints(pValueArray, (pValueArray+nCount), nCount);


	delete []pValueArray;
	return 0;
}


