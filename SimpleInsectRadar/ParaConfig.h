#pragma once
#include "afxwin.h"
#include "stdafx.h"
#include "afxdtctl.h"
#include <afx.h>
#include <vector>


// CParaConfig �Ի���
typedef struct _RadarPara
{
	UINT nParaType;      //����������;0x6b6b6b6b
	UINT nLen;           //����
	UINT nPara_2;        //����ģʽ��
	UINT nPara_3;        //�������ģʽ
	UINT nPara_4;        //��������
	UINT nPara_5;        //PRT
	UINT nPara_6;        //����������
	UINT nPara_7;        //��ʼ��������
	UINT nPara_8;        //ʵʱ�����ϴ�����
	UINT nPara_9;        //��Ϣ�ϴ�����
	UINT nPara_10;		 //������Ƶ����
	UINT nPara_11;		 //AGC������1
	UINT nPara_12;		 //AGC������2
	UINT nPara_13;		 //��׼ͨ��ʹ��
	UINT nPara_14;		 //��׼ͨ������
	UINT nPara_15;		 //����ת��ģʽ
	UINT nPara_16;		 //����������/��λ��תȦ��
	UINT nPara_17;		 //�Ƕȸ���
	float nNewAziSpeed;  //������λ��ɨ���ٶ�(�߶���������ģʽ(1,2,3)����Ч)
	float nNewEleSpeed;	 //����������ɨ���ٶ�(�߶���������ģʽ(1,2,3)����Ч)
	float nPara_18;      //��λ��ɨ����ʼ�Ƕ�
	float nPara_19;      //��λ��ɨ����ֹ�Ƕ�
	float nPara_20;      //��λ��ɨ���ٶ�
	float nPara_21;      //������ɨ����ʼ�Ƕ�
	float nPara_22;      //������ɨ����ֹ�Ƕ�
	float nPara_23;      //������ɨ���ٶ�
	float nPara_24;      //��ƵԤ��ʱ��
	float reserve[7];    //Ԥ��
	UINT nPara_32;		 //��λ���ʱ��
	UINT nPara_33;		 //HH����̽����Ԫ��
	UINT nPara_34;		 //VV����̽����Ԫ��
	int  nPara_35;		 //HV��HH�������
	int  nPara_36;		 //VH��HH�������
	int  nPara_37;		 //VV��HH�������
	UINT nPara_38;		 //��ⵥԪ��
	UINT nPara_39;		 //�ο���Ԫ��
	float fPara_40;		 //�龯��
	UINT nPara_47;		 //һ�����������
	UINT nPara_41;		 //ʱ���������
	UINT nPara_42;		 //�����������
	UINT nPara_43;		 //��λ�ǹ�������
	UINT nPara_44;		 //�����ǹ�������
	UINT nPara_45;		 //����ɾ��ʱ��
	UINT nPara_46;		 //����ɾ������
	float nPara_48;		 //���β���ʱ��
	UINT nPara_workingModes; // ����ģʽ
	UINT nPara_miniinterval;  // ���ݲɼ���Сʱ����
	float nPara_iniAzimuth; // �ɼ���ʼ��λ�Ƕ�
	float nPara_endAzimuth; // �ɼ���ֹ��λ�Ƕ�
	UINT nPara_dptWavPlusWid;        // ����������
	UINT nPara_dptInitSampDist;        // ������-��ʼ��������
	UINT nPara_distDetect;	// �����ⵥԪ��
	UINT nPara_dopplerDetect;	// �����ռ�ⵥԪ��
	UINT nPara_detectionChannel;	//���ͨ��0-HH-����1У׼��1-HV-����2У׼��2-VH��3-VV
	UINT nParaTail;
}RadarPara;

class CParaConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CParaConfig)

public:
	CParaConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CParaConfig();

	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_DLGPARACONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

	//�ռ�������������
	void GetData(RadarPara &radarPara/*unsigned char *p, UINT len = 0*/);

	//������matlab��������
	bool ConfigMatlabPara();

	//��ȡ�·���Matlab����
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