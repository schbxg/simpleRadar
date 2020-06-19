#pragma once
#include "stdafx.h"
#include "SimpleInsectRadarDlg.h"
#include "DigitalStatic/Digistatic.h"
#include "FormDlg3.h"
#include "FormDlg4.h"
#include "FormDlg5.h"

#include "ParaConfig.h"
#include "afxcmn.h"
#include "afxwin.h"
//#include "SimpleInsectRadarDlg.h"
// CFormDlg1 �Ի���

class CFormDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(CFormDlg1)

public:
	CFormDlg1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFormDlg1();

	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_FORMVIEW1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CDigiStatic m_AntennaAziAngle;      //���߷�λָ���
	CDigiStatic m_AntennaEleAngle;      //���߸���ָ���
	CDigiStatic m_RFTemperature; //��Ƶģ���¶�
	CDigiStatic m_SATASaveSpeed; //SATA�洢�ٶ�
	CDigiStatic m_SATAVolum;     //SATA�洢����
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	//CTchart1 m_chart1;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	//CTchart1 m_chart2;

	CParaConfig m_dlgParaConfig;
	afx_msg void OnBnClickedButton2();
	//CSimpleInsectRadarDlg  m_simpleInsectRadarDlg;

	//����SATA����
	double calculSATAVolum();

private:
	static UINT RadarWorkThread(LPVOID lpParam);
	UINT RadarWorkProcess();
	//һά�������ϵͳ״̬��Ϣ������
	void DataProcessing(byte *p, int len);
	//�ٽ�������
	CCriticalSection m_criticalsection;

	//void Draw(float *p, UINT nLen, UINT nSeriesCnt, CSeries series);
protected:
	afx_msg LRESULT OnUpdateformdlg1Ui(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButton6();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnUser222(WPARAM wParam, LPARAM lParam);

public:
	void IFFT_tchart1();
	void IFFT_tchart2();
protected:
	afx_msg LRESULT OnMsgProtectUI(WPARAM wParam, LPARAM lParam);
public:
	CTabCtrl		m_TabCtrl;
	CFormDlg3		m_formDlg3;
	CFormDlg4		m_formDlg4;
	CFormDlg5		m_formDlg5;
	//CSimpleInsectRadarDlg  m_simpleInsectRadarDlg;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	void LoadMatlabPara();

private:
	//void Matlab_();
	CWinThread *m_pStroeThread;
	DWORD exitCode;
	CCriticalSection storeCriticalSection;
protected:
	afx_msg LRESULT OnUser223(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser224(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser888(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser889(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser890(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser891(WPARAM wParam, LPARAM lParam);
private:
	static UINT threadStore(LPVOID lParam);
	UINT storeProcess();
public:
	//CSimpleInsectRadarDlg m_simpleInsectRadarDlg;
	CButton m_btnPlayBack;
	afx_msg void OnBnClickedButtonPlayback();
	static UINT PlayBackThread(LPVOID lpParam);
	UINT PlayBackProcess();

	void playBackFileNames();
	void trackPlayBack(CString str);
	void compareFileNameToTimePiker(CString strFullName);
	//void DeleteFiles(LPCTSTR LRFileName); // ɾ�������ļ�

	CString CreateFileFolder(CString str);//�������ڴ洢OriTrack���ļ���
	void GetFileNameFromDir(CString strDirPath); // ��ȡ�ļ������ļ�ʱ�䲢����
	int GetFileCreateTimeStamp(CString str);

	CString  ReadTrackLogFile(CString strFileName);
	void CreateFilePath(CString filePath);
	CommonFun m_commonFun;
};
