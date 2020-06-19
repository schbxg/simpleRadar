#pragma once
#include "afxwin.h"
#include "stdafx.h"
#include "afxdtctl.h"
#include <afx.h>
#include <vector>


// CParaConfig 对话框
typedef struct _RadarPara
{
	UINT nParaType;      //数据类型码;0x6b6b6b6b
	UINT nLen;           //长度
	UINT nPara_2;        //波形模式码
	UINT nPara_3;        //脉间编码模式
	UINT nPara_4;        //波形脉宽
	UINT nPara_5;        //PRT
	UINT nPara_6;        //采样窗点数
	UINT nPara_7;        //起始采样距离
	UINT nPara_8;        //实时成像上传点数
	UINT nPara_9;        //信息上传周期
	UINT nPara_10;		 //处理跳频点数
	UINT nPara_11;		 //AGC控制码1
	UINT nPara_12;		 //AGC控制码2
	UINT nPara_13;		 //标准通道使能
	UINT nPara_14;		 //标准通道控制
	UINT nPara_15;		 //天线转动模式
	UINT nPara_16;		 //俯仰波段数/方位旋转圈数
	UINT nPara_17;		 //角度个数
	float nNewAziSpeed;  //新增方位角扫描速度(高度连续覆盖模式(1,2,3)下有效)
	float nNewEleSpeed;	 //新增俯仰角扫描速度(高度连续覆盖模式(1,2,3)下有效)
	float nPara_18;      //方位向扫描起始角度
	float nPara_19;      //方位向扫描终止角度
	float nPara_20;      //方位向扫描速度
	float nPara_21;      //俯仰向扫描起始角度
	float nPara_22;      //俯仰向扫描终止角度
	float nPara_23;      //俯仰向扫描速度
	float nPara_24;      //调频预留时间
	float reserve[7];    //预留
	UINT nPara_32;		 //相参积累时间
	UINT nPara_33;		 //HH距离探索单元数
	UINT nPara_34;		 //VV距离探索单元数
	int  nPara_35;		 //HV与HH距离误差
	int  nPara_36;		 //VH与HH距离误差
	int  nPara_37;		 //VV与HH距离误差
	UINT nPara_38;		 //检测单元数
	UINT nPara_39;		 //参考单元数
	float fPara_40;		 //虚警率
	UINT nPara_47;		 //一级门限信噪比
	UINT nPara_41;		 //时间关联门限
	UINT nPara_42;		 //距离关联门限
	UINT nPara_43;		 //方位角关联门限
	UINT nPara_44;		 //俯仰角关联门限
	UINT nPara_45;		 //航迹删除时间
	UINT nPara_46;		 //航迹删除点数
	float nPara_48;		 //单次采样时间
	UINT nPara_workingModes; // 工作模式
	UINT nPara_miniinterval;  // 数据采集最小时间间隔
	float nPara_iniAzimuth; // 采集起始方位角度
	float nPara_endAzimuth; // 采集终止方位角度
	UINT nPara_dptWavPlusWid;        // 副波形脉宽
	UINT nPara_dptInitSampDist;        // 副波形-起始采样距离
	UINT nPara_distDetect;	// 距离检测单元数
	UINT nPara_dopplerDetect;	// 多普勒检测单元数
	UINT nPara_detectionChannel;	//检测通道0-HH-发射1校准、1-HV-发射2校准、2-VH、3-VV
	UINT nParaTail;
}RadarPara;

class CParaConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CParaConfig)

public:
	CParaConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CParaConfig();

	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLGPARACONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	CComboBox m_combox1;
	CComboBox m_combox2;
	CComboBox m_combox3;
	CComboBox m_combox4;
	CComboBox m_combox5;
	CComboBox m_combox6;
	RadarPara m_radarPara;
	CComboBox m_combox7;
	CComboBox m_combox8;
	CComboBox m_combox9;
	CComboBox m_combox10;
	CComboBox m_comboxPlusWidth;
	CComboBox m_comboxSimpleRage;
	CComboBox m_combox13;
	CComboBox m_combox14;
	CComboBox m_combox15;
	UINT m_wbNum;
	float m_AziStart;
	float m_AziEnd;
	float m_AziSpeed;
	float m_EleStart;
	float m_EleEnd;
	float m_EleSpeed;
	UINT m_aziCircleCnt;
	CComboBox m_combox17;
	CComboBox m_combox18;
	UINT m_edit_1;
	CComboBox m_combox19;
	CComboBox m_combox20;
	CComboBox m_combox21;
	CComboBox m_combox22;
	CComboBox m_combox23;
	UINT m_edit_2;
	UINT m_edit_3;
	float m_edit_4;
	UINT m_edit_5;
	UINT m_edit_6;
	UINT m_edit_7;
	UINT m_edit_8;
	UINT m_edit_9;
	UINT m_edit_10;
	UINT m_edit_11;
	float m_edit_12;


	afx_msg void OnCbnSelchangeCombo1();	
	afx_msg void OnEnUpdateEdit11();	
	afx_msg void OnCbnSelchangeCombo15();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo11();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();

	//收集界面参数并打包
	void GetData(RadarPara &radarPara/*unsigned char *p, UINT len = 0*/);

	//配置与matlab交互参数
	bool ConfigMatlabPara();

	//获取下发至Matlab参数
	void GetData_ToMatlab(TOMATLABPARA &Para);

	CString m_szSavePath;
	void InitFilePath_jiaozhun();
	void SaveFilePath_jiaozhun();
	
	float m_RCS_ball;
	CComboBox m_combox24;
	afx_msg void OnCbnSelchangeCombo18();

	int MinMaxFloat();
	
	double m_dlMinLength_Cali;
	double m_dlMinLength_Orien;
	double m_dlMinLength_Den;
	CComboBox m_comboxWorkingModes;
	CComboBox m_minitime;
	float m_iniAzimuth;
	CComboBox m_comboxAttenu;
	CComboBox m_mainWavPlusWid;
	CComboBox m_mainInitSapDist;
	CComboBox m_dptWavPlusWid;
	CComboBox m_dptInitSampDist;
	afx_msg void OnCbnSelchangeComboWorkingmodes();
	afx_msg void OnCbnSelchangeCombo5();
	CComboBox m_combox_workMode;

//private:
//	static UINT countThread(LPVOID lParam);
//	UINT countProcess();
public:
	CDateTimeCtrl m_dateTimePickerStart;
	CDateTimeCtrl m_dateTimePickerStop;
	UINT m_edit_distDetect;
	UINT m_edit_dopplerDetect;
	CComboBox m_autoCali;
	CComboBox m_comboxAutoCaliMode;
	CComboBox m_combox_zhuancun;
	CComboBox m_combox_zhuanCunTime;
	CComboBox m_combox_detectionChannel;
	CComboBox m_comboxEnablePlayBack;
	CString m_editPlayBackTrackPath;
//	CDateTimeCtrl m_dateTimePickerDtart;
	CDateTimeCtrl m_dateTimerPickerStopPlayBack;
	CDateTimeCtrl m_dateTimePickerStartPlayBack;
	int m_editPlayBackTimerInterval;
	afx_msg void OnBnClickedButtonChoseplaybackpath();

	void GetDateTimeFromCtrl();
	CDateTimeCtrl m_dateTimePickerStartPlayBackDate;
	CDateTimeCtrl m_dateTimePickerStopDate;

	static UINT InitMatlabPlayBackLib(LPVOID lpParam);
	UINT InitMatlabPlayBackLibProcess();

	void ArRadarParaConfig(RadarPara radarConfig);
	void DeleteFiles(LPCTSTR LRFileName);
	CComboBox m_comboxSlowScan;
};



typedef unsigned (_stdcall *PTHREAD_START) (void *);

#define chBEGINTHREADEX(psa, cbStack, pfnStartAddr,			\
	pvParam, fdwCreate, pdwThreadId)						\
		((HANDLE) _beginthreadex(							\
			(void *) (psa),									\
			(unsigned) (cbStackSize),						\
			(PTHREAD_START) (pfnStartAddr),					\
			(void *) (pvParam),								\
			(unsigned) (dwCreateFlags),						\
			(unsigned *) (pdwThreadID)))