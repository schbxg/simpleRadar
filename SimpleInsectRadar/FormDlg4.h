#pragma once
#include "afxwin.h"
//#include "d:\huangxigan\815\01\02z\simpleinsectradar_v2_20180530\simpleinsectradar\chartctrl\chartctrl.h"
//#include <Eigen/Dense>



// CFormDlg4 对话框

class CFormDlg4 : public CDialogEx
{
	DECLARE_DYNAMIC(CFormDlg4)

public:
	CFormDlg4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFormDlg4();

// 对话框数据
	enum { IDD = IDD_FORMVIEW4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CChartCtrl m_ChartCtrl_1;
	CChartCtrl m_ChartCtrl_2;
	CChartCtrl m_ChartCtrl_3;
	CChartCtrl m_ChartCtrl_4;

private:
	//坐标轴
	CChartStandardAxis* m_pBottomAxis_Chart_1;
	CChartStandardAxis* m_pLeftAxis_Chart_1;
	CChartStandardAxis* m_pBottomAxis_Chart_2;
	CChartStandardAxis* m_pLeftAxis_Chart_2;
	CChartStandardAxis* m_pBottomAxis_Chart_3;
	CChartStandardAxis* m_pLeftAxis_Chart_3;
	CChartStandardAxis* m_pBottomAxis_Chart_4;
	CChartStandardAxis* m_pLeftAxis_Chart_4;

	//点或线
	//CChartPointsSerie* m_pPointsSeries_1;
	CChartLineSerie* m_pLinesSeries_1;
	CChartPointsSerie* m_pPointsSeries_2;
	CChartPointsSerie* m_pPointsSeries_3;
	CChartPointsSerie* m_pPointsSeries;
	//CChartLineSerie*   m_pLinesSeries;
	CChartPointsSerie* m_pLinesSeries_6;

private:
	void InitChartCtrl();
	void DrawChart_1();
	void DrawChart_2();
	void DrawChart_3();
	void DrawChart_4();

public:
	
protected:
	afx_msg LRESULT OnUser121(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser122(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser123(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser124(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser125(WPARAM wParam, LPARAM lParam);
public:
	CChartCtrl m_ChartCtrl_6;
};


