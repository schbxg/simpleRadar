#pragma once

#include <time.h>
#include "DigitalStatic/Digistatic.h"

// CFormDlg2 �Ի���





class CFormDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(CFormDlg2)

public:
	CFormDlg2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFormDlg2();

// �Ի�������
	enum { IDD = IDD_FORMVIEW2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_szSavePath;
	//CDigiStatic m_AntennaAziAngle;     //���߷�λָ���
	//CDigiStatic m_AntennaEleAngle;     //���߸���ָ���
	//CDigiStatic m_RFTemperature;       //��Ƶģ���¶�
	CDigiStatic m_DiskRemainVolum;     //��ѡ����ʣ������
	CDigiStatic m_SATATransSpeed;      //SATA�ϴ��ٶ�
	CDigiStatic m_SATAVolum;           //SATA�洢����
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton7();

	//���㱻ѡ��·�����ڵĴ�������
	double calculDiskVolum();

private:
	//�����ϴ��߳�
	static UINT TransThread(LPVOID lpParma);
	UINT TransProcess();
	
	//���ݴ����߳�
	static UINT WriteFileThread(LPVOID lpParam);
	UINT WriteFileProcess();


	//һ��ͨ��fifo�����ڻ����ϴ�����
	CVDFIFO<byte, FifoWith, 2000, 1> m_RecvFiFo;

	//void Draw(float *p, UINT nLen, UINT nSeriesCnt, CSeries series);
	//�ٽ�������
	CCriticalSection m_criticalsection;

public:
	//ָ������
	//CTypedPtrList<CPtrList, PFILELISTINFO>m_fileinfolist;
	CPtrList m_fileinfolist;

	//��ʼ���ļ��б�ؼ�
	void InitFileListCtrl();

public:
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	CString m_strDataVol;
protected:
	afx_msg LRESULT OnUpdateformdlg2Ui(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	//CTchart1 m_chart1;
	//CTchart1 m_chart2;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void IFFT_tchart1();
	void IFFT_tchart2();
protected:
	afx_msg LRESULT OnUser444(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser778(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser892(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser893(WPARAM wParam, LPARAM lParam);	// ���������ť
};
