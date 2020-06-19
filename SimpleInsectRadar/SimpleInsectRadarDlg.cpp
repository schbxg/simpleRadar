
// SimpleInsectRadarDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SimpleInsectRadar.h"
#include "SimpleInsectRadarDlg.h"
#include "afxdialogex.h"
//#include <Windows.h>
//#include "DBWindow.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <winbase.h>

#define DFLAG 0


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
	
END_MESSAGE_MAP()


// CSimpleInsectRadarDlg 对话框




CSimpleInsectRadarDlg::CSimpleInsectRadarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSimpleInsectRadarDlg::IDD, pParent) 
	//,m_tcpTest(8000, "127.0.0.1")
{
	m_bIsFileExist = false;
	m_strFileName = _T("");
	m_hFile = NULL;
	m_nItem = 0;
	//ulCount = 0;
	m_dFileTransRate = 0.0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(pHrrpBuf, 0, HRRPBUFFERSIZE);			//初始化全局一维像数据缓存
	memset(pTemp, 0, HRRPBUFFERSIZE);
	m_pWriteFileThread = NULL;


}

CSimpleInsectRadarDlg::~CSimpleInsectRadarDlg()
{
	
};

void CSimpleInsectRadarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_TabCtrlMain);
	DDX_Control(pDX, IDC_LIST_PRINT, m_listPrint);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEditCtrl);
	DDX_Control(pDX, IDC_LIST_FILE, m_filelist);
}

BEGIN_MESSAGE_MAP(CSimpleInsectRadarDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CSimpleInsectRadarDlg::OnTcnSelchangeTabMain)
	ON_COMMAND(ID_32771, &CSimpleInsectRadarDlg::OnMenuExit)
	ON_COMMAND(ID_32775, &CSimpleInsectRadarDlg::OnMenuAbout)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_USER+100, &CSimpleInsectRadarDlg::OnPrintMessage)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_FILE, &CSimpleInsectRadarDlg::OnNMRClickListFile)
	ON_COMMAND(ID_32776, &CSimpleInsectRadarDlg::OnReadfile)
	ON_WM_TIMER()
	ON_MESSAGE(WM_USER+400, &CSimpleInsectRadarDlg::OnUser400)
	ON_MESSAGE(WM_USER+111, &CSimpleInsectRadarDlg::OnUser111)
	ON_MESSAGE(WM_USER+333, &CSimpleInsectRadarDlg::OnUser333)
	ON_MESSAGE(WM_USER+555, &CSimpleInsectRadarDlg::OnUser555)
	ON_MESSAGE(WM_USER+777, &CSimpleInsectRadarDlg::OnUser777)
	ON_MESSAGE(WM_USER+894, &CSimpleInsectRadarDlg::OnUser894)	// 擦除后配参
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CSimpleInsectRadarDlg 消息处理程序

BOOL CSimpleInsectRadarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	//char szBuf[100];
	//GetConsoleTitleA(szBuf, 100);					//得到控制台标题

	//HWND hwnd = ::FindWindowA(NULL, szBuf);			//查找控制台
	//HMENU hmenu = ::GetSystemMenu(hwnd, FALSE);		//获取菜单
	//::RemoveMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);	//移除关闭

	//DBWindowWrite(L"alall");

	//byte *p = new byte[4];
	//*((float*)p) = 1.0;

	//byte *q = new byte[4];
	//*((float*)q) = 2.0;
	//*((float*)q) += *((float*)p);

	//float r = *((float*)q);

	//int data = m_dFileTransRate * 100;
	//CString str;
	//str.Format(L"%d", data);

	//m_filelist.SetItemText(nItem, 2, str);

	CRect rect;

	//tab初始化
	m_TabCtrlMain.InsertItem(0, _T("雷达显示控制"));
	m_TabCtrlMain.InsertItem(1, _T("数据上传控制"));

	//状态栏
	UINT array[3]={11001,11002,11003};									//声明数组
	m_StatusBar.Create(this); 											//创建状态栏窗口
	m_StatusBar.SetIndicators(array,sizeof(array)/sizeof(UINT));		//添加面板
	GetClientRect(&rect);
	m_StatusBar.SetPaneInfo(0,array[0],0,rect.Width()*3/6); 			//设置面板宽度
	m_StatusBar.SetPaneInfo(1,array[1],0,rect.Width()*2/6); 			//设置面板宽度
	m_StatusBar.SetPaneInfo(2,array[2],0,rect.Width()*1/6); 			//设置面板宽度
	m_StatusBar.SetPaneText(0,_T("  北京理工雷科电子信息技术有限公司"));								//设置面板文本
	m_StatusBar.SetPaneText(1,_T("雷达部"));						//设置面板文本
	m_StatusBar.SetPaneText(2,_T("V0.5 Beta"));						//设置面板文本
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);


	//信息打印列表控件初始化
	m_listPrint.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES|LVS_OWNERDATA | LVS_EX_DOUBLEBUFFER);
	m_listPrint.InsertColumn(0, _T("雷达参数"));
	m_listPrint.InsertColumn(1, _T("雷达参数值"));
	m_listPrint.InsertColumn(2, _T("雷达参数"));
	m_listPrint.InsertColumn(3, _T("雷达参数值"));
	m_listPrint.SetColumnWidth(0, 120);
	m_listPrint.SetColumnWidth(1, 100);
	m_listPrint.SetColumnWidth(2, 100);
	m_listPrint.SetColumnWidth(3, 120);

	m_filelist.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES|LVS_OWNERDATA | LVS_EX_DOUBLEBUFFER);
	m_filelist.InsertColumn(0, _T("文件序号"));
	m_filelist.InsertColumn(1, _T("文件大小(单位：MB)"));
	m_filelist.InsertColumn(2, _T("转存进度"));
	//m_listPrint.InsertColumn(3,_T("雷达参数值"));
	m_filelist.SetColumnWidth(0, 188);
	m_filelist.SetColumnWidth(1, 140);
	m_filelist.SetColumnWidth(2, 100);

	m_filelist.ShowWindow(FALSE);
	
	m_RichEditCtrl.SetReadOnly(TRUE);
	m_formDlg1.Create(IDD_FORMVIEW1, &m_TabCtrlMain);
	m_formDlg2.Create(IDD_FORMVIEW2, &m_TabCtrlMain);
	m_TabCtrlMain.GetClientRect( &rect );
	//m_formDlg1.MoveWindow( rect.left+1,rect.top+22, rect.Width()-4, rect.Height()-25, TRUE );
	m_formDlg1.SetWindowPos(NULL, rect.left+1,rect.top+22, rect.Width()-4, rect.Height()-25, SWP_SHOWWINDOW);
	m_formDlg1.ShowWindow(TRUE);
	//m_formDlg2.MoveWindow( rect.left+1,rect.top+22, rect.Width()-4, rect.Height()-25, TRUE );
	m_formDlg2.SetWindowPos(NULL, rect.left+1,rect.top+22, rect.Width()-4, rect.Height()-25, SWP_SHOWWINDOW);
	m_formDlg2.ShowWindow(FALSE);
	
	//InitMatlabLib();
	//网络初始化
	//g_iIsTcpConnect = 0;
	
	g_iIsTcpConnect = g_tcpClient.Open();
	g_iIsUdpOpen = g_udpClientReceive.Open(true);
	g_iIsUdpOpen = g_udpClientCmdFeedBack.Open(false);
	g_iIsUdpOpen = g_udpClientFileFeedBack.Open(false);
	//CString str;
	//GetLastErrorW(str.GetBuffer(), 2);
	//pTestThread = NULL;
	if(g_iIsUdpOpen == 0)
	{
		PrintMessage(_T("udp open!"));
		AfxBeginThread(DataTranspondThread, this);
		//AfxBeginThread(NetWorkThread, this);     //启动网络收数线程
	}
	if (g_iIsTcpConnect == 0)
	{
		PrintMessage(_T("网络连接成功"));
		InitMatlabLib();						 //初始化matlab接口库
		//g_bIsRadarWork = true;
		AfxBeginThread(NetWorkThread, this);     //启动网络收数线程
		PrintMessage(_T("网络收数线程启动"));
		//m_pWriteFileThread = AfxBeginThread(WriteFileThread, this/*, 0, 0, CREATE_SUSPENDED*/);//创建写文件线程，并挂起
		
		// 启动读取配置文件线程
		AfxBeginThread(ReadParaConfigThread, this); 

#if DFLAG
		AfxBeginThread(DataTranspondThread, this);
#endif
			
	}
	else 
	{
		//AfxBeginThread(ReadParaConfigThread, this); 
		PrintMessage(_T("网络未连接！"));
	}
	//m_pWriteFileThread = AfxBeginThread(WriteFileThread, this, 0, 0, CREATE_SUSPENDED);//创建写文件线程，并挂起
	ShowWindow(SW_HIDE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSimpleInsectRadarDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSimpleInsectRadarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSimpleInsectRadarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


extern bool b_flag1;
//点击TAB事件响应函数
void CSimpleInsectRadarDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int cur = 0;
	cur = m_TabCtrlMain.GetCurSel();

	switch(cur)
	{
	case 0:
		m_TabCtrlMain.SetCurSel(0);
		m_formDlg1.ShowWindow(TRUE);
		m_formDlg2.ShowWindow(FALSE);
		m_listPrint.ShowWindow(TRUE);
		m_filelist.ShowWindow(FALSE);
		break;
	case 1:
		//if (b_flag1)
		//{
		//	MessageBox(_T("网络异常，无法开始工作"), NULL, MB_ICONWARNING);
		//	break;
		//}
		m_TabCtrlMain.SetCurSel(1);
		m_formDlg1.ShowWindow(FALSE);
		m_formDlg2.ShowWindow(TRUE);
		m_listPrint.ShowWindow(FALSE);
		m_filelist.ShowWindow(TRUE);
		break;
	default:
		break;
	}

	*pResult = 0;
}


afx_msg LRESULT CSimpleInsectRadarDlg::OnPrintMessage(WPARAM wParam, LPARAM lParam)
{
	CString str;
	str = *((CString *)wParam);
	CString strTime;
	CTime timeNow;
	timeNow = CTime::GetCurrentTime();
	//strTime.Format(TEXT("%04d-%02d-%02d  %02d:%02d:%02d"),timeNow.GetYear(),timeNow.GetMonth(),timeNow.GetDay(),
	//	timeNow.GetHour(), timeNow.GetMinute(), timeNow.GetSecond());
	strTime.Format(TEXT("%02d:%02d:%02d"), timeNow.GetHour(), timeNow.GetMinute(), timeNow.GetSecond());

	//int count = m_listPrint.GetItemCount();
	//m_listPrint.InsertItem(count,TEXT(""));
	//m_listPrint.SetItemText(count,0,strTime);
	//m_listPrint.SetItemText(count,1,str);
	//m_listPrint.EnsureVisible(count,true);

	CString strMessage;
	strMessage = strTime + L"：" + str + L"\r\n";
	m_RichEditCtrl.ReplaceSel(strMessage);
	m_RichEditCtrl.SetReadOnly(TRUE);
	::PostMessage(m_RichEditCtrl.m_hWnd, WM_VSCROLL, SB_BOTTOM, 0);

	return 0;
}


//信息打印函数
void CSimpleInsectRadarDlg::PrintMessage(CString str)
{
	SendMessage(WM_USER+100, (WPARAM)&str);
}


//菜单——退出
void CSimpleInsectRadarDlg::OnMenuExit()
{
	OnClose();
	//CDialogEx::OnCancel();
}


//菜单——关于
void CSimpleInsectRadarDlg::OnMenuAbout()
{
	// TODO: 在此添加命令处理程序代码
	//MessageBox( _T("工号：Y0591\n\n作者：孙铎\n\n联系方式：18813007611"), _T("技术支持"));
}


//关闭
void CSimpleInsectRadarDlg::OnClose()
{

	if (g_fAntennaEleAngle > 0.2)
	{
		MessageBox(_T("请将伺服角度归零!"), NULL, MB_ICONWARNING);
		return;
	}


	if (!WaitForSingleObject(m_pWriteFileThread, 0))
	{
		if (GetLastError() != 0x06)
		{
			if (MessageBox(L"后台正在上传数据文件，确定要关闭程序？", NULL, MB_YESNO) == IDYES)
			{
				CloseHandle(m_hFile);
				//关闭套接字
				if (g_iIsTcpConnect == 0)
				{
					g_tcpClient.Close();
					g_iIsTcpConnect = -1;
				}

				//停止网络收数线程
				m_criticalsection.Lock();
				g_bIsRadarWork = false;
				m_criticalsection.Unlock();

				POSITION pos = theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetHeadPosition();
				while (pos != NULL)
				{
					delete theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetNext(pos);
				}
				theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.RemoveAll();

				if (pTemp)
				{
					delete []pTemp;
					pTemp = NULL;
				}
				if (pHrrpBuf)
				{
					delete []pHrrpBuf;
					pHrrpBuf = NULL;
				}
			}
		}
	}
	//DWORD dwErrorCode = GetLastError();

	if (MessageBox(L"是否关闭程序？", NULL, MB_YESNO) == IDYES)
	{
		CloseHandle(m_hFile);
		//关闭套接字
		if (g_iIsTcpConnect == 0)
		{
			g_tcpClient.Close();
			g_iIsTcpConnect = -1;
		}

		//停止网络收数线程
		m_criticalsection.Lock();
		g_bIsRadarWork = false;
		m_criticalsection.Unlock();

		POSITION pos = theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetHeadPosition();
		while (pos != NULL)
		{
			delete theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetNext(pos);
		}
		theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.RemoveAll();

		if (pTemp)
		{
			delete []pTemp;
			pTemp = NULL;
		}
		if (pHrrpBuf)
		{
			delete []pHrrpBuf;
			pHrrpBuf = NULL;
		}
	}
	else
		return;

	CDialogEx::OnClose();
}


// 读取配置文件线程函数
UINT CSimpleInsectRadarDlg::ReadParaConfigThread(LPVOID lpParam)
{
	return ((CSimpleInsectRadarDlg*) lpParam)->ReadParaConfigProcess();
}

RadarPara ToDspParaConfig; // 下发给DSP的结构体
UINT CSimpleInsectRadarDlg::ReadParaConfigProcess()
{
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("ConfigFile.txt"));

	CString strModulePath;
	strModulePath = szModulePath;

	FileOP(strModulePath);
	return 0;
}

 
// 读取配置文件
bool b_tempFlag_paracfg = false;
bool isAutoClickStartWorkButton = false; // 在读取配置文件下是否自动点击开始工作按钮标志
void CSimpleInsectRadarDlg::FileOP(LPCTSTR LRFileName)
{
	CStdioFile mFileIn;
	CString strTempLine;
	if(!mFileIn.Open(LRFileName, CFile::modeRead)) {
	    AfxMessageBox(_T("找不到配置文件"));
	 	return;
	}
	CString strTempLineArray[5];
	int iConfigCount = 0;
	while(mFileIn.ReadString(strTempLine)!= NULL)
	{		
		if(iConfigCount <= 4)
		{
			CharToUTF8(strTempLine);
			strTempLineArray[iConfigCount] = strTempLine;
			iConfigCount++;
		}

	}
	mFileIn.Close();
	//PrintMessage(_T("配置文件读取完毕！"));
	if(strTempLineArray[1] == "0")
	{
		PrintMessage(_T("手动模式!"));
		return;
	}
	if(strTempLineArray[1] == "1" && strTempLineArray[2] == "开始工作")
	{

		// 获取参数
		//Sleep(5000);
		GetDataFromDspParaConfig();
		GetDataFromMatlabParaConfig();
		GetDataFromOwnParaConfig();
		Sleep(5000);
		PrintMessage(_T("自动模式!"));

		//// 向DSP发送参数
		int tt = 0;
		tt = g_tcpClient.Send((byte *)(&ToDspParaConfig), sizeof(ToDspParaConfig));

		if (tt == sizeof(ToDspParaConfig))
		{
			::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+400, NULL, NULL);
		}
		b_tempFlag_paracfg = true;
		isAutoClickStartWorkButton = true;
	}
	//while(mFileIn.ReadString(strTempLine)!=NULL)
	//{ 
	//	CharToUTF8(strTempLine);
	//	if(strTempLine == "0")
	//	{
	//		PrintMessage(_T("不读取配置文件!"));
	//		break;
	//	}
	//	else if(strTempLine == "开始工作")
	//	{
	//		
	//		// 获取参数
	//		//Sleep(5000);
	//		GetDataFromDspParaConfig();
	//		GetDataFromMatlabParaConfig();
	//		GetDataFromOwnParaConfig();
	//		Sleep(5000);
	//		PrintMessage(_T("读取配置文件!"));

	//		//// 向DSP发送参数
	//		int tt = 0;
	//		tt = g_tcpClient.Send((byte *)(&ToDspParaConfig), sizeof(ToDspParaConfig));

	//		if (tt == sizeof(ToDspParaConfig))
	//		{
	//			::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+400, NULL, NULL);
	//		}
	//		b_tempFlag_paracfg = true;
	//		isAutoClickStartWorkButton = true;
	//	}
	//}
	
}


extern UINT tempnPara_7;
extern float tempnPara_48;
extern RadarPara tempRadarPara;
extern UINT tempStartRan;
void CSimpleInsectRadarDlg::GetDataFromDspParaConfig()
{
	// 从文档中读出数据
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("ToDspParaConfig.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file(strModulePath, CFile::modeRead);
	CArchive ar(&file,CArchive::load);

	
	ar >> ToDspParaConfig.nParaType;
	ar >> ToDspParaConfig.nLen;
	ar >> ToDspParaConfig.nPara_2;
	ar >> ToDspParaConfig.nPara_3;
	ar >> ToDspParaConfig.nPara_4;
	ar >> ToDspParaConfig.nPara_5;
	ar >> ToDspParaConfig.nPara_6;
	ar >> ToDspParaConfig.nPara_7;
	ar >> ToDspParaConfig.nPara_8;
	ar >> ToDspParaConfig.nPara_9;
	ar >> ToDspParaConfig.nPara_10;
	ar >> ToDspParaConfig.nPara_11;
	ar >> ToDspParaConfig.nPara_12;
	ar >> ToDspParaConfig.nPara_13;
	ar >> ToDspParaConfig.nPara_14;
	ar >> ToDspParaConfig.nPara_15;
	ar >> ToDspParaConfig.nPara_16;
	ar >> ToDspParaConfig.nPara_17;
	ar >> ToDspParaConfig.nNewAziSpeed;
	ar >> ToDspParaConfig.nNewEleSpeed;
	ar >> ToDspParaConfig.nPara_18;
	ar >> ToDspParaConfig.nPara_19;
	ar >> ToDspParaConfig.nPara_20;
	ar >> ToDspParaConfig.nPara_21;
	ar >> ToDspParaConfig.nPara_22;
	ar >> ToDspParaConfig.nPara_23;
	ar >> ToDspParaConfig.nPara_24;
	ar >> ToDspParaConfig.reserve[0];
	ar >> ToDspParaConfig.reserve[1];
	ar >> ToDspParaConfig.reserve[2];
	ar >> ToDspParaConfig.reserve[3];
	ar >> ToDspParaConfig.reserve[4];
	ar >> ToDspParaConfig.reserve[5];
	ar >> ToDspParaConfig.reserve[6];
	ar >> ToDspParaConfig.nPara_32;
	ar >> ToDspParaConfig.nPara_33;
	ar >> ToDspParaConfig.nPara_34;
	ar >> ToDspParaConfig.nPara_35;
	ar >> ToDspParaConfig.nPara_36;
	ar >> ToDspParaConfig.nPara_37;
	ar >> ToDspParaConfig.nPara_38;
	ar >> ToDspParaConfig.nPara_39;
	ar >> ToDspParaConfig.fPara_40;
	ar >> ToDspParaConfig.nPara_47;
	ar >> ToDspParaConfig.nPara_41;
	ar >> ToDspParaConfig.nPara_42;
	ar >> ToDspParaConfig.nPara_43;
	ar >> ToDspParaConfig.nPara_44;
	ar >> ToDspParaConfig.nPara_45;
	ar >> ToDspParaConfig.nPara_46;
	ar >> ToDspParaConfig.nPara_48;
	ar >> ToDspParaConfig.nPara_workingModes;
	ar >> ToDspParaConfig.nPara_miniinterval;
	ar >> ToDspParaConfig.nPara_iniAzimuth;
	ar >> ToDspParaConfig.nPara_endAzimuth;
	ar >> ToDspParaConfig.nPara_dptWavPlusWid;
	ar >> ToDspParaConfig.nPara_dptInitSampDist;
	ar >> ToDspParaConfig.nPara_distDetect;
	ar >> ToDspParaConfig.nPara_dopplerDetect;
	ar >> ToDspParaConfig.nPara_detectionChannel;



	// 其他参数
	ar >> waveMode;
	ar >> codeMode;
	ar >> g_nDrawNodes;
	ar >> g_nCoefficient;
	ar >> g_nPara_7;
	ar >> g_singleAcquistionTimeMax;
	ar >> tempnPara_48;
	ar >> tempnPara_7;
	ar >> tempStartRan; // 起始采样距离

	tempRadarPara = ToDspParaConfig;
}

// 读取MATLAB参数
void CSimpleInsectRadarDlg::GetDataFromMatlabParaConfig()
{
	// 从文档中读出数据
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("ToMatlabParaConfig.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file(strModulePath, CFile::modeRead);
	CArchive ar(&file,CArchive::load);

	ar >> toMatlabPara.RCS_ball;
	ar >> toMatlabPara.StartRan;
	ar >> toMatlabPara.SampleNum;
	ar >> toMatlabPara.PRT;
	ar >> toMatlabPara.WaveForm;
	ar >> toMatlabPara.CodeType;
	ar >> toMatlabPara.s1;
	ar >> toMatlabPara.s2;
	ar >> toMatlabPara.mode;
	ar >> toMatlabPara.dlMinLength_Cali;
	ar >> toMatlabPara.dlMinLength_ParaEst;
	ar >> toMatlabPara.dlMinLength_Den;
	ar >> toMatlabPara.fPulseWid;
	ar >> toMatlabPara.SampleTime;
	ar >> toMatlabPara.workingMode;
	ar >> toMatlabPara.fAzi_S;
	ar >> toMatlabPara.fAzi_E;
	ar >> toMatlabPara.fElv_D;
	ar >> toMatlabPara.fElv_H;
	ar >> toMatlabPara.enableAutoCali;


}
extern bool b_isOkBtnParaConfig;
void CSimpleInsectRadarDlg::GetDataFromOwnParaConfig()
{
	// 从文档中读出数据
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("ToOwnParaConfig.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file(strModulePath, CFile::modeRead);
	CArchive ar(&file,CArchive::load);

	ar >> ToDspParaConfig.nPara_endAzimuth;
	ar >> g_autoCali;
	ar >> g_autoCaliMode;
	ar >> g_zhuanCun;
	ar >> g_zhuanCunTime;
	// 内校准模式配参数
	if(g_autoCali == 1 && g_autoCaliMode == 0)
	{
		toMatlabPara.UintCaliType = 5;
		ToDspParaConfig.nPara_13 = 0;
		ToDspParaConfig.nPara_14 = 160;
	}
	else if(g_autoCali == 1 && g_autoCaliMode == 1)
	{
		toMatlabPara.UintCaliType = 1;
		ToDspParaConfig.nPara_13 = 1;
		ToDspParaConfig.nPara_14 = 32;
	}
	if(g_autoCali == 1)	// 自动内校准模式
	{
		ToDspParaConfig.nPara_7 = 0;	// 起始采样距离为0
		ToDspParaConfig.nPara_dptInitSampDist = 0;	// 交替模式下副波形起始采样距离
	}
	if(g_autoCali == 1 && g_autoCaliMode == 1)
	{
		ToDspParaConfig.nPara_detectionChannel = 0; // 内校准模式下手动配参首先进行发射一校准，HH通道
	}
	ar >> g_workMode;
	ar >> b_isOkBtnParaConfig;
}

// 字符转换
void CSimpleInsectRadarDlg::CharToUTF8(CString &str)
{
	char *szBuf = new char[str.GetLength() + 1];//注意“+1”，char字符要求结束符，而CString没有
	memset(szBuf, '\0',str.GetLength());


	int i;
	for ( i = 0 ; i < str.GetLength(); i++)
	{
		szBuf[i] = (char)str.GetAt(i);
	}
	szBuf[i] = '\0';//结束符。否则会在末尾产生乱码。

	int nLen;
	WCHAR *ptch;
	CString strOut;
	if(szBuf == NULL)
	{
		return;
	}
	nLen = MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, NULL, 0);//获得需要的宽字符字节数
	ptch = new WCHAR[nLen];
	memset(ptch, '\0', nLen);
	MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, ptch, nLen);
	//str.Format(_T("%s"), ptch);
	str = ptch;
	if(NULL != ptch)
		delete [] ptch;
	ptch = NULL;

	if(NULL != szBuf)
		delete []szBuf;
	szBuf = NULL;
	return ;
}

//网络收数线程
UINT CSimpleInsectRadarDlg::NetWorkThread(LPVOID lpParam)
{
	return ((CSimpleInsectRadarDlg*)lpParam)->NetWorkProcess();
}

UINT CSimpleInsectRadarDlg::TrackCalcThread(LPVOID lpParam)
{
	return ((CSimpleInsectRadarDlg*)lpParam)->TrackCalcProcess();
}

// 数据转发线程
UINT CSimpleInsectRadarDlg::DataTranspondThread(LPVOID lpParam)
{
	return ((CSimpleInsectRadarDlg*)lpParam)->DataTranspondProcess();
}

UINT CSimpleInsectRadarDlg::DataTranspondProcess()
{
	g_bIsRadarWork = true;
	byte frameHead[8] = {0};
	byte *p = frameHead;
	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9083);
	bind(s, (sockaddr*)&addr, sizeof(addr));
	int addrSize= sizeof(addr);
	SOCKADDR_IN addr2;
	INT addrSize2 = sizeof(addr);

	while(true)
	{
		PrintMessage(_T("recvfrom"));
		char buff[8192] = { 0 };
		int nRecv = recvfrom(s, buff, 8192, 0, (sockaddr*)&addr, &addrSize);
		//p = buff;
		UINT32 type =0;
		type = *((UINT32 *)(buff+4));                //获取指令码长度
		UINT len =0;
		len = *((UINT *)(buff+4));                //获取指令码长度
		byte *pBuffer = new byte[len + 8];
		memset(pBuffer, 0, len + 8);
		memcpy(pBuffer, buff, len+8);
		DisplaySoftDataProcessing((byte*)pBuffer, len+8);//对接收的数据进行分析 
#if 0
		int nRet = g_udpClientReceive.Recv(p, 8);//前四个字节是包头；后四个字节是包长
		if(nRet == 0)
		{
			PrintMessage(_T("continue"));
			continue;
		}
		int nError = WSAGetLastError();
		UINT len =0;
		len = *((UINT *)(p+4));                //获取指令码长度

		byte *pBuffer = new byte [len + 8 + 4];         //开辟接收数据缓冲区
		memset(pBuffer, 0, len + 8 + 4);
		nRet = g_udpClientReceive.Recv(pBuffer + 8, len+4);			//** 接收指定长度数据
		if (nRet < 0)
		{
			PrintMessage(_T("Socket连接已经断开，请重启软件"));
			break;
		}
		memcpy(pBuffer, p, 8);                      //将数据拼好
		//g_tcpDisplaySoftClient.Send(pBuffer, len + 8); // 工作指令转发
		DisplaySoftDataProcessing(pBuffer, len + 8 + 4);//对接收的数据进行分析 
#endif  
		Sleep(1);
	}

	return 0;
}

//网络收数任务
UINT CSimpleInsectRadarDlg::NetWorkProcess()
{
	g_bIsRadarWork = true;

	byte frameHead[8] = {0};
	byte *p = frameHead;
	byte *pushbuf = NULL;
	while((pushbuf = new byte[64*1024*1024]) == NULL);
	UINT offset = 0;

	ULONGLONG tStartTime = GetTickCount64();
	ULONGLONG ulTotalBytes = 0;
	long lDistanceToMove = 0;

	//CString strFileName(_T("1.bin"));
	//m_hFile = CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	while(/*g_bIsRadarWork*/true)
	{
		g_tcpClient.Recv(p, 8);  //前四个字节是包头；后四个字节是包长
		// ******* 下面的流程分两种情况,分别为雷达工作模式和数据上传模式 ******** //
		int nError = WSAGetLastError();
		UINT len =0;
		//len = *((UINT *)(p));
		len = *((UINT *)(p+4));                //获取指令码长度

		//if (len > 827808)
		//{
		//	continue;
		//}

		byte *pBuffer = new byte [len + 8];         //开辟接收数据缓冲区
		memset(pBuffer, 0, len + 8);
		int nRet = g_tcpClient.Recv(pBuffer + 8, len);			//** 接收指定长度数据
		if (nRet < 0)
		{
			PrintMessage(_T("Socket连接已经断开，请重启软件"));
			break;
			//continue;
		}

		//m_criticalsection.Lock();
		memcpy(pBuffer, p, 8);                      //将数据拼好
		
		
		UINT nDataType = *((UINT *)p);     //解析反馈数据类型码
		DWORD dwWrites;
		//if (nDataType == 0x7c7c7c7c || nDataType == 0x17181920)
		//{
		//	long lDistanceToMoveHigh = 0;
		//	WriteFile(m_hFile, pBuffer, len + 8, &dwWrites, NULL);
		//	SetFilePointer(m_hFile, lDistanceToMove, NULL, FILE_CURRENT);

		//	lDistanceToMove = dwWrites * (-1);
		//	//CloseHandle(m_hFile);
		//}

		//存文件
		if (g_bWritingFile)
		{
			memcpy(pushbuf + offset, pBuffer, (len + 8)); //对上传数据文件再拷贝，为入FIFO做准备
			offset += (len + 8);

			ulTotalBytes += (ULONGLONG)nRet;	//统计开始上传后总的网络数据量

			while(offset >= FifoWith)
			{
				byte *p = NULL;
				//byte *q = NULL;
				while((p = m_FIFO.Alloc()) == NULL);
				memcpy(p, pushbuf, FifoWith);
				m_FIFO.Push(p);
				//q = m_FIFO.Pop();
				//BOOL BB = m_FIFO.Free(q);
				memcpy(pushbuf, pushbuf + FifoWith, offset - FifoWith);
				offset -= FifoWith;			
			}

			ULONGLONG tEndTime = GetTickCount64();
			if (tEndTime - tStartTime > 1000)
			{
				//平均速度
				g_dlNetSpeed = (double)ulTotalBytes / (double)(tEndTime - tStartTime) * 1000;//B/s;
				g_dlNetSpeed = g_dlNetSpeed / 1024 / 1024;
				::PostMessage(theApp.m_pMainDlg->m_formDlg2.m_hWnd, WM_USER+444, NULL, NULL);
				tStartTime = tEndTime;
				ulTotalBytes = 0;
			}
			//return;
		}
		//else
		//{
		//	memcpy(pBuffer, p, 8);                      //将数据拼好
		//}
		//else
		//{
			DataProcessing(pBuffer, len + 8);           //对接收的数据进行分析
		//}
		

		//m_criticalsection.Unlock();
	}

	delete []pushbuf;

	return 0;
}

extern bool b_flag1;
bool b_isTempCountTrack = true;	// 是否在进行内校准标志位
/*static*/ int tempiTwiceCount = 0;
static int tempiCount = 0;


bool tempFlag = false;
CString oriTrack;

extern CString oriTrackFilePath; // 原始点迹存储路径
extern CString CPIFileBackPath; // CPI数据备份路径
extern CString trackFilePath; // track数据打包
extern CString CPIFilePath; // CPI数据存储路径
extern CString HRRPFilePath; // 一维距离像数据存储路径
extern map<LONGLONG, CString> mapFileName; // oriTrack
extern map<LONGLONG, CString>::iterator itTxtFileTime; // log 记录的文件时间
UINT CSimpleInsectRadarDlg::TrackCalcProcess()
{
	//HANDLE hFile = CreateFile(_T("123.bin"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	while (/*1*/b_flag1)
	{
		byte *q = NULL;	//  unsigned char ---byte
		q = g_fifo_track.Pop();
		//q = new byte;
		//if (0)
		//{
			//UINT len = *((UINT*)(q+4)) + 8;

			//DWORD dwWrites;
			//bool bRet = WriteFile(hFile, q, len, &dwWrites, NULL);
			//CloseHandle(hFile);
		//	return 0;
		//	g_fifo_track.Free(q);
		//}
		//if (q)
		//{
		//	g_fifo_track.Free(q);
		//}

		if (q)
		{
			/*
			int len = *((int*)(q + 4));
			UINT q_uStartRan = 0;
			mxInt32 mx_StartRan = 0;
			mxDouble mx_PulseWid = 0;

			if(toMatlabPara.workingMode == 3)	// 从数据包中去解析采样距离和波形脉宽的值
			{
				q_uStartRan = *(UINT *)(q + len);
				mx_StartRan = q_uStartRan;           //    % 起始采样距离      对应：“起始采样距离”
				//g_nPara_7 = q_uStartRan;	// 用于一维距离像显示
				float q_fPulseWid = *(float *)(q + len + 4);
				mx_PulseWid = q_fPulseWid * 1000000; // 波形脉宽以us为单位
			}
			else
			{
				mx_StartRan = toMatlabPara.StartRan;           //    % 起始采样距离      对应：“起始采样距离”
				mx_PulseWid = toMatlabPara.fPulseWid; // 波形脉宽-us
				//len += 8;
			}

			len += 8;
			*/

			int len = *((int*)(q + 4));
			UINT q_uStartRan = 0;
			CString str;
			str.Format(_T("%d"), len);
			//PrintMessage("len："+str);
#if 1
			// 获取系统时间
			SYSTEMTIME curSystemTime;
			GetLocalTime(&curSystemTime);

			CString strSystemTime;
			strSystemTime.Format(L"%4d_%02d_%02d_%02d_%02d_%02d_%03d", 
				curSystemTime.wYear, curSystemTime.wMonth, curSystemTime.wDay, 
				curSystemTime.wHour, curSystemTime.wMinute, curSystemTime.wSecond, curSystemTime.wMilliseconds);

			//CString filePath = "D://test//02_scanMode//oriTrack";
			oriTrack = oriTrackFilePath + "//OriginalTrack_" + strSystemTime + ".bin";
			
			//PrintMessage("Start write file!");
			HANDLE hTrackFile = CreateFile(oriTrack, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			DWORD dTrackWrites;
			WriteFile(hTrackFile, q, len + 8, &dTrackWrites, NULL);
			CloseHandle(hTrackFile);
			//PrintMessage("Write file completed!");
#if 1
			CString oriTrackFileName;
			oriTrackFileName = "OriginalTrack_" + strSystemTime + ".bin";
			time_t tOriTrackTimeStamp;
			tOriTrackTimeStamp = m_formDlg1.GetFileCreateTimeStamp(oriTrackFileName);
			//m_trackCriticalsection.Lock();
			mapFileName.insert(pair<LONGLONG, CString>(tOriTrackTimeStamp, oriTrackFileName));
#endif
			//m_trackCriticalsection.Unlock();
			
#endif

#if 0	
			// 数据解析
			
			PrintMessage("Start Date_translate!");

			mxInt32 mx_Result= 0;
			mwArray mw_Result(1, 1, mxINT32_CLASS);
			char oriTrackFile_name[1024] = {0};
			WideCharToMultiByte(oriTrack, oriTrackFile_name, 1024);
				
			mwArray mw_oriTrackFile_name(oriTrackFile_name);
			char oriTrackFileOutputPath[] = {"D://test//02_scanMode//01"};
			mwArray mw_oriTrackFileOutputPath(oriTrackFileOutputPath);

			char oriTrackFileBackupPath[] = {"D://test//02_scanMode//backup"};
			mwArray mw_oriTrackFileBackupPath(oriTrackFileBackupPath);

			Date_translate(1, mw_Result, mw_oriTrackFile_name, mw_oriTrackFileOutputPath, mw_oriTrackFileBackupPath);
			int result = mw_Result.Get(1,1);
			if(result == 1)
				PrintMessage("Date_translate success!");
			else
				PrintMessage("Date_translate error!");
			PrintMessage("**********************");

#endif

#if 1
			if(!tempFlag)
			{				
				// 开启OriTrackProcess
				AfxBeginThread(MatlabTrackProcessThread, this);
				AfxBeginThread(MatlabInversionAlgProcessThread, this);
				PrintMessage("MatlabTrackProcessThread start!");
				SetTimer(3, 2000, NULL);
				tempFlag = true;
			}
#endif

#if 0
			if(!tempFlag)
			{
				struct thrStruct
				{
					double thrTime; // 时间关联门限
					double thrRange; // 距离关联门限
					double thrAzi; // 方位角关联门限
					double thrEle; // 俯仰角关联门限
					double thrDelDetlatime; // 航迹删除时间
					double thrDelNum; // 航迹删除点数
				};

				thrStruct thr;
				thr.thrTime = 2;
				thr.thrRange = 3;
				thr.thrAzi = 1;
				thr.thrEle = 1;
				thr.thrDelDetlatime = 100;
				thr.thrDelNum = 50;

				const int nFields = 6; // 结构体中变量个数
				const char *fieldNames[6] = {"ThrTime", "ThrRange", "ThrAzi", "ThrEle", "Del_detlatime", "Del_Num"}; // 结构体中变量名

				mwArray mwStruct(1, 1, nFields, fieldNames);

				mwArray mwThrTime(thr.thrTime);
				mwStruct(fieldNames[0], 1, 1) = mwThrTime;

				mwArray mwThrRange(thr.thrRange);
				mwStruct(fieldNames[1], 1, 1) = mwThrRange;

				mwArray mwThrAzi(thr.thrAzi);
				mwStruct(fieldNames[2], 1, 1) = mwThrAzi;

				mwArray mwThrEle(thr.thrEle);
				mwStruct(fieldNames[3], 1, 1) = mwThrEle;

				mwArray mwThrDelDetlatime(thr.thrDelDetlatime);
				mwStruct(fieldNames[4], 1, 1) = mwThrDelDetlatime;

				mwArray mwThrDelNum(thr.thrDelNum);
				mwStruct(fieldNames[5], 1, 1) = mwThrDelNum;

				mwArray mwFlag(1, 1, mxDOUBLE_CLASS);

				char savePath[] = {"D://test//02_scanMode//02"};
				mwArray mwSavePath(savePath);

				mxInt32 mx_ResultTrack = 0;
				mwArray mw_ResultTrack(1, 1, mxDOUBLE_CLASS);
				
				mwArray mw_TrackOneMat(9, 1, mxDOUBLE_CLASS);
				mwArray mw_CellNum(1, 1, mxDOUBLE_CLASS);
				mxInt32 mx_CellNum = 1;
				mw_CellNum.SetData(&mx_CellNum, 1);

				mwArray mw_TrackNo(1, 1, mxDOUBLE_CLASS);
				mxInt32 mx_TrackNo = -1;
				mw_TrackNo.SetData(&mx_TrackNo, 1);

				mwArray mw_Track(9, 1, mxDOUBLE_CLASS);
				mwArray mw_TrackNoIn(1, 1, mxDOUBLE_CLASS);
				mwArray mw_CellNumIn(1, 1, mxDOUBLE_CLASS);

				char oriTrackFileOutputPath[] = {"D://test//02_scanMode//01"};
				mwArray mw_oriTrackFileOutputPath(oriTrackFileOutputPath);

				PrintMessage("Start func_Track!\n");
				func_Track_v2(4, mw_ResultTrack, mw_TrackOneMat, mw_CellNum, mw_TrackNo, mw_Track, 
							mw_TrackNoIn, mw_CellNumIn, mw_oriTrackFileOutputPath, mwSavePath, mwStruct);
				PrintMessage("func_Track completed!\n");
			

				tempFlag = true;
			}


#endif
			
		
#if 0

			// debug
			/*CString str;
			str.Format(_T("%d"), mx_StartRan);*/
			//PrintMessage("起始采样距离："+str);

			TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
			GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
			(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
			//wcscpy(gszSettingPath , szModulePath);
			wcscat(szModulePath , _T("Track.bin"));
			HANDLE hFile = CreateFile(/*_T("123.bin")*/szModulePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			DWORD dwWrites;
			bool bRet = WriteFile(hFile, q, len, &dwWrites, NULL);
			CloseHandle(hFile);

			


			mxInt8 mx_Result = 0;
			mwArray mw_Result(1, 1, mxINT8_CLASS);

			//mxInt32 mx_StartRan = toMatlabPara.StartRan;           //    % 起始采样距离      对应：“起始采样距离”
			mxInt32 mx_SampleNum = toMatlabPara.SampleNum;		 //    % 采样点数          对应：“采样窗点数”
			mxInt32 mx_PRT = toMatlabPara.PRT;				 //    % PRT              对应： “PRT”
			mxInt32 mx_WaveForm = toMatlabPara.WaveForm;			 //    % 波形编码          对应：“波形编码”
			mxInt32 mx_CodeType = toMatlabPara.CodeType;			 //    % 脉间编码模式      对应：“脉间编码模式”
			mxDouble mx_RCS_ball = toMatlabPara.RCS_ball;
			mxDouble mx_MinLength_Cali = toMatlabPara.dlMinLength_Cali;
			mxDouble mx_MinLength_ParaEst = toMatlabPara.dlMinLength_ParaEst; //mw_MinLength_ParaEst == mx_MinLength_Orien
			mxDouble mx_MinLength_Den = toMatlabPara.dlMinLength_Den;

			//mxDouble mx_PulseWid = toMatlabPara.fPulseWid; // 波形脉宽
			mxInt32  mx_SampleTime = toMatlabPara.SampleTime; // 单次采集时间

			mxDouble mx_Azi_S = toMatlabPara.fAzi_S; // 方位起始采集角度
			mxDouble mx_Azi_E = toMatlabPara.fAzi_E; // 方位终止采集角度

			mxInt32 mx_IntCaliType = toMatlabPara.UintCaliType;	// 校准指令

			mxDouble mx_Elv_D = toMatlabPara.fElv_D; // 俯仰起始角度
			mxDouble mx_Elv_H = toMatlabPara.fElv_H; // 俯仰终止角度

			mxInt32 mx_IntCali_Enable = toMatlabPara.enableAutoCali;

			
			// debug
			*if(b_isTempCountTrack && (g_workMode == 1) && (g_autoCali == 1))
			{*/
				//str.Format(_T("%d"), mx_IntCaliType);
				//PrintMessage("校准指令："+str);
			*}*/


			mwArray mw_StartRan(1, 1, mxINT32_CLASS);
			mwArray mw_SampleNum(1, 1, mxINT32_CLASS);
			mwArray mw_PRT(1, 1, mxINT32_CLASS);
			mwArray mw_WaveForm(1, 1, mxINT32_CLASS);
			mwArray mw_CodeType(1, 1, mxINT32_CLASS);
			mwArray mw_RCS_ball(1,1,mxDOUBLE_CLASS);
			mwArray mw_MinLength_Cali(1,1,mxDOUBLE_CLASS);
			mwArray mw_MinLength_ParaEst(1,1,mxDOUBLE_CLASS);
			mwArray mw_MinLength_Den(1,1,mxDOUBLE_CLASS);

			mwArray mw_PulseWid(1,1,mxDOUBLE_CLASS); // 波形脉宽
			mwArray mw_SampleTime(1,1, mxINT32_CLASS); // 单次采集时间

			mwArray mw_Azi_S(1,1,mxDOUBLE_CLASS);	// 方位起始采集角度
			mwArray mw_Azi_E(1,1,mxDOUBLE_CLASS);	// 方位终止采集角度

			mwArray mw_IntCaliType(1, 1, mxINT32_CLASS);	// 校准指令

			mwArray mw_Elv_D(1,1,mxDOUBLE_CLASS);	// 俯仰起始角度
			mwArray mw_Elv_H(1,1,mxDOUBLE_CLASS);	// 俯仰终止角度

			mwArray mw_IntCali_Enable(1, 1, mxINT32_CLASS);

			

			mw_StartRan.SetData(&mx_StartRan, 1);
			mw_SampleNum.SetData(&mx_SampleNum, 1);
			mw_PRT.SetData(&mx_PRT, 1);
			mw_WaveForm.SetData(&mx_WaveForm, 1);
			mw_CodeType.SetData(&mx_CodeType, 1);
			mw_RCS_ball.SetData(&mx_RCS_ball,1);
			mw_MinLength_Cali.SetData(&mx_MinLength_Cali,1);
			mw_MinLength_ParaEst.SetData(&mx_MinLength_ParaEst,1);
			mw_MinLength_Den.SetData(&mx_MinLength_Den,1);

			mw_PulseWid.SetData(&mx_PulseWid,1);
			mw_SampleTime.SetData(&mx_SampleTime, 1);

			mw_Azi_S.SetData(&mx_Azi_S, 1);
			mw_Azi_E.SetData(&mx_Azi_E,1);

			mw_IntCaliType.SetData(&mx_IntCaliType,1);

			mw_Elv_D.SetData(&mx_Elv_D, 1);
			mw_Elv_H.SetData(&mx_Elv_H, 1);
			mw_IntCali_Enable.SetData(&mx_IntCali_Enable,1);
			/////////////////////////////////////

			//char Data_input[] = {"123.bin"};
			//INT32 nlen_Data_input = sizeof(Data_input);
			//long long nLen_Data = 3872388;//58982400;//23592960;			//数组长度为读取map.out文件大小
			//UINT32 *pData_out = new UINT32[nLen_Data/4];
			//FILE *pFile_ClutterMapFile = fopen(Data_input, "rb+");
			//fread(pData_out, 4, nLen_Data/4, pFile_ClutterMapFile);
			//fclose(pFile_ClutterMapFile);

			/////////////////////////////////////
			//len = nLen_Data;
			mxUint32 *mx_Track_Input = new mxUint32[len/4];
			memcpy(mx_Track_Input, /*pData_out*/q, len);
			mwArray *mw_Track_Input = new mwArray(len/4, 1, mxUINT32_CLASS);
			mw_Track_Input->SetData(mx_Track_Input, len/4);
			func_Date_Transform(1, mw_Result, *mw_Track_Input);
			mw_Result.GetData(&mx_Result,1);
			if (mx_Track_Input)
				delete []mx_Track_Input;
			if (mw_Track_Input)
				delete mw_Track_Input;
			if (mx_Result == 0)
			{
				g_fifo_track.Free(q);
				continue;
			}

			CString strTemp;
			strTemp = toMatlabPara.s1;
			//char TrackFile_name[] = {"E:\\01探虫雷达\\01多频全极化雷达\\Matlab&VS_TC\\Matlab_TC\\Track_DSPupLoad.mat"};
			//char TrackFile_name[] = {"d:\\近距分时全极化_无脉间编码_0_0.mat"};
			char TrackFile_name[1024] = {"1.mat"};
			//WideCharToMultiByte(strTemp, TrackFile_name, 1024);
			mwArray mw_TrackFile_name(TrackFile_name);

			strTemp = toMatlabPara.s2;
			//char CaliFile_name[] = {"那个啥CaliFile_name"};
			char CaliFile_name[1024] = {0};
			WideCharToMultiByte(strTemp, CaliFile_name, 1024);
			mwArray mw_CaliFile_name(CaliFile_name);

			//PrintMessage(_T("TrackCalcProcess!"));

			//tempiCount++;
			if(b_isTempCountTrack && g_autoCali == 1)
			{
				
				
				//PrintMessage(_T("调用内校准函数！" ));
				// 内校准函数
				//func_InternalCalibration(const mwArray& TrackFile_name, const mwArray& PulseWid, const mwArray& IntCaliType);
				func_InternalCalibration(mw_TrackFile_name, mw_PulseWid, mw_IntCaliType);
				//PrintMessage(_T("调用内校准函数！" ));
			}


			if ((toMatlabPara.mode == 0) && (!b_isTempCountTrack || g_autoCali == 0))			//正常模式
			{
				char Cali_ball_File_name[] = {"E:\\01探虫雷达\\01多频全极化雷达\\Matlab&VS_TC\\Matlab_TC\\CaliFile_20180312T170000.mat"};//对应校准文件名字，校准文件名字来源于界面的参数组合

				mwArray mw_Cali_ball_File_name(Cali_ball_File_name);

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

				

				/********************************************************************************************/


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

				// 体长分布
				//mxDouble mx_BodyLen_X[5000];
				//mxInt32 mx_BodyLen_X_N;
				//mxDouble mx_BodyLen_Y[5000];
				//mxInt32 mx_BodyLen_Y_N;

				mxDouble *pmx_BodyLen_X = new mxDouble[5000];
				mxInt32 mx_BodyLen_X_N;
				mxDouble *pmx_BodyLen_Y = new mxDouble[5000];
				mxInt32 mx_BodyLen_Y_N;

				// 体重分布
				/*mxDouble mx_BodyMass_X[5000];
				mxInt32 mx_BodyMass_X_N;
				mxDouble mx_BodyMass_Y[5000];
				mxInt32 mx_BodyMass_Y_N;*/

				mxDouble *pmx_BodyMass_X = new mxDouble[5000];
				mxInt32 mx_BodyMass_X_N;
				mxDouble *pmx_BodyMass_Y = new mxDouble[5000];
				mxInt32 mx_BodyMass_Y_N;

				// 高度-时间分布
				/*mxDouble mx_HTDiv_X[5000];
				mxInt32 mx_HTDiv_T_N;
				mxDouble mx_HTDiv_Y[5000];
				mxInt32 mx_HTDiv_H_N;
				*/

				// 高度-时间分布
				mxDouble *pmx_HTDiv_X = new mxDouble[5000];
				mxInt32 mx_HTDiv_T_N;
				mxDouble *pmx_HTDiv_Y = new mxDouble[5000];
				mxInt32 mx_HTDiv_H_N;


				//func_NormalMode(16, mw_T_wght,mw_T_wght_N,mw_R_wght,mw_R_wght_N,
				//	mw_XX,mw_XX_N,mw_YY,mw_YY_N,
				//	mw_PP_X,mw_PP_X_N,mw_PP_Y,mw_PP_Y_N,
				//	mw_Fre_axis_1,mw_Fre_axis_1_N,mw_FreqV_FFT,mw_FreqV_FFT_N,

				//	mw_TrackFile_name, mw_CaliFile_name/*mw_Cali_ball_File_name*/,mw_StartRan,mw_SampleNum,mw_PRT,mw_WaveForm,mw_CodeType,mw_RCS_ball, mw_MinLength_Den, mw_MinLength_Orien);

				
				
				//func_Playback_VerticalLookingMode(TrackFile_name,MinLength_Den,MinLength_ParaEst)
				//垂直模式-单一脉宽 垂直模式-交替脉宽
				if(toMatlabPara.workingMode == 1 || toMatlabPara.workingMode == 3)
				{
					///*密度廓线**/// 朝向分布*// 振翅频率分布// 体长分布// 体重分布// 个体振翅频率// 高度-时间分布// 极化方向图*
					//func_VerticalLookingMode(int nargout, mwArray& DenProf_X, mwArray& DenProf_X_N, mwArray& DenProf_Y, mwArray& DenProf_Y_N,
					//mwArray& Orien_X, mwArray& Orien_X_N, mwArray& Orien_Y, mwArray& Orien_Y_N,
					//mwArray& WingBeatFre_X, mwArray& WingBeatFre_X_N, mwArray& WingBeatFre_Y, mwArray& WingBeatFre_Y_N, 
					//mwArray& BodyLen_X, mwArray& BodyLen_X_N, mwArray& BodyLen_Y, mwArray& BodyLen_Y_N,
					//mwArray& BodyMass_X, mwArray& BodyMass_X_N, mwArray& BodyMass_Y, mwArray& BodyMass_Y_N, 
					//mwArray& WBF_Ind_X, mwArray& WBF_Ind_X_N, mwArray& WBF_Ind_Y, mwArray& WBF_Ind_Y_N, 
					//mwArray& HTDiv_X, mwArray& HTDiv_T_N, mwArray& HTDiv_Y, mwArray& HTDiv_H_N, 
					//mwArray& PP_X, mwArray& PP_X_N, mwArray& PP_Y, mwArray& PP_Y_N, 
					//const mwArray& TrackFile_name, const mwArray& CaliFilePath, const mwArray& StartRan, const mwArray& SampleNum, const mwArray& PRT, const mwArray& PulseWid, const mwArray& WaveForm, const mwArray& CodeType, const mwArray& RCS_ball, const mwArray& MinLength_Den, const mwArray& MinLength_ParaEst, const mwArray& SampleTime, const mwArray& IntCali_Enable);

					//PrintMessage(_T("调用垂直模式函数！" ));
					func_VerticalLookingMode(32, mw_DenProf_X,mw_DenProf_X_N, mw_DenProf_Y, mw_DenProf_Y_N, 
						mw_Orien_X,mw_Orien_X_N,mw_Orien_Y,mw_Orien_Y_N,						
						mw_WingBeatFre_X, mw_WingBeatFre_X_N, mw_WingBeatFre_Y, mw_WingBeatFre_Y_N,
						mw_BodyLen_X,mw_BodyLen_X_N,mw_BodyLen_Y,mw_BodyLen_Y_N,				
						mw_BodyMass_X,mw_BodyMass_X_N,mw_BodyMass_Y,mw_BodyMass_Y_N,			
						mw_WBF_Ind_X, mw_WBF_Ind_X_N, mw_WBF_Ind_Y, mw_WBF_Ind_Y_N,				
						mw_HTDiv_X, mw_HTDiv_T_N, mw_HTDiv_Y, mw_HTDiv_H_N,						
						mw_PP_X,mw_PP_X_N,mw_PP_Y,mw_PP_Y_N,								

						mw_TrackFile_name, mw_CaliFile_name/*mw_Cali_ball_File_name*/,mw_StartRan,mw_SampleNum,mw_PRT,mw_PulseWid,mw_WaveForm,mw_CodeType,mw_RCS_ball, mw_MinLength_Den, mw_MinLength_ParaEst, mw_SampleTime, mw_IntCali_Enable);
					//PrintMessage(_T("调用垂直模式函数！" ));

					//func_Playback_VerticalLookingMode(32, 
						//mwArray& DenProf_X, mwArray& DenProf_X_N, mwArray& DenProf_Y, mwArray& DenProf_Y_N, mwArray& Orien_X, mwArray& Orien_X_N, mwArray& Orien_Y, mwArray& Orien_Y_N, mwArray& WingBeatFre_X, mwArray& WingBeatFre_X_N, mwArray& WingBeatFre_Y, mwArray& WingBeatFre_Y_N, mwArray& BodyLen_X, mwArray& BodyLen_X_N, mwArray& BodyLen_Y, mwArray& BodyLen_Y_N, mwArray& BodyMass_X, mwArray& BodyMass_X_N, mwArray& BodyMass_Y, mwArray& BodyMass_Y_N, mwArray& WBF_Ind_X, mwArray& WBF_Ind_X_N, mwArray& WBF_Ind_Y, mwArray& WBF_Ind_Y_N, mwArray& HTDiv_X, mwArray& HTDiv_T_N, mwArray& HTDiv_Y, mwArray& HTDiv_H_N, mwArray& PP_X, mwArray& PP_X_N, mwArray& PP_Y, mwArray& PP_Y_N, const mwArray& TrackFile_name, const mwArray& MinLength_Den, const mwArray& MinLength_ParaEst);
					//PrintMessage(_T("调用垂直模式函数！"));
					/*func_Playback_VerticalLookingMode(32,
					mwArray& DenProf_X, mwArray& DenProf_X_N, mwArray& DenProf_Y, mwArray& DenProf_Y_N, mwArray& Orien_X, mwArray& Orien_X_N, mwArray& Orien_Y, mwArray& Orien_Y_N, mwArray& WingBeatFre_X, mwArray& WingBeatFre_X_N, mwArray& WingBeatFre_Y, mwArray& WingBeatFre_Y_N, mwArray& BodyLen_X, mwArray& BodyLen_X_N, mwArray& BodyLen_Y, mwArray& BodyLen_Y_N, mwArray& BodyMass_X, mwArray& BodyMass_X_N, mwArray& BodyMass_Y, mwArray& BodyMass_Y_N, mwArray& WBF_Ind_X, mwArray& WBF_Ind_X_N, mwArray& WBF_Ind_Y, mwArray& WBF_Ind_Y_N, mwArray& HTDiv_X, mwArray& HTDiv_T_N, mwArray& HTDiv_Y, mwArray& HTDiv_H_N, mwArray& PP_X, mwArray& PP_X_N, mwArray& PP_Y, mwArray& PP_Y_N, const mwArray& TrackFile_name, const mwArray& MinLength_Den, const mwArray& MinLength_ParaEst);*/
					
					
				}

				// 扫描模式
				if(toMatlabPara.workingMode == 2)
				{
					func_ScanMode(4, mw_DenProf_X, mw_DenProf_X_N, mw_DenProf_Y, mw_DenProf_Y_N, 
						mw_TrackFile_name, mw_CaliFile_name, mw_StartRan, mw_SampleNum, mw_PRT, mw_PulseWid, mw_WaveForm, mw_CodeType, mw_RCS_ball, mw_Azi_S, mw_Azi_E, mw_Elv_D, mw_Elv_H);
					//PrintMessage(_T("调用扫描模式函数！"));
				}

				//func_NormalMode(int nargout, mwArray& DenProf_X, mwArray& DenProf_X_N, mwArray& DenProf_Y, mwArray& DenProf_Y_N, 
				//mwArray& Orien_X, mwArray& Orien_X_N, mwArray& Orien_Y, mwArray& Orien_Y_N, 
				//mwArray& WingBeatFre_X, mwArray& WingBeatFre_X_N, mwArray& WingBeatFre_Y, mwArray& WingBeatFre_Y_N, 
				//mwArray& BodyLen_X, mwArray& BodyLen_X_N, mwArray& BodyLen_Y, mwArray& BodyLen_Y_N, 
				//mwArray& BodyMass_X, mwArray& BodyMass_X_N, mwArray& BodyMass_Y, mwArray& BodyMass_Y_N, 
				//mwArray& WBF_Ind_X, mwArray& WBF_Ind_X_N, mwArray& WBF_Ind_Y, mwArray& WBF_Ind_Y_N, 
				//mwArray& HTDiv_X, mwArray& HTDiv_T_N, mwArray& HTDiv_Y, mwArray& HTDiv_H_N, 
				//mwArray& PP_X, mwArray& PP_X_N, mwArray& PP_Y, mwArray& PP_Y_N, 
				
				//const mwArray& TrackFile_name, const mwArray& CaliFilePath, const mwArray& StartRan, const mwArray& SampleNum, const mwArray& PRT, const mwArray& PulseWid, const mwArray& WaveForm, const mwArray& CodeType, const mwArray& RCS_ball, const mwArray& MinLength_Den, const mwArray& MinLength_ParaEst, const mwArray& SampleTime);
				
				//mw_Result.GetData(&mx_Result,1);

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

				//发送消息去画图
				//::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg4.m_hWnd, WM_USER+123, (WPARAM)pmx_FreqV_FFT, (LPARAM)&mx_FreqV_FFT_N);
				//return 0;
			}

			else if ((toMatlabPara.mode == 1) && (!b_isTempCountTrack || g_autoCali == 0))	//校准模式
			{
				func_CaliMode(1,mw_Result,mw_TrackFile_name,mw_CaliFile_name,mw_StartRan,mw_SampleNum,mw_PRT,mw_WaveForm,mw_CodeType,mw_MinLength_Cali/*mw_RCS_ball*/);
				mw_Result.GetData(&mx_Result,1);
				//PrintMessage(_T("调用校准函数！"));
			}

			tempiCount++;
			*CString str;
			str.Format(_T("%d"), tempiCount);
			PrintMessage(_T("tempiCount:")+str);*/
			if(tempiCount == /*6*/2 && b_isTempCountTrack && g_autoCali == 1)
			{
				tempiCount = 0;
				tempiTwiceCount++;
				if(tempiTwiceCount == 2 && g_autoCaliMode == 0)	// 两通道同时，需要2次校准
				{
					b_isTempCountTrack = false;	//	
					tempiTwiceCount = 0;
					PrintMessage(_T("b_isTempCount= false！"));
				}
				else if(tempiTwiceCount == 4 && g_autoCaliMode == 1)	// 两通道分时，需要4次校准
				{
					b_isTempCountTrack = false;
					PrintMessage(_T("b_isTempCount= false！"));

					tempiTwiceCount = 0;
				}
			}
			
			//if(b_isTempCountTrack && g_autoCali == 1)
			//{
			//	tempiCount++;
			//	/*CString str;
			//	str.Format(_T("%d"), tempiCount);
			//	PrintMessage(_T("tempiCount:")+str);*/
			//	if(tempiCount == /*6*/2 && b_isTempCountTrack && g_autoCali == 1)
			//	{
			//		tempiCount = 0;
			//		tempiTwiceCount++;
			//		if(tempiTwiceCount == 2 && g_autoCaliMode == 0)	// 两通道同时，需要2次校准
			//		{
			//			b_isTempCountTrack = false;	//	
			//			tempiTwiceCount = 0;
			//			//PrintMessage(_T("b_isTempCount= false！"));
			//		}
			//		else if(tempiTwiceCount == 4 && g_autoCaliMode == 1)	// 两通道分时，需要4次校准
			//		{
			//			b_isTempCountTrack = false;
			//			//PrintMessage(_T("b_isTempCount= false！"));

			//			tempiTwiceCount = 0;
			//		}
			//	}
			//	//PrintMessage(_T("调用内校准函数！" ));
			//	// 内校准函数
			//	//func_InternalCalibration(const mwArray& TrackFile_name, const mwArray& PulseWid, const mwArray& IntCaliType);
			//	func_InternalCalibration(mw_TrackFile_name, mw_PulseWid, mw_IntCaliType);
			//	//PrintMessage(_T("调用内校准函数！" ));
			//}

			//tempiCount++;
			//CString str;
			//str.Format(_T("%d"), tempiCount);
			//PrintMessage(_T("tempiCount:")+str);
			//if(tempiCount == /*6*/2 && b_isTempCountTrack && g_autoCali == 1)
			//{
			//	tempiCount = 0;
			//	tempiTwiceCount++;
			//	if(tempiTwiceCount == 2 && g_autoCaliMode == 0)	// 两通道同时，需要2次校准
			//	{
			//		b_isTempCountTrack = false;	//	
			//		tempiTwiceCount = 0;
			//		PrintMessage(_T("b_isTempCount= false！"));
			//	}
			//	else if(tempiTwiceCount == 4 && g_autoCaliMode == 1)	// 两通道分时，需要4次校准
			//	{
			//		b_isTempCountTrack = false;
			//		PrintMessage(_T("b_isTempCount= false！"));

			//		tempiTwiceCount = 0;
			//	}
			//}

#endif

			g_fifo_track.Free(q);
		}
	}

	return 0;
}

//OriTrackProcess线程
//UINT CSimpleInsectRadarDlg::OriTrackProcessThread(LPVOID lpParam)
//{
//	return ((CSimpleInsectRadarDlg *)lpParam)->OriTrackProcess();
//}

#if 1
mxDouble *pmx_TrackOneMat = NULL;
mxDouble *pmx_CellNum = NULL;
int targetCounts = 9;
int cellNumCounts = 1;
mxInt32 mx_CellNum = 0;
extern bool b_initFuncV2Param; // 初始化FuncV2参数标志
int mx_packFlag = 0;
extern CString VerticalFilePath;
bool bTimer4Flag = true;
mxDouble mx_EmptyFlagIn = 1;
CString TrackFile_name;
int packResult;
int relevantFlag = 0;
int iTimer3Count = 0;
UINT CSimpleInsectRadarDlg::OriTrackProcess(int CPIOut)
{
	// track打包数据
	char trackFileOutputPath[1024] = {0};
	WideCharToMultiByte(trackFilePath, trackFileOutputPath, 1024);	
	mwArray mwSavePath(trackFileOutputPath);

	char oriTrackFileOutputPath[1024] = {0};
	WideCharToMultiByte(CPIFilePath, oriTrackFileOutputPath, 1024);	
	mwArray mw_oriTrackFileOutputPath(oriTrackFileOutputPath);

	mxInt32 mx_ResultTrack = 0;
	mwArray mw_ResultTrack(1, 1, mxDOUBLE_CLASS);
				
	mwArray mw_TrackOneMat(9, 1, mxDOUBLE_CLASS);
	mwArray mw_CellNum(1, 1, mxDOUBLE_CLASS);
	
	mwArray mw_EmptyFlagIn(1, 1, mxDOUBLE_CLASS);
	mwArray mw_EmptyFlag(1, 1, mxDOUBLE_CLASS);
	mwArray mw_relevantFlag(1, 1, mxINT32_CLASS);
	mwArray mw_packResultFlag(1, 1, mxINT32_CLASS);
	mwArray mw_PackName;

	int mx_packFlagTemp = 1;
	mwArray mw_packFlag(1, 1, mxINT32_CLASS);
	mw_packFlag.SetData(&mx_packFlag, 1);
	if(bTimer4Flag)
	{
		//SetTimer(4, 5000, NULL);
		bTimer4Flag = false;
	}
	
	if(CPIOut == 1 || b_initFuncV2Param)
	{
		mwArray mw_Track(9, 1, mxDOUBLE_CLASS);
		mwArray mw_CellNumIn(1, 1, mxDOUBLE_CLASS);
		mw_EmptyFlagIn.SetData(&mx_EmptyFlagIn, 1);
	
		PrintMessage("Start func_Track!");
		func_Track_v2(6, mw_relevantFlag, mw_TrackOneMat, mw_CellNum, mw_EmptyFlag, mw_packResultFlag, mw_PackName,
			mw_Track, mw_CellNumIn, mw_EmptyFlagIn, mw_oriTrackFileOutputPath, mw_packFlag, mwSavePath);
		mx_packFlag = 0;
		PrintMessage("func_Track completed!");

		delete []pmx_TrackOneMat;
		pmx_TrackOneMat = NULL;
		targetCounts = mw_TrackOneMat.NumberOfElements();

		pmx_TrackOneMat = new mxDouble[targetCounts];
		mw_TrackOneMat.GetData(pmx_TrackOneMat, targetCounts);

		delete []pmx_CellNum;
		cellNumCounts = mw_CellNum.NumberOfElements();
		pmx_CellNum = new mxDouble[cellNumCounts];
		mw_CellNum.GetData(pmx_CellNum, cellNumCounts);
		mx_EmptyFlagIn = mw_EmptyFlag.Get(1,1);

		b_initFuncV2Param = false;

		CString str;
		str.Format(_T("%d"), targetCounts);
		PrintMessage("targetCounts："+str);
		str.Format(_T("%d"), cellNumCounts);
		PrintMessage("mx_CellNum："+str);
		PrintMessage("b_initFuncV2Param!");	
	}
	else
	{
		mwArray mw_Track(targetCounts, 1, mxDOUBLE_CLASS);
		mwArray mw_CellNumIn(1, cellNumCounts, mxDOUBLE_CLASS);
		mw_Track.SetData(pmx_TrackOneMat, targetCounts);
		mw_CellNumIn.SetData(pmx_CellNum, cellNumCounts);
		mw_EmptyFlagIn.SetData(&mx_EmptyFlagIn, 1);
		//if(b_initFuncV2Param)
		//{
		//	/*mxInt32 mx_CellNumIn = 1;
		//	mw_CellNumIn.SetData(&mx_CellNumIn, 1);*/
		//	mxDouble mx_EmptyFlagIn = 1;
		//	mw_EmptyFlagIn.SetData(&mx_EmptyFlagIn, 1);
		//	b_initFuncV2Param = false;
		//	PrintMessage("b_initFuncV2Param!");
		//}
		//else
		//{
		//	/*mw_CellNumIn.SetData(&mx_CellNum, 1);	*/
		//	mw_Track.SetData(pmx_TrackOneMat, targetCounts);
		//	mw_CellNumIn.SetData(pmx_CellNum, cellNumCounts);
		//	mw_EmptyFlagIn.SetData(&mx_EmptyFlagIn, 1);
		//}

		PrintMessage("Start func_Track!");
		if(mx_packFlag == 1)
		{
			PrintMessage(_T("开始打包!"));
		}
		/*int mw_TrackCount = mw_Track.NumberOfElements();
		CString str1;
		str1.Format(_T("%d"), mw_TrackCount);
		PrintMessage("TrackOneMatCount："+str1);
		int mw_CellNumInCount = mw_CellNumIn.NumberOfElements();
		str1.Format(_T("%d"), mw_CellNumInCount);
		PrintMessage("CellNumTempCount："+str1);
		int mw_EmptyFlagInTemp = mw_EmptyFlagIn.Get(1,1);
		str1.Format(_T("%d"), mw_EmptyFlagInTemp);
		PrintMessage("EmptyFlagTemp："+str1);*/

		func_Track_v2(6, mw_relevantFlag, mw_TrackOneMat, mw_CellNum, mw_EmptyFlag, mw_packResultFlag, mw_PackName,
			mw_Track, mw_CellNumIn, mw_EmptyFlagIn, mw_oriTrackFileOutputPath, mw_packFlag, mwSavePath);
		packResult = mw_packResultFlag.Get(1, 1);
		if(packResult == 1)
		{
			mwString mx_PackNameTemp = mw_PackName.ToString();
			CString packNameTemp = (CString) mx_PackNameTemp;
			TrackFile_name = trackFilePath + L"\\" + packNameTemp + L".mat";		
			iTimer3Count = 0;
			PrintMessage(L"打包成功!");
		}
		mx_packFlag = 0;
		relevantFlag = mw_relevantFlag.Get(1, 1);
		PrintMessage("func_Track completed!");
		delete []pmx_TrackOneMat;
		pmx_TrackOneMat = NULL;
		targetCounts = mw_TrackOneMat.NumberOfElements();
		pmx_TrackOneMat = new mxDouble[targetCounts];
		mw_TrackOneMat.GetData(pmx_TrackOneMat, targetCounts);
		delete []pmx_CellNum;
		cellNumCounts = mw_CellNum.NumberOfElements();
		pmx_CellNum = new mxDouble[cellNumCounts];
		mw_CellNum.GetData(pmx_CellNum, cellNumCounts);

		mx_EmptyFlagIn = mw_EmptyFlag.Get(1,1);
		/*CString str;
		str.Format(_T("%d"), targetCounts);
		PrintMessage("---targetCounts："+str);
		str.Format(_T("%d"), cellNumCounts);
		PrintMessage("---mx_CellNum："+str);	*/
#if 0
		mxInt32 mx_flag = 0;
		mwArray mw_flag(1, 1, mxINT32_CLASS);
		mw_flag.SetData(&mx_flag, 1);

		char mx_TrackFile_name[1024] = {0};
		WideCharToMultiByte(TrackFile_name, mx_TrackFile_name, 1024);	
		mwArray mw_TrackFile_name(mx_TrackFile_name);

		// 校准文件路径
		char CaliFilePath[1024] = {0};
		CString strTemp = toMatlabPara.s2;
		WideCharToMultiByte(strTemp, CaliFilePath, 1024);
		mwArray mw_CaliFilePath(CaliFilePath);

		mxDouble mx_RCS_ball = 0.0135;
		mwArray mw_RCS_ball(1, 1, mxDOUBLE_CLASS);
		mw_RCS_ball.SetData(&mx_RCS_ball, 1);

		mxDouble mx_MinLength_Den = 50;
		mwArray mw_MinLength_Den(1, 1, mxDOUBLE_CLASS);
		mw_MinLength_Den.SetData(&mx_MinLength_Den, 1);

		mxDouble mx_MinLength_ParaEst = 100;
		mwArray mw_MinLength_ParaEst(1,1,mxDOUBLE_CLASS);
		mw_MinLength_ParaEst.SetData(&mx_MinLength_ParaEst, 1);

		mxDouble mx_SampleTime = 3;
		mwArray mw_SampleTime(1, 1, mxDOUBLE_CLASS);
		mw_SampleTime.SetData(&mx_SampleTime, 1);

		mxDouble mx_IntCali_Enable = 0;
		mwArray mw_IntCali_Enable(1, 1, mxDOUBLE_CLASS);
		mw_IntCali_Enable.SetData(&mx_IntCali_Enable, 1);

		char OutputPathName[1024] = {0};
		WideCharToMultiByte(VerticalFilePath, OutputPathName, 1024);
		mwArray mw_OutputPathName(OutputPathName);
		int packResult = mw_packResultFlag.Get(1, 1);
		if(packResult == 1)
		{
			func_Main_VerticalLookingMode(1, mw_flag, 
				mw_TrackFile_name, mw_CaliFilePath, mw_RCS_ball, mw_MinLength_Den, 
				mw_MinLength_ParaEst, mw_SampleTime, mw_IntCali_Enable, mw_OutputPathName);
			mx_packFlag = 0;
		}
#endif
	}
	return 0;
}
#endif



// 数据分类
void CSimpleInsectRadarDlg::DisplaySoftDataProcessing(byte* p, UINT len)
{
	UINT nDataType = *((UINT *)p);     //解析反馈数据类型码

	switch(nDataType)
	{
	case 0x94EF032B:
		// 配置参数
		g_tcpClient.Send(p, len);
		break;
	case 0x94EF0127:
		// 配置参数MATLAB		
		toMatlabPara.RCS_ball = *((double*)(p+1024*2+10));
		toMatlabPara.dlMinLength_Den = *((double*)(p+1024*2+18));
		toMatlabPara.dlMinLength_ParaEst = *((double*)(p+1024*2+26));
		toMatlabPara.SampleTime = *((double*)(p+1024*2+34));
		toMatlabPara.dlMinLength_ParaEst = *((double*)(p+1024*2+42));
		toMatlabPara.enableAutoCali = *((double*)(p+1024*2+50));
		break;
	case 0x94EF0329:
		// 控制指令
		//DisplaySoftCmdProcessing(p, len);		   //指令反馈解
		//g_tcpClient.Send(p, len);   //开始工作，停止工作
		m_formDlg1.OnBnClickedButton3();
		break;
	case 0x94EF032D:
		// 开始存储
		//g_tcpClient.Send(p, len);   //开始存储指令 + 存储起始地址，停止存储
		m_formDlg1.OnBnClickedButton4();
		break;
	case 0x94EF0111:
		// 文件存储选项
		
		break;
	case 0x94EF0129:
		// 回放
		
		break;
	}
}


//数据分类
bool b_autoCaliFlag = false;	// 内校准模式标志
bool b_isStopStoreFlag = false;
//bool b_tempFlag_paracfg = false;
bool b_isCountTrack = true;
static int iCount = 0;
/*static*/ int iTwiceCount = 0;
static int iChunZhiCount = 0;
bool b_isSimulateClickBtn = false;
bool b_isTenMinWorktFlag = false;
bool b_isTenMinWork = false;
bool b_isTrackFlag = false;
bool b_isWorkStoreFlag = false;	// 单点开始工作，不点击开始存储就停止工作标志
bool b_isTimerOutFlag = false;	// timer 2定时器终止时间触发标志
int iCountCirculations = 0;		// 内校准循环次数计数
bool b_isStopCountCirculations = false;	// 内校准循环终止标志

bool b_isSlowScanFlag = false; // 慢扫模式状态

extern bool b_isManualClickBtn;

extern bool b_isSetTimeThreadFlag;
void CSimpleInsectRadarDlg::DataProcessing(byte *p, UINT len)
{
	UINT nDataType = *((UINT *)p);     //解析反馈数据类型码
	
	switch (nDataType)
	{
	case 0x94EF0329:				   
		CmdProcessing(p, len);		   //指令反馈解析
#if DFLAG
		g_tcpDisplaySoftClient.Send(p, len); // 一维距离像数据转发给显控
#endif
		break;
	case 0x94EF032B:    
		g_udpClientCmdFeedBack.Send(p, len);// 反馈至显控
		RadarParaProcessing(p, len);   //配置参数反馈解析
		g_bflag_paracfg = true;
		if((b_tempFlag_paracfg && g_autoCali == 1) || isAutoClickStartWorkButton)
		{			
			Sleep(2000);
			//PrintMessage(_T("点击开始工作~~~"));
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+891, NULL, NULL);	// 点击开始工作按钮
			//isAutoClickStartWorkButton = false;
			//::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+890, NULL, NULL);	// 开始存储
			//b_tempFlag_paracfg = false;
		}
		if(g_autoCali == 1)
		{
			iCount = 0;
			tempiCount = 0;
			b_isStopStoreFlag = true;
			b_autoCaliFlag = true;
		}
		else if(g_autoCali == 0)
		{
			b_autoCaliFlag = false;
		}
		if(b_isOkBtnParaConfig)	// 手动配置参数情况下
		{
			b_isCountTrack = true;	// 如果不是在定时中，开始2个track停止的流程
			//b_isTempCountTrack = true;
			b_isOkBtnParaConfig = false;
			//b_isStopStoreFlag = true;
			b_isTenMinWork = false;
			b_isTenMinWorktFlag = false;
			b_isSimulateClickBtn = false;
			iTwiceCount = 0;
			tempiTwiceCount = 0;
			iCountCirculations = 0;
			KillTimer(2);
			b_isManualClickBtn = false;
			b_isSetTimeThreadFlag = false;

			if(g_autoCali == 1)
			{
				b_isStopStoreFlag = true;
				b_isTempCountTrack = true;
			}

			if(g_workMode == 1)	// 定时模式，启动计数线程
			{
				//TRACE("%d\n", g_workMode);
				AfxBeginThread(countThread, this);
			}
			if(g_autoCaliMode == 0)
			{
				toMatlabPara.UintCaliType = 5;
				tempRadarPara.nPara_13 = 1;
				tempRadarPara.nPara_14 = 160;
			}
			else if(g_autoCaliMode == 1)
			{
				toMatlabPara.UintCaliType = 1;
				tempRadarPara.nPara_13 = 1;
				tempRadarPara.nPara_14 = 32;
			}
			if(b_isTempCountTrack && g_autoCali == 1)
			{
				tempRadarPara.nPara_13 = 1;
				g_nPara_7 = 0;	// 起始采样距离为0
				toMatlabPara.StartRan = 0;	// 起始采样距离
				tempRadarPara.nPara_7 = 0;	// 起始采样距离-to DSP----交替模式下主波形起始采样距离
				tempRadarPara.nPara_dptInitSampDist = 0; // 交替模式下副波形起始采样距离
				tempRadarPara.nPara_48 = 0.5;	// 单次采集时间 0.5
			}
			//debug
			/*CString str;
			str.Format(_T("%.2f"), tempRadarPara.nPara_48);
			PrintMessage("单次采集时间：" +str);
			str.Format(_T("%.2f"), toMatlabPara.StartRan);
			PrintMessage("起始采样距离：" +str);*/

		}
		break;
	case 0x94EF0331:
		HRRPProcessing(p, len);		   //一维距离像和系统工作状态解析
#if DFLAG
		g_tcpDisplaySoftClient.Send(p, len); // 一维距离像数据转发给显控
#endif
		break;
	case 0x94EF032D:				   //指令反馈——停止存储
		{
			PrintMessage(_T("停止存储数据"));
			//logFile.WriteLog(_T("收到停止存储反馈！"));
			//g_workMode = 1;
			int b = TRUE;
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+779, (WPARAM)&b, NULL);
			PostMessage(WM_USER+111, (WPARAM)p, (LPARAM)&len);

			if(b_isTimerOutFlag)
			{
				iCountCirculations++;	// 每经过一次内校准循环增加一次
				b_isCountTrack = true;
				b_isTempCountTrack = true;
				iCount = 0;
				tempiCount = 0;
				//PrintMessage(_T("2分钟到！"));
				/*b_isTenMinWork = false;
				b_isTenMinWorktFlag = false;*/
				
				if(g_autoCali == 1)
				{
					b_autoCaliFlag = true;
				}
				else if(g_autoCali == 0)
				{
					b_autoCaliFlag = false;
				}
				b_isTimerOutFlag = false;
			}

			
			// 开始上传数据
			if((g_zhuanCun == 1) && (iCountCirculations == g_zhuanCunTime) && (g_workMode == 1) && (g_autoCali == 1))
			{
				b_isWorkStoreFlag = true;	// 不再继续配置参数，继续下个内校准循环
				b_isStopCountCirculations = true;	// 内校准循环计数终止标志，下边开始转存数据操作
			}

			if(g_stopWorkFlag == 1)
			{
				//PrintMessage(_T("点击停止工作~~~"));
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+889, NULL, NULL);	// 开始、停止工作
			}
			if(/*b_isStopStoreFlag*//*g_autoCali == 1*/ b_autoCaliFlag) // 内校准模式和慢扫模式
			{
				//b_isSimulateClickBtn = true;
				//PrintMessage(_T("点击停止工作~~~"));
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+891, NULL, NULL);	// 停止工作
			}
#if DFLAG
			g_tcpDisplaySoftClient.Send(p, len); // 一维距离像数据转发给显控
#endif
			break;
		}
		
	//case 0x8d8d8d8d:
	//	PrintMessage(_T("开始存储数据"));
	//	break;
	case 0x9e9e9e9e:
		{
			g_bWritingFile = true;    //标志位——开始上传
			//m_pWriteFileThread->ResumeThread();
			PrintMessage(_T("开始上传数据"));
#if DFLAG
			g_tcpDisplaySoftClient.Send(p, len); // 一维距离像数据转发给显控
#endif
			break;
		}
		
	//case 0xafafafaf :
	//	PrintMessage(_T("停止上传数据"));
	//	PostMessage(WM_USER+111, (WPARAM)p, (LPARAM)&len);
	case 0x94EF0333: // 点迹数据反馈码
		{
			/*static int iChunZhiCount = 0;*/
			if(toMatlabPara.workingMode == 3)
			{
				
				if(iChunZhiCount % 2 == 0)
				{
					g_nPara_7 = tempRadarPara.nPara_dptInitSampDist * 15;// 副波形起始采样距离60
					//m_formDlg3.IFFT_tchart1();
				}
				else
				{
					g_nPara_7 = tempRadarPara.nPara_7 * 15; // 150
					//m_formDlg3.IFFT_tchart1();
				}
				iChunZhiCount++;
				/*CString str;
				str.Format(_T("%d"), g_nPara_7);
				PrintMessage(str);*/
				
			}
			else
			{
				iChunZhiCount = 0;
			}
			b_isSimulateClickBtn = false;	// 是否处于两个track就停止工作的状态
			DetectProcessing(p, len);		//Track数据——用于MATLAB计算用
			CString str;
			static int i = 0;
			//static int iCount = 0;
			//static int iTwiceCount = 0;
			iCount++;
			i++;
			str.Format(_T("track_%d"), i);
			//PrintMessage(str);
			b_isTrackFlag = true;

			// 过两个track就停止存储
			if(iCount == /*6*/2 && b_isCountTrack && g_autoCali == 1)
			{
				b_isSimulateClickBtn = true;
				//PrintMessage(_T("点击停止存储~~~"));
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+890, NULL, NULL);	// 停止存储
				b_isStopStoreFlag = true;
				
				iCount = 0;
				iTwiceCount++;
				if(iTwiceCount == 2 && g_autoCaliMode == 0)	// 两通道同时，需要2次校准
				{
					b_isCountTrack = false;	// 停止两个track限制
					iTwiceCount = 0;
					b_isTenMinWorktFlag = true;
				}
				else if(iTwiceCount == 4 && g_autoCaliMode == 1)	// 两通道分时，需要4次校准
				{
					b_isCountTrack = false;	// 停止两个track限制
	
					iTwiceCount = 0;
					b_isTenMinWorktFlag = true;
				}
			}
#if DFLAG
			g_tcpDisplaySoftClient.Send(p, len); // 一维距离像数据转发给显控
#endif
			break;
		}
	case 0x22334455:
		{
			TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
			GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
			(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
			//wcscpy(gszSettingPath , szModulePath);
			wcscat(szModulePath , _T("OriData.bin"));
			HANDLE hFile = CreateFile(/*_T("123.bin")*/szModulePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			DWORD dwWrites;
			bool bRet = WriteFile(hFile, p, len, &dwWrites, NULL);
			CloseHandle(hFile);

			delete []p;
			p = NULL;
			break;
		}
	default:
		//ASSERT(false);
		CloseHandle(m_hFile);
		break;
	}
}

//UINT CSimpleInsectRadarDlg::pressStopWorkButtonProcess(LPVOID lParam)
//{
//	return ((CSimpleInsectRadarDlg *)lParam)->pressStopWorkButton();
//}
//
//UINT CSimpleInsectRadarDlg::pressStopWorkButton()
//{
//	::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+889, NULL, NULL);
//	return 0;
//}

// 显控软件下发指令解析
void CSimpleInsectRadarDlg::DisplaySoftCmdProcessing(byte* p, UINT len)
{
	UINT nCmdType = *((UINT *)(p + 8));
	switch(nCmdType)
	{
	case 0x01:		    //指令反馈——自检		
		PrintMessage(_T("自检完毕"));
		break;
	case 0x03:
		// 开始工作
		m_formDlg1.OnBnClickedButton3();
		break;
	case 0x04:
		// 停止工作
		m_formDlg1.OnBnClickedButton3();
		break;
	case 0x06:
		// 停止存储
		m_formDlg1.OnBnClickedButton4();
		break;
	case 0x0a:
		// 停止上传
		break;
	}
	delete []p;
	p = NULL;
}


//指令反馈解析
//extern RadarPara tempRadarPara;


extern UINT tempDptInitSampDist;
extern UINT tempStartRan;

extern bool b_isTimeOutFlag;

int verticalOrSlowScanCount = 0;

void CSimpleInsectRadarDlg::CmdProcessing(byte *p, UINT len)
{
	UINT nCmdType = *((UINT *)(p + 8));
	g_udpClientCmdFeedBack.Send(p, len);
	switch (nCmdType)
	{
	case 0x01:		    //指令反馈——自检		
		PrintMessage(_T("自检完毕"));
		break;
	case 0x02:			//指令反馈——参数配置	
		PrintMessage(_T("参数配置完毕"));
		g_bflag_paracfg = true;
		break;
	case 0x03:			//指令反馈——开始工作
		{		
			PrintMessage(_T("开始工作"));
			//g_startWorkFlag = 1;
			b_isWorkStoreFlag = true;
			g_bflag_paracfg = false;
			g_bflag_enable = false;		//开始工作后此标志位false，忽略参数配置的确定按钮
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+223, NULL, NULL);
			if(b_tempFlag_paracfg && g_autoCali == 1)	// 自动模式，模拟发消息
			{
				Sleep(3000);
				//PrintMessage(_T("点击开始存储~~~"));
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+890, NULL, NULL);	// 开始存储
				b_tempFlag_paracfg = false;	// 配置参数标志
				if(b_isTenMinWorktFlag)	// 如果开始10分钟标志为真，启动计时
				{
					if(g_slowScan == 1) // 慢扫模式
					{
						if(verticalOrSlowScanCount & 1)
						{
							PrintMessage(_T("10S"));
							PrintMessage(_T("慢扫~~~"));
							SetTimer(2, 10000, NULL);
						}
						else
						{
							PrintMessage(_T("15S"));
							PrintMessage(_T("垂测~~~"));
							SetTimer(2, 15000, NULL);
						}
					}
					else
					{
						SetTimer(2, 10000, NULL);
					}					
					b_isTenMinWork = true; 
				}
				
			}

			if(isAutoClickStartWorkButton && g_autoCali == 0)
			{
				Sleep(3000);
				//PrintMessage(_T("点击开始存储~~~"));
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+890, NULL, NULL);	// 开始存储

			}
			//if(g_slowScan == 1) // 满扫模式
			//{

			//}
			break;
		}
	case 0x04:			//指令反馈——停止工作
		{
			PrintMessage(_T("停止工作"));
			//logFile.WriteLog(_T("收到停止工作反馈！"));
			memset(pTemp, 0, HRRPBUFFERSIZE);
			g_bflag_enable = true;
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+224, NULL, NULL);

			// 开始转存
			if(b_isStopCountCirculations)
			{
				// 发送消息开始转存数据
				::SendMessage(m_formDlg2.m_hWnd, WM_USER+892, NULL, NULL);
				//PrintMessage(_T("发送点击开始上传按钮消息！"));
			}

			if((g_workMode == 1 && !b_isWorkStoreFlag && b_isTimeOutFlag) || (b_isStopStoreFlag && !b_isWorkStoreFlag) /*|| g_slowScan == 1*//* || isAutoClickStartWorkButton*/)	// 配置参数
			{
				PrintMessage(_T("自动配参！！！"));
				if((b_isManualClickBtn && g_autoCali == 1) /*|| b_isCountTrack*/)
				{
					b_isTempCountTrack = true;
				}
				CString str;
				
				//b_isTempCountTrack = true;

				if(toMatlabPara.workingMode == 3)
				{
					if(iChunZhiCount % 2 == 0)
					{
						g_nPara_7 = tempRadarPara.nPara_dptInitSampDist * 15;
						str.Format(_T("%d"), g_nPara_7);
						PrintMessage(_T("g_nPara_7")+str);
						//m_formDlg3.IFFT_tchart1();
					}
					else
					{
						g_nPara_7 = tempRadarPara.nPara_7 * 15;
						str.Format(_T("%d"), g_nPara_7);
						PrintMessage(_T("g_nPara_7")+str);
						//m_formDlg3.IFFT_tchart1();
					}
				}

				if(b_isTempCountTrack && g_autoCali == 1)	// 自动内校准模式
				{
					tempRadarPara.nPara_7 = 0;	// 起始采样距离为0---给dsp发送需要置0吗？
					tempRadarPara.nPara_dptInitSampDist = 0; // 交替模式下副波形起始采样距离
					toMatlabPara.StartRan = 0;
					g_nPara_7 = 0;			
					tempRadarPara.nPara_48 = 0.5;	// 单次采样时间0.5
					str.Format(_T("%d"), g_nPara_7);
					//PrintMessage(_T("g_nPara_7")+str);
				}
				else if(b_isTenMinWorktFlag) // 非内校准模式下
				{
					tempRadarPara.nPara_7 = tempnPara_7;	// 非自动校准模式下为实际值
					tempRadarPara.nPara_dptInitSampDist = tempDptInitSampDist;
					toMatlabPara.StartRan = tempStartRan;
					if(!(toMatlabPara.workingMode == 3))
					{
						g_nPara_7 = tempStartRan;
					}
					else
					{
						if(iChunZhiCount % 2 == 0)
						{
							g_nPara_7 = tempRadarPara.nPara_dptInitSampDist * 15;
							//m_formDlg3.IFFT_tchart1();
						}
						else
						{
							g_nPara_7 = tempRadarPara.nPara_7 * 15;
							//m_formDlg3.IFFT_tchart1();
						}
					}
					
					str.Format(_T("%d"), g_nPara_7);
					//PrintMessage(_T("g_nPara_7")+str);	
					tempRadarPara.nPara_48 = tempnPara_48; 
				}
				
				// debug
				/*CString str;
				str.Format(_T("%.2f"), tempRadarPara.nPara_48);
				PrintMessage("单次采集时间："+str);*/

				// 两通道同时的2个校准指令
				if(iTwiceCount == 0 && g_autoCaliMode == 0)
				{
					tempRadarPara.nPara_13 = 0;
					//tempRadarPara.nPara_7 = 0;	// 起始采样距离-0-dsp
					//toMatlabPara.StartRan = 0;	// 起始采样距离-0-matlab
					tempRadarPara.nPara_14 = 160;	// 101
					toMatlabPara.UintCaliType = 5;	
				}
				else if(iTwiceCount == 1 && g_autoCaliMode == 0)
				{
					tempRadarPara.nPara_13 = 0;
					//tempRadarPara.nPara_7 = 0;
					//toMatlabPara.StartRan = 0;	// 起始采样距离-0-matlab
					tempRadarPara.nPara_14 = 192;	// 110
					toMatlabPara.UintCaliType = 6;				
				}				
				else
				{
					tempRadarPara.nPara_7 = tempnPara_7;	// 非校准模式下为实际值-起始采样距离
					toMatlabPara.StartRan = tempStartRan;
				}

				// 两通道分时的4个校准指令
				if(iTwiceCount == 0 && g_autoCaliMode == 1)
				{
					tempRadarPara.nPara_13 = 1;
					
					tempRadarPara.nPara_14 = 32;	// 001
					tempRadarPara.nPara_detectionChannel = 0; // HH通道校准，发射1校准
					toMatlabPara.UintCaliType = 1;
				}
				else if(iTwiceCount == 1 && g_autoCaliMode == 1)
				{
					tempRadarPara.nPara_13 = 1;
	
					tempRadarPara.nPara_14 = 64;	// 010
					tempRadarPara.nPara_detectionChannel = 1; // HV通道校准，发射2校准
					toMatlabPara.UintCaliType = 2;

					
				}
				else if(iTwiceCount == 2 && g_autoCaliMode == 1)
				{
					
					tempRadarPara.nPara_13 = 0;
					
					tempRadarPara.nPara_14 = 96;	// 011
					tempRadarPara.nPara_detectionChannel = 0; // HH通道校准，接收1校准
					toMatlabPara.UintCaliType = 3;

					
				}
				else if(iTwiceCount == 3 && g_autoCaliMode == 1)
				{
					tempRadarPara.nPara_13 = 1;
					//tempRadarPara.nPara_7 = 0;
					//toMatlabPara.StartRan = 0;	// 起始采样距离-0-matlab
					tempRadarPara.nPara_14 = 128;	// 100
					tempRadarPara.nPara_detectionChannel = 2; // VH通道校准，接收2校准
					toMatlabPara.UintCaliType = 4;

					
				}
				

				/*str.Format(_T("%.2f"), tempRadarPara.nPara_14);
				PrintMessage("配参校准指令："+str);*/
				if(b_isTenMinWorktFlag)
				{
					tempRadarPara.nPara_14 = 0;
					tempRadarPara.nPara_13 = 0;	// 正常工作模式下校准通道使能置为0

					tempRadarPara.nPara_7 = tempnPara_7;	// 非校准模式下为实际值-起始采样距离
					toMatlabPara.StartRan = tempStartRan;

					// 伺服参数配置
					if(verticalOrSlowScanCount & 1) // 慢扫模式:伺服工作方式配置单程二维扫模式
					{
						tempRadarPara.nPara_15 = 7;// 天线转动模式：定位模式
						tempRadarPara.nPara_16 = 6;// 俯仰波段数
						tempRadarPara.nPara_18 = -180;// 方位起始角度
						tempRadarPara.nPara_19 = 180;// 方位终止角度
						tempRadarPara.nPara_21 = 10;// 俯仰起始角度
						tempRadarPara.nPara_22 = 82;// 俯仰终止角度
						tempRadarPara.nPara_20 = 15;// 方位向扫描速度
						tempRadarPara.nPara_23 = 15;// 俯仰向扫描速度
						PrintMessage(_T("慢扫模式-俯仰向扫描速度：15"));	
					}
					else // 内校准模式、垂测模式：伺服工作模式配置定位模式
					{
						tempRadarPara.nPara_15 = 2;// 天线转动模式：定位模式
						tempRadarPara.nPara_21 = 90; // 俯仰起始角度
						PrintMessage(_T("垂测-俯仰角度：90"));	
					}
				}
				else
				{
					tempRadarPara.nPara_7 = 0;	// 校准模式下为实际值-起始采样距离
					toMatlabPara.StartRan = 0;
				}

				if(/*g_autoCali == 1*/ b_autoCaliFlag)
				{
					b_tempFlag_paracfg = true;	// 内校准自动开始工作标志
				}
				if((b_isSetTimeThreadFlag || g_autoCali == 0) && g_workMode == 1)	// 启动定时模式
				{
					AfxBeginThread(countThread, this);
				}

				// 配置参数
				//PrintMessage(_T("自动配置参数！"));
				Sleep(1000);
				
			
			
				int tt = 0;
				tt = g_tcpClient.Send((byte *)(&tempRadarPara), sizeof(tempRadarPara));
				//GetData_ToMatlab(toMatlabPara);
				CString str01;
				str01.Format(_T("%d"), tempRadarPara.nPara_7);
				PrintMessage("起始采样距离："+str01);

				if (tt == sizeof(tempRadarPara))
				{
					::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+400, NULL, NULL);
					//GetData_ToMatlab(toMatlabPara);
				}
				

				b_isTimeOutFlag = false;	// 定时模式时间到标志位
				
				if(b_isManualClickBtn)	// 处于两个track计时状态，每次自动配置参数将计数器置为0
				{
					b_isCountTrack = true;	// 如果不是在定时中，开始2个track停止的流程
					b_isTempCountTrack = true;
					b_isOkBtnParaConfig = false;
					b_isStopStoreFlag = true;
					b_isTenMinWork = false;
					b_isTenMinWorktFlag = false;
					b_isSimulateClickBtn = false;
					iTwiceCount = 0;
					tempiTwiceCount = 0;
					KillTimer(2);
					iCount = 0;
					tempiCount = 0;
					//g_autoCali = 1;
					//iTwiceCount = 0;
					b_isManualClickBtn = false;
					b_isSetTimeThreadFlag = false;
				}	
			}
			break;
		}
		
	case 0x05:			//指令反馈——开始存储
		{
			PrintMessage(_T("开始存储"));
			b_isWorkStoreFlag = false;
			int b = FALSE;
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+779, (WPARAM)&b, NULL);
			break;
		}
	case 0x06:			//指令反馈——停止存储
		{
			PrintMessage(_T("停止存储"));
			//logFile.WriteLog(_T("收到停止存储反馈！"));
			//m_criticalsectionStop.Lock();
			//g_bisStopSave = false;
			//m_criticalsectionStop.Unlock();
			int b = TRUE;
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+779, (WPARAM)&b, NULL);
			break;
		}
	case 0x07:			//指令反馈——开环校准
		PrintMessage(_T("开环校准"));
		break;
	case 0x08:			//指令反馈——闭环校准
		PrintMessage(_T("闭环校准"));
		break;
	case 0x09:
		PrintMessage(_T("开始上传数据"));

		g_bWritingFile = true;
		//m_pWriteFileThread->ResumeThread();

		//PrintMessage(_T("开始上传数据"));
		break;
	case 0x0a:			//指令反馈——停止上传数据		
		PrintMessage(_T("停止上传数据"));
		
		g_bWritingFile = false;   //标志位——停止上传
		
		break;
	case 0x0b:			//指令反馈——数据擦除
		PrintMessage(_T("数据擦除成功"));
		break;
	default:
		//ASSERT(false);
		PrintMessage(_T("回馈信息有误！！！"));
		break;
	}

	delete []p;
	p = NULL;
}


//配置参数反馈解析
void CSimpleInsectRadarDlg::RadarParaProcessing(byte *p, UINT len)
{
	//RadarPara radaPara = {0};
	//memcpy(&radaPara, p, sizeof(radaPara));
	//m_formDlg1.m_dlgParaConfig.m_radarPara
	//while()
	//{
	PrintMessage(_T("参数配置完毕！！！"));
	//}
	delete []p;
	p = NULL;

	// 启动计数线程
	//if(g_workMode == 1)
	//{
	//	//TRACE("%d\n", g_workMode);
	//	AfxBeginThread(countThread, this);
	//}
}

UINT CSimpleInsectRadarDlg::countThread(LPVOID lParam)
{
	return ((CSimpleInsectRadarDlg *)lParam)->countProcess();	
}

UINT CSimpleInsectRadarDlg::countProcess()
{
	while(g_workMode)
	{
		// 获取当前系统时间
		SYSTEMTIME curSystemTime;
		GetLocalTime(&curSystemTime);
		
		//TRACE("%d\n", curSystemTime.wMinute);
		if((curSystemTime.wHour == setTimeInfo.iStartHour) && (curSystemTime.wMinute == setTimeInfo.iStartMinute) 
			&& curSystemTime.wSecond == setTimeInfo.isStartSecond /*&& curSystemTime.wMilliseconds == setTimeInfo.iStartMilliseconds*/)
		{
			// 发消息，模拟点击开始按钮
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+888, NULL, NULL);
			//PrintMessage(_T("时间到，开始工作！"));
			//logFile.WriteLog(_T("SendMessage---开始工作，开始存储"));
			break;
		}
		Sleep(1);
		OutputDebugString(_T("获取时间！\n"));
	}

	return 0;
}


//一维距离像和系统工作状态
void CSimpleInsectRadarDlg::HRRPProcessing(byte *p, UINT len)
{
	//static DWORD t1 = 0;
	//DWORD t2 = GetTickCount();

	m_criticalsection.Lock();
	PrintMessage(_T("HRRPProcessing！"));
	memcpy(pTemp, p, len);				//将接收到的数据复制到全局缓存中，用于画图显示

	m_criticalsection.Unlock();
#if 1
	// 一维距离像存储
#if 0
	CString strSystemTime, strSystemTimePath;
	strSystemTime = m_commonFun.ComFunGetSystemTime(7);
	strSystemTimePath = m_commonFun.ComFunGetSystemTime(3);
#endif
	SYSTEMTIME curSystemTime;
	GetLocalTime(&curSystemTime);

	CString strSystemTime, strSystemTimePath, HRRPFilePathTemp;
	strSystemTime = m_commonFun.ComFunGetSystemTime(7);
	strSystemTimePath = m_commonFun.ComFunGetSystemTime(3);
	/*strSystemTime.Format(L"%4d_%02d_%02d_%02d_%02d_%02d_%03d", 
		curSystemTime.wYear, curSystemTime.wMonth, curSystemTime.wDay, 
		curSystemTime.wHour, curSystemTime.wMinute, curSystemTime.wSecond, curSystemTime.wMilliseconds);
	strSystemTimePath.Format(L"%4d_%02d_%02d_%02d", 
		curSystemTime.wYear, curSystemTime.wMonth, curSystemTime.wDay, 
		curSystemTime.wHour);*/
	HRRPFilePathTemp = HRRPFilePath + "//" + strSystemTimePath;
	if(!PathIsDirectory(HRRPFilePathTemp))
	{
		CreateDirectory(HRRPFilePathTemp, 0); // 不存在路径就创建
	}
	CString hrrpFile = HRRPFilePathTemp + "//Hrrp_" + strSystemTime + ".bin";
	HANDLE hHrrpFile = CreateFile(hrrpFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dHrrpWrites;
	WriteFile(hHrrpFile, pTemp, len, &dHrrpWrites, NULL);
	timeStruct.head = 0x94EF0113;
	timeStruct.year = curSystemTime.wYear;
	timeStruct.month = curSystemTime.wMonth;
	timeStruct.day = curSystemTime.wDay;
	timeStruct.hour = curSystemTime.wHour;
	timeStruct.minute = curSystemTime.wMinute;
	timeStruct.second = curSystemTime.wSecond;
	timeStruct.millisecond = curSystemTime.wMilliseconds;
	timeStruct.tail = 0x95F00114;
	g_udpClientCmdFeedBack.Send((byte *)&timeStruct, sizeof(timeStruct));
	PrintMessage(_T("HRRPProcessing-------！"));
	HRRPFilePathTemp = "";
	CloseHandle(hHrrpFile);
#endif
	//if (t2 - t1 > 100)
	//{
	//	if (!g_bWritingFile)
	//	{
	//		//向雷达显控界面发送消息
	//		::SendMessage(m_formDlg1.m_hWnd, UPDATEFORMDLG1_UI, (WPARAM)p, (LPARAM)&len);
	//	}
	//	else if (g_bWritingFile)
	//	{
	//		//向数据上传界面发送消息
	//		::SendMessage(m_formDlg2.m_hWnd, UPDATEFORMDLG2_UI, (WPARAM)p, (LPARAM)&len);
	//	}
	//	
	//	t1 = t2;
	//}

	delete []p;

	p = NULL;
}


void CSimpleInsectRadarDlg::DetectProcessing(byte *p, UINT len)
{
	//m_criticalsection.Lock();

	//memcpy(pTemp, p, len);				//将接收到的数据复制到全局缓存中，用于画图显示

	//m_criticalsection.Unlock();

	byte *q = NULL;
	while((q = g_fifo_track.Alloc()) == NULL);
	memcpy(q, p, len);
	g_fifo_track.Push(q);

	delete []p;

	p = NULL;
}


//没用到--SATA反馈的存储结束地址
void CSimpleInsectRadarDlg::SATAEndAddress(byte *p, UINT len)
{
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("FileListInfo.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file;
	file.Open(strModulePath, CFile::modeCreate | CFile::modeWrite);

	ULONGLONG ulEndAddress = *((unsigned long long *)(p + 8));
	if (theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetSize())  
	{
		FILELISTINFO *q = (FILELISTINFO *)theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetTail();
		q->EndAddress = ulEndAddress;

		POSITION pos = theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetTailPosition();
		while (pos != NULL)
		{
			FILELISTINFO *p = (FILELISTINFO *)theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetPrev(pos);
			file.Write(p, sizeof(FILELISTINFO));

			//更新显示
			CString strFileName;
			strFileName.Format(_T("%.4d_%.2d_%.2d-%.2d_%.2d_%.2d.dat"),
				p->systime.wYear, p->systime.wMonth, p->systime.wDay, 
				p->systime.wHour, p->systime.wMinute, p->systime.wSecond);

			theApp.m_pMainDlg->m_filelist.InsertItem(0, strFileName);  //更新文件名;
			ULONGLONG uEachFileSize = ((p->EndAddress) - (p->BeginAddress)) / (1024 * 1024);
			CString strEachFileSize;
			strEachFileSize.Format(_T("%d"), uEachFileSize);
			theApp.m_pMainDlg->m_filelist.SetItemText(0, 1, strEachFileSize);  //更新文件大小
		}
	}

	file.Close();
}

//创建文件
bool CSimpleInsectRadarDlg::CreateFileEx()
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	CString str;
	str.Format(_T("%.4d_%.2d_%.2d_%.2d_%.2d_%.2d.dat"), sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour,sysTime.wMinute, sysTime.wSecond);
	m_strFileName = m_formDlg2.m_szSavePath + str;
	//m_bIsFileExist = m_file.Open(m_strFileName, CFile::modeCreate | CFile::modeWrite);

	return m_bIsFileExist;
}


//点击文件列表右键响应
void CSimpleInsectRadarDlg::OnNMRClickListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//获取鼠标坐标
	CPoint ptCurSel(0, 0);
	GetCursorPos(&ptCurSel);

	NMLISTVIEW  *pNMListView = (NMLISTVIEW *)pNMHDR;

	//如果有选中项
	if (pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point (LOWORD(dwPos), HIWORD(dwPos));
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU2));
		CMenu *popup = menu.GetSubMenu(0);
		ASSERT(popup!=NULL);
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}

	*pResult = 0;
}


extern bool b_flag4;
//导出文件
void CSimpleInsectRadarDlg::OnReadfile()
{
	m_fileSelectedArray.RemoveAll();

	int totalCnt = m_filelist.GetItemCount();

	//检测被选中的项，并记录
	for (UINT i=0; i<totalCnt; i++)				
	{
		if (m_filelist.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			m_fileSelectedArray.Add(i);
		}
	}

	if (m_fileSelectedArray.GetSize() == 1)
	{
		m_PullFileCfgDlg.DoModal();
	}
	else if (m_fileSelectedArray.GetSize() > 1)
	{
		MessageBox(_T("不接受多于一个被选项的鼠标右键相应"));
	}

	m_fileSelectedArray.RemoveAll();

	//CPullFileCfg m_PullFileCfgDlg;
	//m_PullFileCfgDlg.DoModal();
	//if (!m_PullFileCfgDlg.m_hWnd)
	//{
	//	m_PullFileCfgDlg.Create(IDD_DIALOG1);
	//}
	//m_PullFileCfgDlg.ShowWindow(TRUE);

	//g_bWritingFile = true;
	//int n = m_fileSelectedArray.GetCount();
	//b_flag4 = true;
	//theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON8)->SetWindowTextW(_T("停止上传"));
	//
	//if (!m_pWriteFileThread)
	//{
	//	//m_pWriteFileThread->ResumeThread();
	//	m_pWriteFileThread = AfxBeginThread(WriteFileThread, this); //创建读文件线程
	//}
	
}


afx_msg LRESULT CSimpleInsectRadarDlg::OnUser777(WPARAM wParam, LPARAM lParam)
{

	g_bWritingFile = true;
	int n = m_fileSelectedArray.GetCount();
	b_flag4 = true;
	//theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON8)->SetWindowTextW(_T("停止上传"));
	theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
	
	if (!m_pWriteFileThread)
	{
		//m_pWriteFileThread->ResumeThread();
		m_pWriteFileThread = AfxBeginThread(WriteFileThread, this); //创建读文件线程
	}

	return 0;
}

//写单个文件线程
UINT CSimpleInsectRadarDlg::WriteFileThread(LPVOID lpParam)
{
	return ((CSimpleInsectRadarDlg *)lpParam)->WriteProcess();
}


//写单个文件任务
UINT CSimpleInsectRadarDlg::WriteProcess()
{
	int nFileCount = m_fileSelectedArray.GetSize();   //得到需要上传文件的个数

	for (int i=0; i<nFileCount; i++)
	{
		if (g_bWritingFile)
		{
			//提取文件链表特定位置元素
			m_nItem = m_fileSelectedArray.GetAt(i);
			POSITION pos;
			pos = theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.FindIndex(m_fileSelectedArray.GetAt(i));
			FILELISTINFO *p = (FILELISTINFO *)theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetAt(pos);
			//nItem = m_fileSelectedArray.GetAt(i);

			//提取上传起始地址和上传数据长度
			UINT nHead = 0x9e9e9e9e;
			UINT nLen = 16;
			ULONGLONG ulBeginAddress = p->BeginAddress + g_startAddress * (ULONGLONG)(1024 * 1024);
			ULONGLONG ulFileSize = 0;
			ulFileSize = g_singleFileSize * (ULONGLONG)(1024 * 1024);
			ULONGLONG k = 0;
			k = ulFileSize / (320 * 1024);			//计数用

			//向DSP->FPGA下发上传起始地址和上传数据长度
			byte buffer[24];
			memcpy(buffer, &nHead, 4);
			memcpy(buffer + 4, &nLen, 4);
			memcpy(buffer + 8, &ulBeginAddress, 8);
			memcpy(buffer + 16, &ulFileSize, 8);
			//g_tcpClient.Send(buffer, sizeof(buffer)); 

			CString strFileName;
			strFileName = m_filelist.GetItemText(m_fileSelectedArray.GetAt(i), 0);
			strFileName = strFileSavePath + _T("\\") + strFileName;
			m_hFile = CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			
			g_tcpClient.Send(buffer, sizeof(buffer)); 
			SetTimer(1, 1000, NULL); 

			//从FIFO读文件
			ULONGLONG j = 0;
			while (g_bWritingFile)
			{
				byte *p = NULL;
				DWORD dwWrites;
				if ((p = m_FIFO.Pop()) != NULL)
				{
					WriteFile(m_hFile, p + 256, 320*1024/*FifoWith*/, &dwWrites, NULL);
					m_FIFO.Free(p);
					p = NULL;
					j++;

					//if (((ULONGLONG)j * /*FifoWith*/(320 * 1024)) == ulFileSize)   //收满指定文件大小后跳出，开始收下一个文件
					if (j  == k)
					{
						//m_dFileTransRate = (double)j  / ((double)(ulFileSize/1024));
						m_dFileTransRate = 1.0;
						KillTimer(1);
						//PostMessage(WM_USER+555, NULL, NULL);
						::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+555, NULL, NULL);
						break;
					}
					m_dFileTransRate = (double)j  / ((double)(ulFileSize/320/1024));
				}
			}

			//关闭文件
			if (m_hFile)
			{
				CloseHandle(m_hFile);
				m_hFile = NULL;
			}
		}
		
	}
	m_pWriteFileThread = NULL;
	m_fileSelectedArray.RemoveAll();
	BOOL bShowWindow = TRUE;
	::SendMessage(theApp.m_pMainDlg->m_formDlg2.m_hWnd, WM_USER+778, (WPARAM)&bShowWindow, NULL);
	KillTimer(1);
	g_bWritingFile = false;

	g_dlNetSpeed = 0.0;

	m_dFileTransRate = 0.0;

	while(1)
	{
		byte *p = NULL;
		p = m_FIFO.Pop();
		if (p)
		{
			m_FIFO.Free(p);
		}
		else
		{
			break;
		}
	}
	m_criticalsection.Lock();
	memset(pTemp, 0, HRRPBUFFERSIZE);
	m_criticalsection.Unlock();
	//m_formDlg2.SetTimer(1, 1000, NULL);
	return 0;
}


//没用到
double CSimpleInsectRadarDlg::GetFileTransRate(int &n)
{
	
	//m_criticalsection.Lock();
	//n = nItem;
	return 0.0;
}

extern bool b_flag2; // 开始/停止存储标志
bool bTempOriTrackFlag = false;
int CPIOut = 1;
extern bool bOriTrackEmpty; // OriTrack文件夹是否为空标志
bool bMatlabTrackProcessFlag = false;

void CSimpleInsectRadarDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		{
			int data = m_dFileTransRate * 100;
			if (data == 99)
			{
				data = 100;
			}
			CString str;
			str.Format(L"%d", data);
			str = str + _T("%");
			m_filelist.SetItemText(m_nItem, 2, str);
			break;
		}	
	case 2:
		{
			if(b_isStopStoreFlag)
			{
				b_isSimulateClickBtn = true;
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+890, NULL, NULL);	// 开始存储
				b_isTimerOutFlag = true;
				b_isTenMinWork = false;
				b_isTenMinWorktFlag = false;	// 非内校准模式标志位
			}
			KillTimer(2);
			verticalOrSlowScanCount++;
			break;
		}

	case 3:
		bMatlabTrackProcessFlag = true;
		iTimer3Count++;
		if(iTimer3Count == 3)
		{
			iTimer3Count = 0;
			mx_packFlag = 1;
		}
			
#if 0
		m_criticalMapIter.Lock();
		if(bOriTrackEmpty)
		{
			itTxtFileTime = mapFileName.begin();
			bOriTrackEmpty = false;
		}
		if(itTxtFileTime != mapFileName.end() && b_flag2)
		{
			PrintMessage("itTxtFileTime: " + itTxtFileTime->second);
			int mapSize = mapFileName.size();
			CString strTemp;
			strTemp.Format(_T("%d"), mapSize);
			PrintMessage("mapSize---:"+ strTemp);
			// 数据解析	
			//PrintMessage("Start Date_translate!");

			mxInt32 mx_Result= 0;
			mwArray mw_Result(1, 1, mxINT32_CLASS);
			mw_Result.SetData(&mx_Result,1);

			mxInt32 mx_CPIOut= 0;
			mwArray mw_CPIOut(1, 1, mxINT32_CLASS);
			mw_CPIOut.SetData(&mx_CPIOut, 1);

			char oriTrackFile_name[1024] = {0};
			CString tempOriTrackPath = oriTrackFilePath + "\\" + itTxtFileTime->second;
			WideCharToMultiByte(tempOriTrackPath, oriTrackFile_name, 1024);	
			mwArray mw_oriTrackFile_name(oriTrackFile_name);

			char oriTrackFileOutputPath[1024] = {0};
			WideCharToMultiByte(CPIFilePath, oriTrackFileOutputPath, 1024);	
			mwArray mw_oriTrackFileOutputPath(oriTrackFileOutputPath);

			char oriTrackFileBackupPath[1024] = {0};
			WideCharToMultiByte(CPIFileBackPath, oriTrackFileBackupPath, 1024);	
			mwArray mw_oriTrackFileBackupPath(oriTrackFileBackupPath);
		
			PrintMessage("Start Date_translate!");
			Date_translate(2, mw_Result, mw_CPIOut, mw_oriTrackFile_name, mw_oriTrackFileOutputPath);
			//Date_translate(2, mw_Result, mw_CPIOut, mw_oriTrackFile_name, mw_oriTrackFileOutputPath, mw_oriTrackFileBackupPath);
			

			int result = mw_Result.Get(1,1);
			int iCPIOut = mw_CPIOut.Get(1,1);
			//CPIOut = mw_CPIOut.Get(1,1);
			if(result == 1)
			{
				PrintMessage("Date_translate success!");
				CString str = itTxtFileTime->second;
				PrintMessage(str);
				OriTrackProcess(iCPIOut);
			}		
			else
			{
				PrintMessage("Date_translate error!");
			}
			/*itTxtFileTime++;*/
			TCHAR szTrackLogPath[MAX_PATH+1];			        	//系统工作目录
			GetModuleFileName( NULL, szTrackLogPath, MAX_PATH);   //获得系统路径
			(_tcsrchr(szTrackLogPath, _T('\\')))[1] = 0;
			//wcscpy(gszSettingPath , szModulePath);
			wcscat(szTrackLogPath , _T("TrackLog.txt"));	// 创建tracklog文件
			SaveTrackLogFile(szTrackLogPath, itTxtFileTime->second);
			PrintMessage("Update log file!");
			itTxtFileTime++;
		}
		else
		{
			PrintMessage("Wating TrackFiles!");
			//KillTimer(3);
		}
		m_criticalMapIter.Unlock();
		PrintMessage("**********************");
#endif
		break;
	case 4:
		mx_packFlag = 1;
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

UINT CSimpleInsectRadarDlg::MatlabTrackProcessThread(LPVOID lpParam)
{
	return ((CSimpleInsectRadarDlg*)lpParam)->MatlabTrackProcess();
}

UINT CSimpleInsectRadarDlg::MatlabTrackProcess()
{
	while(true)
	{
		if(bMatlabTrackProcessFlag)
		{
			m_criticalMapIter.Lock();
			if(bOriTrackEmpty)
			{
				itTxtFileTime = mapFileName.begin();
				bOriTrackEmpty = false;
			}
			if(itTxtFileTime != mapFileName.end() && b_flag2)
			{
				PrintMessage("itTxtFileTime: " + itTxtFileTime->second);
				/*int mapSize = mapFileName.size();
				CString strTemp;
				strTemp.Format(_T("%d"), mapSize);
				PrintMessage("mapSize---:"+ strTemp);*/
				// 数据解析	
				//PrintMessage("Start Date_translate!");

				mxInt32 mx_Result= 0;
				mwArray mw_Result(1, 1, mxINT32_CLASS);
				mw_Result.SetData(&mx_Result,1);

				mxInt32 mx_CPIOut= 0;
				mwArray mw_CPIOut(1, 1, mxINT32_CLASS);
				mw_CPIOut.SetData(&mx_CPIOut, 1);

				char oriTrackFile_name[1024] = {0};
				CString tempOriTrackPath = oriTrackFilePath + "\\" + itTxtFileTime->second;
				WideCharToMultiByte(tempOriTrackPath, oriTrackFile_name, 1024);	
				mwArray mw_oriTrackFile_name(oriTrackFile_name);

				char oriTrackFileOutputPath[1024] = {0};
				WideCharToMultiByte(CPIFilePath, oriTrackFileOutputPath, 1024);	
				mwArray mw_oriTrackFileOutputPath(oriTrackFileOutputPath);

				char oriTrackFileBackupPath[1024] = {0};
				WideCharToMultiByte(CPIFileBackPath, oriTrackFileBackupPath, 1024);	
				mwArray mw_oriTrackFileBackupPath(oriTrackFileBackupPath);
		
				//PrintMessage("Start Date_translate!");
				Date_translate(2, mw_Result, mw_CPIOut, mw_oriTrackFile_name, mw_oriTrackFileOutputPath);
				
				int result = mw_Result.Get(1,1);
				int iCPIOut = mw_CPIOut.Get(1,1);
				//CPIOut = mw_CPIOut.Get(1,1);
				if(result == 1)
				{
					PrintMessage("Date_translate success!");
					/*CString str = itTxtFileTime->second;
					PrintMessage(str);*/
					OriTrackProcess(iCPIOut);
				}		
				else
				{
					PrintMessage("Date_translate error!");
				}
				/*itTxtFileTime++;*/
				TCHAR szTrackLogPath[MAX_PATH+1];			        	//系统工作目录
				GetModuleFileName( NULL, szTrackLogPath, MAX_PATH);   //获得系统路径
				(_tcsrchr(szTrackLogPath, _T('\\')))[1] = 0;
				//wcscpy(gszSettingPath , szModulePath);
				wcscat(szTrackLogPath , _T("TrackLog.txt"));	// 创建tracklog文件
				SaveTrackLogFile(szTrackLogPath, itTxtFileTime->second);
				PrintMessage("Update log file!");
				itTxtFileTime++;
			}
			else
			{
				PrintMessage("Wating TrackFiles!");
				//KillTimer(3);
			}
			m_criticalMapIter.Unlock();
			PrintMessage("**********************");
			bMatlabTrackProcessFlag = false;
		}
		Sleep(1);
	}

	return 0;
}

UINT CSimpleInsectRadarDlg::MatlabInversionAlgProcessThread(LPVOID lpParam)
{
	return ((CSimpleInsectRadarDlg*)lpParam)->MatlabInversionAlgProcess();
}

UINT CSimpleInsectRadarDlg::MatlabInversionAlgProcess()
{
	while(true)
	{
		if(packResult == 1)
		{
			packResult = 0;
			mxInt32 mx_flag = 0;
			mwArray mw_flag(1, 1, mxINT32_CLASS);
			mw_flag.SetData(&mx_flag, 1);

			char mx_TrackFile_name[1024] = {0};
			CString TrackFile_nameTemp = TrackFile_name;
			WideCharToMultiByte(TrackFile_nameTemp, mx_TrackFile_name, 1024);	
			mwArray mw_TrackFile_name(mx_TrackFile_name);
			PrintMessage("%%%%%"+TrackFile_name);
			// 校准文件路径
			char CaliFilePath[1024] = {0};
			CString strTemp = toMatlabPara.s2;
			WideCharToMultiByte(strTemp, CaliFilePath, 1024);
			mwArray mw_CaliFilePath(CaliFilePath);

			mxDouble mx_RCS_ball = 0.0135;
			mwArray mw_RCS_ball(1, 1, mxDOUBLE_CLASS);
			mw_RCS_ball.SetData(&mx_RCS_ball, 1);

			mxDouble mx_MinLength_Den = 50;
			mwArray mw_MinLength_Den(1, 1, mxDOUBLE_CLASS);
			mw_MinLength_Den.SetData(&mx_MinLength_Den, 1);

			mxDouble mx_MinLength_ParaEst = 100;
			mwArray mw_MinLength_ParaEst(1,1,mxDOUBLE_CLASS);
			mw_MinLength_ParaEst.SetData(&mx_MinLength_ParaEst, 1);

			mxDouble mx_SampleTime = 3;
			mwArray mw_SampleTime(1, 1, mxDOUBLE_CLASS);
			mw_SampleTime.SetData(&mx_SampleTime, 1);

			mxDouble mx_IntCali_Enable = 0;
			mwArray mw_IntCali_Enable(1, 1, mxDOUBLE_CLASS);
			mw_IntCali_Enable.SetData(&mx_IntCali_Enable, 1);

			char OutputPathName[1024] = {0};
			WideCharToMultiByte(VerticalFilePath, OutputPathName, 1024);
			mwArray mw_OutputPathName(OutputPathName);
			func_Main_VerticalLookingMode(1, mw_flag, 
				mw_TrackFile_name, mw_CaliFilePath, mw_RCS_ball, mw_MinLength_Den, 
				mw_MinLength_ParaEst, mw_SampleTime, mw_IntCali_Enable, mw_OutputPathName);
			int verticalLookFlag = mw_flag.Get(1,1);
			if(1 == verticalLookFlag)
			{
				
				PrintMessage("********VerticalLookingMode success!**********");
			}
		}

		Sleep(1);
	}

	return 0;
}
void CSimpleInsectRadarDlg::SaveTrackLogFile(CString strFileName, CString strTrackFileName)
{
	CFileException fileException;
	CStdioFile myFile;
	if(myFile.Open(strFileName, CFile::typeText | CFile::modeCreate | CFile::modeWrite), &fileException)
	{
		myFile.WriteString(strTrackFileName);
	}
	myFile.Flush();
	myFile.Close();
}

//刷新界面配置参数显示区域
afx_msg LRESULT CSimpleInsectRadarDlg::OnUser400(WPARAM wParam, LPARAM lParam)
{
	if (m_formDlg1.m_dlgParaConfig)
	{
		m_listPrint.DeleteAllItems();
		CString str;
		m_listPrint.InsertItem(0, _T("波形模式"));						//波形模式
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO1,str);	
		m_listPrint.SetItemText(0, 1, str);

		//脉间编码模式
		int nItem = m_formDlg1.m_dlgParaConfig.m_combox1.GetCurSel();
		if (nItem == 0 || nItem == 2)
		{
			m_listPrint.SetItemText(0, 2, _T("脉间编码模式"));				
			m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO2,str);	
			m_listPrint.SetItemText(0, 3, str);
		}
		else
		{
			m_listPrint.SetItemText(0, 2, _T("脉间编码模式"));				
			m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO17,str);	
			m_listPrint.SetItemText(0, 3, str);
		}
		
		//远距波形脉宽
		if (nItem == 0 || nItem == 1)
		{
			m_listPrint.InsertItem(1, _T("远距波形脉宽"));
			m_listPrint.SetItemText(1, 1, _T("0.1us"));

		}
		else
		{
			m_listPrint.InsertItem(1, _T("远距波形脉宽"));					
			m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO11,str);	
			m_listPrint.SetItemText(1, 1, str);
		}
		

		m_listPrint.SetItemText(1, 2, _T("PRT"));						//PRT
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO3,str);	
		m_listPrint.SetItemText(1, 3, str);

		m_listPrint.InsertItem(2, _T("采样窗点数"));					//采样窗点数
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO5,str);	
		m_listPrint.SetItemText(2, 1, str);

		m_listPrint.SetItemText(2, 2, _T("起始采样距离"));				//起始采样距离
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO12,str);	
		m_listPrint.SetItemText(2, 3, str);

		m_listPrint.InsertItem(3, _T("实时成像上传点数"));				//实时成像上传点数
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO6,str);	
		m_listPrint.SetItemText(3, 1, str);

		m_listPrint.SetItemText(3, 2, _T("信息上传周期"));				//信息上传周期
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO4,str);	
		m_listPrint.SetItemText(3, 3, str);

		m_listPrint.InsertItem(4, _T("处理跳频点数"));					//处理跳频点数
		if (m_formDlg1.m_dlgParaConfig.m_combox1.GetCurSel() == 0 || m_formDlg1.m_dlgParaConfig.m_combox1.GetCurSel() == 2)
		{
			m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO14,str);	
			m_listPrint.SetItemText(4, 1, str);
		}
		else
		{
			m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO13,str);	
			m_listPrint.SetItemText(4, 1, str);
		}

		m_listPrint.SetItemText(4, 2, _T("天线转动模式"));					//天线转动模式
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO15,str);	
		m_listPrint.SetItemText(4, 3, str);
		
		m_listPrint.InsertItem(5, _T("AGC控制码1"));						//AGC控制码1
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO7,str);	
		m_listPrint.SetItemText(5, 1, str);

		m_listPrint.SetItemText(5, 2, _T("校准通道使能"));					//校准通道使能
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO9,str);	
		m_listPrint.SetItemText(5, 3, str);

		m_listPrint.InsertItem(6, _T("AGC控制码2"));						//AGC控制码2
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO8,str);	
		m_listPrint.SetItemText(6, 1, str);

		m_listPrint.SetItemText(6, 2, _T("校准通道控制"));					//校准通道控制
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO10,str);	
		m_listPrint.SetItemText(6, 3, str);
	}
	
	return 0;
}


LPSTR CSimpleInsectRadarDlg::ConvertErrorCodeToString(DWORD ErrorCode)
{
	HLOCAL LocalAddress = NULL;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, ErrorCode, 0, (PTSTR)&LocalAddress, 0, NULL);
	
	return (LPSTR)LocalAddress;
}


DWORD CSimpleInsectRadarDlg::GetLastErrorW(LPWSTR lpErrorString, DWORD cchWideChar)
{
	return FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
			lpErrorString,
			cchWideChar,
			NULL);
}


//接收DSP回传的结束存储地址并存文件
afx_msg LRESULT CSimpleInsectRadarDlg::OnUser111(WPARAM wParam, LPARAM lParam)
{
	BYTE *p = (BYTE*)wParam;

	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("FileListInfo.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file;
	file.Open(strModulePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);

	ULONGLONG ulEndAddress = *((unsigned long long *)(p + 8));
	if (theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetSize())  
	{
		FILELISTINFO *q = (FILELISTINFO *)theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetTail();
		q->EndAddress = ulEndAddress;
		q->BeginAddress;
		file.SeekToEnd();
		file.Write(q, sizeof(FILELISTINFO));

		m_filelist.DeleteAllItems();

		POSITION pos = theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetTailPosition();
		int i = theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetCount();
		while (pos != NULL)
		{
			FILELISTINFO *p = (FILELISTINFO *)theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetPrev(pos);

			//file.SeekToEnd();
			//file.Write(p, sizeof(FILELISTINFO));

			//更新显示
			CString strFileName;
			strFileName.Format(_T("%d_%.4d_%.2d_%.2d-%.2d_%.2d_%.2d.dat"), i, 
				p->systime.wYear, p->systime.wMonth, p->systime.wDay, 
				p->systime.wHour, p->systime.wMinute, p->systime.wSecond);

			theApp.m_pMainDlg->m_filelist.InsertItem(0, strFileName);  //更新文件名;
			ULONGLONG uEachFileSize = ((p->EndAddress) - (p->BeginAddress)) / (1024 * 1024);
			CString strEachFileSize;
			strEachFileSize.Format(_T("%d"), uEachFileSize);
			theApp.m_pMainDlg->m_filelist.SetItemText(0, 1, strEachFileSize);  //更新文件大小
			i--;
		}
	}

	file.Close();


	//更新formdlg1和formdlg2中的SATA存储容量
	double dl = theApp.m_pMainDlg->m_formDlg1.calculSATAVolum();
	CString strLastFileSize;
	strLastFileSize.Format(_T("%.2f"), dl);
	theApp.m_pMainDlg->m_formDlg1.m_SATAVolum.SetText(strLastFileSize);
	theApp.m_pMainDlg->m_formDlg2.m_SATAVolum.SetText(strLastFileSize);
	theApp.m_pMainDlg->m_formDlg1.m_SATASaveSpeed.SetText(_T("0000.00"));


	//UpdateData(FALSE);

	return 0;
}


//开始上传响应函数
afx_msg LRESULT CSimpleInsectRadarDlg::OnUser333(WPARAM wParam, LPARAM lParam)
{
	g_bWritingFile = true;
	int n = m_fileSelectedArray.GetCount();
	b_flag4 = true;
	//theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON8)->SetWindowTextW(_T("停止上传"));

	if (!m_pWriteFileThread)
	{
		//m_pWriteFileThread->ResumeThread();
		m_pWriteFileThread = AfxBeginThread(WriteFileThreadEx, this); //创建读文件线程
	}

	return 0;
}

//写文件线程
UINT CSimpleInsectRadarDlg::WriteFileThreadEx(LPVOID lpParam)
{
	return ((CSimpleInsectRadarDlg *)lpParam)->WriteProcessEx();
}


//写文件任务
UINT CSimpleInsectRadarDlg::WriteProcessEx()
{
	int nFileCount = m_fileSelectedArray.GetSize();   //得到需要上传文件的个数

	//将开始上传按钮置灰
	BOOL bShowWindow = FALSE;
	::SendMessage(theApp.m_pMainDlg->m_formDlg2.m_hWnd, WM_USER+778, (WPARAM)&bShowWindow, NULL);

	//CString strFileName;
	//strFileName = _T("1.bin");
	//strFileName = strFileSavePath + _T("\\") + strFileName;
	//m_hFile = CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//SetTimer(1, 1000, NULL);            //设置定时器，用于刷新listctrl的转存进度
	//m_formDlg2.SetTimer(1, 1000, NULL);
	for (int i=0; i<nFileCount; i++)
	{
		if (g_bWritingFile)
		{
			//提取文件链表特定位置元素
			m_nItem = m_fileSelectedArray.GetAt(i);
			POSITION pos;
			pos = theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.FindIndex(m_fileSelectedArray.GetAt(i));
			FILELISTINFO *p = (FILELISTINFO *)theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetAt(pos);

			//提取上传起始地址和上传数据长度
			UINT nHead = 0x9e9e9e9e;
			UINT nLen = 16;
			ULONGLONG ulBeginAddress = p->BeginAddress;
			ULONGLONG ulFileSize = 0;
			ulFileSize =(p->EndAddress) - (p->BeginAddress);		//文件大小
			ULONGLONG k = 0;
			k = ulFileSize / (320 * 1024);			//计数用

			//向DSP->FPGA下发上传起始地址和上传数据长度
			byte buffer[24];
			memcpy(buffer, &nHead, 4);
			memcpy(buffer + 4, &nLen, 4);
			memcpy(buffer + 8, &ulBeginAddress, 8);
			memcpy(buffer + 16, &ulFileSize, 8);
			//g_tcpClient.Send(buffer, sizeof(buffer)); 

			CString strFileName;
			strFileName = m_filelist.GetItemText(m_fileSelectedArray.GetAt(i), 0);
			strFileName = strFileSavePath + _T("\\") + strFileName;
			m_hFile = CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

			g_tcpClient.Send(buffer, sizeof(buffer)); 
			SetTimer(1, 1000, NULL); 

			//从FIFO读文件
			ULONGLONG j = 0;
			while (g_bWritingFile)
			{
				byte *p = NULL;
				DWORD dwWrites;
				if (p = m_FIFO.Pop())
				{
					WriteFile(m_hFile, p + 256, 320*1024, &dwWrites, NULL);
					m_FIFO.Free(p);
					p = NULL;
					j++;

					//if (((ULONGLONG)j * 320 * 1024) == ulFileSize)   //收满指定文件大小后跳出，开始收下一个文件
					if (j  == k)
					{
						//m_dFileTransRate = (double)j  / ((double)(ulFileSize/1024));
						m_dFileTransRate = 1.0;
						KillTimer(1);
						//PostMessage(WM_USER+555, NULL, NULL);
						::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+555, NULL, NULL);
						break;
					}
					m_dFileTransRate = (double)j  / ((double)(ulFileSize/320/1024));
				}
			}

			//关闭文件
			if (m_hFile)
			{
				CloseHandle(m_hFile);
				m_hFile = NULL;
			}
		}

	}

	m_pWriteFileThread = NULL;
	m_fileSelectedArray.RemoveAll();
	m_criticalsection.Lock();
	memset(pTemp, 0, HRRPBUFFERSIZE);
	m_criticalsection.Unlock();
	KillTimer(1);
	//m_formDlg2.SetTimer(1, 1000, NULL);
	g_bWritingFile = false;

	g_dlNetSpeed = 0.0;

	//将开始上传按钮置亮
	bShowWindow = TRUE;
	::SendMessage(theApp.m_pMainDlg->m_formDlg2.m_hWnd, WM_USER+778, (WPARAM)&bShowWindow, NULL);

	return 0;
}

extern int iunloadingFileNum;
afx_msg LRESULT CSimpleInsectRadarDlg::OnUser555(WPARAM wParam, LPARAM lParam)
{
	CString str;
	KillTimer(1);

	str = _T("转存完成");
	m_filelist.SetItemText(m_nItem, 2, str);

	//更新上位机磁盘容量
	double dLeftSize = theApp.m_pMainDlg->m_formDlg2.calculDiskVolum();
	CString strShow = _T("");
	strShow.Format( _T("%0.2f"), dLeftSize );
	theApp.m_pMainDlg->m_formDlg2.m_DiskRemainVolum.SetText( strShow );

	theApp.m_pMainDlg->m_formDlg2.m_SATATransSpeed.SetText( _T("0000.00") );

	static int tempi = 0;
	tempi++;
	if((tempi == iunloadingFileNum) && g_workMode == 1 && g_autoCali == 1)	// 在定时、内校准下触发
	{
		Sleep(2000);
		// 发送点击擦除sata盘按钮的消息
		::SendMessage(m_formDlg2.m_hWnd, WM_USER+893, NULL, NULL);
		PrintMessage(_T("发送点击擦除按钮消息！~~~"));
		tempi = 0;
	}

	//UpdateData(FALSE);

	return 0;
}

// 擦除后配参
afx_msg LRESULT CSimpleInsectRadarDlg::OnUser894(WPARAM wParam, LPARAM lParam)
{
	if((g_workMode == 1 && !b_isWorkStoreFlag && b_isTimeOutFlag) || (b_isStopStoreFlag && !b_isWorkStoreFlag))	// 配置参数
	{

		if(b_isManualClickBtn && g_autoCali == 1)
		{
			b_isTempCountTrack = true;
		}

		if(b_isTempCountTrack && g_autoCali == 1)	// 自动内校准模式
		{
			tempRadarPara.nPara_7 = 0;	// 起始采样距离为0---给dsp发送需要置0吗？
			tempRadarPara.nPara_dptInitSampDist = 0; // 交替模式下副波形起始采样距离
			toMatlabPara.StartRan = 0;
			g_nPara_7 = 0;			
			tempRadarPara.nPara_48 = 0.5;
		}
		else
		{
			tempRadarPara.nPara_7 = tempnPara_7;	// 非自动校准模式下为实际值
			tempRadarPara.nPara_dptInitSampDist = tempDptInitSampDist;
			toMatlabPara.StartRan = tempStartRan;
			if(!(toMatlabPara.workingMode == 3))
			{
				g_nPara_7 = tempStartRan;
			}

			tempRadarPara.nPara_48 = tempnPara_48; 
		}

		// debug
		CString str;
		str.Format(_T("%.2f"), tempRadarPara.nPara_48);
		PrintMessage("单次采集时间："+str);

		// 两通道同时的2个校准指令
		if(iTwiceCount == 0 && g_autoCaliMode == 0)
		{
			tempRadarPara.nPara_13 = 0;
			//tempRadarPara.nPara_7 = 0;	// 起始采样距离-0-dsp
			//toMatlabPara.StartRan = 0;	// 起始采样距离-0-matlab
			tempRadarPara.nPara_14 = 160;// 101
			toMatlabPara.UintCaliType = 5;
		}
		else if(iTwiceCount == 1 && g_autoCaliMode == 0)
		{
			tempRadarPara.nPara_13 = 0;
			//tempRadarPara.nPara_7 = 0;
			//toMatlabPara.StartRan = 0;	// 起始采样距离-0-matlab
			tempRadarPara.nPara_14 = 192;// 110
			toMatlabPara.UintCaliType = 6;
		}
		//else
		//{
		//	tempRadarPara.nPara_7 = tempnPara_7;	// 非校准模式下为实际值-起始采样距离
		//	toMatlabPara.StartRan = tempStartRan;
		//}

		// 两通道分时的4个校准指令
		if(iTwiceCount == 0 && g_autoCaliMode == 1)
		{
			tempRadarPara.nPara_13 = 1;
			//tempRadarPara.nPara_7 = 0;
			//toMatlabPara.StartRan = 0;	// 起始采样距离-0-matlab
			tempRadarPara.nPara_14 = 32;	// 001
			tempRadarPara.nPara_detectionChannel = 0; // HH通道校准，发射1校准
			toMatlabPara.UintCaliType = 1;
		}
		else if(iTwiceCount == 1 && g_autoCaliMode == 1)
		{
			tempRadarPara.nPara_13 = 1;
			//tempRadarPara.nPara_7 = 0;
			//toMatlabPara.StartRan = 0;	// 起始采样距离-0-matlab
			tempRadarPara.nPara_14 = 64;	// 010
			tempRadarPara.nPara_detectionChannel = 1; // HV通道校准，发射2校准
			toMatlabPara.UintCaliType = 2;
		}
		else if(iTwiceCount == 2 && g_autoCaliMode == 1)
		{
			tempRadarPara.nPara_13 = 0;
			//tempRadarPara.nPara_7 = 0;
			//toMatlabPara.StartRan = 0;	// 起始采样距离-0-matlab
			tempRadarPara.nPara_14 = 96;// 011
			tempRadarPara.nPara_detectionChannel = 0; // HH通道校准，接收1校准
			toMatlabPara.UintCaliType = 3;
		}
		else if(iTwiceCount == 3 && g_autoCaliMode == 1)
		{
			tempRadarPara.nPara_13 = 1;
			//tempRadarPara.nPara_7 = 0;
			//toMatlabPara.StartRan = 0;	// 起始采样距离-0-matlab
			tempRadarPara.nPara_14 = 128;// 100
			tempRadarPara.nPara_detectionChannel = 2; // VH通道校准，接收2校准
			toMatlabPara.UintCaliType = 4;
		}
		//else
		//{
		//	tempRadarPara.nPara_7 = tempnPara_7;	// 非校准模式下为实际值-起始采样距离
		//	toMatlabPara.StartRan = tempStartRan;
		//}

		if(b_isTenMinWorktFlag)
		{
			tempRadarPara.nPara_14 = 0;
			tempRadarPara.nPara_13 = 0;	// 正常工作模式下校准通道使能置为0
		}


		if(/*g_autoCali == 1*/ b_autoCaliFlag)
		{
			b_tempFlag_paracfg = true;	// 内校准自动开始工作标志
		}
		if((b_isSetTimeThreadFlag || g_autoCali == 0) && g_workMode == 1)	// 启动定时模式
		{
			AfxBeginThread(countThread, this);
		}

		// 配置参数
		//PrintMessage(_T("自动配置参数！"));
		int tt = 0;
		tt = g_tcpClient.Send((byte *)(&tempRadarPara), sizeof(tempRadarPara));
		//GetData_ToMatlab(toMatlabPara);

		if (tt == sizeof(tempRadarPara))
		{
			::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+400, NULL, NULL);
			//GetData_ToMatlab(toMatlabPara);
		}
		b_isTimeOutFlag = false;	// 定时模式时间到标志位

		if(b_isManualClickBtn)	// 处于两个track计时状态，每次自动配置参数将计数器置为0
		{
			b_isCountTrack = true;	// 如果不是在定时中，开始2个track停止的流程
			b_isTempCountTrack = true;
			b_isOkBtnParaConfig = false;
			b_isStopStoreFlag = true;
			b_isTenMinWork = false;
			b_isTenMinWorktFlag = false;
			b_isSimulateClickBtn = false;
			iTwiceCount = 0;
			tempiTwiceCount = 0;
			KillTimer(2);
			iCount = 0;
			tempiCount = 0;
			//g_autoCali = 1;
			//iTwiceCount = 0;
			b_isManualClickBtn = false;
			b_isSetTimeThreadFlag = false;
		}	
	}

	return 0;
}


BOOL CSimpleInsectRadarDlg::InitMatlabLib()
{
	
	if (!libfunc_CaliModeInitialize())
		return FALSE;
	if (!libfunc_VerticalLookingModeInitialize())
		return FALSE;
	if (!libfunc_Date_TransformInitialize())
		return FALSE;
	if (!libfunc_ScanModeInitialize())
		return FALSE;
	if (!libfunc_InternalCalibrationInitialize())
		return FALSE;
	if (!libfunc_Playback_VerticalLookingModeInitialize())
		return FALSE;
	if (!Date_translateInitialize())
	{
		PrintMessage("lib Date_translateInitialize error!");
		return FALSE;
	}
	else
	{
		PrintMessage("lib Date_translateInitialize success!");
	}

	if (!func_Track_v2Initialize())
	{
		PrintMessage("lib func_Track_v2Initialize error!");
		return FALSE;
	}
	else
	{
		PrintMessage("lib func_Track_v2Initialize success!");
	}
	if (!func_Main_VerticalLookingModeInitialize())
	{
		PrintMessage("lib func_Main_VerticalLookingMode error!");
		return FALSE;
	}
	else
	{
		PrintMessage("lib func_Main_VerticalLookingMode success!");
	}	

	return TRUE;
}


void CSimpleInsectRadarDlg::CreateTrackThread()
{
	AfxBeginThread(TrackCalcThread, this);		//启动track计算线程
}


void CSimpleInsectRadarDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CRichEditCtrl::OnLButtonDown(nFlags, point);


	CDialogEx::OnLButtonDown(nFlags, point);
}
