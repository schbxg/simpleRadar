#pragma once
//#include "d:\huangxigan\815\01\02z\simpleinsectradar_v2_20180530\simpleinsectradar\chartctrl\chartctrl.h"
//#include "d:\huangxigan\815\01\02z\simpleinsectradar_v2_20180530\simpleinsectradar\chartctrl\chartctrl.h"
//#include "d:\huangxigan\815\01\02z\simpleinsectradar_v2_20180530\simpleinsectradar\chartctrl\chartctrl.h"


// CFormDlg5 �Ի���

class CFormDlg5 : public CDialogEx
{
	DECLARE_DYNAMIC(CFormDlg5)

public:
	CFormDlg5(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFormDlg5();

// �Ի�������
	enum { IDD = IDD_FORMVIEW5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CChartCtrl m_ChartCtrl_7;
	CChartCtrl m_ChartCtrl_8;
	CChartCtrl m_ChartCtrl_9;
	virtual BOOL OnInitDialog();

private:
	void InitChartCtrl();
	CChartPointsSerie* m_pPointsSeries_7;
	CChartLineSerie*   m_pLinesSeries_8;
	//CChartLineSerie*   m_pLinesSeries_9;
	CChartPointsSerie* m_pPointsSeries_9;

protected:
	afx_msg LRESULT OnUser126(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser127(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser128(WPARAM wParam, LPARAM lParam);


};
