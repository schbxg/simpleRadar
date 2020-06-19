// FormDlg1.cpp : 实现文件
//

#include "stdafx.h"
#include "SimpleInsectRadar.h"
#include "FormDlg1.h"
#include "afxdialogex.h"
#include <math.h>
#include "DSPF_sp_ifftSPxSP_cn.h"


// CFormDlg1 对话框

IMPLEMENT_DYNAMIC(CFormDlg1, CDialogEx)

CFormDlg1::CFormDlg1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFormDlg1::IDD, pParent)
	//, m_chart1(0)
	//, m_chart2(0)
{
	m_dlgParaConfig.m_hWnd = NULL;
}

CFormDlg1::~CFormDlg1()
{
}

void CFormDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ANGLE, m_AntennaAziAngle);
	DDX_Control(pDX, IDC_STATIC_ANGLE2, m_AntennaEleAngle);
	DDX_Control(pDX, IDC_STATIC_TEMPERATURE, m_RFTemperature);
	DDX_Control(pDX, IDC_STATIC_SAVESPEED, m_SATASaveSpeed);
	DDX_Control(pDX, IDC_STATIC_VOLUME, m_SATAVolum);
	//DDX_Control(pDX, IDC_TCHART1, m_chart1);
	//DDX_Control(pDX, IDC_TCHART2, m_chart2);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
	DDX_Control(pDX, IDC_BUTTON_PLAYBACK, m_btnPlayBack);
}


BEGIN_MESSAGE_MAP(CFormDlg1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CFormDlg1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CFormDlg1::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CFormDlg1::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CFormDlg1::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CFormDlg1::OnBnClickedButton2)
	ON_MESSAGE(UPDATEFORMDLG1_UI, &CFormDlg1::OnUpdateformdlg1Ui)
	ON_BN_CLICKED(IDC_BUTTON6, &CFormDlg1::OnBnClickedButton6)
	ON_WM_TIMER()
	ON_MESSAGE(WM_USER+222, &CFormDlg1::OnUser222)
	ON_MESSAGE(WM_USER+779, &CFormDlg1::OnMsgProtectUI)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CFormDlg1::OnTcnSelchangeTab1)
	ON_MESSAGE(WM_USER+223, &CFormDlg1::OnUser223)
	ON_MESSAGE(WM_USER+224, &CFormDlg1::OnUser224)
	ON_MESSAGE(WM_USER+888, &CFormDlg1::OnUser888)
	ON_MESSAGE(WM_USER+889, &CFormDlg1::OnUser889)
	ON_MESSAGE(WM_USER+890, &CFormDlg1::OnUser890)
	ON_MESSAGE(WM_USER+891, &CFormDlg1::OnUser891)
	ON_BN_CLICKED(IDC_BUTTON_PLAYBACK, &CFormDlg1::OnBnClickedButtonPlayback)
END_MESSAGE_MAP()


// CFormDlg1 消息处理程序


BOOL CFormDlg1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CRect rect;

	m_formDlg3.Create(IDD_FORMVIEW3, &m_TabCtrl);
	m_formDlg4.Create(IDD_FORMVIEW4, &m_TabCtrl);
	m_formDlg5.Create(IDD_FORMVIEW5, &m_TabCtrl);
	m_TabCtrl.GetClientRect( &rect );
	//m_formDlg3.MoveWindow( rect.left+1,rect.top+22, rect.Width()-4, rect.Height()-25, TRUE );
	m_formDlg3.SetWindowPos(NULL, rect.left+1,rect.top+22, rect.Width()-4, rect.Height()-25, SWP_SHOWWINDOW);
	m_formDlg3.ShowWindow(TRUE);

	//m_formDlg4.MoveWindow( rect.left+1,rect.top+22, rect.Width()-4, rect.Height()-25, TRUE );
	m_formDlg4.SetWindowPos(NULL, rect.left+1,rect.top+22, rect.Width()-4, rect.Height()-25, SWP_SHOWWINDOW);
	m_formDlg4.ShowWindow(FALSE);

	m_formDlg5.SetWindowPos(NULL, rect.left+1,rect.top+22, rect.Width()-4, rect.Height()-25, SWP_SHOWWINDOW);
	m_formDlg5.ShowWindow(FALSE);
	//tab初始化
	m_TabCtrl.InsertItem(0, _T("一维距离像"));
	m_TabCtrl.InsertItem(1, _T("生物参数"));
	m_TabCtrl.InsertItem(2, _T("生物参数（调试）"));

	m_AntennaAziAngle.SetText( _T("0000.00"));
	m_AntennaEleAngle.SetText( _T("0000.00"));
	m_RFTemperature.SetText(_T("0000.00"));
	m_SATASaveSpeed.SetText(_T("0000.00"));
	m_SATAVolum.SetText(_T("0000.00"));

	//GetDlgItem(IDC_BUTTON3)->SetWindowTextW(_T("开始工作"));

	if (m_dlgParaConfig.m_hWnd ==NULL)
	{
		m_dlgParaConfig.Create(IDD_DLGPARACONFIG);
	}
	m_dlgParaConfig.ShowWindow(false);

	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);

	//计算SATA容量
	double dl = calculSATAVolum();
	CString strLastFileSize;
	strLastFileSize.Format(_T("%.2f"), dl);
	m_SATAVolum.SetText(strLastFileSize);


	//float *q = new float[8192*2];
	//memset(q, 0, 8192*8);

	//Draw(q, 8192*8, 8);		//送显

	//SetTimer(2, 1000, NULL);

	////初始化网络
	//g_iIsTcpConnect = g_tcpClient.Open();
	//if (g_iIsTcpConnect == 0)
	//{
	//	theApp.m_pMainDlg->PrintMessage(_T("网络连接成功"));
	//	g_bIsRadarWork = true;
	//	AfxBeginThread(RadarWorkThread, this);     //启动网络收数线程
	//	theApp.m_pMainDlg->PrintMessage(_T("网络收数线程启动"));
	//}
	//else
	//{
	//	theApp.m_pMainDlg->PrintMessage(_T("网络连接失败，请检查网络运行情况"));
	//}

	//申请内存
	//double *pData = new double[128];
	//double *pData1 = new double[128];
	//double *pData2 = new double[128];
	//double *pData3 = new double[128];

	//for (int i=0; i<128; i++)
	//{
	//	赋值
	//	pData[i] = 100.0*sin(6.28*i/128);
	//	pData1[i] = 100.0*sin(6.28*i/128+1);
	//	pData2[i] = 100.0*sin(6.28*i/128+2);
	//	pData3[i] = 100.0*sin(6.28*i/128+3);
	//}

	//获取数据指针
	//double *pData = (double*)wParam;

	//定义字符串变量
	//CString strData;
	//for (int i=0; i<N; i++)
	//{
	//	//格式化字符串
	//	strData.Format("%lf", pData[i]);

	//	//设置列表信息
	//	m_wndListCtrl1.SetItemText(i, 1, strData);
	//}

	////获取曲线的数量
	//long SeriesCount = m_chart1.get_SeriesCount();

	////断言曲线数量为1
	////ASSERT(SeriesCount == 1);

	////获取第0条曲线
	//CSeries m_Series0 = m_chart1.Series(0);
	//CSeries m_Series1 = m_chart1.Series(1);
	//CSeries m_Series2 = m_chart1.Series(2);
	//CSeries m_Series3 = m_chart1.Series(3);

	//CSeries m_Series4 = m_chart2.Series(0);
	//CSeries m_Series5 = m_chart2.Series(1);
	//CSeries m_Series6 = m_chart2.Series(2);
	//CSeries m_Series7 = m_chart2.Series(3);
	//清空曲线点
	//m_Series0.Clear();

	////定义X轴和Y轴数据变量
	//COleSafeArray XValues, YValues;

	////定义数据长度
	//DWORD rgElements[] = {128};

	////申请数据内存空间
	//XValues.Create(VT_R8, 1, rgElements);
	//YValues.Create(VT_R8, 1, rgElements);

	////赋值
	//for (long j=0; j<128; j++)
	//{
	//	double x = (double)j;
	//	double y = pData[j];
	//	XValues.PutElement(&j, &x);
	//	YValues.PutElement(&j, &y);
	//}

	//for (long j=0; j<128; j++)
	//{
	//	m_Series0.AddXY(j, pData[j], NULL, 0);
	//	m_Series1.AddXY(j, pData1[j], NULL, 0);
	//	m_Series2.AddXY(j, pData2[j], NULL, 0);
	//	m_Series3.AddXY(j, pData3[j], NULL, 0);

	//	m_Series4.AddXY(j, pData[j], NULL, 0);
	//	m_Series5.AddXY(j, pData1[j], NULL, 0);
	//	m_Series6.AddXY(j, pData2[j], NULL, 0);
	//	m_Series7.AddXY(j, pData3[j], NULL, 0);
	//}


	//绘制曲线
	//m_Series.AddArray(128, YValues, XValues);

	//释放内存
	//delete[] pData;
	//delete[] pData1;
	//delete[] pData2;
	//delete[] pData3;

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//自检
void CFormDlg1::OnBnClickedButton1()
{
	if (g_iIsTcpConnect != 0)
	{
		MessageBox(_T("网络异常，自检功能无法使用"), NULL, MB_ICONWARNING);
		return;
	}
	UINT nBuffer[3] = {0x5a5a5a5a, 0x04, 0x01};
	g_tcpClient.Send((byte *)nBuffer, sizeof(nBuffer));
	
	//theApp.m_pMainDlg->PrintMessage(_T("系统启动"));
}

bool b_flag1 = false;
extern bool b_isStopStoreFlag;
//开始/停止按钮
void CFormDlg1::OnBnClickedButton3()
{
	//theApp.m_pMainDlg->PrintMessage(_T("开始工作！"));
	if (g_iIsTcpConnect != 0)
	{
		MessageBox(_T("网络异常，无法开始工作"), NULL, MB_ICONWARNING);
		return;
	}

	b_flag1 = !b_flag1;

	if (!b_flag1)
	{
		UINT nBuffer[4] = {0x94EF0329, 0x04, 0x04, 0x94EF032A};
		g_tcpClient.Send((byte *)nBuffer, sizeof(nBuffer));
		GetDlgItem(IDC_BUTTON3)->SetWindowTextW(_T("开始工作"));
		//KillTimer(2);
		
		m_formDlg3.KillTimer(1);
		memset(pTemp, 0, HRRPBUFFERSIZE);
		memset(pTemp_Detect, 0, DETECTBUFFERSIZE);
		//m_criticalsection.Lock();
		//g_bIsRadarWork = false;
		//m_criticalsection.Unlock();

		//RadarPara radarPara;
		//theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.GetData(radarPara);
		//radarPara.nPara_15 = 0;
		//int tt = g_tcpClient.Send((byte *)(&radarPara), sizeof(radarPara));


		GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
		/*g_bisStopSave = true;
		CLogFile log;
		log.WriteLog(_T("g_bisStopSave = true;"));*/
	}
	else if (b_flag1)
	{
		if (g_bflag_paracfg == false)
		{
			MessageBox(_T("请先完成参数配置！！！"));
			b_flag1 = false;
			return;
		}

		// 创建雷达数据存储路径
		CString oriTrackFileFolder = "原始点迹";
		CreateFileFolder(oriTrackFileFolder);
		//调用matlab相关函数

		// 在内校准模式下手动停止工作
		//if(!b_isStopStoreFlag)
		//{
		//	g_workMode == 0;
		//}
		//LoadMatlabPara();
		theApp.m_pMainDlg->CreateTrackThread();

		UINT nBuffer[4] = {0x94EF0329, 0x04, 0x03, 0x94EF032A};
		g_tcpClient.Send((byte *)nBuffer, sizeof(nBuffer));
		//SetTimer(2, 1000, NULL);		//打开定时器，刷新formdlg1的一维像信息
		//HWND hwnd_temp = theApp.m_pMainDlg->m_formDlg1.m_formDlg3.m_hWnd;
		//::SendMessage(hwnd_temp, MSG_TO_FORMDLG3, NULL, NULL);	//向formdlg3发送消息，通知其刷新界面一维像信息
#if 0 // 屏蔽一维距离像显示
		m_formDlg3.SetTimer(1, 1000, NULL);		//打开formdlg3定时器，刷新其界面一维像信息
#endif
		GetDlgItem(IDC_BUTTON3)->SetWindowTextW(_T("停止工作"));
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);

		theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
		theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
		theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);

	}
}


//开始/停止存储
bool b_isStoreFlag = false;
bool b_flag2 = false;
extern bool b_isTenMinWork;
extern bool b_isTrackFlag;	// 是否产生track标志
extern bool b_tempFlag_paracfg;
extern bool b_isCountTrack;
extern bool b_isSimulateClickBtn;
extern bool b_isWorkStoreFlag;
extern bool b_autoCaliFlag;
//extern bool b_isCountTrack;
bool b_isManualClickBtn = false;
bool b_isSetTimeThreadFlag = false;	// 是否启用定时线程标志
bool b_initFuncV2Param = false; // 初始化FuncV2参数标志
CString strOriTrackFileName; // tracklog文件中记录文件名
void CFormDlg1::OnBnClickedButton4()
{
	if (g_iIsTcpConnect != 0)
	{
		MessageBox(_T("网络异常，无法进行存储功能"), /*NULL,*/ NULL, MB_ICONWARNING);
		//return;
	}
	//g_workMode = 0;
	b_flag2 = !b_flag2;

	if (b_flag2)
	{
		GetDlgItem(IDC_BUTTON4)->SetWindowTextW(_T("停止存储"));

		// 1.获取track记录文件中的文件名
		CString strFileName;
		TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
		GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
		(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
		//wcscpy(gszSettingPath , szModulePath);
		wcscat(szModulePath , _T("TrackLog.txt"));	// 创建tracklog文件

		if(PathFileExists(szModulePath))
		{
			strOriTrackFileName = ReadTrackLogFile(szModulePath); // log中记录的文件名
			//theApp.m_pMainDlg->PrintMessage("ReadTrackLogFile");
		}
		else
		{
			HANDLE hFile = CreateFile(/*_T("123.bin")*/szModulePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			//theApp.m_pMainDlg->PrintMessage("CreateLogFile");
		}

		// 创建用于存储OriTrack的文件夹
		//CString oriTrackFileFolder = "点迹";
		//CreateFileFolder(oriTrackFileFolder);
		b_initFuncV2Param = true;
		//m_formDlg3.KillTimer(1);
		int n = theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetSize();
		if (theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetSize())  //列表不为空，说明有文件列表存在
		{
			FILELISTINFO *q = (FILELISTINFO *)theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetTail();

			////如果结束地址为零，说明由于某些异常，上位机没有接收到DSP回传的结束地址
			//if (q->EndAddress == 0)
			//{

			//}
			//新申请一个记录要存储文件的时间、起始存储地址
			SYSTEMTIME systime = {0};
			GetLocalTime(&systime);
			FILELISTINFO *p = new FILELISTINFO;
			p->systime = systime;
			p->BeginAddress = q->EndAddress;
			theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.AddTail(p);     //入队

			UINT nBuffer[2] = {0x94EF032D, 0x08};
			UINT nBufferTail = 0x94EF032E;
			byte cmdBuffer[20] = {0};
			memcpy(cmdBuffer, nBuffer, 8);
			memcpy(cmdBuffer + 8, &(p->BeginAddress), 8);
			memcpy(cmdBuffer + 16, &nBufferTail, 4);
			g_tcpClient.Send(cmdBuffer, sizeof(cmdBuffer));   //开始存储指令 + 存储起始地址

			theApp.m_pMainDlg->PrintMessage(_T("开始存储数据"));
			b_isWorkStoreFlag = false;
			int b = FALSE;
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+779, (WPARAM)&b, NULL);
		}
		else //文件列表为空，说明已经清过列表，需要从头写文件
		{
			SYSTEMTIME systime = {0};
			GetLocalTime(&systime);
			FILELISTINFO *p = new FILELISTINFO;
			p->systime = systime;
			p->BeginAddress = 0x0000000000000000;
			theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.AddTail(p);     //入队

			UINT nBuffer[2] = {0x94EF032D, 0x08};
			UINT nBufferTail = 0x94EF032E;
			byte cmdBuffer[20] = {0};
			memcpy(cmdBuffer, nBuffer, 8);
			memcpy(cmdBuffer + 8, &(p->BeginAddress), 8);
			memcpy(cmdBuffer + 16, &nBufferTail, 4);
			g_tcpClient.Send(cmdBuffer, sizeof(cmdBuffer));   //开始存储指令 + 存储起始地址
			theApp.m_pMainDlg->PrintMessage(_T("开始存储数据"));
			b_isWorkStoreFlag = false;
			int b = FALSE;
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+779, (WPARAM)&b, NULL);
		}
	}
	else if (!b_flag2)
	{
		// CSimpleInsectRadarDlg m_simpleInsectRadarDlg;
		//m_formDlg3.SetTimer(1, 1000, NULL);
		if(b_isTenMinWork || (b_isCountTrack && !b_isSimulateClickBtn && g_autoCali == 1))	// 如果在10分钟计时中点击了停止存储，就停止自动配置参数
		{
			b_isStopStoreFlag = false;
			b_tempFlag_paracfg = false;
			// m_simpleInsectRadarDlg.KillTimer(2);

			//g_autoCali = 0;
			b_autoCaliFlag = false;
			b_isSetTimeThreadFlag = true;

			if(g_workMode == 1)
			{
				storeCriticalSection.Lock();
				b_isStoreFlag = false;
				storeCriticalSection.Unlock();
			}
			b_isManualClickBtn = true;
		}
		if(g_workMode == 1 && g_autoCali == 0)
		{
			storeCriticalSection.Lock();
			b_isStoreFlag = false;
			storeCriticalSection.Unlock();
		}
		b_isSimulateClickBtn = false;
		//storeCriticalSection.Lock();
		//b_isStoreFlag = false;
		//storeCriticalSection.Unlock();
		
		b_isTrackFlag = false;
		UINT nBuffer[4] = {0x94EF0329, 0x04, 0x06, 0x94EF032A};
		g_tcpClient.Send((byte *)nBuffer, sizeof(nBuffer));  //停止存储指令

		GetDlgItem(IDC_BUTTON4)->SetWindowTextW(_T("开始存储"));
	}
}


CString  CFormDlg1::ReadTrackLogFile(CString strFileName)
{
	CStdioFile myFile;
	CFileException fileException;
	
	if(myFile.Open(strFileName, CFile::typeText | CFile::modeReadWrite), &fileException)
	{
		myFile.SeekToBegin();
		
		myFile.ReadString(strFileName);
		//MessageBox(strFileName);
		theApp.m_pMainDlg->PrintMessage("LogFileName: " + strFileName);
	}

	myFile.Close();
	return strFileName;
}

map<LONGLONG, CString> mapFileName; //原始点迹文件名存储 key:时间戳，value:文件名
map<LONGLONG, CString>::iterator itTxtFileTime;
CString oriTrackFilePath; // 点迹存储路径
CString CPIFileBackPath; // CPI数据备份路径
CString trackFilePath; // 航迹数据存储路径
CString CPIFilePath; // CPI数据存储路径
CString HRRPFilePath; // 一维距离像数据存储路径
CString VerticalFilePath; // 垂测模式反演结果
CString ScanTrackFilePath; // 扫描航迹
CString ScanBioParaFilePath; // 扫描模式统计结果
CString FusionSpotFilePath; // 融合后点迹
bool bOriTrackEmpty = false;
CString CFormDlg1::CreateFileFolder(CString str)
{
	CString fileFolderName;
	fileFolderName = str;
	if(fileFolderName.GetLength() == 0)
	{
		MessageBox(L"文件名为空！");
		return "error";
	}
	// 获取程序运行全路径
	char exeFullPath[MAX_PATH];
	GetModuleFileName(NULL, (LPWCH)exeFullPath, MAX_PATH);
	// 格式化为字符串
	CString mStrExeFullPath, strDriveLetter;
	mStrExeFullPath.Format(L"%s", exeFullPath);
	//MessageBox(mStrExeFullPath);
	strDriveLetter = mStrExeFullPath.Left(2);
	//MessageBox(strDriveLetter);

	// 创建track存储文件夹
	CString filePath;
	filePath = strDriveLetter + L"\\雷达数据";
	m_commonFun.CreateFilePath(filePath);

	
	CPIFilePath = filePath + L"\\CPI";
	m_commonFun.CreateFilePath(CPIFilePath);

	trackFilePath = filePath + L"\\Track数据打包";
	m_commonFun.CreateFilePath(trackFilePath);
	
	HRRPFilePath = filePath + L"\\一维距离像";
	m_commonFun.CreateFilePath(HRRPFilePath);

	VerticalFilePath = filePath + L"\\垂测模式反演结果";
	m_commonFun.CreateFilePath(VerticalFilePath);
	
	// 扫描航迹
	ScanTrackFilePath = filePath + L"\\扫描航迹";
	m_commonFun.CreateFilePath(ScanTrackFilePath);

	// 扫描模式统计结果
	ScanBioParaFilePath = filePath + L"\\扫描模式统计结果";
	m_commonFun.CreateFilePath(ScanBioParaFilePath);

	// 融合后点迹
	FusionSpotFilePath = filePath + L"\\融合后点迹";
	m_commonFun.CreateFilePath(FusionSpotFilePath);

	// 原始点迹
	oriTrackFilePath = filePath + L"\\" + str;
	if(!PathIsDirectory(oriTrackFilePath))
	{
		CreateDirectory(oriTrackFilePath, 0); // 不存在路径就创建
		bOriTrackEmpty = true;
		theApp.m_pMainDlg->PrintMessage("bOriTrackEmpty = true");
		//theApp.m_pMainDlg->PrintMessage("Create oriTrack Directory");
	}
	else // 文件夹存在
	{
		// 获取文件夹中的文件名并放入map
		GetFileNameFromDir(oriTrackFilePath);
		time_t tTxtFileNameTime;
		// 找到trackLog文档中记录的文件名在map中的位置
		if(!strOriTrackFileName.IsEmpty())
		{
			tTxtFileNameTime = GetFileCreateTimeStamp(strOriTrackFileName);
			itTxtFileTime = mapFileName.find(tTxtFileNameTime);
			theApp.m_pMainDlg->PrintMessage("trackLog");
		}
		else
		{
			itTxtFileTime = mapFileName.begin();
			theApp.m_pMainDlg->PrintMessage("mapFileName.begin()");
		}
		//theApp.m_pMainDlg->PrintMessage("GetFileNameFromDir");
	}
	//theApp.m_pMainDlg->PrintMessage("Create file folder done!");
	return filePath;
}

void CFormDlg1::CreateFilePath(CString filePath)
{
	if(!PathIsDirectory(filePath))
	{
		CreateDirectory(filePath, 0); // 不存在路径就创建
		//theApp.m_pMainDlg->PrintMessage("Create trackFilePath Directory");
	}
}

//获取文件夹下文件时间并排序

void CFormDlg1::GetFileNameFromDir(CString strDirPath)
{
	HANDLE file;
	WIN32_FIND_DATA fileData;

	strDirPath = strDirPath + "\\*.bin"; //获取文件夹下所有的mat文件，并排序 
	file = FindFirstFile(strDirPath.GetBuffer(), &fileData);

	if(INVALID_HANDLE_VALUE == file)
	{
		theApp.m_pMainDlg->PrintMessage("无初始点迹文件！");
		bOriTrackEmpty = true;
		return;
	}

	time_t tFileNameStamp;
	tFileNameStamp = GetFileCreateTimeStamp(fileData.cFileName);
	mapFileName.insert(pair<LONGLONG, CString>(tFileNameStamp, fileData.cFileName));

	bool bState = false;
	bState = FindNextFile(file, &fileData);
	while(bState)
	{	
		tFileNameStamp = GetFileCreateTimeStamp(fileData.cFileName);
		mapFileName.insert(pair<LONGLONG, CString>(tFileNameStamp, fileData.cFileName));
		bState = FindNextFile(file, &fileData);
	}	
}

// 获取文件创建时间
int CFormDlg1::GetFileCreateTimeStamp(CString str)
{
	if(str.IsEmpty())
	{
		return 1;
	}
	CString strFileName; // 文件名格式："OriginalTrack_2019_01_09_09_43_37.mat"
	strFileName = str;

	struct tm tFileCreateTime;
	tFileCreateTime.tm_year = _ttoi(strFileName.Mid(14, 4));
	tFileCreateTime.tm_year -= 1900;
	tFileCreateTime.tm_mon = _ttoi(strFileName.Mid(19, 2));
	tFileCreateTime.tm_mon -= 1;
	tFileCreateTime.tm_mday = _ttoi(strFileName.Mid(22, 2));
	tFileCreateTime.tm_hour = _ttoi(strFileName.Mid(25, 2));
	tFileCreateTime.tm_min = _ttoi(strFileName.Mid(28, 2));
	tFileCreateTime.tm_sec = _ttoi(strFileName.Mid(31, 2));
	int tmMilisec = _ttoi(strFileName.Mid(34, 3));
	time_t fileNameTime;
	time_t fileNameTimeMilisec;
	fileNameTime = mktime(&tFileCreateTime);
	fileNameTimeMilisec = fileNameTime * 1000 + tmMilisec;
	return fileNameTimeMilisec;
}


UINT CFormDlg1::threadStore(LPVOID lParam)
{
	return ((CFormDlg1 *)lParam)->storeProcess();
}

bool b_isTimeOutFlag = false;	// 定时模式时间到标志位
extern bool b_isStopCountCirculations;	// 是否处于开始上传状态标志
bool tempisStopCountCirculations = false;
extern int tempiTwiceCount;
extern int iTwiceCount;
UINT CFormDlg1::storeProcess()
{
	//bool tempFlag = false;
	// 获取系统时间，停止存储
	while(b_isStoreFlag)
	{
		// 获取当前系统时间
		SYSTEMTIME curSystemTime;
		GetLocalTime(&curSystemTime);
		//if((curSystemTime.wHour == setTimeInfo.iStopHour) && (curSystemTime.wMinute == setTimeInfo.iStopMinute) &&
		//	(curSystemTime.wSecond == setTimeInfo.iStopSecond) && b_flag2)
		//{
		//	g_stopWorkFlag = 1;
		//	break;

		//	/*if(b_flag2)
		//	{
		//	g_stopWorkFlag = 1;
		//	break;
		//	}
		//	else if()
		//	{

		//	}*/
		//}

		if(g_workMode == 1 && g_autoCali == 0)
		{
			if((curSystemTime.wHour == setTimeInfo.iStopHour) && (curSystemTime.wMinute == setTimeInfo.iStopMinute) &&
			(curSystemTime.wSecond == setTimeInfo.iStopSecond) && b_flag2)
			{
				g_stopWorkFlag = 1;
				b_isTimeOutFlag = true;
				break;

				/*if(b_flag2)
				{
				g_stopWorkFlag = 1;
				break;
				}
				else if()
				{

				}*/
			}
		}
		if(g_workMode == 1 && g_autoCali == 1)
		{
			if((curSystemTime.wHour == setTimeInfo.iStopHour) && (curSystemTime.wMinute == setTimeInfo.iStopMinute) &&
				b_flag2 && (b_isTenMinWork || b_isTrackFlag))
			{
				//if(b_isStopCountCirculations)	// 处于上传状态直接跳出while循环
				//{
				//	OutputDebugString(_T("处于上传状态直接跳出while循环\n"));
				//	tempisStopCountCirculations = true;
				//	break;
				//}
				//else
				//{
				iTwiceCount = 0;
				tempiTwiceCount = 0;
				g_stopWorkFlag = 1;
				b_isTimeOutFlag = true;
				break;
				//}
				/*if(b_flag2)
				{
				g_stopWorkFlag = 1;
				break;
				}
				else if()
				{

				}*/
			}
			else if((curSystemTime.wHour == setTimeInfo.iStopHour) && (curSystemTime.wMinute == setTimeInfo.iStopMinute) &&
				(curSystemTime.wSecond == setTimeInfo.iStopSecond) && b_isStopCountCirculations) // 处于上传状态
			{
				iTwiceCount = 0;
				tempiTwiceCount = 0;
				OutputDebugString(_T("处于上传状态直接跳出while循环\n"));
				tempisStopCountCirculations = true;
				break;
			}
		}	
	}
	if(tempisStopCountCirculations)
	{
		b_isStoreFlag = false;
	}

	while(tempisStopCountCirculations)
	{
		Sleep(1);
		OutputDebugString(_T("tempisStopCountCirculations~~~~\n"));
		if((!b_isStopCountCirculations) && (b_isTenMinWork || b_isTrackFlag) && b_flag2)
		{
			g_stopWorkFlag = 1;
			b_isTimeOutFlag = true;
			break;
		}	
	}
	if (g_stopWorkFlag == 1)
	{
		tempisStopCountCirculations = false;
		PostMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON4, BN_CLICKED), NULL);	// 停止存储
	}
	
	return 0;
}

//开环/闭环校准
bool b_flag3 = false;
void CFormDlg1::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	if (g_iIsTcpConnect != 0)
	{
		MessageBox(_T("网络异常，无法进行校准功能"), /*NULL,*/ NULL, MB_ICONWARNING);
		return;
	}

	b_flag3 = !b_flag3;

	if (b_flag3)
	{
		UINT nBuffer[3] = {0x5a5a5a5a, 0x04, 0x07};
		g_tcpClient.Send((byte *)nBuffer, sizeof(nBuffer));
		GetDlgItem(IDC_BUTTON5)->SetWindowTextW(_T("闭环校准"));
	}
	else if (!b_flag3)
	{
		UINT nBuffer[3] = {0x5a5a5a5a, 0x04, 0x08};
		g_tcpClient.Send((byte *)nBuffer, sizeof(nBuffer));
		GetDlgItem(IDC_BUTTON5)->SetWindowTextW(_T("开环校准"));
	}
}



//参数配置
extern bool isAutoClickStartWorkButton;
void CFormDlg1::OnBnClickedButton2()
{
	/*storeCriticalSection.Lock();
	g_workMode = 0;
	storeCriticalSection.Unlock();*/
	
	/*DeleteFiles(_T("ToDspParaConfig.txt"));
	DeleteFiles(_T("ToOwnParaConfig.txt"));
	DeleteFiles(_T("ToMatlabParaConfig.txt"));*/

	b_tempFlag_paracfg = false;
	isAutoClickStartWorkButton = false;
	m_dlgParaConfig.ShowWindow(true);
}

//void CFormDlg1::DeleteFiles(LPCTSTR LRFileName)
//{
//	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
//	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
//	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
//	//wcscpy(gszSettingPath , szModulePath);
//	wcscat(szModulePath , LRFileName);
//
//	DeleteFile(szModulePath);
//}




//雷达工作线程
UINT CFormDlg1::RadarWorkThread(LPVOID lpParam)
{
	return ((CFormDlg1*)lpParam)->RadarWorkProcess();
}


//没用到——雷达工作任务
UINT CFormDlg1::RadarWorkProcess()
{
	g_bIsRadarWork = true;
	//收集界面参数，下发至DSP，

	byte frameHead[8] = {0};
	byte *p = frameHead;
	
	while(g_bIsRadarWork)
	{
		int nRet = g_tcpClient.Recv(p, 8);  //先接收8个字节，前四个字节是包头；后四个字节是包长
		if (nRet == 8)
		{
			UINT *pHead32 = (UINT *)p;
			if (*pHead32 == 0xaaaaaaaa/*具体帧头信息*/)     //检测包头
			{
				UINT len = *((UINT *)(p+4));                //获取包长
				len -= 4;                                   //计算数据信息长度
				byte *pBuffer = new byte [len];             //开辟接收数据缓冲区
				nRet = g_tcpClient.Recv(pBuffer, len);
				//对接收的数据进行分析
				if (nRet == len)
				{
					DataProcessing(pBuffer, len);           //数据处理
				}
			}
		}
	}

	return 0;
}


//没用到—— 一维距离像和系统状态信息处理函数
void CFormDlg1::DataProcessing(byte *p, int len)
{
	UINT nDataType = *((UINT *)p);  //提取信息反馈指令码
	switch (nDataType)
	{
	case 0x01://具体对应的指令码

		break;
	case 0x02:

		break;
	case 0x03://一维距离像和系统工作状态

		break;
	default:
		ASSERT(false);
	}
}


//没用到——  刷新雷达显控界面
afx_msg LRESULT CFormDlg1::OnUpdateformdlg1Ui(WPARAM wParam, LPARAM lParam)
{
	byte *p = (byte *)wParam;
	UINT nLen = *((UINT *)lParam);
	//UINT nHrrpCnt = (nLen - (3*4)) / 4;			//一维像点数

	//UINT nAerAngel = *((UINT *)(p + 8));        //天线角度
	//UINT nRFTemperature = *((UINT *)(p + 12));  //射频温度
	//UINT nSATASaveSpeed = *((UINT *)(p + 16));  //SATA存储速度
	//UINT nSATAVolum = *((UINT *)(p + 20));      //SATA存储容量

	//CString strAntennaAziAngle;
	//CString strRFTemperature;
	//CString strSATASaveSpeed;
	//CString strSATAVolum;
	//
	//strAntennaAziAngle.Format(_T("%.2d"), nAerAngel);
	//m_AntennaAziAngle.SetText(strAntennaAziAngle);
	//strRFTemperature.Format(_T("%.2d"), nRFTemperature);
	//m_RFTemperature.SetText(strAntennaAziAngle);
	//strSATASaveSpeed.Format(_T("%.2d"), nSATASaveSpeed);
	//m_SATASaveSpeed.SetText(strSATASaveSpeed);
	//strSATAVolum.Format(_T("%.2d"), nSATAVolum);
	//m_SATAVolum.SetText(strSATAVolum);

	//下面将添加一维像的送显
	UINT *p32 = NULL;
	p32 = (UINT *)(p + 8);
	UINT nChannelCnt = *p32;			//一维像路数

	UINT nEachChannelCnt = (nLen - 4 * 8) / (nChannelCnt * 8);		//每路一维像原始数据点数

	p32 = (UINT *)(p + 28);
	UINT nIFFTCnt = *p32;				//每路需要做傅里叶逆变换的点数

	float *pHrrpSrc = NULL;
	pHrrpSrc = (float *)(p + 32);					//指向一维像原始数据头

	
	if (nChannelCnt == 4)				//需要计算4路
	{
		float *p = new float[nChannelCnt * nIFFTCnt * 2];
		memset(p, 0, nChannelCnt * nIFFTCnt * 2);
		for (int i=0; i<nChannelCnt; i++)
		{
			memcpy((p + i*nIFFTCnt), (pHrrpSrc + i*nEachChannelCnt*8), nEachChannelCnt*8);
		}
		float *q = new float[/*nChannelCnt **/ nIFFTCnt * 2];
		float *w = new float[/*nChannelCnt **/ nIFFTCnt * 2];
		tw_gen(w, nIFFTCnt);
		for (int i=0; i<nChannelCnt; i++)
		{
			DSPF_sp_ifftSPxSP_cn(nIFFTCnt, (p + i*nIFFTCnt), w, q, NULL, 0, 0, nIFFTCnt);
			//Draw(q, /*nChannelCnt **/ nIFFTCnt * 2 * 4, nChannelCnt);		//送显
		}
		//DSPF_sp_ifftSPxSP_cn(nIFFTCnt, p, w, q, NULL, 0, 0, 0);		//傅里叶逆变换
		//Draw(q, /*nChannelCnt **/ nIFFTCnt * 2 * 4, nChannelCnt);		//送显
		delete []p;
		delete []w;
	}
	else if (nChannelCnt == 2)			//需要计算2路
	{
		float *p = new float[nChannelCnt * nIFFTCnt * 2];
		memset(p, 0, nChannelCnt * nIFFTCnt * 2);
		for (int i=0; i<nChannelCnt; i++)
		{
			memcpy((p + i*nIFFTCnt), (pHrrpSrc + i*nEachChannelCnt*8), nEachChannelCnt*8);
		}
	}

	return 0;
}


//void CFormDlg1::Draw(float *p, UINT nLen, UINT nSeriesCnt, CSeries series)
//{
//	//double *pData = (double*)p;
//
//	//获取曲线的数量
//	long SeriesCount = m_chart1.get_SeriesCount();
//
//	//断言曲线数量为4
//	ASSERT(SeriesCount == 4);
//
//	//获取曲线
//	//CSeries m_Series[4];
//	//m_Series[0] = (m_chart1.Series(0));
//	//m_Series[1] = (m_chart1.Series(1));
//	//m_Series[2] = (m_chart1.Series(2));
//	//m_Series[3] = (m_chart1.Series(3));
//	//CSeries m_Series0 = m_chart1.Series(0);
//	//CSeries m_Series1 = m_chart1.Series(1);
//	//CSeries m_Series2 = m_chart1.Series(2);
//	//CSeries m_Series3 = m_chart1.Series(3);
//
//	//清空曲线点
//	//m_Series[0].Clear();
//	//m_Series[1].Clear();
//	//m_Series[2].Clear();
//	//m_Series[3].Clear();
//
//	//m_Series0.Clear();
//	//m_Series1.Clear();
//	//m_Series2.Clear();
//	//m_Series3.Clear();
//
//	//定义X轴和Y轴数据变量
//	COleSafeArray XValues, YValues;
//
//	//定义数据长度
//	//UINT N = nLen / 8;
//	UINT N = g_nDrawNodes;
//
//
//	DWORD rgElements[] = {N};
//
//	//申请数据内存空间
//	XValues.Create(VT_R8, 1, rgElements);
//	YValues.Create(VT_R8, 1, rgElements);
//
//	//赋值
//	static int tt = 0;
//	if (nSeriesCnt == 4)
//	{
//		for (long j=0; j<N; j++)
//		{
//			double x = (double)j;
//			float real = p[j * 2];
//			float image = p[j * 2 + 1];
//			double z = powf(real, 2.0) + powf(image, 2.0);
//			z = sqrt(z);
//			//long double zlog = 10 * log((long double)z);
//			//double z = real;
//			XValues.PutElement(&j, &x);
//			YValues.PutElement(&j, &z);
//			//series.AddXY(x, z);
//		}
//		if (N == 16384)
//		{
//			tt++;
//		}
//		CString str;
//		str.Format(_T("%d\r\n"), tt);
//		TRACE(str);
//		//绘制曲线
//		series.AddArray(N, YValues, XValues);
//		
//	}
//	else if (nSeriesCnt == 2)
//	{
//
//	}
//	int dd = 0;
//	//绘制曲线
//	//m_Series0.AddArray(N, YValues, XValues);
//	//////////////////////////////////////////////////////
//	//申请数据内存空间
//	//XValues.Create(VT_R8, 1, rgElements);
//	//YValues.Create(VT_R8, 1, rgElements);
//
//	////赋值
//	//for (long j=0; j<N; j++)
//	//{
//	//	double x = (double)j;
//	//	//double y = pData[j];
//	//	float y = p[j * 2];
//	//	XValues.PutElement(&j, &x);
//	//	YValues.PutElement(&j, &y);
//	//}
//
//	////绘制曲线
//	//m_Series0.AddArray(N, YValues, XValues);
//
//
//	//for (int i=0; i<nSeriesCnt; i++)
//	//{
//	//	//申请数据内存空间
//	//	XValues.Create(VT_R8, 1, rgElements);
//	//	YValues.Create(VT_R8, 1, rgElements);
//
//	//	//赋值
//	//	for (long j=0; j<N; j++)
//	//	{
//	//		double x = (double)j;
//	//		//double y = pData[j];
//	//		float y = p[j * 2 + i *(nLen / 4)];
//	//		XValues.PutElement(&j, &x);
//	//		YValues.PutElement(&j, &y);
//	//	}
//
//	//	//绘制曲线
//	//	m_Series[i].AddArray(N, YValues, XValues); 
//	//}
//
//
//	//释放内存
//	//delete[] p;
//}


//抓屏
void CFormDlg1::OnBnClickedButton6()
{
	m_formDlg3.IFFT_tchart2();		//调用formdlg3的抓屏功能
	//IFFT_tchart2();

}


//该定时器用于刷新界面显示信息
void CFormDlg1::OnTimer(UINT_PTR nIDEvent)
{
	//m_criticalsection.Lock();

	IFFT_tchart1();


	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CFormDlg1::OnUser222(WPARAM wParam, LPARAM lParam)
{
	float *p = (float*)wParam;

	CString str;

	//天线指向方位角
	float fAntennaAziAngle = *(p + 3);
	if (fAntennaAziAngle < -180.0 || fAntennaAziAngle > 180.0)
	{
		return 0;
	}
	str.Format(_T("%.2f"), fAntennaAziAngle);
	g_fAntennaAziAngle = fAntennaAziAngle;
	m_AntennaAziAngle.SetText(str);

	//天线指向俯仰角
	float fAntennaEleAngle = *(p + 4);
	str.Format(_T("%.2f"), fAntennaEleAngle);
	m_AntennaEleAngle.SetText( str);
	g_fAntennaEleAngle = fAntennaEleAngle;

	//射频模块温度
	float fRFTemperature = *(p + 5);
	str.Format(_T("%.2f"), fRFTemperature);
	m_RFTemperature.SetText(str);

	//SATA存储速度
	float fSATASaveSpeed = *(p + 6);
	str.Format(_T("%.2f"), fSATASaveSpeed);
	m_SATASaveSpeed.SetText(str);


	//SATA存储容量
	if (b_flag2 == true)
	{
		double *q = (double*)wParam;
		q += 4;
		double ulSATAVolum = *q;
		double uSATAVolum = ulSATAVolum /1024/1024/1024 ;
		str.Format(_T("%d"), uSATAVolum);
		m_SATAVolum.SetText(str);
	}

	

	return 0;
}


void CFormDlg1::IFFT_tchart1()
{
	memcpy(pHrrpBuf, pTemp, HRRPBUFFERSIZE);

	//m_criticalsection.Unlock();

	UINT *p32 = NULL;
	p32 = (UINT *)pHrrpBuf;
	UINT nDataType = *p32;			//解析数据头

	if (nDataType == 0x7c7c7c7c)
	{

		PostMessage(WM_USER+222, (WPARAM)pHrrpBuf, HRRPBUFFERSIZE);
		//::PostMessage(theApp.m_pMainDlg->m_formDlg2.m_hWnd, WM_USER+444, (WPARAM)pHrrpBuf, HRRPBUFFERSIZE);

		p32 = (UINT *)(pHrrpBuf + 4);
		UINT nTotalBytesLen = *p32;									//除去帧头和长度信息的数据总长度

		p32 = (UINT *)(pHrrpBuf + 8);
		UINT nChannelCnt = *p32;									//一维像路数

		//UINT nTotalHrrpBytesLen = nTotalBytesLen - 24;				//N路一维像原始数据所占的字节数

		p32 = (UINT *)(pHrrpBuf + 40/*28*/);
		UINT nEachChannelNodes = *p32 ;								//每路原始一维像有效点数

		UINT nEachChannelBytes = nEachChannelNodes * 8 ;			//每路一维像原始数据所占的字节数

		p32 = (UINT *)(pHrrpBuf + 44/*32*/);
		UINT nEachChannelIFFTNodes = *p32;							//每路需要扩展后的点数

		UINT nEachChannelIFFTBytes = nEachChannelIFFTNodes * 8;		//每路扩展后的字节数


		byte *pHrrpSrc = NULL;
		pHrrpSrc = pHrrpBuf + 48 + 128/*36*/;									//指向一维像原始数据头
		double *pdlHrrpSrc = NULL;
		pdlHrrpSrc = (double *)pHrrpSrc;

		//同时模式
		if (waveMode == 0)
		{
			for (int i=0; i<4; i++)
			{
				byte *p1 = new byte[nEachChannelIFFTBytes];		//用于存放前四路数据拆分后的缓存
				byte *p2 = new byte[nEachChannelIFFTBytes];		//用于存放后四路数据拆分后的缓存

				memset(p1, 0, nEachChannelIFFTBytes);
				memcpy((p1 + (nEachChannelIFFTBytes-nEachChannelBytes/2)), (pHrrpSrc + i*nEachChannelBytes), nEachChannelBytes/2);
				memcpy(p1, (pHrrpSrc + i*nEachChannelBytes + nEachChannelBytes/2), nEachChannelBytes/2);

				memset(p2, 0, nEachChannelIFFTBytes);
				memcpy((p2 + (nEachChannelIFFTBytes-nEachChannelBytes/2)), ((pHrrpSrc+nEachChannelBytes*4) + i*nEachChannelBytes), nEachChannelBytes/2);
				memcpy(p2, ((pHrrpSrc+nEachChannelBytes*4) + i*nEachChannelBytes + nEachChannelBytes/2), nEachChannelBytes/2);


				//做傅里叶逆变换
				byte *q1 = new byte[nEachChannelIFFTBytes];		//存放输出结果
				byte *q2 = new byte[nEachChannelIFFTBytes];		//存放输出结果
				byte *w1 = new byte[nEachChannelIFFTBytes];		//铰链因子
				byte *w2 = new byte[nEachChannelIFFTBytes];		//铰链因子
				memset(q1, 0, nEachChannelIFFTBytes);
				memset(q2, 0, nEachChannelIFFTBytes);
				memset(w1, 0, nEachChannelIFFTBytes);
				memset(w2, 0, nEachChannelIFFTBytes);

				int j = 0;
				for (int i=0; i<=31; i++)
				{
					if ((nEachChannelIFFTNodes & (1 << i)) == 0)
						j++;
					else
						break;
				}
				int rad = 0;
				if (j % 2 == 0)
					rad = 4;
				else
					rad = 2;
				tw_gen((float*)w1, nEachChannelIFFTNodes);					//计算铰链因子
				tw_gen((float*)w2, nEachChannelIFFTNodes);					//计算铰链因子
				DSPF_sp_ifftSPxSP_cn(nEachChannelIFFTNodes, (float*)p1, (float*)w1, (float*)q1, NULL, rad, 0, nEachChannelIFFTNodes);
				DSPF_sp_ifftSPxSP_cn(nEachChannelIFFTNodes, (float*)p2, (float*)w2, (float*)q2, NULL, rad, 0, nEachChannelIFFTNodes);

				if (codeMode == 2)		//双帧脉间四相编码
				{
					for (int k=0; k<nEachChannelIFFTNodes*2; k++)
					{
						//*((float *)q1 + k) += *((float*)q2 + k);	//前四路和后四路对应点相加
						float ftemp = *((float *)q1 + k) + *((float*)q2 + k);
						*((float *)q1 + k) = ftemp;
					}
				}
				else if (codeMode == 3)	//双帧脉间二相编码
				{
					if (i%2 == 0)
					{
						for (int k=0; k<nEachChannelIFFTNodes*2; k++)
						{
							*((float *)q1 + k) += *((float*)q2 + k);	//第一路和第三路对应相加
						}
					}
					else
					{
						for (int k=0; k<nEachChannelIFFTNodes*2; k++)
						{
							*((float *)q1 + k) -= *((float*)q2 + k);	//第一路和第三路对应相加
						}
					}
				}

				//送显
				//CSeries series[4];
				//series[i] = (m_chart1.Series(i));
				//series[i].Clear();
				//Draw((float*)q1, nEachChannelIFFTBytes, nChannelCnt, series[i]);			//送显画图

				delete []p1;
				delete []q1;
				delete []w1;
				delete []p2;
				delete []q2;
				delete []w2;
				p1 = NULL;
				q1 = NULL;
				w1 = NULL;
				p2 = NULL;
				q2 = NULL;
				w2 = NULL;
				//memset(pTemp, 0, HRRPBUFFERSIZE);
			}
		}

		//分时模式
		else if (waveMode == 1)
		{
			//存放拆分重拼接后的原始一维像数据
			byte *pHrrpTemp = new byte[nEachChannelBytes * nChannelCnt];
			double *pdlHrrptemp = NULL;
			pdlHrrptemp = (double *)pHrrpTemp;


			//存放经过翻转且补零后待做傅里叶逆变换的原始一维像数据
			HANDLE m_hFile;
			CString strFileName(_T("2.bin"));
			//m_hFile = CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			//拆分数据(我的天呀)
			UINT nEachPrtBytes = nEachChannelBytes / 40;			//每个PRT所占的字节数
			for (int i=0; i<20; i++)
			{
				memcpy((pHrrpTemp + i*nEachPrtBytes), (pHrrpSrc+(i*2*nEachPrtBytes)), nEachPrtBytes);
				memcpy(((pHrrpTemp + nEachChannelBytes/2) + i*nEachPrtBytes), ((pHrrpSrc+nEachChannelBytes*2)+i*2*nEachPrtBytes), nEachPrtBytes);

				memcpy(((pHrrpTemp+nEachChannelBytes) + i*nEachPrtBytes), (pHrrpSrc+((i*2+1)*nEachPrtBytes)), nEachPrtBytes);
				memcpy((((pHrrpTemp+nEachChannelBytes) + nEachChannelBytes/2) +  i*nEachPrtBytes), ((pHrrpSrc+nEachChannelBytes*2)+(i*2+1)*nEachPrtBytes), nEachPrtBytes);

				memcpy(((pHrrpTemp+nEachChannelBytes*2) + i*nEachPrtBytes), ((pHrrpSrc+nEachChannelBytes)+(i*2*nEachPrtBytes)), nEachPrtBytes);
				memcpy((((pHrrpTemp+nEachChannelBytes*2)+nEachChannelBytes/2) + i*nEachPrtBytes), ((pHrrpSrc+nEachChannelBytes*3)+(i*2*nEachPrtBytes)), nEachPrtBytes);

				memcpy(((pHrrpTemp+nEachChannelBytes*3) + i*nEachPrtBytes), ((pHrrpSrc+nEachChannelBytes)+((i*2+1)*nEachPrtBytes)), nEachPrtBytes);
				memcpy((((pHrrpTemp+nEachChannelBytes*3)+nEachChannelBytes/2) + i*nEachPrtBytes), ((pHrrpSrc+nEachChannelBytes*3)+(i*2+1)*nEachPrtBytes), nEachPrtBytes);
			}

// 			for (int i=0; i<nEachChannelNodes/2; i++)
// 			{
// 				*(pdlHrrptemp + i)  = *(pdlHrrpSrc + (i*2));
// 				*((pdlHrrptemp+nEachChannelNodes/2) +  i) = *((pdlHrrpSrc+nEachChannelNodes*2) + (i*2));
// 
// 				*((pdlHrrptemp+nEachChannelNodes) + i) = *(pdlHrrpSrc+ (i*2+1));
// 				*(((pdlHrrptemp+nEachChannelNodes) + nEachChannelNodes/2) +  i) = *((pdlHrrpSrc+nEachChannelNodes*2) + (i*2 +1));
// 
// 				*((pdlHrrptemp+nEachChannelNodes*2) + i) = *((pdlHrrpSrc+nEachChannelNodes) + (i*2));
// 				*(((pdlHrrptemp+nEachChannelNodes*2) + nEachChannelNodes/2) + i) = *((pdlHrrpSrc+nEachChannelNodes*3) + (i*2));
// 
// 				*((pdlHrrptemp+nEachChannelNodes*3) + i) = *((pdlHrrpSrc+nEachChannelNodes) + (i*2+1));
// 				*(((pdlHrrptemp+nEachChannelNodes*3) + nEachChannelNodes/2) + i) = *((pdlHrrpSrc+nEachChannelNodes*3) + (i*2+1));
// 			}

			for (int i=0; i<4; i++)
			{
				byte *p = NULL;
				while((p = new byte[nEachChannelIFFTBytes])==NULL);
				memset(p, 0, nEachChannelIFFTBytes);

				memcpy((p + (nEachChannelIFFTBytes-nEachChannelBytes/2)), (pHrrpTemp + i*nEachChannelBytes), nEachChannelBytes/2);
				memcpy(p, (pHrrpTemp + i*nEachChannelBytes + nEachChannelBytes/2), nEachChannelBytes/2);
				//做傅里叶变换后送显
				byte *q = new byte[nEachChannelIFFTBytes];		//存放输出结果
				byte *w = new byte[nEachChannelIFFTBytes];		//铰链因子
				memset(q, 0, nEachChannelIFFTBytes);
				memset(w, 0, nEachChannelIFFTBytes);

				int j = 0;
				for (int i=0; i<=31; i++)
				{
					if ((nEachChannelIFFTNodes & (1 << i)) == 0)
						j++;
					else
						break;
				}
				int rad = 0;
				if (j % 2 == 0)
					rad = 4;
				else
					rad = 2;
				tw_gen((float*)w, nEachChannelIFFTNodes);					//计算铰链因子
				DSPF_sp_ifftSPxSP_cn(nEachChannelIFFTNodes, (float*)p, (float*)w, (float*)q, NULL, rad, 0, nEachChannelIFFTNodes);
				
				DWORD dwWrites;
				//WriteFile(m_hFile, q, nEachChannelIFFTBytes, &dwWrites, NULL);
				
				
				//CSeries series[4];
				//series[i] = (m_chart1.Series(i));
				//series[i].Clear();
				//Draw((float*)q, nEachChannelIFFTBytes, nChannelCnt, series[i]);			//送显画图

				delete []p;
				delete []q;
				delete []w;
				p = NULL;
				q = NULL;
				w = NULL;
				m_criticalsection.Lock();

				//memset(pTemp, 0, HRRPBUFFERSIZE);
				m_criticalsection.Unlock();
			}
			//CloseHandle(m_hFile);
			delete []pHrrpTemp;
			pHrrpTemp = NULL;
			pdlHrrptemp = NULL;
		}
	}
}


void CFormDlg1::IFFT_tchart2()
{
	memcpy(pHrrpBuf, pTemp, HRRPBUFFERSIZE);

	//m_criticalsection.Unlock();

	UINT *p32 = NULL;
	p32 = (UINT *)pHrrpBuf;
	UINT nDataType = *p32;			//解析数据头

	if (nDataType == 0x7c7c7c7c)
	{

		PostMessage(WM_USER+222, (WPARAM)pHrrpBuf, HRRPBUFFERSIZE);
		//::PostMessage(theApp.m_pMainDlg->m_formDlg2.m_hWnd, WM_USER+444, (WPARAM)pHrrpBuf, HRRPBUFFERSIZE);

		p32 = (UINT *)(pHrrpBuf + 4);
		UINT nTotalBytesLen = *p32;									//除去帧头和长度信息的数据总长度

		p32 = (UINT *)(pHrrpBuf + 8);
		UINT nChannelCnt = *p32;									//一维像路数

		//UINT nTotalHrrpBytesLen = nTotalBytesLen - 24;				//N路一维像原始数据所占的字节数

		p32 = (UINT *)(pHrrpBuf + 40/*28*/);
		UINT nEachChannelNodes = *p32 ;								//每路原始一维像有效点数

		UINT nEachChannelBytes = nEachChannelNodes * 8 ;			//每路一维像原始数据所占的字节数

		p32 = (UINT *)(pHrrpBuf + 44/*32*/);
		UINT nEachChannelIFFTNodes = *p32;							//每路需要扩展后的点数

		UINT nEachChannelIFFTBytes = nEachChannelIFFTNodes * 8;		//每路扩展后的字节数


		byte *pHrrpSrc = NULL;
		pHrrpSrc = pHrrpBuf + 48 + 128/*36*/;									//指向一维像原始数据头
		double *pdlHrrpSrc = NULL;
		pdlHrrpSrc = (double *)pHrrpSrc;

		//同时模式
		if (waveMode == 0)
		{
			for (int i=0; i<4; i++)
			{
				byte *p1 = new byte[nEachChannelIFFTBytes];		//用于存放前四路数据拆分后的缓存
				byte *p2 = new byte[nEachChannelIFFTBytes];		//用于存放后四路数据拆分后的缓存

				memset(p1, 0, nEachChannelIFFTBytes);
				memcpy((p1 + (nEachChannelIFFTBytes-nEachChannelBytes/2)), (pHrrpSrc + i*nEachChannelBytes), nEachChannelBytes/2);
				memcpy(p1, (pHrrpSrc + i*nEachChannelBytes + nEachChannelBytes/2), nEachChannelBytes/2);

				memset(p2, 0, nEachChannelIFFTBytes);
				memcpy((p2 + (nEachChannelIFFTBytes-nEachChannelBytes/2)), ((pHrrpSrc+nEachChannelBytes*4) + i*nEachChannelBytes), nEachChannelBytes/2);
				memcpy(p2, ((pHrrpSrc+nEachChannelBytes*4) + i*nEachChannelBytes + nEachChannelBytes/2), nEachChannelBytes/2);


				//做傅里叶逆变换
				byte *q1 = new byte[nEachChannelIFFTBytes];		//存放输出结果
				byte *q2 = new byte[nEachChannelIFFTBytes];		//存放输出结果
				byte *w1 = new byte[nEachChannelIFFTBytes];		//铰链因子
				byte *w2 = new byte[nEachChannelIFFTBytes];		//铰链因子
				memset(q1, 0, nEachChannelIFFTBytes);
				memset(q2, 0, nEachChannelIFFTBytes);
				memset(w1, 0, nEachChannelIFFTBytes);
				memset(w2, 0, nEachChannelIFFTBytes);

				int j = 0;
				for (int i=0; i<=31; i++)
				{
					if ((nEachChannelIFFTNodes & (1 << i)) == 0)
						j++;
					else
						break;
				}
				int rad = 0;
				if (j % 2 == 0)
					rad = 4;
				else
					rad = 2;
				tw_gen((float*)w1, nEachChannelIFFTNodes);					//计算铰链因子
				tw_gen((float*)w2, nEachChannelIFFTNodes);					//计算铰链因子
				DSPF_sp_ifftSPxSP_cn(nEachChannelIFFTNodes, (float*)p1, (float*)w1, (float*)q1, NULL, rad, 0, nEachChannelIFFTNodes);
				DSPF_sp_ifftSPxSP_cn(nEachChannelIFFTNodes, (float*)p2, (float*)w2, (float*)q2, NULL, rad, 0, nEachChannelIFFTNodes);

				if (codeMode == 2)		//双帧脉间四相编码
				{
					for (int k=0; k<nEachChannelIFFTNodes*2; k++)
					{
						//*((float *)q1 + k) += *((float*)q2 + k);	//前四路和后四路对应点相加
						float ftemp = *((float *)q1 + k) + *((float*)q2 + k);
						*((float *)q1 + k) = ftemp;
					}
				}
				else if (codeMode == 3)	//双帧脉间二相编码
				{
					if (i%2 == 0)
					{
						for (int k=0; k<nEachChannelIFFTNodes*2; k++)
						{
							*((float *)q1 + k) += *((float*)q2 + k);	//第一路和第三路对应相加
						}
					}
					else
					{
						for (int k=0; k<nEachChannelIFFTNodes*2; k++)
						{
							*((float *)q1 + k) -= *((float*)q2 + k);	//第一路和第三路对应相加
						}
					}
				}

				//送显
				//CSeries series[4];
				//series[i] = (m_chart2.Series(i));
				//series[i].Clear();
				//Draw((float*)q1, nEachChannelIFFTBytes, nChannelCnt, series[i]);			//送显画图

				delete []p1;
				delete []q1;
				delete []w1;
				delete []p2;
				delete []q2;
				delete []w2;
				p1 = NULL;
				q1 = NULL;
				w1 = NULL;
				p2 = NULL;
				q2 = NULL;
				w2 = NULL;
				//memset(pTemp, 0, HRRPBUFFERSIZE);
			}
		}

		//分时模式
		else if (waveMode == 1)
		{
			//存放拆分重拼接后的原始一维像数据
			byte *pHrrpTemp = new byte[nEachChannelBytes * nChannelCnt];
			double *pdlHrrptemp = NULL;
			pdlHrrptemp = (double *)pHrrpTemp;


			//存放经过翻转且补零后待做傅里叶逆变换的原始一维像数据
			HANDLE m_hFile;
			CString strFileName(_T("2.bin"));
			//m_hFile = CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			//拆分数据(我的天呀)
			UINT nEachPrtBytes = nEachChannelBytes / 40;			//每个PRT所占的字节数
			for (int i=0; i<20; i++)
			{
				memcpy((pHrrpTemp + i*nEachPrtBytes), (pHrrpSrc+(i*2*nEachPrtBytes)), nEachPrtBytes);
				memcpy(((pHrrpTemp + nEachChannelBytes/2) + i*nEachPrtBytes), ((pHrrpSrc+nEachChannelBytes*2)+i*2*nEachPrtBytes), nEachPrtBytes);

				memcpy(((pHrrpTemp+nEachChannelBytes) + i*nEachPrtBytes), (pHrrpSrc+((i*2+1)*nEachPrtBytes)), nEachPrtBytes);
				memcpy((((pHrrpTemp+nEachChannelBytes) + nEachChannelBytes/2) +  i*nEachPrtBytes), ((pHrrpSrc+nEachChannelBytes*2)+(i*2+1)*nEachPrtBytes), nEachPrtBytes);

				memcpy(((pHrrpTemp+nEachChannelBytes*2) + i*nEachPrtBytes), ((pHrrpSrc+nEachChannelBytes)+(i*2*nEachPrtBytes)), nEachPrtBytes);
				memcpy((((pHrrpTemp+nEachChannelBytes*2)+nEachChannelBytes/2) + i*nEachPrtBytes), ((pHrrpSrc+nEachChannelBytes*3)+(i*2*nEachPrtBytes)), nEachPrtBytes);

				memcpy(((pHrrpTemp+nEachChannelBytes*3) + i*nEachPrtBytes), ((pHrrpSrc+nEachChannelBytes)+((i*2+1)*nEachPrtBytes)), nEachPrtBytes);
				memcpy((((pHrrpTemp+nEachChannelBytes*3)+nEachChannelBytes/2) + i*nEachPrtBytes), ((pHrrpSrc+nEachChannelBytes*3)+(i*2+1)*nEachPrtBytes), nEachPrtBytes);
			}

// 			for (int i=0; i<nEachChannelNodes/2; i++)
// 			{
// 				*(pdlHrrptemp + i)  = *(pdlHrrpSrc + (i*2));
// 				*((pdlHrrptemp+nEachChannelNodes/2) +  i) = *((pdlHrrpSrc+nEachChannelNodes*2) + (i*2));
// 
// 				*((pdlHrrptemp+nEachChannelNodes) + i) = *(pdlHrrpSrc+ (i*2+1));
// 				*(((pdlHrrptemp+nEachChannelNodes) + nEachChannelNodes/2) +  i) = *((pdlHrrpSrc+nEachChannelNodes*2) + (i*2 +1));
// 
// 				*((pdlHrrptemp+nEachChannelNodes*2) + i) = *((pdlHrrpSrc+nEachChannelNodes) + (i*2));
// 				*(((pdlHrrptemp+nEachChannelNodes*2) + nEachChannelNodes/2) + i) = *((pdlHrrpSrc+nEachChannelNodes*3) + (i*2));
// 
// 				*((pdlHrrptemp+nEachChannelNodes*3) + i) = *((pdlHrrpSrc+nEachChannelNodes) + (i*2+1));
// 				*(((pdlHrrptemp+nEachChannelNodes*3) + nEachChannelNodes/2) + i) = *((pdlHrrpSrc+nEachChannelNodes*3) + (i*2+1));
// 			}

			for (int i=0; i<4; i++)
			{
				byte *p = NULL;
				while((p = new byte[nEachChannelIFFTBytes])==NULL);
				memset(p, 0, nEachChannelIFFTBytes);

				memcpy((p + (nEachChannelIFFTBytes-nEachChannelBytes/2)), (pHrrpTemp + i*nEachChannelBytes), nEachChannelBytes/2);
				memcpy(p, (pHrrpTemp + i*nEachChannelBytes + nEachChannelBytes/2), nEachChannelBytes/2);
				//做傅里叶变换后送显
				byte *q = new byte[nEachChannelIFFTBytes];		//存放输出结果
				byte *w = new byte[nEachChannelIFFTBytes];		//铰链因子
				memset(q, 0, nEachChannelIFFTBytes);
				memset(w, 0, nEachChannelIFFTBytes);

				int j = 0;
				for (int i=0; i<=31; i++)
				{
					if ((nEachChannelIFFTNodes & (1 << i)) == 0)
						j++;
					else
						break;
				}
				int rad = 0;
				if (j % 2 == 0)
					rad = 4;
				else
					rad = 2;
				tw_gen((float*)w, nEachChannelIFFTNodes);					//计算铰链因子
				DSPF_sp_ifftSPxSP_cn(nEachChannelIFFTNodes, (float*)p, (float*)w, (float*)q, NULL, rad, 0, nEachChannelIFFTNodes);
				
				DWORD dwWrites;
				//WriteFile(m_hFile, q, nEachChannelIFFTBytes, &dwWrites, NULL);
				
				
				//CSeries series[4];
				//series[i] = (m_chart2.Series(i));
				//series[i].Clear();
				//Draw((float*)q, nEachChannelIFFTBytes, nChannelCnt, series[i]);			//送显画图

				delete []p;
				delete []q;
				delete []w;
				p = NULL;
				q = NULL;
				w = NULL;
				//m_criticalsection.Lock();
				//memset(pTemp, 0, HRRPBUFFERSIZE);
				//m_criticalsection.Unlock();
			}
			//CloseHandle(m_hFile);
			delete []pHrrpTemp;
			pHrrpTemp = NULL;
			pdlHrrptemp = NULL;
		}
	}
}

afx_msg LRESULT CFormDlg1::OnMsgProtectUI(WPARAM wParam, LPARAM lParam)
{
	int b = *((int*)wParam);
	((CButton*)GetDlgItem(IDC_BUTTON3))->EnableWindow(b);
	//Sleep(1000);
	//if(g_stopWorkFlag == 1)
	//{
	//	//Sleep(10000);
	//	::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+889, NULL, NULL);
	//}
	return 0;
}


//计算SATA容量
double CFormDlg1::calculSATAVolum()
{
	//计算SATA容量
	double ulSATAVolum = 1908.0;
	double uLastFileSize = 0.0;

	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("FileListInfo.txt"));
	CString strModulePath;
	strModulePath = szModulePath;
	CFile file;
	if (file.Open(strModulePath, CFile::modeRead))
	{
		ULONGLONG uFileSize = file.GetLength();
		ULONGLONG uCount = uFileSize / sizeof(FILELISTINFO);	//获取上一次采集的文件个数
		for (int i=0; i<uCount; i++)
		{
			//读文件列表信息
			FILELISTINFO *pFileListInfo = new FILELISTINFO; 
			memset(pFileListInfo, 0, sizeof(FILELISTINFO));
			file.Read(pFileListInfo, sizeof(FILELISTINFO));

			 uLastFileSize = (double)(pFileListInfo->EndAddress) / (1024 * 1024 * 1024);
			//CString strLastFileSize;
			//strLastFileSize.Format(_T("%.2f"), (ulSATAVolum-uLastFileSize));
			//m_SATAVolum.SetText(strLastFileSize);
			//theApp.m_pMainDlg->m_filelist.SetItemText(i, 1, strLastFileSize);  //更新文件大小
			delete pFileListInfo;
			pFileListInfo = NULL;
		}
		file.Close();
	}

	return (ulSATAVolum - uLastFileSize);
}


void CFormDlg1::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	int cur = 0;
	cur = m_TabCtrl.GetCurSel();

	switch(cur)
	{
	case 0:
		m_TabCtrl.SetCurSel(0);
		m_formDlg3.ShowWindow(TRUE);
		m_formDlg4.ShowWindow(FALSE);
		m_formDlg5.ShowWindow(FALSE);
		break;
	case 1:
		m_TabCtrl.SetCurSel(1);
		m_formDlg3.ShowWindow(FALSE);
		m_formDlg4.ShowWindow(TRUE);
		m_formDlg5.ShowWindow(FALSE);
		break;
	case 2:
		m_TabCtrl.SetCurSel(2);
		m_formDlg3.ShowWindow(FALSE);
		m_formDlg4.ShowWindow(FALSE);
		m_formDlg5.ShowWindow(TRUE);
		break;
	default:
		break;
	}



	*pResult = 0;
}


void CFormDlg1::LoadMatlabPara()
{
	//RCS_ball
	float fRCS_ball = theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_RCS_ball;
	CString s;
	//起始采样距离
	int nlhs = theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_comboxSimpleRage.GetCurSel();
	int StartRan = nlhs * 15;
	theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_comboxSimpleRage.GetLBText(nlhs, s);
	//采样窗点数
	nlhs = theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_combox5.GetCurSel();
	theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_combox5.GetLBText(nlhs, s);
	int SampleNum = _ttoi(s);
	//PRT
	nlhs = theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_combox3.GetCurSel();
	theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_combox3.GetLBText(nlhs, s);
	int PRT = _ttoi(s);
	//波形编码
	int WaveForm;
	//脉间编码
	int CodeType;
}


afx_msg LRESULT CFormDlg1::OnUser223(WPARAM wParam, LPARAM lParam)
{
	((CButton*)GetDlgItem(IDC_BUTTON1))->EnableWindow(FALSE);

	return 0;
}


afx_msg LRESULT CFormDlg1::OnUser224(WPARAM wParam, LPARAM lParam)
{
	((CButton*)GetDlgItem(IDC_BUTTON1))->EnableWindow(TRUE);
	theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON8)->EnableWindow(TRUE);
	theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON9)->EnableWindow(TRUE);
	return 0;
}


afx_msg LRESULT CFormDlg1::OnUser888(WPARAM wParam, LPARAM lParam)
{
	PostMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON3, BN_CLICKED), NULL);		// 点击开始工作按钮
	OutputDebugString(_T("模拟点击开始工作按钮！\n"));
	PostMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON4, BN_CLICKED), NULL);		// 点击开始存储按钮
	OutputDebugString(_T("模拟点击开始存储按钮！\n"));


	// 创建计数线程
	if(g_workMode == 1)
	{
		b_isStoreFlag = true;
		m_pStroeThread = AfxBeginThread(threadStore, this);
	}
	return 0;
}
afx_msg LRESULT CFormDlg1::OnUser889(WPARAM wParam, LPARAM lParam)
{
	// 停止工作
	if(g_stopWorkFlag == 1)
	{
		SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON3, BN_CLICKED), NULL);		// 点击开始工作按钮
		g_stopWorkFlag = 0;
	}
	return 0;
}

afx_msg LRESULT CFormDlg1::OnUser890(WPARAM wParam, LPARAM lParam)
{
	// 停止存储
	PostMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON4, BN_CLICKED), NULL);	

	return 0;
}

afx_msg LRESULT CFormDlg1::OnUser891(WPARAM wParam, LPARAM lParam)
{
	// 停止工作
	SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON3, BN_CLICKED), NULL);	

	return 0;
}

bool b_isPlayBackFlag = false;
//CFormDlg1 m_formDlg1;
void CFormDlg1::OnBnClickedButtonPlayback()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!g_isSucessInitMatlabPlayBacklib)
	{
		MessageBox(L"请等待Matlab完成初始化！");
		return;
	}
	if(g_trackFilePath.IsEmpty())
	{
		MessageBox(L"路径为空，请选择Track文件有效路径！");
		return;
	}
	if(!b_isPlayBackFlag)
	{
		AfxBeginThread(PlayBackThread,this);
		theApp.m_pMainDlg->PrintMessage(L"开始回放！");
		
		m_btnPlayBack.SetWindowTextW(L"停止回放");
		b_isPlayBackFlag = true;
	}
	else
	{
		m_btnPlayBack.SetWindowTextW(L"开始回放");
		theApp.m_pMainDlg->PrintMessage(L"停止回放！");
		
		b_isPlayBackFlag = false;
	}
		
}
UINT CFormDlg1::PlayBackThread(LPVOID lpParam)
{
	return ((CFormDlg1*)lpParam)->PlayBackProcess();
}
UINT CFormDlg1::PlayBackProcess()
{
	playBackFileNames();
	return 0;
}


vector<CString> vctrFileToMatlab;
void CFormDlg1::playBackFileNames()
{
	vctrFileToMatlab.clear();
	CString strMatch = g_trackFilePath + ("\\*.*");
	CString strFullNamePath, strFullName;
	CFileFind finder;

	BOOL bWorking = finder.FindFile(strMatch);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if (finder.IsDots()) // 判断文件名是否为.或者..
			continue;

		if (finder.IsDirectory())
			playBackFileNames();
		else
		{		
			strFullName = finder.GetFileName();
			compareFileNameToTimePiker(strFullName);
		}
	}

	if(!vctrFileToMatlab.size())
	{
		MessageBox(L"无符合回放条件的文件，请重新选择！");
		m_btnPlayBack.SetWindowTextW(L"开始回放");
		theApp.m_pMainDlg->PrintMessage(L"停止回放！");

		b_isPlayBackFlag = false;
		return;
	}

	int iCountToMatlabFiles = 0;
	vector<CString>::iterator iter;
	for(iter = vctrFileToMatlab.begin(); iter != vctrFileToMatlab.end(); iter++)
	{
		// 传递文件名
		iCountToMatlabFiles++;
		trackPlayBack(*iter);
		if(!b_isPlayBackFlag)
		{
			break;
		}
		if(iCountToMatlabFiles == vctrFileToMatlab.size())
		{
			m_btnPlayBack.SetWindowTextW(L"开始回放");
			theApp.m_pMainDlg->PrintMessage(L"回放完成！");
			b_isPlayBackFlag = false;
		}
		Sleep(g_playBackTimeInterval);
	}
	finder.Close();
}


void CFormDlg1::compareFileNameToTimePiker(CString strFullName)
{

	CString tempStrMonth, strFileNamePath, strFullNameTemp;
	int iFileNameYear = 0;
	int iFileNameMonths = 0; 

	strFullNameTemp = strFullName;
	if(!strFullNameTemp)
	{
		MessageBox(L"文件错误！");
		return;
	}

	struct tm sFileNameDate ;

	// 获取年
	iFileNameYear = (int)_ttoi(strFullName.Mid(6, 4));
	sFileNameDate.tm_year = iFileNameYear;
	sFileNameDate.tm_year -= 1900;
	// 获取月份
	strFullName.Delete(0,11);
	int tempIndex = strFullName.Find(_T("_"));
	tempStrMonth = strFullName.Left(tempIndex);

	if(tempStrMonth == "January")
	{
		iFileNameMonths = 1;
	}
	else if(tempStrMonth == "February")
	{
		iFileNameMonths = 2;
	}
	else if(tempStrMonth == "March")
	{
		iFileNameMonths = 3;
	}
	else if(tempStrMonth == "April")
	{
		iFileNameMonths = 4;
	}
	else if(tempStrMonth == "May")
	{
		iFileNameMonths = 5;
	}
	else if(tempStrMonth == "June")
	{
		iFileNameMonths = 6;
	}
	else if(tempStrMonth == "July")
	{
		iFileNameMonths = 7;
	}
	else if(tempStrMonth == "August")
	{
		iFileNameMonths = 8;
	}
	else if(tempStrMonth == "September")
	{
		iFileNameMonths = 9;
	}
	else if(tempStrMonth == "October")
	{
		iFileNameMonths = 10;
	}
	else if(tempStrMonth == "November")
	{
		iFileNameMonths = 11;
	}
	else if(tempStrMonth == "December")
	{
		iFileNameMonths = 12;
	}

	sFileNameDate.tm_mday = _ttoi(strFullName.Mid(tempIndex+1,2));
	sFileNameDate.tm_hour = _ttoi(strFullName.Mid(tempIndex+4, 2));
	sFileNameDate.tm_min = _ttoi(strFullName.Mid(tempIndex+6, 2));
	sFileNameDate.tm_sec = _ttoi(strFullName.Mid(tempIndex+8, 2));
	sFileNameDate.tm_mon = iFileNameMonths;
	sFileNameDate.tm_mon -= 1;

	// 转化成时间戳
	time_t tStartPlayBack, tStopPlayBack, tFileNameDate;
	

	tStartPlayBack = mktime(&sStrartPlayBack);
	tStopPlayBack = mktime(&sStopPlayBack);
	tFileNameDate = mktime(&sFileNameDate);

	strFileNamePath = g_trackFilePath + ("\\") + strFullNameTemp;
	if((tFileNameDate > tStartPlayBack || tFileNameDate == tStartPlayBack) && (tFileNameDate < tStopPlayBack || tFileNameDate == tStopPlayBack))
	{
		vctrFileToMatlab.push_back(strFileNamePath);
	}
}

void CFormDlg1::trackPlayBack(CString str)
{
	CString strTrackFileName = str;

	mxDouble mx_MinLength_ParaEst = toMatlabPara.dlMinLength_ParaEst; 
	mxDouble mx_MinLength_Den = toMatlabPara.dlMinLength_Den;
	mwArray mw_MinLength_ParaEst(1,1,mxDOUBLE_CLASS);
	mwArray mw_MinLength_Den(1,1,mxDOUBLE_CLASS);

	mw_MinLength_ParaEst.SetData(&mx_MinLength_ParaEst,1);
	mw_MinLength_Den.SetData(&mx_MinLength_Den,1);

	CString strTemp;
	strTemp = strTrackFileName;

	char TrackFile_name[1024] = {"1.mat"};
	WideCharToMultiByte(strTemp, TrackFile_name, 1024);
	mwArray mw_TrackFile_name(TrackFile_name);

	// 密度廓线
	mwArray mw_DenProf_X(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_DenProf_X_N(1, 1, mxINT32_CLASS);
	mwArray mw_DenProf_Y(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_DenProf_Y_N(1, 1, mxINT32_CLASS);

	// 朝向分布
	mwArray mw_Orien_X(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_Orien_X_N(1, 1, mxINT32_CLASS);
	mwArray mw_Orien_Y(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_Orien_Y_N(1, 1, mxINT32_CLASS);

	// 极化方向图
	mwArray mw_PP_X(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_PP_X_N(1, 1, mxINT32_CLASS);
	mwArray mw_PP_Y(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_PP_Y_N(1, 1, mxINT32_CLASS);

	// 振翅频率==个体频率分布
	mwArray mw_WBF_Ind_X(500000, 1, mxDOUBLE_CLASS);
	mwArray mw_WBF_Ind_X_N(1, 1, mxINT32_CLASS);
	mwArray mw_WBF_Ind_Y(500000, 1, mxDOUBLE_CLASS);
	mwArray mw_WBF_Ind_Y_N(1, 1, mxINT32_CLASS);

	// 振翅频率分布
	mwArray mw_WingBeatFre_X(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_WingBeatFre_X_N(1, 1, mxINT32_CLASS);
	mwArray mw_WingBeatFre_Y(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_WingBeatFre_Y_N(1, 1, mxINT32_CLASS);

	// 体长分布
	mwArray mw_BodyLen_X(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_BodyLen_X_N(1, 1, mxINT32_CLASS);
	mwArray mw_BodyLen_Y(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_BodyLen_Y_N(1, 1, mxINT32_CLASS);

	// 体重分布
	mwArray mw_BodyMass_X(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_BodyMass_X_N(1, 1, mxINT32_CLASS);
	mwArray mw_BodyMass_Y(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_BodyMass_Y_N(1, 1, mxINT32_CLASS);


	// 高度-时间分布
	mwArray mw_HTDiv_X(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_HTDiv_T_N(1, 1, mxINT32_CLASS);
	mwArray mw_HTDiv_Y(5000, 1, mxDOUBLE_CLASS);
	mwArray mw_HTDiv_H_N(1, 1, mxINT32_CLASS);

	// 密度廓线
	mxDouble mx_DenProf_X[5000];
	mxInt32 mx_DenProf_X_N;
	mxDouble mx_DenProf_Y[5000];
	mxInt32 mx_DenProf_Y_N;

	// 朝向分布
	mxDouble mx_Orien_X[5000];
	mxInt32 mx_Orien_X_N;
	mxDouble mx_Orien_Y[5000];
	mxInt32 mx_Orien_Y_N;

	// 极化方向图
	mxDouble mx_PP_X[5000];
	mxInt32 mx_PP_X_N;
	mxDouble mx_PP_Y[5000];
	mxInt32 mx_PP_Y_N;

	// 振翅频率==个体频率分布
	mxDouble *pmx_WBF_Ind_X = new mxDouble[500000];
	mxInt32 mx_WBF_Ind_X_N;
	mxDouble *pmx_WBF_Ind_Y = new mxDouble[500000];
	mxInt32 mx_WBF_Ind_Y_N;

	// 振翅频率分布
	mxDouble mx_WingBeatFre_X[5000];
	mxInt32 mx_WingBeatFre_X_N;
	mxDouble mx_WingBeatFre_Y[5000];
	mxInt32 mx_WingBeatFre_Y_N;

	mxDouble *pmx_BodyLen_X = new mxDouble[5000];
	mxInt32 mx_BodyLen_X_N;
	mxDouble *pmx_BodyLen_Y = new mxDouble[5000];
	mxInt32 mx_BodyLen_Y_N;

	mxDouble *pmx_BodyMass_X = new mxDouble[5000];
	mxInt32 mx_BodyMass_X_N;
	mxDouble *pmx_BodyMass_Y = new mxDouble[5000];
	mxInt32 mx_BodyMass_Y_N;

	// 高度-时间分布
	mxDouble *pmx_HTDiv_X = new mxDouble[5000];
	mxInt32 mx_HTDiv_T_N;
	mxDouble *pmx_HTDiv_Y = new mxDouble[5000];
	mxInt32 mx_HTDiv_H_N;


	// 回放matlab函数
	func_Playback_VerticalLookingMode(32, mw_DenProf_X,mw_DenProf_X_N, mw_DenProf_Y, mw_DenProf_Y_N, 
		mw_Orien_X,mw_Orien_X_N,mw_Orien_Y,mw_Orien_Y_N,						
		mw_WingBeatFre_X, mw_WingBeatFre_X_N, mw_WingBeatFre_Y, mw_WingBeatFre_Y_N,
		mw_BodyLen_X,mw_BodyLen_X_N,mw_BodyLen_Y,mw_BodyLen_Y_N,				
		mw_BodyMass_X,mw_BodyMass_X_N,mw_BodyMass_Y,mw_BodyMass_Y_N,			
		mw_WBF_Ind_X, mw_WBF_Ind_X_N, mw_WBF_Ind_Y, mw_WBF_Ind_Y_N,				
		mw_HTDiv_X, mw_HTDiv_T_N, mw_HTDiv_Y, mw_HTDiv_H_N,						
		mw_PP_X,mw_PP_X_N,mw_PP_Y,mw_PP_Y_N	,							

		mw_TrackFile_name, mw_MinLength_Den, mw_MinLength_ParaEst);

	// 密度廓线*
	mw_DenProf_X_N.GetData(&mx_DenProf_X_N,1);
	mw_DenProf_X.GetData(mx_DenProf_X,mx_DenProf_X_N);
	mw_DenProf_Y_N.GetData(&mx_DenProf_Y_N,1);
	mw_DenProf_Y.GetData(mx_DenProf_Y,mx_DenProf_Y_N);
	memcpy((mx_DenProf_X + mx_DenProf_X_N), mx_DenProf_Y, mx_DenProf_X_N*8);
	::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg4.m_hWnd, WM_USER+121, (WPARAM)mx_DenProf_X, (LPARAM)&mx_DenProf_X_N);

	// 1朝向分布*
	mw_Orien_X_N.GetData(&mx_Orien_X_N,1);
	mw_Orien_X.GetData(mx_Orien_X, mx_Orien_X_N);
	mw_Orien_Y_N.GetData(&mx_Orien_Y_N,1);
	mw_Orien_Y.GetData(mx_Orien_Y, mx_Orien_Y_N);
	memcpy((mx_Orien_X + mx_Orien_X_N), mx_Orien_Y, mx_Orien_X_N*8);
	::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg4.m_hWnd, WM_USER+122, (WPARAM)mx_Orien_X, (LPARAM)&mx_Orien_X_N);

	// 2振翅频率分布*
	mw_WingBeatFre_X_N.GetData(&mx_WingBeatFre_X_N,1);
	mw_WingBeatFre_X.GetData(mx_WingBeatFre_X, mx_WingBeatFre_X_N);
	mw_WingBeatFre_Y_N.GetData(&mx_WingBeatFre_Y_N,1);
	mw_WingBeatFre_Y.GetData(mx_WingBeatFre_Y, mx_WingBeatFre_Y_N);
	memcpy((mx_WingBeatFre_X + mx_WingBeatFre_X_N), mx_WingBeatFre_Y, mx_WingBeatFre_X_N*8);
	::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg4.m_hWnd, WM_USER+124, (WPARAM)mx_WingBeatFre_X, (LPARAM)&mx_WingBeatFre_X_N);

	// 体长分布*
	mw_BodyLen_X_N.GetData(&mx_BodyLen_X_N,1);
	mw_BodyLen_X.GetData(pmx_BodyLen_X, mx_BodyLen_X_N);
	mw_BodyLen_Y_N.GetData(&mx_BodyLen_Y_N,1);
	mw_BodyLen_Y.GetData(pmx_BodyLen_Y, mx_BodyLen_Y_N);
	memcpy((pmx_BodyLen_X + mx_BodyLen_X_N), pmx_BodyLen_Y, mx_BodyLen_X_N*8);
	::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg4.m_hWnd, WM_USER+123, (WPARAM)pmx_BodyLen_X, (LPARAM)&mx_BodyLen_X_N);
	if (pmx_BodyLen_Y)
	{
		delete []pmx_BodyLen_Y;
		pmx_BodyLen_Y = NULL;
	}

	// 体重分布*
	mw_BodyMass_X_N.GetData(&mx_BodyMass_X_N,1);
	mw_BodyMass_X.GetData(pmx_BodyMass_X, mx_BodyMass_X_N);
	mw_BodyMass_Y_N.GetData(&mx_BodyMass_Y_N,1);
	mw_BodyMass_Y.GetData(pmx_BodyMass_Y, mx_BodyMass_Y_N);
	memcpy((pmx_BodyMass_X + mx_BodyMass_X_N), pmx_BodyMass_Y, mx_BodyMass_X_N*8);
	::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg4.m_hWnd, WM_USER+125, (WPARAM)pmx_BodyMass_X, (LPARAM)&mx_BodyMass_X_N);
	if (pmx_BodyMass_Y)
	{
		delete []pmx_BodyMass_Y;
		pmx_BodyMass_Y = NULL;
	}

	// 极化方向图
	mw_PP_X_N.GetData(&mx_PP_X_N, 1);
	mw_PP_X.GetData(mx_PP_X, mx_PP_X_N);
	mw_PP_Y_N.GetData(&mx_PP_Y_N, 1);
	mw_PP_Y.GetData(mx_PP_Y, mx_PP_Y_N);
	memcpy((mx_PP_X + mx_PP_X_N), mx_PP_Y, mx_PP_X_N*8);
	::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg5.m_hWnd, WM_USER+128, (WPARAM)mx_PP_X, (LPARAM)&mx_PP_X_N);

	// 高度-时间分布
	mw_HTDiv_T_N.GetData(&mx_HTDiv_T_N,1);
	mw_HTDiv_X.GetData(pmx_HTDiv_X, mx_HTDiv_T_N);
	mw_HTDiv_H_N.GetData(&mx_HTDiv_H_N,1);
	mw_HTDiv_Y.GetData(pmx_HTDiv_Y, mx_HTDiv_H_N);
	memcpy((pmx_HTDiv_X + mx_HTDiv_T_N), pmx_HTDiv_Y, mx_HTDiv_T_N*8);
	::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg5.m_hWnd, WM_USER+126, (WPARAM)pmx_HTDiv_X, (LPARAM)&mx_HTDiv_T_N);
	if (pmx_HTDiv_Y)
	{
		delete []pmx_HTDiv_Y;
		pmx_HTDiv_Y = NULL;
	}

	// 振翅频率==个体振翅频率分布
	mw_WBF_Ind_X_N.GetData(&mx_WBF_Ind_X_N, 1);
	mw_WBF_Ind_X.GetData(pmx_WBF_Ind_X, mx_WBF_Ind_X_N);
	mw_WBF_Ind_Y_N.GetData(&mx_WingBeatFre_Y_N, 1);
	mw_WBF_Ind_Y.GetData(pmx_WBF_Ind_Y, mx_WingBeatFre_Y_N);
	memcpy((pmx_WBF_Ind_X + mx_WBF_Ind_X_N), pmx_WBF_Ind_Y, mx_WBF_Ind_X_N*8);
	if (pmx_WBF_Ind_Y)
	{
		delete []pmx_WBF_Ind_Y;
		pmx_WBF_Ind_Y = NULL;
	}
	::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg5.m_hWnd, WM_USER+127, (WPARAM)pmx_WBF_Ind_X, (LPARAM)&mx_WBF_Ind_X_N);
}
