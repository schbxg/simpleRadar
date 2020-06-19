#pragma once
#include "DigitalStatic/Digistatic.h"
#include "afxcmn.h"

// CFormDlg3 对话框

class CFormDlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(CFormDlg3)

public:
	CFormDlg3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFormDlg3();

// 对话框数据
	enum { IDD = IDD_FORMVIEW3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	//CTchart1 m_chart3;		//一维距离像
	//CTchart1 m_chart4;		//抓屏一维距离像
	CChartCtrl m_chart3;	//一维距离像
	CChartCtrl m_chart4;	//抓屏一维距离像

	void InitChartCtrl();

	void IFFT_tchart1();
	void IFFT_tchart2();


protected:
	afx_msg LRESULT OnOnupdateformdlg3UI(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	CCriticalSection m_criticalsection;
	void Draw(float *p, UINT nLen, UINT nSeriesCnt, CChartLineSerie *series);

	CChartLineSerie *m_pLineSeries[4];
	CChartLineSerie *m_pLineSeries_capture[4];

public:
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
};
