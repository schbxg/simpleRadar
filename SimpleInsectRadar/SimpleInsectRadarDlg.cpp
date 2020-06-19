
// SimpleInsectRadarDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSimpleInsectRadarDlg �Ի���




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
	memset(pHrrpBuf, 0, HRRPBUFFERSIZE);			//��ʼ��ȫ��һά�����ݻ���
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
	ON_MESSAGE(WM_USER+894, &CSimpleInsectRadarDlg::OnUser894)	// ���������
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CSimpleInsectRadarDlg ��Ϣ�������

BOOL CSimpleInsectRadarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	//char szBuf[100];
	//GetConsoleTitleA(szBuf, 100);					//�õ�����̨����

	//HWND hwnd = ::FindWindowA(NULL, szBuf);			//���ҿ���̨
	//HMENU hmenu = ::GetSystemMenu(hwnd, FALSE);		//��ȡ�˵�
	//::RemoveMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);	//�Ƴ��ر�

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

	//tab��ʼ��
	m_TabCtrlMain.InsertItem(0, _T("�״���ʾ����"));
	m_TabCtrlMain.InsertItem(1, _T("�����ϴ�����"));

	//״̬��
	UINT array[3]={11001,11002,11003};									//��������
	m_StatusBar.Create(this); 											//����״̬������
	m_StatusBar.SetIndicators(array,sizeof(array)/sizeof(UINT));		//������
	GetClientRect(&rect);
	m_StatusBar.SetPaneInfo(0,array[0],0,rect.Width()*3/6); 			//���������
	m_StatusBar.SetPaneInfo(1,array[1],0,rect.Width()*2/6); 			//���������
	m_StatusBar.SetPaneInfo(2,array[2],0,rect.Width()*1/6); 			//���������
	m_StatusBar.SetPaneText(0,_T("  �������׿Ƶ�����Ϣ�������޹�˾"));								//��������ı�
	m_StatusBar.SetPaneText(1,_T("�״ﲿ"));						//��������ı�
	m_StatusBar.SetPaneText(2,_T("V0.5 Beta"));						//��������ı�
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);


	//��Ϣ��ӡ�б�ؼ���ʼ��
	m_listPrint.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES|LVS_OWNERDATA | LVS_EX_DOUBLEBUFFER);
	m_listPrint.InsertColumn(0, _T("�״����"));
	m_listPrint.InsertColumn(1, _T("�״����ֵ"));
	m_listPrint.InsertColumn(2, _T("�״����"));
	m_listPrint.InsertColumn(3, _T("�״����ֵ"));
	m_listPrint.SetColumnWidth(0, 120);
	m_listPrint.SetColumnWidth(1, 100);
	m_listPrint.SetColumnWidth(2, 100);
	m_listPrint.SetColumnWidth(3, 120);

	m_filelist.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES|LVS_OWNERDATA | LVS_EX_DOUBLEBUFFER);
	m_filelist.InsertColumn(0, _T("�ļ����"));
	m_filelist.InsertColumn(1, _T("�ļ���С(��λ��MB)"));
	m_filelist.InsertColumn(2, _T("ת�����"));
	//m_listPrint.InsertColumn(3,_T("�״����ֵ"));
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
	//�����ʼ��
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
		//AfxBeginThread(NetWorkThread, this);     //�������������߳�
	}
	if (g_iIsTcpConnect == 0)
	{
		PrintMessage(_T("�������ӳɹ�"));
		InitMatlabLib();						 //��ʼ��matlab�ӿڿ�
		//g_bIsRadarWork = true;
		AfxBeginThread(NetWorkThread, this);     //�������������߳�
		PrintMessage(_T("���������߳�����"));
		//m_pWriteFileThread = AfxBeginThread(WriteFileThread, this/*, 0, 0, CREATE_SUSPENDED*/);//����д�ļ��̣߳�������
		
		// ������ȡ�����ļ��߳�
		AfxBeginThread(ReadParaConfigThread, this); 

#if DFLAG
		AfxBeginThread(DataTranspondThread, this);
#endif
			
	}
	else 
	{
		//AfxBeginThread(ReadParaConfigThread, this); 
		PrintMessage(_T("����δ���ӣ�"));
	}
	//m_pWriteFileThread = AfxBeginThread(WriteFileThread, this, 0, 0, CREATE_SUSPENDED);//����д�ļ��̣߳�������
	ShowWindow(SW_HIDE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSimpleInsectRadarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSimpleInsectRadarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


extern bool b_flag1;
//���TAB�¼���Ӧ����
void CSimpleInsectRadarDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		//	MessageBox(_T("�����쳣���޷���ʼ����"), NULL, MB_ICONWARNING);
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
	strMessage = strTime + L"��" + str + L"\r\n";
	m_RichEditCtrl.ReplaceSel(strMessage);
	m_RichEditCtrl.SetReadOnly(TRUE);
	::PostMessage(m_RichEditCtrl.m_hWnd, WM_VSCROLL, SB_BOTTOM, 0);

	return 0;
}


//��Ϣ��ӡ����
void CSimpleInsectRadarDlg::PrintMessage(CString str)
{
	SendMessage(WM_USER+100, (WPARAM)&str);
}


//�˵������˳�
void CSimpleInsectRadarDlg::OnMenuExit()
{
	OnClose();
	//CDialogEx::OnCancel();
}


//�˵���������
void CSimpleInsectRadarDlg::OnMenuAbout()
{
	// TODO: �ڴ���������������
	//MessageBox( _T("���ţ�Y0591\n\n���ߣ�����\n\n��ϵ��ʽ��18813007611"), _T("����֧��"));
}


//�ر�
void CSimpleInsectRadarDlg::OnClose()
{

	if (g_fAntennaEleAngle > 0.2)
	{
		MessageBox(_T("�뽫�ŷ��Ƕȹ���!"), NULL, MB_ICONWARNING);
		return;
	}


	if (!WaitForSingleObject(m_pWriteFileThread, 0))
	{
		if (GetLastError() != 0x06)
		{
			if (MessageBox(L"��̨�����ϴ������ļ���ȷ��Ҫ�رճ���", NULL, MB_YESNO) == IDYES)
			{
				CloseHandle(m_hFile);
				//�ر��׽���
				if (g_iIsTcpConnect == 0)
				{
					g_tcpClient.Close();
					g_iIsTcpConnect = -1;
				}

				//ֹͣ���������߳�
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

	if (MessageBox(L"�Ƿ�رճ���", NULL, MB_YESNO) == IDYES)
	{
		CloseHandle(m_hFile);
		//�ر��׽���
		if (g_iIsTcpConnect == 0)
		{
			g_tcpClient.Close();
			g_iIsTcpConnect = -1;
		}

		//ֹͣ���������߳�
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


// ��ȡ�����ļ��̺߳���
UINT CSimpleInsectRadarDlg::ReadParaConfigThread(LPVOID lpParam)
{
	return ((CSimpleInsectRadarDlg*) lpParam)->ReadParaConfigProcess();
}

RadarPara ToDspParaConfig; // �·���DSP�Ľṹ��
UINT CSimpleInsectRadarDlg::ReadParaConfigProcess()
{
	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("ConfigFile.txt"));

	CString strModulePath;
	strModulePath = szModulePath;

	FileOP(strModulePath);
	return 0;
}

 
// ��ȡ�����ļ�
bool b_tempFlag_paracfg = false;
bool isAutoClickStartWorkButton = false; // �ڶ�ȡ�����ļ����Ƿ��Զ������ʼ������ť��־
void CSimpleInsectRadarDlg::FileOP(LPCTSTR LRFileName)
{
	CStdioFile mFileIn;
	CString strTempLine;
	if(!mFileIn.Open(LRFileName, CFile::modeRead)) {
	    AfxMessageBox(_T("�Ҳ��������ļ�"));
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
	//PrintMessage(_T("�����ļ���ȡ��ϣ�"));
	if(strTempLineArray[1] == "0")
	{
		PrintMessage(_T("�ֶ�ģʽ!"));
		return;
	}
	if(strTempLineArray[1] == "1" && strTempLineArray[2] == "��ʼ����")
	{

		// ��ȡ����
		//Sleep(5000);
		GetDataFromDspParaConfig();
		GetDataFromMatlabParaConfig();
		GetDataFromOwnParaConfig();
		Sleep(5000);
		PrintMessage(_T("�Զ�ģʽ!"));

		//// ��DSP���Ͳ���
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
	//		PrintMessage(_T("����ȡ�����ļ�!"));
	//		break;
	//	}
	//	else if(strTempLine == "��ʼ����")
	//	{
	//		
	//		// ��ȡ����
	//		//Sleep(5000);
	//		GetDataFromDspParaConfig();
	//		GetDataFromMatlabParaConfig();
	//		GetDataFromOwnParaConfig();
	//		Sleep(5000);
	//		PrintMessage(_T("��ȡ�����ļ�!"));

	//		//// ��DSP���Ͳ���
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
	// ���ĵ��ж�������
	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
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



	// ��������
	ar >> waveMode;
	ar >> codeMode;
	ar >> g_nDrawNodes;
	ar >> g_nCoefficient;
	ar >> g_nPara_7;
	ar >> g_singleAcquistionTimeMax;
	ar >> tempnPara_48;
	ar >> tempnPara_7;
	ar >> tempStartRan; // ��ʼ��������

	tempRadarPara = ToDspParaConfig;
}

// ��ȡMATLAB����
void CSimpleInsectRadarDlg::GetDataFromMatlabParaConfig()
{
	// ���ĵ��ж�������
	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
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
	// ���ĵ��ж�������
	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
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
	// ��У׼ģʽ�����
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
	if(g_autoCali == 1)	// �Զ���У׼ģʽ
	{
		ToDspParaConfig.nPara_7 = 0;	// ��ʼ��������Ϊ0
		ToDspParaConfig.nPara_dptInitSampDist = 0;	// ����ģʽ�¸�������ʼ��������
	}
	if(g_autoCali == 1 && g_autoCaliMode == 1)
	{
		ToDspParaConfig.nPara_detectionChannel = 0; // ��У׼ģʽ���ֶ�������Ƚ��з���һУ׼��HHͨ��
	}
	ar >> g_workMode;
	ar >> b_isOkBtnParaConfig;
}

// �ַ�ת��
void CSimpleInsectRadarDlg::CharToUTF8(CString &str)
{
	char *szBuf = new char[str.GetLength() + 1];//ע�⡰+1����char�ַ�Ҫ�����������CStringû��
	memset(szBuf, '\0',str.GetLength());


	int i;
	for ( i = 0 ; i < str.GetLength(); i++)
	{
		szBuf[i] = (char)str.GetAt(i);
	}
	szBuf[i] = '\0';//���������������ĩβ�������롣

	int nLen;
	WCHAR *ptch;
	CString strOut;
	if(szBuf == NULL)
	{
		return;
	}
	nLen = MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, NULL, 0);//�����Ҫ�Ŀ��ַ��ֽ���
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

//���������߳�
UINT CSimpleInsectRadarDlg::NetWorkThread(LPVOID lpParam)
{
	return ((CSimpleInsectRadarDlg*)lpParam)->NetWorkProcess();
}

UINT CSimpleInsectRadarDlg::TrackCalcThread(LPVOID lpParam)
{
	return ((CSimpleInsectRadarDlg*)lpParam)->TrackCalcProcess();
}

// ����ת���߳�
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
		type = *((UINT32 *)(buff+4));                //��ȡָ���볤��
		UINT len =0;
		len = *((UINT *)(buff+4));                //��ȡָ���볤��
		byte *pBuffer = new byte[len + 8];
		memset(pBuffer, 0, len + 8);
		memcpy(pBuffer, buff, len+8);
		DisplaySoftDataProcessing((byte*)pBuffer, len+8);//�Խ��յ����ݽ��з��� 
#if 0
		int nRet = g_udpClientReceive.Recv(p, 8);//ǰ�ĸ��ֽ��ǰ�ͷ�����ĸ��ֽ��ǰ���
		if(nRet == 0)
		{
			PrintMessage(_T("continue"));
			continue;
		}
		int nError = WSAGetLastError();
		UINT len =0;
		len = *((UINT *)(p+4));                //��ȡָ���볤��

		byte *pBuffer = new byte [len + 8 + 4];         //���ٽ������ݻ�����
		memset(pBuffer, 0, len + 8 + 4);
		nRet = g_udpClientReceive.Recv(pBuffer + 8, len+4);			//** ����ָ����������
		if (nRet < 0)
		{
			PrintMessage(_T("Socket�����Ѿ��Ͽ������������"));
			break;
		}
		memcpy(pBuffer, p, 8);                      //������ƴ��
		//g_tcpDisplaySoftClient.Send(pBuffer, len + 8); // ����ָ��ת��
		DisplaySoftDataProcessing(pBuffer, len + 8 + 4);//�Խ��յ����ݽ��з��� 
#endif  
		Sleep(1);
	}

	return 0;
}

//������������
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
		g_tcpClient.Recv(p, 8);  //ǰ�ĸ��ֽ��ǰ�ͷ�����ĸ��ֽ��ǰ���
		// ******* ��������̷��������,�ֱ�Ϊ�״﹤��ģʽ�������ϴ�ģʽ ******** //
		int nError = WSAGetLastError();
		UINT len =0;
		//len = *((UINT *)(p));
		len = *((UINT *)(p+4));                //��ȡָ���볤��

		//if (len > 827808)
		//{
		//	continue;
		//}

		byte *pBuffer = new byte [len + 8];         //���ٽ������ݻ�����
		memset(pBuffer, 0, len + 8);
		int nRet = g_tcpClient.Recv(pBuffer + 8, len);			//** ����ָ����������
		if (nRet < 0)
		{
			PrintMessage(_T("Socket�����Ѿ��Ͽ������������"));
			break;
			//continue;
		}

		//m_criticalsection.Lock();
		memcpy(pBuffer, p, 8);                      //������ƴ��
		
		
		UINT nDataType = *((UINT *)p);     //������������������
		DWORD dwWrites;
		//if (nDataType == 0x7c7c7c7c || nDataType == 0x17181920)
		//{
		//	long lDistanceToMoveHigh = 0;
		//	WriteFile(m_hFile, pBuffer, len + 8, &dwWrites, NULL);
		//	SetFilePointer(m_hFile, lDistanceToMove, NULL, FILE_CURRENT);

		//	lDistanceToMove = dwWrites * (-1);
		//	//CloseHandle(m_hFile);
		//}

		//���ļ�
		if (g_bWritingFile)
		{
			memcpy(pushbuf + offset, pBuffer, (len + 8)); //���ϴ������ļ��ٿ�����Ϊ��FIFO��׼��
			offset += (len + 8);

			ulTotalBytes += (ULONGLONG)nRet;	//ͳ�ƿ�ʼ�ϴ����ܵ�����������

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
				//ƽ���ٶ�
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
		//	memcpy(pBuffer, p, 8);                      //������ƴ��
		//}
		//else
		//{
			DataProcessing(pBuffer, len + 8);           //�Խ��յ����ݽ��з���
		//}
		

		//m_criticalsection.Unlock();
	}

	delete []pushbuf;

	return 0;
}

extern bool b_flag1;
bool b_isTempCountTrack = true;	// �Ƿ��ڽ�����У׼��־λ
/*static*/ int tempiTwiceCount = 0;
static int tempiCount = 0;


bool tempFlag = false;
CString oriTrack;

extern CString oriTrackFilePath; // ԭʼ�㼣�洢·��
extern CString CPIFileBackPath; // CPI���ݱ���·��
extern CString trackFilePath; // track���ݴ��
extern CString CPIFilePath; // CPI���ݴ洢·��
extern CString HRRPFilePath; // һά���������ݴ洢·��
extern map<LONGLONG, CString> mapFileName; // oriTrack
extern map<LONGLONG, CString>::iterator itTxtFileTime; // log ��¼���ļ�ʱ��
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

			if(toMatlabPara.workingMode == 3)	// �����ݰ���ȥ������������Ͳ��������ֵ
			{
				q_uStartRan = *(UINT *)(q + len);
				mx_StartRan = q_uStartRan;           //    % ��ʼ��������      ��Ӧ������ʼ�������롱
				//g_nPara_7 = q_uStartRan;	// ����һά��������ʾ
				float q_fPulseWid = *(float *)(q + len + 4);
				mx_PulseWid = q_fPulseWid * 1000000; // ����������usΪ��λ
			}
			else
			{
				mx_StartRan = toMatlabPara.StartRan;           //    % ��ʼ��������      ��Ӧ������ʼ�������롱
				mx_PulseWid = toMatlabPara.fPulseWid; // ��������-us
				//len += 8;
			}

			len += 8;
			*/

			int len = *((int*)(q + 4));
			UINT q_uStartRan = 0;
			CString str;
			str.Format(_T("%d"), len);
			//PrintMessage("len��"+str);
#if 1
			// ��ȡϵͳʱ��
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
			// ���ݽ���
			
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
				// ����OriTrackProcess
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
					double thrTime; // ʱ���������
					double thrRange; // �����������
					double thrAzi; // ��λ�ǹ�������
					double thrEle; // �����ǹ�������
					double thrDelDetlatime; // ����ɾ��ʱ��
					double thrDelNum; // ����ɾ������
				};

				thrStruct thr;
				thr.thrTime = 2;
				thr.thrRange = 3;
				thr.thrAzi = 1;
				thr.thrEle = 1;
				thr.thrDelDetlatime = 100;
				thr.thrDelNum = 50;

				const int nFields = 6; // �ṹ���б�������
				const char *fieldNames[6] = {"ThrTime", "ThrRange", "ThrAzi", "ThrEle", "Del_detlatime", "Del_Num"}; // �ṹ���б�����

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
			//PrintMessage("��ʼ�������룺"+str);

			TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
			GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
			(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
			//wcscpy(gszSettingPath , szModulePath);
			wcscat(szModulePath , _T("Track.bin"));
			HANDLE hFile = CreateFile(/*_T("123.bin")*/szModulePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			DWORD dwWrites;
			bool bRet = WriteFile(hFile, q, len, &dwWrites, NULL);
			CloseHandle(hFile);

			


			mxInt8 mx_Result = 0;
			mwArray mw_Result(1, 1, mxINT8_CLASS);

			//mxInt32 mx_StartRan = toMatlabPara.StartRan;           //    % ��ʼ��������      ��Ӧ������ʼ�������롱
			mxInt32 mx_SampleNum = toMatlabPara.SampleNum;		 //    % ��������          ��Ӧ����������������
			mxInt32 mx_PRT = toMatlabPara.PRT;				 //    % PRT              ��Ӧ�� ��PRT��
			mxInt32 mx_WaveForm = toMatlabPara.WaveForm;			 //    % ���α���          ��Ӧ�������α��롱
			mxInt32 mx_CodeType = toMatlabPara.CodeType;			 //    % �������ģʽ      ��Ӧ�����������ģʽ��
			mxDouble mx_RCS_ball = toMatlabPara.RCS_ball;
			mxDouble mx_MinLength_Cali = toMatlabPara.dlMinLength_Cali;
			mxDouble mx_MinLength_ParaEst = toMatlabPara.dlMinLength_ParaEst; //mw_MinLength_ParaEst == mx_MinLength_Orien
			mxDouble mx_MinLength_Den = toMatlabPara.dlMinLength_Den;

			//mxDouble mx_PulseWid = toMatlabPara.fPulseWid; // ��������
			mxInt32  mx_SampleTime = toMatlabPara.SampleTime; // ���βɼ�ʱ��

			mxDouble mx_Azi_S = toMatlabPara.fAzi_S; // ��λ��ʼ�ɼ��Ƕ�
			mxDouble mx_Azi_E = toMatlabPara.fAzi_E; // ��λ��ֹ�ɼ��Ƕ�

			mxInt32 mx_IntCaliType = toMatlabPara.UintCaliType;	// У׼ָ��

			mxDouble mx_Elv_D = toMatlabPara.fElv_D; // ������ʼ�Ƕ�
			mxDouble mx_Elv_H = toMatlabPara.fElv_H; // ������ֹ�Ƕ�

			mxInt32 mx_IntCali_Enable = toMatlabPara.enableAutoCali;

			
			// debug
			*if(b_isTempCountTrack && (g_workMode == 1) && (g_autoCali == 1))
			{*/
				//str.Format(_T("%d"), mx_IntCaliType);
				//PrintMessage("У׼ָ�"+str);
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

			mwArray mw_PulseWid(1,1,mxDOUBLE_CLASS); // ��������
			mwArray mw_SampleTime(1,1, mxINT32_CLASS); // ���βɼ�ʱ��

			mwArray mw_Azi_S(1,1,mxDOUBLE_CLASS);	// ��λ��ʼ�ɼ��Ƕ�
			mwArray mw_Azi_E(1,1,mxDOUBLE_CLASS);	// ��λ��ֹ�ɼ��Ƕ�

			mwArray mw_IntCaliType(1, 1, mxINT32_CLASS);	// У׼ָ��

			mwArray mw_Elv_D(1,1,mxDOUBLE_CLASS);	// ������ʼ�Ƕ�
			mwArray mw_Elv_H(1,1,mxDOUBLE_CLASS);	// ������ֹ�Ƕ�

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
			//long long nLen_Data = 3872388;//58982400;//23592960;			//���鳤��Ϊ��ȡmap.out�ļ���С
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
			//char TrackFile_name[] = {"E:\\01̽���״�\\01��Ƶȫ�����״�\\Matlab&VS_TC\\Matlab_TC\\Track_DSPupLoad.mat"};
			//char TrackFile_name[] = {"d:\\�����ʱȫ����_���������_0_0.mat"};
			char TrackFile_name[1024] = {"1.mat"};
			//WideCharToMultiByte(strTemp, TrackFile_name, 1024);
			mwArray mw_TrackFile_name(TrackFile_name);

			strTemp = toMatlabPara.s2;
			//char CaliFile_name[] = {"�Ǹ�ɶCaliFile_name"};
			char CaliFile_name[1024] = {0};
			WideCharToMultiByte(strTemp, CaliFile_name, 1024);
			mwArray mw_CaliFile_name(CaliFile_name);

			//PrintMessage(_T("TrackCalcProcess!"));

			//tempiCount++;
			if(b_isTempCountTrack && g_autoCali == 1)
			{
				
				
				//PrintMessage(_T("������У׼������" ));
				// ��У׼����
				//func_InternalCalibration(const mwArray& TrackFile_name, const mwArray& PulseWid, const mwArray& IntCaliType);
				func_InternalCalibration(mw_TrackFile_name, mw_PulseWid, mw_IntCaliType);
				//PrintMessage(_T("������У׼������" ));
			}


			if ((toMatlabPara.mode == 0) && (!b_isTempCountTrack || g_autoCali == 0))			//����ģʽ
			{
				char Cali_ball_File_name[] = {"E:\\01̽���״�\\01��Ƶȫ�����״�\\Matlab&VS_TC\\Matlab_TC\\CaliFile_20180312T170000.mat"};//��ӦУ׼�ļ����֣�У׼�ļ�������Դ�ڽ���Ĳ������

				mwArray mw_Cali_ball_File_name(Cali_ball_File_name);

				// �ܶ�����
				mwArray mw_DenProf_X(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_DenProf_X_N(1, 1, mxINT32_CLASS);
				mwArray mw_DenProf_Y(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_DenProf_Y_N(1, 1, mxINT32_CLASS);

				// ����ֲ�
				mwArray mw_Orien_X(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_Orien_X_N(1, 1, mxINT32_CLASS);
				mwArray mw_Orien_Y(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_Orien_Y_N(1, 1, mxINT32_CLASS);

				// ��������ͼ
				mwArray mw_PP_X(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_PP_X_N(1, 1, mxINT32_CLASS);
				mwArray mw_PP_Y(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_PP_Y_N(1, 1, mxINT32_CLASS);

				// ���Ƶ��==����Ƶ�ʷֲ�
				mwArray mw_WBF_Ind_X(500000, 1, mxDOUBLE_CLASS);
				mwArray mw_WBF_Ind_X_N(1, 1, mxINT32_CLASS);
				mwArray mw_WBF_Ind_Y(500000, 1, mxDOUBLE_CLASS);
				mwArray mw_WBF_Ind_Y_N(1, 1, mxINT32_CLASS);

				// ���Ƶ�ʷֲ�
				mwArray mw_WingBeatFre_X(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_WingBeatFre_X_N(1, 1, mxINT32_CLASS);
				mwArray mw_WingBeatFre_Y(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_WingBeatFre_Y_N(1, 1, mxINT32_CLASS);

				// �峤�ֲ�
				mwArray mw_BodyLen_X(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_BodyLen_X_N(1, 1, mxINT32_CLASS);
				mwArray mw_BodyLen_Y(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_BodyLen_Y_N(1, 1, mxINT32_CLASS);

				// ���طֲ�
				mwArray mw_BodyMass_X(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_BodyMass_X_N(1, 1, mxINT32_CLASS);
				mwArray mw_BodyMass_Y(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_BodyMass_Y_N(1, 1, mxINT32_CLASS);


				// �߶�-ʱ��ֲ�
				mwArray mw_HTDiv_X(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_HTDiv_T_N(1, 1, mxINT32_CLASS);
				mwArray mw_HTDiv_Y(5000, 1, mxDOUBLE_CLASS);
				mwArray mw_HTDiv_H_N(1, 1, mxINT32_CLASS);

				

				/********************************************************************************************/


				// �ܶ�����
				mxDouble mx_DenProf_X[5000];
				mxInt32 mx_DenProf_X_N;
				mxDouble mx_DenProf_Y[5000];
				mxInt32 mx_DenProf_Y_N;

				// ����ֲ�
				mxDouble mx_Orien_X[5000];
				mxInt32 mx_Orien_X_N;
				mxDouble mx_Orien_Y[5000];
				mxInt32 mx_Orien_Y_N;

				// ��������ͼ
				mxDouble mx_PP_X[5000];
				mxInt32 mx_PP_X_N;
				mxDouble mx_PP_Y[5000];
				mxInt32 mx_PP_Y_N;

				// ���Ƶ��==����Ƶ�ʷֲ�
				mxDouble *pmx_WBF_Ind_X = new mxDouble[500000];
				mxInt32 mx_WBF_Ind_X_N;
				mxDouble *pmx_WBF_Ind_Y = new mxDouble[500000];
				mxInt32 mx_WBF_Ind_Y_N;

				// ���Ƶ�ʷֲ�
				mxDouble mx_WingBeatFre_X[5000];
				mxInt32 mx_WingBeatFre_X_N;
				mxDouble mx_WingBeatFre_Y[5000];
				mxInt32 mx_WingBeatFre_Y_N;

				// �峤�ֲ�
				//mxDouble mx_BodyLen_X[5000];
				//mxInt32 mx_BodyLen_X_N;
				//mxDouble mx_BodyLen_Y[5000];
				//mxInt32 mx_BodyLen_Y_N;

				mxDouble *pmx_BodyLen_X = new mxDouble[5000];
				mxInt32 mx_BodyLen_X_N;
				mxDouble *pmx_BodyLen_Y = new mxDouble[5000];
				mxInt32 mx_BodyLen_Y_N;

				// ���طֲ�
				/*mxDouble mx_BodyMass_X[5000];
				mxInt32 mx_BodyMass_X_N;
				mxDouble mx_BodyMass_Y[5000];
				mxInt32 mx_BodyMass_Y_N;*/

				mxDouble *pmx_BodyMass_X = new mxDouble[5000];
				mxInt32 mx_BodyMass_X_N;
				mxDouble *pmx_BodyMass_Y = new mxDouble[5000];
				mxInt32 mx_BodyMass_Y_N;

				// �߶�-ʱ��ֲ�
				/*mxDouble mx_HTDiv_X[5000];
				mxInt32 mx_HTDiv_T_N;
				mxDouble mx_HTDiv_Y[5000];
				mxInt32 mx_HTDiv_H_N;
				*/

				// �߶�-ʱ��ֲ�
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
				//��ֱģʽ-��һ���� ��ֱģʽ-��������
				if(toMatlabPara.workingMode == 1 || toMatlabPara.workingMode == 3)
				{
					///*�ܶ�����**/// ����ֲ�*// ���Ƶ�ʷֲ�// �峤�ֲ�// ���طֲ�// �������Ƶ��// �߶�-ʱ��ֲ�// ��������ͼ*
					//func_VerticalLookingMode(int nargout, mwArray& DenProf_X, mwArray& DenProf_X_N, mwArray& DenProf_Y, mwArray& DenProf_Y_N,
					//mwArray& Orien_X, mwArray& Orien_X_N, mwArray& Orien_Y, mwArray& Orien_Y_N,
					//mwArray& WingBeatFre_X, mwArray& WingBeatFre_X_N, mwArray& WingBeatFre_Y, mwArray& WingBeatFre_Y_N, 
					//mwArray& BodyLen_X, mwArray& BodyLen_X_N, mwArray& BodyLen_Y, mwArray& BodyLen_Y_N,
					//mwArray& BodyMass_X, mwArray& BodyMass_X_N, mwArray& BodyMass_Y, mwArray& BodyMass_Y_N, 
					//mwArray& WBF_Ind_X, mwArray& WBF_Ind_X_N, mwArray& WBF_Ind_Y, mwArray& WBF_Ind_Y_N, 
					//mwArray& HTDiv_X, mwArray& HTDiv_T_N, mwArray& HTDiv_Y, mwArray& HTDiv_H_N, 
					//mwArray& PP_X, mwArray& PP_X_N, mwArray& PP_Y, mwArray& PP_Y_N, 
					//const mwArray& TrackFile_name, const mwArray& CaliFilePath, const mwArray& StartRan, const mwArray& SampleNum, const mwArray& PRT, const mwArray& PulseWid, const mwArray& WaveForm, const mwArray& CodeType, const mwArray& RCS_ball, const mwArray& MinLength_Den, const mwArray& MinLength_ParaEst, const mwArray& SampleTime, const mwArray& IntCali_Enable);

					//PrintMessage(_T("���ô�ֱģʽ������" ));
					func_VerticalLookingMode(32, mw_DenProf_X,mw_DenProf_X_N, mw_DenProf_Y, mw_DenProf_Y_N, 
						mw_Orien_X,mw_Orien_X_N,mw_Orien_Y,mw_Orien_Y_N,						
						mw_WingBeatFre_X, mw_WingBeatFre_X_N, mw_WingBeatFre_Y, mw_WingBeatFre_Y_N,
						mw_BodyLen_X,mw_BodyLen_X_N,mw_BodyLen_Y,mw_BodyLen_Y_N,				
						mw_BodyMass_X,mw_BodyMass_X_N,mw_BodyMass_Y,mw_BodyMass_Y_N,			
						mw_WBF_Ind_X, mw_WBF_Ind_X_N, mw_WBF_Ind_Y, mw_WBF_Ind_Y_N,				
						mw_HTDiv_X, mw_HTDiv_T_N, mw_HTDiv_Y, mw_HTDiv_H_N,						
						mw_PP_X,mw_PP_X_N,mw_PP_Y,mw_PP_Y_N,								

						mw_TrackFile_name, mw_CaliFile_name/*mw_Cali_ball_File_name*/,mw_StartRan,mw_SampleNum,mw_PRT,mw_PulseWid,mw_WaveForm,mw_CodeType,mw_RCS_ball, mw_MinLength_Den, mw_MinLength_ParaEst, mw_SampleTime, mw_IntCali_Enable);
					//PrintMessage(_T("���ô�ֱģʽ������" ));

					//func_Playback_VerticalLookingMode(32, 
						//mwArray& DenProf_X, mwArray& DenProf_X_N, mwArray& DenProf_Y, mwArray& DenProf_Y_N, mwArray& Orien_X, mwArray& Orien_X_N, mwArray& Orien_Y, mwArray& Orien_Y_N, mwArray& WingBeatFre_X, mwArray& WingBeatFre_X_N, mwArray& WingBeatFre_Y, mwArray& WingBeatFre_Y_N, mwArray& BodyLen_X, mwArray& BodyLen_X_N, mwArray& BodyLen_Y, mwArray& BodyLen_Y_N, mwArray& BodyMass_X, mwArray& BodyMass_X_N, mwArray& BodyMass_Y, mwArray& BodyMass_Y_N, mwArray& WBF_Ind_X, mwArray& WBF_Ind_X_N, mwArray& WBF_Ind_Y, mwArray& WBF_Ind_Y_N, mwArray& HTDiv_X, mwArray& HTDiv_T_N, mwArray& HTDiv_Y, mwArray& HTDiv_H_N, mwArray& PP_X, mwArray& PP_X_N, mwArray& PP_Y, mwArray& PP_Y_N, const mwArray& TrackFile_name, const mwArray& MinLength_Den, const mwArray& MinLength_ParaEst);
					//PrintMessage(_T("���ô�ֱģʽ������"));
					/*func_Playback_VerticalLookingMode(32,
					mwArray& DenProf_X, mwArray& DenProf_X_N, mwArray& DenProf_Y, mwArray& DenProf_Y_N, mwArray& Orien_X, mwArray& Orien_X_N, mwArray& Orien_Y, mwArray& Orien_Y_N, mwArray& WingBeatFre_X, mwArray& WingBeatFre_X_N, mwArray& WingBeatFre_Y, mwArray& WingBeatFre_Y_N, mwArray& BodyLen_X, mwArray& BodyLen_X_N, mwArray& BodyLen_Y, mwArray& BodyLen_Y_N, mwArray& BodyMass_X, mwArray& BodyMass_X_N, mwArray& BodyMass_Y, mwArray& BodyMass_Y_N, mwArray& WBF_Ind_X, mwArray& WBF_Ind_X_N, mwArray& WBF_Ind_Y, mwArray& WBF_Ind_Y_N, mwArray& HTDiv_X, mwArray& HTDiv_T_N, mwArray& HTDiv_Y, mwArray& HTDiv_H_N, mwArray& PP_X, mwArray& PP_X_N, mwArray& PP_Y, mwArray& PP_Y_N, const mwArray& TrackFile_name, const mwArray& MinLength_Den, const mwArray& MinLength_ParaEst);*/
					
					
				}

				// ɨ��ģʽ
				if(toMatlabPara.workingMode == 2)
				{
					func_ScanMode(4, mw_DenProf_X, mw_DenProf_X_N, mw_DenProf_Y, mw_DenProf_Y_N, 
						mw_TrackFile_name, mw_CaliFile_name, mw_StartRan, mw_SampleNum, mw_PRT, mw_PulseWid, mw_WaveForm, mw_CodeType, mw_RCS_ball, mw_Azi_S, mw_Azi_E, mw_Elv_D, mw_Elv_H);
					//PrintMessage(_T("����ɨ��ģʽ������"));
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

				// �ܶ�����*
				mw_DenProf_X_N.GetData(&mx_DenProf_X_N,1);
				mw_DenProf_X.GetData(mx_DenProf_X,mx_DenProf_X_N);
				mw_DenProf_Y_N.GetData(&mx_DenProf_Y_N,1);
				mw_DenProf_Y.GetData(mx_DenProf_Y,mx_DenProf_Y_N);
				memcpy((mx_DenProf_X + mx_DenProf_X_N), mx_DenProf_Y, mx_DenProf_X_N*8);
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg4.m_hWnd, WM_USER+121, (WPARAM)mx_DenProf_X, (LPARAM)&mx_DenProf_X_N);

				// 1����ֲ�*
				mw_Orien_X_N.GetData(&mx_Orien_X_N,1);
				mw_Orien_X.GetData(mx_Orien_X, mx_Orien_X_N);
				mw_Orien_Y_N.GetData(&mx_Orien_Y_N,1);
				mw_Orien_Y.GetData(mx_Orien_Y, mx_Orien_Y_N);
				memcpy((mx_Orien_X + mx_Orien_X_N), mx_Orien_Y, mx_Orien_X_N*8);
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg4.m_hWnd, WM_USER+122, (WPARAM)mx_Orien_X, (LPARAM)&mx_Orien_X_N);

				// 2���Ƶ�ʷֲ�*
				mw_WingBeatFre_X_N.GetData(&mx_WingBeatFre_X_N,1);
				mw_WingBeatFre_X.GetData(mx_WingBeatFre_X, mx_WingBeatFre_X_N);
				mw_WingBeatFre_Y_N.GetData(&mx_WingBeatFre_Y_N,1);
				mw_WingBeatFre_Y.GetData(mx_WingBeatFre_Y, mx_WingBeatFre_Y_N);
				memcpy((mx_WingBeatFre_X + mx_WingBeatFre_X_N), mx_WingBeatFre_Y, mx_WingBeatFre_X_N*8);
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg4.m_hWnd, WM_USER+124, (WPARAM)mx_WingBeatFre_X, (LPARAM)&mx_WingBeatFre_X_N);

				// �峤�ֲ�*
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

				// ���طֲ�*
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

				// ��������ͼ
				mw_PP_X_N.GetData(&mx_PP_X_N, 1);
				mw_PP_X.GetData(mx_PP_X, mx_PP_X_N);
				mw_PP_Y_N.GetData(&mx_PP_Y_N, 1);
				mw_PP_Y.GetData(mx_PP_Y, mx_PP_Y_N);
				memcpy((mx_PP_X + mx_PP_X_N), mx_PP_Y, mx_PP_X_N*8);
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg5.m_hWnd, WM_USER+128, (WPARAM)mx_PP_X, (LPARAM)&mx_PP_X_N);

				// �߶�-ʱ��ֲ�
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

				// ���Ƶ��==�������Ƶ�ʷֲ�
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

				//������Ϣȥ��ͼ
				//::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_formDlg4.m_hWnd, WM_USER+123, (WPARAM)pmx_FreqV_FFT, (LPARAM)&mx_FreqV_FFT_N);
				//return 0;
			}

			else if ((toMatlabPara.mode == 1) && (!b_isTempCountTrack || g_autoCali == 0))	//У׼ģʽ
			{
				func_CaliMode(1,mw_Result,mw_TrackFile_name,mw_CaliFile_name,mw_StartRan,mw_SampleNum,mw_PRT,mw_WaveForm,mw_CodeType,mw_MinLength_Cali/*mw_RCS_ball*/);
				mw_Result.GetData(&mx_Result,1);
				//PrintMessage(_T("����У׼������"));
			}

			tempiCount++;
			*CString str;
			str.Format(_T("%d"), tempiCount);
			PrintMessage(_T("tempiCount:")+str);*/
			if(tempiCount == /*6*/2 && b_isTempCountTrack && g_autoCali == 1)
			{
				tempiCount = 0;
				tempiTwiceCount++;
				if(tempiTwiceCount == 2 && g_autoCaliMode == 0)	// ��ͨ��ͬʱ����Ҫ2��У׼
				{
					b_isTempCountTrack = false;	//	
					tempiTwiceCount = 0;
					PrintMessage(_T("b_isTempCount= false��"));
				}
				else if(tempiTwiceCount == 4 && g_autoCaliMode == 1)	// ��ͨ����ʱ����Ҫ4��У׼
				{
					b_isTempCountTrack = false;
					PrintMessage(_T("b_isTempCount= false��"));

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
			//		if(tempiTwiceCount == 2 && g_autoCaliMode == 0)	// ��ͨ��ͬʱ����Ҫ2��У׼
			//		{
			//			b_isTempCountTrack = false;	//	
			//			tempiTwiceCount = 0;
			//			//PrintMessage(_T("b_isTempCount= false��"));
			//		}
			//		else if(tempiTwiceCount == 4 && g_autoCaliMode == 1)	// ��ͨ����ʱ����Ҫ4��У׼
			//		{
			//			b_isTempCountTrack = false;
			//			//PrintMessage(_T("b_isTempCount= false��"));

			//			tempiTwiceCount = 0;
			//		}
			//	}
			//	//PrintMessage(_T("������У׼������" ));
			//	// ��У׼����
			//	//func_InternalCalibration(const mwArray& TrackFile_name, const mwArray& PulseWid, const mwArray& IntCaliType);
			//	func_InternalCalibration(mw_TrackFile_name, mw_PulseWid, mw_IntCaliType);
			//	//PrintMessage(_T("������У׼������" ));
			//}

			//tempiCount++;
			//CString str;
			//str.Format(_T("%d"), tempiCount);
			//PrintMessage(_T("tempiCount:")+str);
			//if(tempiCount == /*6*/2 && b_isTempCountTrack && g_autoCali == 1)
			//{
			//	tempiCount = 0;
			//	tempiTwiceCount++;
			//	if(tempiTwiceCount == 2 && g_autoCaliMode == 0)	// ��ͨ��ͬʱ����Ҫ2��У׼
			//	{
			//		b_isTempCountTrack = false;	//	
			//		tempiTwiceCount = 0;
			//		PrintMessage(_T("b_isTempCount= false��"));
			//	}
			//	else if(tempiTwiceCount == 4 && g_autoCaliMode == 1)	// ��ͨ����ʱ����Ҫ4��У׼
			//	{
			//		b_isTempCountTrack = false;
			//		PrintMessage(_T("b_isTempCount= false��"));

			//		tempiTwiceCount = 0;
			//	}
			//}

#endif

			g_fifo_track.Free(q);
		}
	}

	return 0;
}

//OriTrackProcess�߳�
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
extern bool b_initFuncV2Param; // ��ʼ��FuncV2������־
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
	// track�������
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
		PrintMessage("targetCounts��"+str);
		str.Format(_T("%d"), cellNumCounts);
		PrintMessage("mx_CellNum��"+str);
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
			PrintMessage(_T("��ʼ���!"));
		}
		/*int mw_TrackCount = mw_Track.NumberOfElements();
		CString str1;
		str1.Format(_T("%d"), mw_TrackCount);
		PrintMessage("TrackOneMatCount��"+str1);
		int mw_CellNumInCount = mw_CellNumIn.NumberOfElements();
		str1.Format(_T("%d"), mw_CellNumInCount);
		PrintMessage("CellNumTempCount��"+str1);
		int mw_EmptyFlagInTemp = mw_EmptyFlagIn.Get(1,1);
		str1.Format(_T("%d"), mw_EmptyFlagInTemp);
		PrintMessage("EmptyFlagTemp��"+str1);*/

		func_Track_v2(6, mw_relevantFlag, mw_TrackOneMat, mw_CellNum, mw_EmptyFlag, mw_packResultFlag, mw_PackName,
			mw_Track, mw_CellNumIn, mw_EmptyFlagIn, mw_oriTrackFileOutputPath, mw_packFlag, mwSavePath);
		packResult = mw_packResultFlag.Get(1, 1);
		if(packResult == 1)
		{
			mwString mx_PackNameTemp = mw_PackName.ToString();
			CString packNameTemp = (CString) mx_PackNameTemp;
			TrackFile_name = trackFilePath + L"\\" + packNameTemp + L".mat";		
			iTimer3Count = 0;
			PrintMessage(L"����ɹ�!");
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
		PrintMessage("---targetCounts��"+str);
		str.Format(_T("%d"), cellNumCounts);
		PrintMessage("---mx_CellNum��"+str);	*/
#if 0
		mxInt32 mx_flag = 0;
		mwArray mw_flag(1, 1, mxINT32_CLASS);
		mw_flag.SetData(&mx_flag, 1);

		char mx_TrackFile_name[1024] = {0};
		WideCharToMultiByte(TrackFile_name, mx_TrackFile_name, 1024);	
		mwArray mw_TrackFile_name(mx_TrackFile_name);

		// У׼�ļ�·��
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



// ���ݷ���
void CSimpleInsectRadarDlg::DisplaySoftDataProcessing(byte* p, UINT len)
{
	UINT nDataType = *((UINT *)p);     //������������������

	switch(nDataType)
	{
	case 0x94EF032B:
		// ���ò���
		g_tcpClient.Send(p, len);
		break;
	case 0x94EF0127:
		// ���ò���MATLAB		
		toMatlabPara.RCS_ball = *((double*)(p+1024*2+10));
		toMatlabPara.dlMinLength_Den = *((double*)(p+1024*2+18));
		toMatlabPara.dlMinLength_ParaEst = *((double*)(p+1024*2+26));
		toMatlabPara.SampleTime = *((double*)(p+1024*2+34));
		toMatlabPara.dlMinLength_ParaEst = *((double*)(p+1024*2+42));
		toMatlabPara.enableAutoCali = *((double*)(p+1024*2+50));
		break;
	case 0x94EF0329:
		// ����ָ��
		//DisplaySoftCmdProcessing(p, len);		   //ָ�����
		//g_tcpClient.Send(p, len);   //��ʼ������ֹͣ����
		m_formDlg1.OnBnClickedButton3();
		break;
	case 0x94EF032D:
		// ��ʼ�洢
		//g_tcpClient.Send(p, len);   //��ʼ�洢ָ�� + �洢��ʼ��ַ��ֹͣ�洢
		m_formDlg1.OnBnClickedButton4();
		break;
	case 0x94EF0111:
		// �ļ��洢ѡ��
		
		break;
	case 0x94EF0129:
		// �ط�
		
		break;
	}
}


//���ݷ���
bool b_autoCaliFlag = false;	// ��У׼ģʽ��־
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
bool b_isWorkStoreFlag = false;	// ���㿪ʼ�������������ʼ�洢��ֹͣ������־
bool b_isTimerOutFlag = false;	// timer 2��ʱ����ֹʱ�䴥����־
int iCountCirculations = 0;		// ��У׼ѭ����������
bool b_isStopCountCirculations = false;	// ��У׼ѭ����ֹ��־

bool b_isSlowScanFlag = false; // ��ɨģʽ״̬

extern bool b_isManualClickBtn;

extern bool b_isSetTimeThreadFlag;
void CSimpleInsectRadarDlg::DataProcessing(byte *p, UINT len)
{
	UINT nDataType = *((UINT *)p);     //������������������
	
	switch (nDataType)
	{
	case 0x94EF0329:				   
		CmdProcessing(p, len);		   //ָ�������
#if DFLAG
		g_tcpDisplaySoftClient.Send(p, len); // һά����������ת�����Կ�
#endif
		break;
	case 0x94EF032B:    
		g_udpClientCmdFeedBack.Send(p, len);// �������Կ�
		RadarParaProcessing(p, len);   //���ò�����������
		g_bflag_paracfg = true;
		if((b_tempFlag_paracfg && g_autoCali == 1) || isAutoClickStartWorkButton)
		{			
			Sleep(2000);
			//PrintMessage(_T("�����ʼ����~~~"));
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+891, NULL, NULL);	// �����ʼ������ť
			//isAutoClickStartWorkButton = false;
			//::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+890, NULL, NULL);	// ��ʼ�洢
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
		if(b_isOkBtnParaConfig)	// �ֶ����ò��������
		{
			b_isCountTrack = true;	// ��������ڶ�ʱ�У���ʼ2��trackֹͣ������
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

			if(g_workMode == 1)	// ��ʱģʽ�����������߳�
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
				g_nPara_7 = 0;	// ��ʼ��������Ϊ0
				toMatlabPara.StartRan = 0;	// ��ʼ��������
				tempRadarPara.nPara_7 = 0;	// ��ʼ��������-to DSP----����ģʽ����������ʼ��������
				tempRadarPara.nPara_dptInitSampDist = 0; // ����ģʽ�¸�������ʼ��������
				tempRadarPara.nPara_48 = 0.5;	// ���βɼ�ʱ�� 0.5
			}
			//debug
			/*CString str;
			str.Format(_T("%.2f"), tempRadarPara.nPara_48);
			PrintMessage("���βɼ�ʱ�䣺" +str);
			str.Format(_T("%.2f"), toMatlabPara.StartRan);
			PrintMessage("��ʼ�������룺" +str);*/

		}
		break;
	case 0x94EF0331:
		HRRPProcessing(p, len);		   //һά�������ϵͳ����״̬����
#if DFLAG
		g_tcpDisplaySoftClient.Send(p, len); // һά����������ת�����Կ�
#endif
		break;
	case 0x94EF032D:				   //ָ�������ֹͣ�洢
		{
			PrintMessage(_T("ֹͣ�洢����"));
			//logFile.WriteLog(_T("�յ�ֹͣ�洢������"));
			//g_workMode = 1;
			int b = TRUE;
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+779, (WPARAM)&b, NULL);
			PostMessage(WM_USER+111, (WPARAM)p, (LPARAM)&len);

			if(b_isTimerOutFlag)
			{
				iCountCirculations++;	// ÿ����һ����У׼ѭ������һ��
				b_isCountTrack = true;
				b_isTempCountTrack = true;
				iCount = 0;
				tempiCount = 0;
				//PrintMessage(_T("2���ӵ���"));
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

			
			// ��ʼ�ϴ�����
			if((g_zhuanCun == 1) && (iCountCirculations == g_zhuanCunTime) && (g_workMode == 1) && (g_autoCali == 1))
			{
				b_isWorkStoreFlag = true;	// ���ټ������ò����������¸���У׼ѭ��
				b_isStopCountCirculations = true;	// ��У׼ѭ��������ֹ��־���±߿�ʼת�����ݲ���
			}

			if(g_stopWorkFlag == 1)
			{
				//PrintMessage(_T("���ֹͣ����~~~"));
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+889, NULL, NULL);	// ��ʼ��ֹͣ����
			}
			if(/*b_isStopStoreFlag*//*g_autoCali == 1*/ b_autoCaliFlag) // ��У׼ģʽ����ɨģʽ
			{
				//b_isSimulateClickBtn = true;
				//PrintMessage(_T("���ֹͣ����~~~"));
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+891, NULL, NULL);	// ֹͣ����
			}
#if DFLAG
			g_tcpDisplaySoftClient.Send(p, len); // һά����������ת�����Կ�
#endif
			break;
		}
		
	//case 0x8d8d8d8d:
	//	PrintMessage(_T("��ʼ�洢����"));
	//	break;
	case 0x9e9e9e9e:
		{
			g_bWritingFile = true;    //��־λ������ʼ�ϴ�
			//m_pWriteFileThread->ResumeThread();
			PrintMessage(_T("��ʼ�ϴ�����"));
#if DFLAG
			g_tcpDisplaySoftClient.Send(p, len); // һά����������ת�����Կ�
#endif
			break;
		}
		
	//case 0xafafafaf :
	//	PrintMessage(_T("ֹͣ�ϴ�����"));
	//	PostMessage(WM_USER+111, (WPARAM)p, (LPARAM)&len);
	case 0x94EF0333: // �㼣���ݷ�����
		{
			/*static int iChunZhiCount = 0;*/
			if(toMatlabPara.workingMode == 3)
			{
				
				if(iChunZhiCount % 2 == 0)
				{
					g_nPara_7 = tempRadarPara.nPara_dptInitSampDist * 15;// ��������ʼ��������60
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
			b_isSimulateClickBtn = false;	// �Ƿ�������track��ֹͣ������״̬
			DetectProcessing(p, len);		//Track���ݡ�������MATLAB������
			CString str;
			static int i = 0;
			//static int iCount = 0;
			//static int iTwiceCount = 0;
			iCount++;
			i++;
			str.Format(_T("track_%d"), i);
			//PrintMessage(str);
			b_isTrackFlag = true;

			// ������track��ֹͣ�洢
			if(iCount == /*6*/2 && b_isCountTrack && g_autoCali == 1)
			{
				b_isSimulateClickBtn = true;
				//PrintMessage(_T("���ֹͣ�洢~~~"));
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+890, NULL, NULL);	// ֹͣ�洢
				b_isStopStoreFlag = true;
				
				iCount = 0;
				iTwiceCount++;
				if(iTwiceCount == 2 && g_autoCaliMode == 0)	// ��ͨ��ͬʱ����Ҫ2��У׼
				{
					b_isCountTrack = false;	// ֹͣ����track����
					iTwiceCount = 0;
					b_isTenMinWorktFlag = true;
				}
				else if(iTwiceCount == 4 && g_autoCaliMode == 1)	// ��ͨ����ʱ����Ҫ4��У׼
				{
					b_isCountTrack = false;	// ֹͣ����track����
	
					iTwiceCount = 0;
					b_isTenMinWorktFlag = true;
				}
			}
#if DFLAG
			g_tcpDisplaySoftClient.Send(p, len); // һά����������ת�����Կ�
#endif
			break;
		}
	case 0x22334455:
		{
			TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
			GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
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

// �Կ�����·�ָ�����
void CSimpleInsectRadarDlg::DisplaySoftCmdProcessing(byte* p, UINT len)
{
	UINT nCmdType = *((UINT *)(p + 8));
	switch(nCmdType)
	{
	case 0x01:		    //ָ��������Լ�		
		PrintMessage(_T("�Լ����"));
		break;
	case 0x03:
		// ��ʼ����
		m_formDlg1.OnBnClickedButton3();
		break;
	case 0x04:
		// ֹͣ����
		m_formDlg1.OnBnClickedButton3();
		break;
	case 0x06:
		// ֹͣ�洢
		m_formDlg1.OnBnClickedButton4();
		break;
	case 0x0a:
		// ֹͣ�ϴ�
		break;
	}
	delete []p;
	p = NULL;
}


//ָ�������
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
	case 0x01:		    //ָ��������Լ�		
		PrintMessage(_T("�Լ����"));
		break;
	case 0x02:			//ָ���������������	
		PrintMessage(_T("�����������"));
		g_bflag_paracfg = true;
		break;
	case 0x03:			//ָ���������ʼ����
		{		
			PrintMessage(_T("��ʼ����"));
			//g_startWorkFlag = 1;
			b_isWorkStoreFlag = true;
			g_bflag_paracfg = false;
			g_bflag_enable = false;		//��ʼ������˱�־λfalse�����Բ������õ�ȷ����ť
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+223, NULL, NULL);
			if(b_tempFlag_paracfg && g_autoCali == 1)	// �Զ�ģʽ��ģ�ⷢ��Ϣ
			{
				Sleep(3000);
				//PrintMessage(_T("�����ʼ�洢~~~"));
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+890, NULL, NULL);	// ��ʼ�洢
				b_tempFlag_paracfg = false;	// ���ò�����־
				if(b_isTenMinWorktFlag)	// �����ʼ10���ӱ�־Ϊ�棬������ʱ
				{
					if(g_slowScan == 1) // ��ɨģʽ
					{
						if(verticalOrSlowScanCount & 1)
						{
							PrintMessage(_T("10S"));
							PrintMessage(_T("��ɨ~~~"));
							SetTimer(2, 10000, NULL);
						}
						else
						{
							PrintMessage(_T("15S"));
							PrintMessage(_T("����~~~"));
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
				//PrintMessage(_T("�����ʼ�洢~~~"));
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+890, NULL, NULL);	// ��ʼ�洢

			}
			//if(g_slowScan == 1) // ��ɨģʽ
			//{

			//}
			break;
		}
	case 0x04:			//ָ�������ֹͣ����
		{
			PrintMessage(_T("ֹͣ����"));
			//logFile.WriteLog(_T("�յ�ֹͣ����������"));
			memset(pTemp, 0, HRRPBUFFERSIZE);
			g_bflag_enable = true;
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+224, NULL, NULL);

			// ��ʼת��
			if(b_isStopCountCirculations)
			{
				// ������Ϣ��ʼת������
				::SendMessage(m_formDlg2.m_hWnd, WM_USER+892, NULL, NULL);
				//PrintMessage(_T("���͵����ʼ�ϴ���ť��Ϣ��"));
			}

			if((g_workMode == 1 && !b_isWorkStoreFlag && b_isTimeOutFlag) || (b_isStopStoreFlag && !b_isWorkStoreFlag) /*|| g_slowScan == 1*//* || isAutoClickStartWorkButton*/)	// ���ò���
			{
				PrintMessage(_T("�Զ���Σ�����"));
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

				if(b_isTempCountTrack && g_autoCali == 1)	// �Զ���У׼ģʽ
				{
					tempRadarPara.nPara_7 = 0;	// ��ʼ��������Ϊ0---��dsp������Ҫ��0��
					tempRadarPara.nPara_dptInitSampDist = 0; // ����ģʽ�¸�������ʼ��������
					toMatlabPara.StartRan = 0;
					g_nPara_7 = 0;			
					tempRadarPara.nPara_48 = 0.5;	// ���β���ʱ��0.5
					str.Format(_T("%d"), g_nPara_7);
					//PrintMessage(_T("g_nPara_7")+str);
				}
				else if(b_isTenMinWorktFlag) // ����У׼ģʽ��
				{
					tempRadarPara.nPara_7 = tempnPara_7;	// ���Զ�У׼ģʽ��Ϊʵ��ֵ
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
				PrintMessage("���βɼ�ʱ�䣺"+str);*/

				// ��ͨ��ͬʱ��2��У׼ָ��
				if(iTwiceCount == 0 && g_autoCaliMode == 0)
				{
					tempRadarPara.nPara_13 = 0;
					//tempRadarPara.nPara_7 = 0;	// ��ʼ��������-0-dsp
					//toMatlabPara.StartRan = 0;	// ��ʼ��������-0-matlab
					tempRadarPara.nPara_14 = 160;	// 101
					toMatlabPara.UintCaliType = 5;	
				}
				else if(iTwiceCount == 1 && g_autoCaliMode == 0)
				{
					tempRadarPara.nPara_13 = 0;
					//tempRadarPara.nPara_7 = 0;
					//toMatlabPara.StartRan = 0;	// ��ʼ��������-0-matlab
					tempRadarPara.nPara_14 = 192;	// 110
					toMatlabPara.UintCaliType = 6;				
				}				
				else
				{
					tempRadarPara.nPara_7 = tempnPara_7;	// ��У׼ģʽ��Ϊʵ��ֵ-��ʼ��������
					toMatlabPara.StartRan = tempStartRan;
				}

				// ��ͨ����ʱ��4��У׼ָ��
				if(iTwiceCount == 0 && g_autoCaliMode == 1)
				{
					tempRadarPara.nPara_13 = 1;
					
					tempRadarPara.nPara_14 = 32;	// 001
					tempRadarPara.nPara_detectionChannel = 0; // HHͨ��У׼������1У׼
					toMatlabPara.UintCaliType = 1;
				}
				else if(iTwiceCount == 1 && g_autoCaliMode == 1)
				{
					tempRadarPara.nPara_13 = 1;
	
					tempRadarPara.nPara_14 = 64;	// 010
					tempRadarPara.nPara_detectionChannel = 1; // HVͨ��У׼������2У׼
					toMatlabPara.UintCaliType = 2;

					
				}
				else if(iTwiceCount == 2 && g_autoCaliMode == 1)
				{
					
					tempRadarPara.nPara_13 = 0;
					
					tempRadarPara.nPara_14 = 96;	// 011
					tempRadarPara.nPara_detectionChannel = 0; // HHͨ��У׼������1У׼
					toMatlabPara.UintCaliType = 3;

					
				}
				else if(iTwiceCount == 3 && g_autoCaliMode == 1)
				{
					tempRadarPara.nPara_13 = 1;
					//tempRadarPara.nPara_7 = 0;
					//toMatlabPara.StartRan = 0;	// ��ʼ��������-0-matlab
					tempRadarPara.nPara_14 = 128;	// 100
					tempRadarPara.nPara_detectionChannel = 2; // VHͨ��У׼������2У׼
					toMatlabPara.UintCaliType = 4;

					
				}
				

				/*str.Format(_T("%.2f"), tempRadarPara.nPara_14);
				PrintMessage("���У׼ָ�"+str);*/
				if(b_isTenMinWorktFlag)
				{
					tempRadarPara.nPara_14 = 0;
					tempRadarPara.nPara_13 = 0;	// ��������ģʽ��У׼ͨ��ʹ����Ϊ0

					tempRadarPara.nPara_7 = tempnPara_7;	// ��У׼ģʽ��Ϊʵ��ֵ-��ʼ��������
					toMatlabPara.StartRan = tempStartRan;

					// �ŷ���������
					if(verticalOrSlowScanCount & 1) // ��ɨģʽ:�ŷ�������ʽ���õ��̶�άɨģʽ
					{
						tempRadarPara.nPara_15 = 7;// ����ת��ģʽ����λģʽ
						tempRadarPara.nPara_16 = 6;// ����������
						tempRadarPara.nPara_18 = -180;// ��λ��ʼ�Ƕ�
						tempRadarPara.nPara_19 = 180;// ��λ��ֹ�Ƕ�
						tempRadarPara.nPara_21 = 10;// ������ʼ�Ƕ�
						tempRadarPara.nPara_22 = 82;// ������ֹ�Ƕ�
						tempRadarPara.nPara_20 = 15;// ��λ��ɨ���ٶ�
						tempRadarPara.nPara_23 = 15;// ������ɨ���ٶ�
						PrintMessage(_T("��ɨģʽ-������ɨ���ٶȣ�15"));	
					}
					else // ��У׼ģʽ������ģʽ���ŷ�����ģʽ���ö�λģʽ
					{
						tempRadarPara.nPara_15 = 2;// ����ת��ģʽ����λģʽ
						tempRadarPara.nPara_21 = 90; // ������ʼ�Ƕ�
						PrintMessage(_T("����-�����Ƕȣ�90"));	
					}
				}
				else
				{
					tempRadarPara.nPara_7 = 0;	// У׼ģʽ��Ϊʵ��ֵ-��ʼ��������
					toMatlabPara.StartRan = 0;
				}

				if(/*g_autoCali == 1*/ b_autoCaliFlag)
				{
					b_tempFlag_paracfg = true;	// ��У׼�Զ���ʼ������־
				}
				if((b_isSetTimeThreadFlag || g_autoCali == 0) && g_workMode == 1)	// ������ʱģʽ
				{
					AfxBeginThread(countThread, this);
				}

				// ���ò���
				//PrintMessage(_T("�Զ����ò�����"));
				Sleep(1000);
				
			
			
				int tt = 0;
				tt = g_tcpClient.Send((byte *)(&tempRadarPara), sizeof(tempRadarPara));
				//GetData_ToMatlab(toMatlabPara);
				CString str01;
				str01.Format(_T("%d"), tempRadarPara.nPara_7);
				PrintMessage("��ʼ�������룺"+str01);

				if (tt == sizeof(tempRadarPara))
				{
					::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+400, NULL, NULL);
					//GetData_ToMatlab(toMatlabPara);
				}
				

				b_isTimeOutFlag = false;	// ��ʱģʽʱ�䵽��־λ
				
				if(b_isManualClickBtn)	// ��������track��ʱ״̬��ÿ���Զ����ò�������������Ϊ0
				{
					b_isCountTrack = true;	// ��������ڶ�ʱ�У���ʼ2��trackֹͣ������
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
		
	case 0x05:			//ָ���������ʼ�洢
		{
			PrintMessage(_T("��ʼ�洢"));
			b_isWorkStoreFlag = false;
			int b = FALSE;
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+779, (WPARAM)&b, NULL);
			break;
		}
	case 0x06:			//ָ�������ֹͣ�洢
		{
			PrintMessage(_T("ֹͣ�洢"));
			//logFile.WriteLog(_T("�յ�ֹͣ�洢������"));
			//m_criticalsectionStop.Lock();
			//g_bisStopSave = false;
			//m_criticalsectionStop.Unlock();
			int b = TRUE;
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+779, (WPARAM)&b, NULL);
			break;
		}
	case 0x07:			//ָ�����������У׼
		PrintMessage(_T("����У׼"));
		break;
	case 0x08:			//ָ��������ջ�У׼
		PrintMessage(_T("�ջ�У׼"));
		break;
	case 0x09:
		PrintMessage(_T("��ʼ�ϴ�����"));

		g_bWritingFile = true;
		//m_pWriteFileThread->ResumeThread();

		//PrintMessage(_T("��ʼ�ϴ�����"));
		break;
	case 0x0a:			//ָ�������ֹͣ�ϴ�����		
		PrintMessage(_T("ֹͣ�ϴ�����"));
		
		g_bWritingFile = false;   //��־λ����ֹͣ�ϴ�
		
		break;
	case 0x0b:			//ָ����������ݲ���
		PrintMessage(_T("���ݲ����ɹ�"));
		break;
	default:
		//ASSERT(false);
		PrintMessage(_T("������Ϣ���󣡣���"));
		break;
	}

	delete []p;
	p = NULL;
}


//���ò�����������
void CSimpleInsectRadarDlg::RadarParaProcessing(byte *p, UINT len)
{
	//RadarPara radaPara = {0};
	//memcpy(&radaPara, p, sizeof(radaPara));
	//m_formDlg1.m_dlgParaConfig.m_radarPara
	//while()
	//{
	PrintMessage(_T("����������ϣ�����"));
	//}
	delete []p;
	p = NULL;

	// ���������߳�
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
		// ��ȡ��ǰϵͳʱ��
		SYSTEMTIME curSystemTime;
		GetLocalTime(&curSystemTime);
		
		//TRACE("%d\n", curSystemTime.wMinute);
		if((curSystemTime.wHour == setTimeInfo.iStartHour) && (curSystemTime.wMinute == setTimeInfo.iStartMinute) 
			&& curSystemTime.wSecond == setTimeInfo.isStartSecond /*&& curSystemTime.wMilliseconds == setTimeInfo.iStartMilliseconds*/)
		{
			// ����Ϣ��ģ������ʼ��ť
			::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+888, NULL, NULL);
			//PrintMessage(_T("ʱ�䵽����ʼ������"));
			//logFile.WriteLog(_T("SendMessage---��ʼ��������ʼ�洢"));
			break;
		}
		Sleep(1);
		OutputDebugString(_T("��ȡʱ�䣡\n"));
	}

	return 0;
}


//һά�������ϵͳ����״̬
void CSimpleInsectRadarDlg::HRRPProcessing(byte *p, UINT len)
{
	//static DWORD t1 = 0;
	//DWORD t2 = GetTickCount();

	m_criticalsection.Lock();
	PrintMessage(_T("HRRPProcessing��"));
	memcpy(pTemp, p, len);				//�����յ������ݸ��Ƶ�ȫ�ֻ����У����ڻ�ͼ��ʾ

	m_criticalsection.Unlock();
#if 1
	// һά������洢
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
		CreateDirectory(HRRPFilePathTemp, 0); // ������·���ʹ���
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
	PrintMessage(_T("HRRPProcessing-------��"));
	HRRPFilePathTemp = "";
	CloseHandle(hHrrpFile);
#endif
	//if (t2 - t1 > 100)
	//{
	//	if (!g_bWritingFile)
	//	{
	//		//���״��Կؽ��淢����Ϣ
	//		::SendMessage(m_formDlg1.m_hWnd, UPDATEFORMDLG1_UI, (WPARAM)p, (LPARAM)&len);
	//	}
	//	else if (g_bWritingFile)
	//	{
	//		//�������ϴ����淢����Ϣ
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

	//memcpy(pTemp, p, len);				//�����յ������ݸ��Ƶ�ȫ�ֻ����У����ڻ�ͼ��ʾ

	//m_criticalsection.Unlock();

	byte *q = NULL;
	while((q = g_fifo_track.Alloc()) == NULL);
	memcpy(q, p, len);
	g_fifo_track.Push(q);

	delete []p;

	p = NULL;
}


//û�õ�--SATA�����Ĵ洢������ַ
void CSimpleInsectRadarDlg::SATAEndAddress(byte *p, UINT len)
{
	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
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

			//������ʾ
			CString strFileName;
			strFileName.Format(_T("%.4d_%.2d_%.2d-%.2d_%.2d_%.2d.dat"),
				p->systime.wYear, p->systime.wMonth, p->systime.wDay, 
				p->systime.wHour, p->systime.wMinute, p->systime.wSecond);

			theApp.m_pMainDlg->m_filelist.InsertItem(0, strFileName);  //�����ļ���;
			ULONGLONG uEachFileSize = ((p->EndAddress) - (p->BeginAddress)) / (1024 * 1024);
			CString strEachFileSize;
			strEachFileSize.Format(_T("%d"), uEachFileSize);
			theApp.m_pMainDlg->m_filelist.SetItemText(0, 1, strEachFileSize);  //�����ļ���С
		}
	}

	file.Close();
}

//�����ļ�
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


//����ļ��б��Ҽ���Ӧ
void CSimpleInsectRadarDlg::OnNMRClickListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡ�������
	CPoint ptCurSel(0, 0);
	GetCursorPos(&ptCurSel);

	NMLISTVIEW  *pNMListView = (NMLISTVIEW *)pNMHDR;

	//�����ѡ����
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
//�����ļ�
void CSimpleInsectRadarDlg::OnReadfile()
{
	m_fileSelectedArray.RemoveAll();

	int totalCnt = m_filelist.GetItemCount();

	//��ⱻѡ�е������¼
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
		MessageBox(_T("�����ܶ���һ����ѡ�������Ҽ���Ӧ"));
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
	//theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON8)->SetWindowTextW(_T("ֹͣ�ϴ�"));
	//
	//if (!m_pWriteFileThread)
	//{
	//	//m_pWriteFileThread->ResumeThread();
	//	m_pWriteFileThread = AfxBeginThread(WriteFileThread, this); //�������ļ��߳�
	//}
	
}


afx_msg LRESULT CSimpleInsectRadarDlg::OnUser777(WPARAM wParam, LPARAM lParam)
{

	g_bWritingFile = true;
	int n = m_fileSelectedArray.GetCount();
	b_flag4 = true;
	//theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON8)->SetWindowTextW(_T("ֹͣ�ϴ�"));
	theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
	
	if (!m_pWriteFileThread)
	{
		//m_pWriteFileThread->ResumeThread();
		m_pWriteFileThread = AfxBeginThread(WriteFileThread, this); //�������ļ��߳�
	}

	return 0;
}

//д�����ļ��߳�
UINT CSimpleInsectRadarDlg::WriteFileThread(LPVOID lpParam)
{
	return ((CSimpleInsectRadarDlg *)lpParam)->WriteProcess();
}


//д�����ļ�����
UINT CSimpleInsectRadarDlg::WriteProcess()
{
	int nFileCount = m_fileSelectedArray.GetSize();   //�õ���Ҫ�ϴ��ļ��ĸ���

	for (int i=0; i<nFileCount; i++)
	{
		if (g_bWritingFile)
		{
			//��ȡ�ļ������ض�λ��Ԫ��
			m_nItem = m_fileSelectedArray.GetAt(i);
			POSITION pos;
			pos = theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.FindIndex(m_fileSelectedArray.GetAt(i));
			FILELISTINFO *p = (FILELISTINFO *)theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetAt(pos);
			//nItem = m_fileSelectedArray.GetAt(i);

			//��ȡ�ϴ���ʼ��ַ���ϴ����ݳ���
			UINT nHead = 0x9e9e9e9e;
			UINT nLen = 16;
			ULONGLONG ulBeginAddress = p->BeginAddress + g_startAddress * (ULONGLONG)(1024 * 1024);
			ULONGLONG ulFileSize = 0;
			ulFileSize = g_singleFileSize * (ULONGLONG)(1024 * 1024);
			ULONGLONG k = 0;
			k = ulFileSize / (320 * 1024);			//������

			//��DSP->FPGA�·��ϴ���ʼ��ַ���ϴ����ݳ���
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

			//��FIFO���ļ�
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

					//if (((ULONGLONG)j * /*FifoWith*/(320 * 1024)) == ulFileSize)   //����ָ���ļ���С����������ʼ����һ���ļ�
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

			//�ر��ļ�
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


//û�õ�
double CSimpleInsectRadarDlg::GetFileTransRate(int &n)
{
	
	//m_criticalsection.Lock();
	//n = nItem;
	return 0.0;
}

extern bool b_flag2; // ��ʼ/ֹͣ�洢��־
bool bTempOriTrackFlag = false;
int CPIOut = 1;
extern bool bOriTrackEmpty; // OriTrack�ļ����Ƿ�Ϊ�ձ�־
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
				::SendMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+890, NULL, NULL);	// ��ʼ�洢
				b_isTimerOutFlag = true;
				b_isTenMinWork = false;
				b_isTenMinWorktFlag = false;	// ����У׼ģʽ��־λ
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
			// ���ݽ���	
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
			TCHAR szTrackLogPath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
			GetModuleFileName( NULL, szTrackLogPath, MAX_PATH);   //���ϵͳ·��
			(_tcsrchr(szTrackLogPath, _T('\\')))[1] = 0;
			//wcscpy(gszSettingPath , szModulePath);
			wcscat(szTrackLogPath , _T("TrackLog.txt"));	// ����tracklog�ļ�
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
				// ���ݽ���	
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
				TCHAR szTrackLogPath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
				GetModuleFileName( NULL, szTrackLogPath, MAX_PATH);   //���ϵͳ·��
				(_tcsrchr(szTrackLogPath, _T('\\')))[1] = 0;
				//wcscpy(gszSettingPath , szModulePath);
				wcscat(szTrackLogPath , _T("TrackLog.txt"));	// ����tracklog�ļ�
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
			// У׼�ļ�·��
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

//ˢ�½������ò�����ʾ����
afx_msg LRESULT CSimpleInsectRadarDlg::OnUser400(WPARAM wParam, LPARAM lParam)
{
	if (m_formDlg1.m_dlgParaConfig)
	{
		m_listPrint.DeleteAllItems();
		CString str;
		m_listPrint.InsertItem(0, _T("����ģʽ"));						//����ģʽ
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO1,str);	
		m_listPrint.SetItemText(0, 1, str);

		//�������ģʽ
		int nItem = m_formDlg1.m_dlgParaConfig.m_combox1.GetCurSel();
		if (nItem == 0 || nItem == 2)
		{
			m_listPrint.SetItemText(0, 2, _T("�������ģʽ"));				
			m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO2,str);	
			m_listPrint.SetItemText(0, 3, str);
		}
		else
		{
			m_listPrint.SetItemText(0, 2, _T("�������ģʽ"));				
			m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO17,str);	
			m_listPrint.SetItemText(0, 3, str);
		}
		
		//Զ�ನ������
		if (nItem == 0 || nItem == 1)
		{
			m_listPrint.InsertItem(1, _T("Զ�ನ������"));
			m_listPrint.SetItemText(1, 1, _T("0.1us"));

		}
		else
		{
			m_listPrint.InsertItem(1, _T("Զ�ನ������"));					
			m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO11,str);	
			m_listPrint.SetItemText(1, 1, str);
		}
		

		m_listPrint.SetItemText(1, 2, _T("PRT"));						//PRT
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO3,str);	
		m_listPrint.SetItemText(1, 3, str);

		m_listPrint.InsertItem(2, _T("����������"));					//����������
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO5,str);	
		m_listPrint.SetItemText(2, 1, str);

		m_listPrint.SetItemText(2, 2, _T("��ʼ��������"));				//��ʼ��������
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO12,str);	
		m_listPrint.SetItemText(2, 3, str);

		m_listPrint.InsertItem(3, _T("ʵʱ�����ϴ�����"));				//ʵʱ�����ϴ�����
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO6,str);	
		m_listPrint.SetItemText(3, 1, str);

		m_listPrint.SetItemText(3, 2, _T("��Ϣ�ϴ�����"));				//��Ϣ�ϴ�����
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO4,str);	
		m_listPrint.SetItemText(3, 3, str);

		m_listPrint.InsertItem(4, _T("������Ƶ����"));					//������Ƶ����
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

		m_listPrint.SetItemText(4, 2, _T("����ת��ģʽ"));					//����ת��ģʽ
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO15,str);	
		m_listPrint.SetItemText(4, 3, str);
		
		m_listPrint.InsertItem(5, _T("AGC������1"));						//AGC������1
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO7,str);	
		m_listPrint.SetItemText(5, 1, str);

		m_listPrint.SetItemText(5, 2, _T("У׼ͨ��ʹ��"));					//У׼ͨ��ʹ��
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO9,str);	
		m_listPrint.SetItemText(5, 3, str);

		m_listPrint.InsertItem(6, _T("AGC������2"));						//AGC������2
		m_formDlg1.m_dlgParaConfig.GetDlgItemText(IDC_COMBO8,str);	
		m_listPrint.SetItemText(6, 1, str);

		m_listPrint.SetItemText(6, 2, _T("У׼ͨ������"));					//У׼ͨ������
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


//����DSP�ش��Ľ����洢��ַ�����ļ�
afx_msg LRESULT CSimpleInsectRadarDlg::OnUser111(WPARAM wParam, LPARAM lParam)
{
	BYTE *p = (BYTE*)wParam;

	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
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

			//������ʾ
			CString strFileName;
			strFileName.Format(_T("%d_%.4d_%.2d_%.2d-%.2d_%.2d_%.2d.dat"), i, 
				p->systime.wYear, p->systime.wMonth, p->systime.wDay, 
				p->systime.wHour, p->systime.wMinute, p->systime.wSecond);

			theApp.m_pMainDlg->m_filelist.InsertItem(0, strFileName);  //�����ļ���;
			ULONGLONG uEachFileSize = ((p->EndAddress) - (p->BeginAddress)) / (1024 * 1024);
			CString strEachFileSize;
			strEachFileSize.Format(_T("%d"), uEachFileSize);
			theApp.m_pMainDlg->m_filelist.SetItemText(0, 1, strEachFileSize);  //�����ļ���С
			i--;
		}
	}

	file.Close();


	//����formdlg1��formdlg2�е�SATA�洢����
	double dl = theApp.m_pMainDlg->m_formDlg1.calculSATAVolum();
	CString strLastFileSize;
	strLastFileSize.Format(_T("%.2f"), dl);
	theApp.m_pMainDlg->m_formDlg1.m_SATAVolum.SetText(strLastFileSize);
	theApp.m_pMainDlg->m_formDlg2.m_SATAVolum.SetText(strLastFileSize);
	theApp.m_pMainDlg->m_formDlg1.m_SATASaveSpeed.SetText(_T("0000.00"));


	//UpdateData(FALSE);

	return 0;
}


//��ʼ�ϴ���Ӧ����
afx_msg LRESULT CSimpleInsectRadarDlg::OnUser333(WPARAM wParam, LPARAM lParam)
{
	g_bWritingFile = true;
	int n = m_fileSelectedArray.GetCount();
	b_flag4 = true;
	//theApp.m_pMainDlg->m_formDlg2.GetDlgItem(IDC_BUTTON8)->SetWindowTextW(_T("ֹͣ�ϴ�"));

	if (!m_pWriteFileThread)
	{
		//m_pWriteFileThread->ResumeThread();
		m_pWriteFileThread = AfxBeginThread(WriteFileThreadEx, this); //�������ļ��߳�
	}

	return 0;
}

//д�ļ��߳�
UINT CSimpleInsectRadarDlg::WriteFileThreadEx(LPVOID lpParam)
{
	return ((CSimpleInsectRadarDlg *)lpParam)->WriteProcessEx();
}


//д�ļ�����
UINT CSimpleInsectRadarDlg::WriteProcessEx()
{
	int nFileCount = m_fileSelectedArray.GetSize();   //�õ���Ҫ�ϴ��ļ��ĸ���

	//����ʼ�ϴ���ť�û�
	BOOL bShowWindow = FALSE;
	::SendMessage(theApp.m_pMainDlg->m_formDlg2.m_hWnd, WM_USER+778, (WPARAM)&bShowWindow, NULL);

	//CString strFileName;
	//strFileName = _T("1.bin");
	//strFileName = strFileSavePath + _T("\\") + strFileName;
	//m_hFile = CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//SetTimer(1, 1000, NULL);            //���ö�ʱ��������ˢ��listctrl��ת�����
	//m_formDlg2.SetTimer(1, 1000, NULL);
	for (int i=0; i<nFileCount; i++)
	{
		if (g_bWritingFile)
		{
			//��ȡ�ļ������ض�λ��Ԫ��
			m_nItem = m_fileSelectedArray.GetAt(i);
			POSITION pos;
			pos = theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.FindIndex(m_fileSelectedArray.GetAt(i));
			FILELISTINFO *p = (FILELISTINFO *)theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetAt(pos);

			//��ȡ�ϴ���ʼ��ַ���ϴ����ݳ���
			UINT nHead = 0x9e9e9e9e;
			UINT nLen = 16;
			ULONGLONG ulBeginAddress = p->BeginAddress;
			ULONGLONG ulFileSize = 0;
			ulFileSize =(p->EndAddress) - (p->BeginAddress);		//�ļ���С
			ULONGLONG k = 0;
			k = ulFileSize / (320 * 1024);			//������

			//��DSP->FPGA�·��ϴ���ʼ��ַ���ϴ����ݳ���
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

			//��FIFO���ļ�
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

					//if (((ULONGLONG)j * 320 * 1024) == ulFileSize)   //����ָ���ļ���С����������ʼ����һ���ļ�
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

			//�ر��ļ�
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

	//����ʼ�ϴ���ť����
	bShowWindow = TRUE;
	::SendMessage(theApp.m_pMainDlg->m_formDlg2.m_hWnd, WM_USER+778, (WPARAM)&bShowWindow, NULL);

	return 0;
}

extern int iunloadingFileNum;
afx_msg LRESULT CSimpleInsectRadarDlg::OnUser555(WPARAM wParam, LPARAM lParam)
{
	CString str;
	KillTimer(1);

	str = _T("ת�����");
	m_filelist.SetItemText(m_nItem, 2, str);

	//������λ����������
	double dLeftSize = theApp.m_pMainDlg->m_formDlg2.calculDiskVolum();
	CString strShow = _T("");
	strShow.Format( _T("%0.2f"), dLeftSize );
	theApp.m_pMainDlg->m_formDlg2.m_DiskRemainVolum.SetText( strShow );

	theApp.m_pMainDlg->m_formDlg2.m_SATATransSpeed.SetText( _T("0000.00") );

	static int tempi = 0;
	tempi++;
	if((tempi == iunloadingFileNum) && g_workMode == 1 && g_autoCali == 1)	// �ڶ�ʱ����У׼�´���
	{
		Sleep(2000);
		// ���͵������sata�̰�ť����Ϣ
		::SendMessage(m_formDlg2.m_hWnd, WM_USER+893, NULL, NULL);
		PrintMessage(_T("���͵��������ť��Ϣ��~~~"));
		tempi = 0;
	}

	//UpdateData(FALSE);

	return 0;
}

// ���������
afx_msg LRESULT CSimpleInsectRadarDlg::OnUser894(WPARAM wParam, LPARAM lParam)
{
	if((g_workMode == 1 && !b_isWorkStoreFlag && b_isTimeOutFlag) || (b_isStopStoreFlag && !b_isWorkStoreFlag))	// ���ò���
	{

		if(b_isManualClickBtn && g_autoCali == 1)
		{
			b_isTempCountTrack = true;
		}

		if(b_isTempCountTrack && g_autoCali == 1)	// �Զ���У׼ģʽ
		{
			tempRadarPara.nPara_7 = 0;	// ��ʼ��������Ϊ0---��dsp������Ҫ��0��
			tempRadarPara.nPara_dptInitSampDist = 0; // ����ģʽ�¸�������ʼ��������
			toMatlabPara.StartRan = 0;
			g_nPara_7 = 0;			
			tempRadarPara.nPara_48 = 0.5;
		}
		else
		{
			tempRadarPara.nPara_7 = tempnPara_7;	// ���Զ�У׼ģʽ��Ϊʵ��ֵ
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
		PrintMessage("���βɼ�ʱ�䣺"+str);

		// ��ͨ��ͬʱ��2��У׼ָ��
		if(iTwiceCount == 0 && g_autoCaliMode == 0)
		{
			tempRadarPara.nPara_13 = 0;
			//tempRadarPara.nPara_7 = 0;	// ��ʼ��������-0-dsp
			//toMatlabPara.StartRan = 0;	// ��ʼ��������-0-matlab
			tempRadarPara.nPara_14 = 160;// 101
			toMatlabPara.UintCaliType = 5;
		}
		else if(iTwiceCount == 1 && g_autoCaliMode == 0)
		{
			tempRadarPara.nPara_13 = 0;
			//tempRadarPara.nPara_7 = 0;
			//toMatlabPara.StartRan = 0;	// ��ʼ��������-0-matlab
			tempRadarPara.nPara_14 = 192;// 110
			toMatlabPara.UintCaliType = 6;
		}
		//else
		//{
		//	tempRadarPara.nPara_7 = tempnPara_7;	// ��У׼ģʽ��Ϊʵ��ֵ-��ʼ��������
		//	toMatlabPara.StartRan = tempStartRan;
		//}

		// ��ͨ����ʱ��4��У׼ָ��
		if(iTwiceCount == 0 && g_autoCaliMode == 1)
		{
			tempRadarPara.nPara_13 = 1;
			//tempRadarPara.nPara_7 = 0;
			//toMatlabPara.StartRan = 0;	// ��ʼ��������-0-matlab
			tempRadarPara.nPara_14 = 32;	// 001
			tempRadarPara.nPara_detectionChannel = 0; // HHͨ��У׼������1У׼
			toMatlabPara.UintCaliType = 1;
		}
		else if(iTwiceCount == 1 && g_autoCaliMode == 1)
		{
			tempRadarPara.nPara_13 = 1;
			//tempRadarPara.nPara_7 = 0;
			//toMatlabPara.StartRan = 0;	// ��ʼ��������-0-matlab
			tempRadarPara.nPara_14 = 64;	// 010
			tempRadarPara.nPara_detectionChannel = 1; // HVͨ��У׼������2У׼
			toMatlabPara.UintCaliType = 2;
		}
		else if(iTwiceCount == 2 && g_autoCaliMode == 1)
		{
			tempRadarPara.nPara_13 = 0;
			//tempRadarPara.nPara_7 = 0;
			//toMatlabPara.StartRan = 0;	// ��ʼ��������-0-matlab
			tempRadarPara.nPara_14 = 96;// 011
			tempRadarPara.nPara_detectionChannel = 0; // HHͨ��У׼������1У׼
			toMatlabPara.UintCaliType = 3;
		}
		else if(iTwiceCount == 3 && g_autoCaliMode == 1)
		{
			tempRadarPara.nPara_13 = 1;
			//tempRadarPara.nPara_7 = 0;
			//toMatlabPara.StartRan = 0;	// ��ʼ��������-0-matlab
			tempRadarPara.nPara_14 = 128;// 100
			tempRadarPara.nPara_detectionChannel = 2; // VHͨ��У׼������2У׼
			toMatlabPara.UintCaliType = 4;
		}
		//else
		//{
		//	tempRadarPara.nPara_7 = tempnPara_7;	// ��У׼ģʽ��Ϊʵ��ֵ-��ʼ��������
		//	toMatlabPara.StartRan = tempStartRan;
		//}

		if(b_isTenMinWorktFlag)
		{
			tempRadarPara.nPara_14 = 0;
			tempRadarPara.nPara_13 = 0;	// ��������ģʽ��У׼ͨ��ʹ����Ϊ0
		}


		if(/*g_autoCali == 1*/ b_autoCaliFlag)
		{
			b_tempFlag_paracfg = true;	// ��У׼�Զ���ʼ������־
		}
		if((b_isSetTimeThreadFlag || g_autoCali == 0) && g_workMode == 1)	// ������ʱģʽ
		{
			AfxBeginThread(countThread, this);
		}

		// ���ò���
		//PrintMessage(_T("�Զ����ò�����"));
		int tt = 0;
		tt = g_tcpClient.Send((byte *)(&tempRadarPara), sizeof(tempRadarPara));
		//GetData_ToMatlab(toMatlabPara);

		if (tt == sizeof(tempRadarPara))
		{
			::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+400, NULL, NULL);
			//GetData_ToMatlab(toMatlabPara);
		}
		b_isTimeOutFlag = false;	// ��ʱģʽʱ�䵽��־λ

		if(b_isManualClickBtn)	// ��������track��ʱ״̬��ÿ���Զ����ò�������������Ϊ0
		{
			b_isCountTrack = true;	// ��������ڶ�ʱ�У���ʼ2��trackֹͣ������
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
	AfxBeginThread(TrackCalcThread, this);		//����track�����߳�
}


void CSimpleInsectRadarDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//CRichEditCtrl::OnLButtonDown(nFlags, point);


	CDialogEx::OnLButtonDown(nFlags, point);
}
