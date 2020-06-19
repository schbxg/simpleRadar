
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once
#include <time.h>
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"
#include "CLogFile.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��


#include <afxsock.h>            // MFC �׽�����չ


#include "./ChartCtrl/ChartCtrl.h"
#include "ChartCtrl\ChartXYSerie.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\ChartPointsSerie.h"

#include "TCPClient.h"

#include "FIFO.h"
#include "CommonFun.h"
#include "UDPClient.h"
#define FifoWith 320 * 1024 + 256
#define FifoWidth_track 60*1024*1024




#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include "common.h"
extern bool g_bIsRadarWork;

extern bool g_bIsTrans;

extern int g_iIsTcpConnect;
extern int g_iIsUdpOpen;

extern CUDPClient g_udpClientReceive;
extern CUDPClient g_udpClientCmdFeedBack;
extern CUDPClient g_udpClientFileFeedBack;
extern CTCPClient g_tcpClient;
extern CTCPClient g_tcpDisplaySoftClient;

#define UPDATEFORMDLG1_UI WM_USER+200

#define UPDATEFORMDLG2_UI WM_USER+300

#define MSG_TO_FORMDLG3 WM_USER+301

//�����Ƿ���̱�־λ
extern bool g_bWritingFile;


//�����ļ���Ϣ�ṹ��
typedef struct _FILELISTINFO
{
	ULONGLONG BeginAddress;    //��дSATA����ʼ��ַ
	ULONGLONG EndAddress;      //��дSATA����ֹ��ַ
	SYSTEMTIME systime;        //�����ļ�ʱ�䣺�����ļ�����
} FILELISTINFO, *PFILELISTINFO;


#define HRRPBUFFERSIZE (320*1024*20 + 200)
#define DETECTBUFFERSIZE (500*3000*13*4)

extern byte *pHrrpBuf;
extern byte *pDetectBuf;

extern byte *pTemp;
extern byte *pTemp_Detect;

extern int waveMode;

extern int codeMode;

extern ULONGLONG g_singleFileSize;
extern ULONGLONG g_startAddress;

extern float g_fAntennaAziAngle;
extern float g_fAntennaEleAngle;

extern UINT g_nDrawNodes;
extern double g_nCoefficient;	// һά������ϵ�������֣�
extern UINT g_nPara_7;		// ��ʼ��������

extern double g_dlNetSpeed;

extern bool g_bflag_paracfg;

extern bool g_bflag_enable;
extern int g_singleAcquistionTimeMax;

extern CLogFile logFile;


typedef struct _TOMATLABPARA
{
	int	  mode;
	double RCS_ball;
	UINT  StartRan;		//��ʼ��������
	UINT  SampleNum;	//����������
	UINT  PRT;			//PRT
	UINT  WaveForm;		//���α���
	UINT  CodeType;		//�������ģʽ
	CString s1;			//track�м��ļ��洢·�� /   
	CString s2;			//У׼�ļ�����·����ȫ�����޺�׺�� / У׼�ļ�ȫ·��
	double dlMinLength_Cali; //��������̳���
	double dlMinLength_ParaEst;	//����������̺���
	double dlMinLength_Den;		//�ܶ�ͳ����̺���
	float fPulseWid;		// ��������
	double SampleTime;		// ���ʲɼ�ʱ��
	int workingMode;		// ����ģʽ
	float fAzi_S;			// ��λ��ʼ�ɼ��Ƕ�
	float fAzi_E;			// ��λ��ֹ�ɼ��Ƕ�
	UINT UintCaliType;	// У׼ָ��
	float fElv_D;	 // ������ʼ�Ƕ�
	float fElv_H;	 // ������ֹ�Ƕ�
	double enableAutoCali; // �Զ���У׼ʹ��
}TOMATLABPARA;

extern TOMATLABPARA toMatlabPara;

typedef struct _SETTIME
{
	int iStartYear;
	int iStartMonth;
	int iStartDate;
	int iStartHour;
	int iStartMinute;
	int isStartSecond;
	int iStartMilliseconds;
	int iStopYear;
	int iStopMonth;
	int iStopDate;
	int iStopHour;
	int iStopMinute;
	int iStopSecond;
}SETTIME;

extern SETTIME setTimeInfo;
extern SETTIME setTimeInfoPlayBack;

extern struct tm sStrartPlayBack, sStopPlayBack;


extern CVSFIFO<byte, FifoWidth_track, 16, 1> g_fifo_track;

extern int g_workMode;
extern int g_startWorkFlag;
extern int g_stopWorkFlag;
extern bool g_bisStopSave;
extern int g_stopStoreFlag;
extern int g_autoCali;	// �Զ���У׼ʹ��
extern int g_autoCaliMode;	// �Զ���У׼ģʽ
extern int g_zhuanCun;
extern int g_zhuanCunTime;

extern CString g_trackFilePath;
extern int g_playBackTimeInterval;
extern bool g_isSucessInitMatlabPlayBacklib;

extern int g_slowScan; // ��ɨʹ��

typedef struct TimeStruct
{
	UINT32 head;
	UINT32 len;
	UINT32 year;
	UINT32 month;
	UINT32 day;
	UINT32 hour;
	UINT32 minute;
	UINT32 second;
	UINT32 millisecond;
	UINT32 tail;
}TimeStruct;

extern TimeStruct timeStruct;

#include "libfunc_Date_Transform.h"
#pragma comment (lib, "libfunc_Date_Transform.lib")

#include "libfunc_CaliMode.h"
#pragma comment (lib, "libfunc_CaliMode.lib")

#include "libfunc_VerticalLookingMode.h"
#pragma comment (lib, "libfunc_VerticalLookingMode.lib")

#include "libfunc_ScanMode.h"
#pragma comment (lib, "libfunc_ScanMode.lib")

#include "libfunc_InternalCalibration.h"
#pragma comment (lib, "libfunc_InternalCalibration.lib")
#include "libfunc_Playback_VerticalLookingMode.h"
#pragma comment (lib, "libfunc_Playback_VerticalLookingMode.lib")

#include "Date_translate.h"
#pragma comment (lib, "Date_translate.lib")

#include "func_Track_v2.h"
#pragma comment (lib, "func_Track_v2.lib")

#include "func_Main_VerticalLookingMode.h"
#include <afx.h>
#pragma comment (lib, "func_Main_VerticalLookingMode.lib")