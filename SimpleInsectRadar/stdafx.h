
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once
#include <time.h>
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"
#include "CLogFile.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持


#include <afxsock.h>            // MFC 套接字扩展


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

//控制是否存盘标志位
extern bool g_bWritingFile;


//定义文件信息结构体
typedef struct _FILELISTINFO
{
	ULONGLONG BeginAddress;    //读写SATA盘起始地址
	ULONGLONG EndAddress;      //读写SATA盘终止地址
	SYSTEMTIME systime;        //创建文件时间：用于文件命名
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
extern double g_nCoefficient;	// 一维距离像系数（部分）
extern UINT g_nPara_7;		// 起始采样点数

extern double g_dlNetSpeed;

extern bool g_bflag_paracfg;

extern bool g_bflag_enable;
extern int g_singleAcquistionTimeMax;

extern CLogFile logFile;


typedef struct _TOMATLABPARA
{
	int	  mode;
	double RCS_ball;
	UINT  StartRan;		//起始采样距离
	UINT  SampleNum;	//采样窗点数
	UINT  PRT;			//PRT
	UINT  WaveForm;		//波形编码
	UINT  CodeType;		//脉间编码模式
	CString s1;			//track中间文件存储路径 /   
	CString s2;			//校准文件生成路径，全名，无后缀名 / 校准文件全路径
	double dlMinLength_Cali; //定标体最短长度
	double dlMinLength_ParaEst;	//参数分析最短航迹
	double dlMinLength_Den;		//密度统计最短航迹
	float fPulseWid;		// 波形脉宽
	double SampleTime;		// 单词采集时间
	int workingMode;		// 工作模式
	float fAzi_S;			// 方位起始采集角度
	float fAzi_E;			// 方位终止采集角度
	UINT UintCaliType;	// 校准指令
	float fElv_D;	 // 俯仰起始角度
	float fElv_H;	 // 俯仰终止角度
	double enableAutoCali; // 自动内校准使能
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
extern int g_autoCali;	// 自动内校准使能
extern int g_autoCaliMode;	// 自动内校准模式
extern int g_zhuanCun;
extern int g_zhuanCunTime;

extern CString g_trackFilePath;
extern int g_playBackTimeInterval;
extern bool g_isSucessInitMatlabPlayBacklib;

extern int g_slowScan; // 慢扫使能

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