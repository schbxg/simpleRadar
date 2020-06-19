
// SimpleInsectRadarDlg.h : 头文件
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

// CSimpleInsectRadarDlg 对话框
class CSimpleInsectRadarDlg : public CDialogEx
{
// 构造
public:
	CSimpleInsectRadarDlg(CWnd* pParent = NULL);	// 标准构造函数

	~CSimpleInsectRadarDlg();

// 对话框数据
	enum { IDD = IDD_SIMPLEINSECTRADAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CFormDlg1		m_formDlg1;
	CFormDlg2		m_formDlg2;
	CPullFileCfg	m_PullFileCfgDlg;		//配置导出文件大小对话框
	CFormDlg3		m_formDlg3;
	CParaConfig     m_paraConfig;
	CTabCtrl		m_TabCtrlMain;
	CStatusBar		m_StatusBar;
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listPrint;

	//信息打印函数
	void PrintMessage(CString str);
	afx_msg void OnMenuExit();

	
	afx_msg void OnMenuAbout();
	CRichEditCtrl m_RichEditCtrl;
	afx_msg void OnClose();

	void CreateTrackThread();

	void FileOP(LPCTSTR LRFileName); // 读取配置文件

	void CharToUTF8(CString &str); // 字符转换

	//读取配置文件线程
	static UINT ReadParaConfigThread(LPVOID lpParam);
	UINT ReadParaConfigProcess();

	void GetDataFromDspParaConfig();
	void GetDataFromMatlabParaConfig();
	void GetDataFromOwnParaConfig();
	

private:
	//临界区对象
	CCriticalSection m_criticalsection;


	static UINT NetWorkThread(LPVOID lpParam);
	UINT NetWorkProcess();

	static UINT TrackCalcThread(LPVOID lpParam);
	UINT TrackCalcProcess();

	//网络数据解析
	void DataProcessing(byte *p, UINT len);

	//指令反馈解析
	void CmdProcessing(byte *p, UINT len);

	//配置参数反馈解析
	void RadarParaProcessing(byte *p, UINT len);

	//一维距离像和系统工作状态
	void HRRPProcessing(byte *p, UINT len);

	//检测结果
	void DetectProcessing(byte *p, UINT len);

	//SATA反馈的存储结束地址
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

	CString strFileSavePath;			//上传文件存储路径
	CString strFileSavePath_jiaozhun;   //上传校准文件存储路径
	CCriticalSection m_criticalsectionStop;

private:
	CVDFIFO<byte, FifoWith, 2000, 1> m_FIFO;

	HANDLE m_hFile;
	

	//写单个文件线程
	static UINT WriteFileThread(LPVOID lpParam);
	UINT WriteProcess();

	//写多个文件线程
	static UINT WriteFileThreadEx(LPVOID lpParam);
	UINT WriteProcessEx();


	int m_nItem;
	
	//ULONGLONG ulCount;

	double m_dFileTransRate;

	//没用到
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
	// oriTrack数据处理线程
	//static UINT OriTrackProcessThread(LPVOID lpParam);
	static UINT MatlabTrackProcessThread(LPVOID lpParam);
	UINT MatlabTrackProcess();

	UINT OriTrackProcess(int CPIOut);
	void SaveTrackLogFile(CString strFileName, CString strTrackFileName);

	//MATLAB 反演算法处理
	static UINT MatlabInversionAlgProcessThread(LPVOID lpParam);
	UINT MatlabInversionAlgProcess();


	//临界区对象
	CCriticalSection m_criticalMapIter;

	// 数据转发线程
	static UINT DataTranspondThread(LPVOID lpParam);
	UINT DataTranspondProcess();
	void DisplaySoftDataProcessing(byte* p, UINT len);
	void DisplaySoftCmdProcessing(byte* p, UINT len);

	CommonFun m_commonFun;
};
