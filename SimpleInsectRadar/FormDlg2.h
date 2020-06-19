#pragma once

#include <time.h>
#include "DigitalStatic/Digistatic.h"

// CFormDlg2 对话框





class CFormDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(CFormDlg2)

public:
	CFormDlg2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFormDlg2();

// 对话框数据
	enum { IDD = IDD_FORMVIEW2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_szSavePath;
	//CDigiStatic m_AntennaAziAngle;     //天线方位指向角
	//CDigiStatic m_AntennaEleAngle;     //天线俯仰指向角
	//CDigiStatic m_RFTemperature;       //射频模块温度
	CDigiStatic m_DiskRemainVolum;     //所选磁盘剩余容量
	CDigiStatic m_SATATransSpeed;      //SATA上传速度
	CDigiStatic m_SATAVolum;           //SATA存储容量
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton7();

	//计算被选中路径所在的磁盘容量
	double calculDiskVolum();

private:
	//数据上传线程
	static UINT TransThread(LPVOID lpParma);
	UINT TransProcess();
	
	//数据存盘线程
	static UINT WriteFileThread(LPVOID lpParam);
	UINT WriteFileProcess();


	//一个通道fifo，用于缓存上传数据
	CVDFIFO<byte, FifoWith, 2000, 1> m_RecvFiFo;

	//void Draw(float *p, UINT nLen, UINT nSeriesCnt, CSeries series);
	//临界区对象
	CCriticalSection m_criticalsection;

public:
	//指针链表
	//CTypedPtrList<CPtrList, PFILELISTINFO>m_fileinfolist;
	CPtrList m_fileinfolist;

	//初始化文件列表控件
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
	afx_msg LRESULT OnUser893(WPARAM wParam, LPARAM lParam);	// 点击擦除按钮
};
