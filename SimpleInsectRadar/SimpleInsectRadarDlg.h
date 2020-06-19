
// SimpleInsectRadarDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "FormDlg1.h"
#include "FormDlg2.h"
#include "FormDlg3.h"
#include "PullFileCfg.h"
#include "HPSocket4C.h"
#include "ParaConfig.h"
#include "Date_translate.h"
#include "CommonFun.h"
#include "stdafx.h"
//#pragma comment (lib, "HPSocket4C_UD.lib")

// CSimpleInsectRadarDlg �Ի���
class CSimpleInsectRadarDlg : public CDialogEx
{
// ����
public:
	CSimpleInsectRadarDlg(CWnd* pParent = NULL);	// ��׼���캯��

	~CSimpleInsectRadarDlg();

// �Ի�������
	enum { IDD = IDD_SIMPLEINSECTRADAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CFormDlg1		m_formDlg1;
	CFormDlg2		m_formDlg2;
	CPullFileCfg	m_PullFileCfgDlg;		//���õ����ļ���С�Ի���
	CFormDlg3		m_formDlg3;
	CParaConfig     m_paraConfig;
	CTabCtrl		m_TabCtrlMain;
	CStatusBar		m_StatusBar;
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listPrint;

	//��Ϣ��ӡ����
	void PrintMessage(CString str);
	afx_msg void OnMenuExit();

	
	afx_msg void OnMenuAbout();
	CRichEditCtrl m_RichEditCtrl;
	afx_msg void OnClose();

	void CreateTrackThread();

	void FileOP(LPCTSTR LRFileName); // ��ȡ�����ļ�

	void CharToUTF8(CString &str); // �ַ�ת��

	//��ȡ�����ļ��߳�
	static UINT ReadParaConfigThread(LPVOID lpParam);
	UINT ReadParaConfigProcess();

	void GetDataFromDspParaConfig();
	void GetDataFromMatlabParaConfig();
	void GetDataFromOwnParaConfig();
	

private:
	//�ٽ�������
	CCriticalSection m_criticalsection;


	static UINT NetWorkThread(LPVOID lpParam);
	UINT NetWorkProcess();

	static UINT TrackCalcThread(LPVOID lpParam);
	UINT TrackCalcProcess();

	//�������ݽ���
	void DataProcessing(byte *p, UINT len);

	//ָ�������
	void CmdProcessing(byte *p, UINT len);

	//���ò�����������
	void RadarParaProcessing(byte *p, UINT len);

	//һά�������ϵͳ����״̬
	void HRRPProcessing(byte *p, UINT len);

	//�����
	void DetectProcessing(byte *p, UINT len);

	//SATA�����Ĵ洢������ַ
	void SATAEndAddress(byte *p, UINT len);

	BOOL InitMatlabLib();

protected:
	afx_msg LRESULT OnPrintMessage(WPARAM wParam, LPARAM lParam);
public:
	//CTCPClient m_tcpTest;
	//CFile m_file;
	bool m_bIsFileExist;
	CString m_strFileName;

	bool CreateFileEx();
	CListCtrl m_filelist;
	afx_msg void OnNMRClickListFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReadfile();

	CUIntArray m_fileSelectedArray;

	CString strFileSavePath;			//�ϴ��ļ��洢·��
	CString strFileSavePath_jiaozhun;   //�ϴ�У׼�ļ��洢·��
	CCriticalSection m_criticalsectionStop;

private:
	CVDFIFO<byte, FifoWith, 2000, 1> m_FIFO;

	HANDLE m_hFile;
	

	//д�����ļ��߳�
	static UINT WriteFileThread(LPVOID lpParam);
	UINT WriteProcess();

	//д����ļ��߳�
	static UINT WriteFileThreadEx(LPVOID lpParam);
	UINT WriteProcessEx();


	int m_nItem;
	
	//ULONGLONG ulCount;

	double m_dFileTransRate;

	//û�õ�
	double GetFileTransRate(int &n);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CWinThread *m_pWriteFileThread;
	//CWinThread *pTestThread;
	afx_msg LRESULT OnUser400(WPARAM wParam, LPARAM lParam);

public:
	LPSTR ConvertErrorCodeToString(DWORD ErrorCode);

	DWORD GetLastErrorW(LPWSTR lpErrorString, DWORD cchWideChar);

private:
	//hpsocket
	/*static UINT pressStopWorkButtonProcess(LPVOID lParam);
	UINT pressStopWorkButton();*/

protected:
	afx_msg LRESULT OnUser111(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser333(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser555(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnUser777(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUser894(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

private:
	static UINT countThread(LPVOID lParam);
	UINT countProcess();

public:
	// oriTrack���ݴ����߳�
	//static UINT OriTrackProcessThread(LPVOID lpParam);
	static UINT MatlabTrackProcessThread(LPVOID lpParam);
	UINT MatlabTrackProcess();

	UINT OriTrackProcess(int CPIOut);
	void SaveTrackLogFile(CString strFileName, CString strTrackFileName);

	//MATLAB �����㷨����
	static UINT MatlabInversionAlgProcessThread(LPVOID lpParam);
	UINT MatlabInversionAlgProcess();


	//�ٽ�������
	CCriticalSection m_criticalMapIter;

	// ����ת���߳�
	static UINT DataTranspondThread(LPVOID lpParam);
	UINT DataTranspondProcess();
	void DisplaySoftDataProcessing(byte* p, UINT len);
	void DisplaySoftCmdProcessing(byte* p, UINT len);

	CommonFun m_commonFun;
};
