
// stdafx.cpp : 只包括标准包含文件的源文件
// SimpleInsectRadar.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


bool g_bIsRadarWork = false;

bool g_bIsTrans = false;

int g_iIsTcpConnect = -1;
int g_iIsUdpOpen = -1;

CTCPClient g_tcpClient(6000, "192.168.2.11");
CTCPClient g_tcpDisplaySoftClient(6000, "192.168.2.11");
CUDPClient g_udpClientReceive(9803, "127.0.0.1");
CUDPClient g_udpClientCmdFeedBack(8083, "127.0.0.1");
CUDPClient g_udpClientFileFeedBack(8084, "127.0.0.1");
//CTCPClient g_tcpClient(6666, "127.0.0.1");

bool g_bWritingFile = false;

byte *pTemp = new byte[HRRPBUFFERSIZE];
byte *pHrrpBuf = new byte[HRRPBUFFERSIZE];

byte *pTemp_Detect = new byte[DETECTBUFFERSIZE];
byte *pDetectBuf = new byte[DETECTBUFFERSIZE];

int waveMode = 0;

int codeMode = 0;


ULONGLONG g_singleFileSize = 0;
ULONGLONG g_startAddress = 0;


float g_fAntennaAziAngle = 0.0f;
float g_fAntennaEleAngle = 0.0f;

//实时成像上传点数
UINT g_nDrawNodes = 0;
double g_nCoefficient = 0.0;	// 一维距离像系数（部分）
UINT g_nPara_7 = 0;		//起始采样点数


double g_dlNetSpeed = 0.0;

bool g_bflag_paracfg = false;

bool g_bflag_enable = true;
int g_singleAcquistionTimeMax = 0;

int g_workMode = 0;
int g_startWorkFlag = 0;
int g_stopWorkFlag = 0;
int g_stopStoreFlag = 0;
bool g_bisStopSave = true;
int g_autoCali = 0;
int g_autoCaliMode = 0;

int g_zhuanCun = 0;
int g_zhuanCunTime = 0;

CString g_trackFilePath = "";
int g_playBackTimeInterval = 0;
bool g_isSucessInitMatlabPlayBacklib = false;

int g_slowScan = 0; // 慢扫使能



//bool 

TOMATLABPARA toMatlabPara;

SETTIME setTimeInfo;
SETTIME setTimeInfoPlayBack;
struct tm sStrartPlayBack, sStopPlayBack;
TimeStruct timeStruct;

CVSFIFO<byte, FifoWidth_track, 16, 1> g_fifo_track;