#pragma once
#include "DigitalStatic/Digistatic.h"
#include "afxcmn.h"

// CFormDlg3 �Ի���

class CFormDlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(CFormDlg3)

public:
	CFormDlg3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFormDlg3();

// �Ի�������
	enum { IDD = IDD_FORMVIEW3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	//CTchart1 m_chart3;		//һά������
	//CTchart1 m_chart4;		//ץ��һά������
	CChartCtrl m_chart3;	//һά������
	CChartCtrl m_chart4;	//ץ��һά������

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
