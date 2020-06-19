// FormDlg2.cpp : 实现文件
//

#include "stdafx.h"
#include "SimpleInsectRadar.h"
#include "FormDlg2.h"
#include "afxdialogex.h"
#include "DSPF_sp_ifftSPxSP_cn.h"
#include <vector>

extern int g_iIsTcpConnect;
extern CTCPClient g_tcpClient;
extern CTCPClient g_tcpDisplaySoftClient;
// CFormDlg2 对话框

IMPLEMENT_DYNAMIC(CFormDlg2, CDialogEx)

CFormDlg2::CFormDlg2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFormDlg2::IDD, pParent)
	, m_szSavePath(_T(""))
	//, m_strDataVol(_T(""))
	//, m_chart1(0)
	//, m_chart2(0)
{

}

CFormDlg2::~CFormDlg2()
{
}

void CFormDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_szSavePath);
	//DDX_Control(pDX, IDC_ANGLE, m_AntennaAziAngle);
	//DDX_Control(pDX, IDC_ANGLE2, m_AntennaEleAngle);
	//DDX_Control(pDX, IDC_TEMPERATURE, m_RFTemperature);
	DDX_Control(pDX, IDC_STATIC_DISKREMAINVOLUMN, m_DiskRemainVolum);
	DDX_Control(pDX, IDC_STATIC_VOLUME, m_SATAVolum);
	DDX_Control(pDX, IDC_STATIC_SPEED, m_SATATransSpeed);
	//DDX_Text(pDX, IDC_EDIT1, m_strDataVol);
	//DDX_Control(pDX, IDC_TCHART1, m_chart1);
	//DDX_Control(pDX, IDC_TCHART2, m_chart2);
}


BEGIN_MESSAGE_MAP(CFormDlg2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON7, &CFormDlg2::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CFormDlg2::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON6, &CFormDlg2::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CFormDlg2::OnBnClickedButton5)
	ON_MESSAGE(UPDATEFORMDLG2_UI, &CFormDlg2::OnUpdateformdlg2Ui)
	ON_BN_CLICKED(IDC_BUTTON9, &CFormDlg2::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CFormDlg2::OnBnClickedButton10)
	ON_WM_TIMER()
	ON_MESSAGE(WM_USER+444, &CFormDlg2::OnUser444)
	ON_MESSAGE(WM_USER+778, &CFormDlg2::OnUser778)
	ON_MESSAGE(WM_USER+892, &CFormDlg2::OnUser892)
	ON_MESSAGE(WM_USER+893, &CFormDlg2::OnUser893)
END_MESSAGE_MAP()


// CFormDlg2 消息处理程序


BOOL CFormDlg2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//m_AntennaAziAngle.SetText( _T("0000.00"));
	//m_AntennaEleAngle.SetText( _T("0000.00"));
	//m_RFTemperature.SetText(_T("0000.00"));

	//计算上位机磁盘容量
	double dLeftSize = calculDiskVolum();
	CString strShow = _T("");
	strShow.Format( _T("%0.2f"), dLeftSize );
	m_DiskRemainVolum.SetText( strShow );

	//计算SATA存储容量
	double dl = theApp.m_pMainDlg->m_formDlg1.calculSATAVolum();
	CString strLastFileSize;
	strLastFileSize.Format(_T("%.2f"), dl);
	m_SATAVolum.SetText(strLastFileSize);
	
	//初始化SATA上传速度
	m_SATATransSpeed.SetText(_T("0000.00"));
	
	UpdateData(FALSE);

	//初始化文件列表控件——即，读取“文件列表信息”文件，数据如对，并更新显示
	InitFileListCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//存储路径选择
void CFormDlg2::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	BROWSEINFO stBrowseInfo;
	ITEMIDLIST *pStItemIdList;
	TCHAR acFilePath[100];
	memset( &stBrowseInfo, 0, sizeof(BROWSEINFO));
	stBrowseInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	pStItemIdList = SHBrowseForFolder( &stBrowseInfo );
	SHGetPathFromIDList( pStItemIdList, acFilePath );
	CString strTemp;
	m_szSavePath.Format((_T("%s")), acFilePath );

	UpdateData( FALSE );

	//SaveSetting();

	__int64 i64FreeBytesToCaller = 0;
	__int64 i64TotalBytes = 0;
	__int64 i64FreeBytes = 0;
	BOOL bReturn = GetDiskFreeSpaceEx( m_szSavePath, (PULARGE_INTEGER)&i64FreeBytesToCaller, (PULARGE_INTEGER)&i64TotalBytes, (PULARGE_INTEGER)&i64FreeBytes );
	if (bReturn == 0)
	{
		MessageBox(_T("该路径不存在，请重新选择"), /*NULL,*/ NULL, MB_ICONWARNING);
		return;
	}
	
	double dLeftSize = i64FreeBytes / 1024.0 / 1024.0 / 1024.0;
	//m_fDiskRemain = dLeftSize;
	CString strShow = _T("");
	strShow.Format( _T("%0.2f"), dLeftSize );
	m_DiskRemainVolum.SetText( strShow );

	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("FilePath.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file(strModulePath, CFile::modeWrite);
	CArchive ar(&file,CArchive::store);
	theApp.m_pMainDlg->strFileSavePath = m_szSavePath;
	ar << m_szSavePath;
}



//开始/停止上传按钮
bool b_flag4 = false;
int iunloadingFileNum = 0;	// 自动转存时需要转存的文件个数
extern bool b_isStopCountCirculations;

void CFormDlg2::OnBnClickedButton8()
{
	UpdateData(TRUE);
	if (g_iIsTcpConnect != 0)
	{
		MessageBox(_T("网络异常，无法上传数据！"), /*NULL,*/ NULL, MB_ICONWARNING);
		return;
	}


	if (!PathIsDirectory(m_szSavePath))
	{
		MessageBox(_T("上传路径不存在，请重新选择！"), NULL, MB_ICONERROR);
		return;
	}

	//b_flag4 = !b_flag4;

	b_flag4 = true;
	if (b_flag4)
	{
		if(b_isStopCountCirculations)
		{
			int totalCnt = theApp.m_pMainDlg->m_filelist.GetItemCount();

			if(g_autoCaliMode == 0)
			{
				iunloadingFileNum = 3;
			}
			else if(g_autoCaliMode == 1)
			{
				iunloadingFileNum = 5;
			}
			
			for (UINT i=0; i<iunloadingFileNum; i++)
			{
				/*if (theApp.m_pMainDlg->m_filelist.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
				{*/
					theApp.m_pMainDlg->m_fileSelectedArray.Add(totalCnt - i - 1);
				/*}*/
			}

			//提取上传起始地址和上传数据长度
			UINT nHead = 0x9e9e9e9e;
			UINT nLen = 16;
			ULONGLONG ulBeginAddress = 0/*p->BeginAddress*/;
			ULONGLONG ulFileSize = 0;
			ulFileSize = (ULONGLONG)5*1024*1024*1024/*(p->EndAddress) - (p->BeginAddress)*/;

			//向DSP->FPGA下发上传起始地址和上传数据长度
			UINT nBuffer[3] = {0x5a5a5a5a, 0x04, 0x09};
			g_tcpClient.Send((byte *)nBuffer, sizeof(nBuffer));
			//GetDlgItem(IDC_BUTTON8)->SetWindowTextW(_T("停止上传"));
			GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);

			g_bWritingFile = true;
			::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+333, NULL, NULL);
		}
		else
		{
			int totalCnt = theApp.m_pMainDlg->m_filelist.GetItemCount();

			for (UINT i=0; i<totalCnt; i++)
			{
				if (theApp.m_pMainDlg->m_filelist.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
				{
					theApp.m_pMainDlg->m_fileSelectedArray.Add(i);
				}
			}

			if (theApp.m_pMainDlg->m_fileSelectedArray.IsEmpty())
			{
				MessageBox(_T("请选择要导出的文件！"), /*NULL,*/ NULL, MB_ICONWARNING);
				return;
			}



			//if (theApp.m_pMainDlg->m_pWriteFileThread)
			//{
			//	theApp.m_pMainDlg->m_pWriteFileThread->ResumeThread();
			//}
			//UINT nBuffer[3] = {0x5a5a5a5a, 0x04, 0x09};

			//提取上传起始地址和上传数据长度
			UINT nHead = 0x9e9e9e9e;
			UINT nLen = 16;
			ULONGLONG ulBeginAddress = 0/*p->BeginAddress*/;
			ULONGLONG ulFileSize = 0;
			ulFileSize = (ULONGLONG)5*1024*1024*1024/*(p->EndAddress) - (p->BeginAddress)*/;

			//向DSP->FPGA下发上传起始地址和上传数据长度
			UINT nBuffer[3] = {0x5a5a5a5a, 0x04, 0x09};
			g_tcpClient.Send((byte *)nBuffer, sizeof(nBuffer));
			//GetDlgItem(IDC_BUTTON8)->SetWindowTextW(_T("停止上传"));
			GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);

			g_bWritingFile = true;
			::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+333, NULL, NULL);
		}	

	}
	//else if (!b_flag4)
	//{
	//	UINT nBuffer[3] = {0x5a5a5a5a, 0x04, 0x0a};
	//	g_tcpClient.Send((byte *)nBuffer, sizeof(nBuffer));
	//	GetDlgItem(IDC_BUTTON8)->SetWindowTextW(_T("开始上传"));
	//	GetDlgItem(IDC_BUTTON9)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	//	g_bWritingFile = false;
	//	theApp.m_pMainDlg->m_fileSelectedArray.RemoveAll();
	//}
}



//暂时没用到	数据上传线程
UINT CFormDlg2::TransThread(LPVOID lpParma)
{
	return ((CFormDlg2 *)lpParma)->TransProcess();
}


//暂时没用到	数据上传任务
UINT CFormDlg2::TransProcess()
{
	m_criticalsection.Lock();
	g_bIsTrans = true;
	m_criticalsection.Unlock();

	byte *pBuffer = NULL;
	while((pBuffer = new byte[FifoWith]) == NULL);   //接收数据缓存
	memset(pBuffer, 0, FifoWith);

	while(g_bIsTrans)
	{
		UINT nRet = g_tcpClient.Recv(pBuffer, FifoWith);
		if (nRet == FifoWith)
		{
			byte *p = NULL;
			while((p = m_RecvFiFo.Alloc()) == NULL);
			memcpy(p, pBuffer, FifoWith);
			m_RecvFiFo.Push(p);                    //入fifo
		}
		else 
		{
			//ASSERT(false);
		}
	}
	

	return 0;
}


//暂时没用到	数据存盘线程
UINT CFormDlg2::WriteFileThread(LPVOID lpParam)
{
	return ((CFormDlg2 *)lpParam)->WriteFileProcess();
}


//暂时没用到	数据存盘任务
UINT CFormDlg2::WriteFileProcess()
{
	HANDLE hFile = NULL;
	CString strFileName;

	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString strTime;
	strTime.Format(L"%.4d_%.2d_%.2d_%.2d_%.2d_%.2d.dat", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);

	strFileName = m_szSavePath + strTime;

	hFile = CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	while (hFile != NULL)
	{
		byte *p = NULL;

		if (p = m_RecvFiFo.Pop())
		{
			DWORD dwWrites;
			bool bRet = WriteFile(hFile, p, FifoWith, &dwWrites, NULL);
			m_RecvFiFo.Free(p);
			p = NULL;
		}
	}

	return 0;
}


//抓屏
void CFormDlg2::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	//IFFT_tchart2();
}


//擦除——清文件列表
extern RadarPara tempRadarPara;
//extern bool b_isManualClickBtn;
//extern bool b_isTempCountTrack;
extern bool b_isTimeOutFlag;
extern bool b_isWorkStoreFlag;
extern int iCountCirculations;
void CFormDlg2::OnBnClickedButton5()
{
	if (g_iIsTcpConnect != 0)
	{
		MessageBox(_T("网络异常，无法上传数据！"), /*NULL,*/ NULL, MB_ICONWARNING);
		return;
	}

	if(b_isStopCountCirculations)
	{
		OutputDebugString(_T("擦除文件！~~~~~~\n\n"));
		UINT nBuffer[3] = {0x5a5a5a5a, 0x04, 0x10};
		g_tcpClient.Send((byte *)nBuffer, sizeof(nBuffer));


		POSITION pos = m_fileinfolist.GetHeadPosition();
		while (pos != NULL)
		{
			delete m_fileinfolist.GetNext(pos);
		}
		m_fileinfolist.RemoveAll();
		int n = m_fileinfolist.GetSize();
		TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
		GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
		(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
		//wcscpy(gszSettingPath , szModulePath);
		wcscat(szModulePath , _T("FileListInfo.txt"));

		CString strModulePath;
		strModulePath = szModulePath;
		CFile file;
		if (file.Open(strModulePath, CFile::modeCreate))
			file.Close();

		theApp.m_pMainDlg->m_filelist.DeleteAllItems();

		//更新formdlg1和formdlg2中的SATA存储容量
		double dl = theApp.m_pMainDlg->m_formDlg1.calculSATAVolum();
		CString strLastFileSize;
		strLastFileSize.Format(_T("%.2f"), dl);
		theApp.m_pMainDlg->m_formDlg1.m_SATAVolum.SetText(strLastFileSize);
		theApp.m_pMainDlg->m_formDlg2.m_SATAVolum.SetText(strLastFileSize);

		// 配参，开始工作，开始存储-----内校准，定时同时具备
		// 发消息配参数
		b_isWorkStoreFlag = false; // 从新开启自动下配参数
		b_isStopCountCirculations = false; // 关闭自动开始上传
		iCountCirculations = 0; // 内循环计数器置0

		::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+894, NULL, NULL);
	}
	else
	{
		if (MessageBox(L"确定擦除数据？", NULL, MB_YESNO | MB_ICONEXCLAMATION | MB_ICONWARNING) == IDYES)
		{
			UINT nBuffer[3] = {0x5a5a5a5a, 0x04, 0x10};
			g_tcpClient.Send((byte *)nBuffer, sizeof(nBuffer));


			POSITION pos = m_fileinfolist.GetHeadPosition();
			while (pos != NULL)
			{
				delete m_fileinfolist.GetNext(pos);
			}
			m_fileinfolist.RemoveAll();
			int n = m_fileinfolist.GetSize();
			TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
			GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
			(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
			//wcscpy(gszSettingPath , szModulePath);
			wcscat(szModulePath , _T("FileListInfo.txt"));

			CString strModulePath;
			strModulePath = szModulePath;
			CFile file;
			if (file.Open(strModulePath, CFile::modeCreate))
				file.Close();

			theApp.m_pMainDlg->m_filelist.DeleteAllItems();

			//更新formdlg1和formdlg2中的SATA存储容量
			double dl = theApp.m_pMainDlg->m_formDlg1.calculSATAVolum();
			CString strLastFileSize;
			strLastFileSize.Format(_T("%.2f"), dl);
			theApp.m_pMainDlg->m_formDlg1.m_SATAVolum.SetText(strLastFileSize);
			theApp.m_pMainDlg->m_formDlg2.m_SATAVolum.SetText(strLastFileSize);
		}
	}

	//if (MessageBox(L"确定擦除数据？", NULL, MB_YESNO | MB_ICONEXCLAMATION | MB_ICONWARNING) == IDYES)
	//{
	//	UINT nBuffer[3] = {0x5a5a5a5a, 0x04, 0x10};
	//	g_tcpClient.Send((byte *)nBuffer, sizeof(nBuffer));


	//	POSITION pos = m_fileinfolist.GetHeadPosition();
	//	while (pos != NULL)
	//	{
	//		delete m_fileinfolist.GetNext(pos);
	//	}
	//	m_fileinfolist.RemoveAll();
	//	int n = m_fileinfolist.GetSize();
	//	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	//	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	//	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//	//wcscpy(gszSettingPath , szModulePath);
	//	wcscat(szModulePath , _T("FileListInfo.txt"));

	//	CString strModulePath;
	//	strModulePath = szModulePath;
	//	CFile file;
	//	if (file.Open(strModulePath, CFile::modeCreate))
	//		file.Close();

	//	theApp.m_pMainDlg->m_filelist.DeleteAllItems();

	//	//更新formdlg1和formdlg2中的SATA存储容量
	//	double dl = theApp.m_pMainDlg->m_formDlg1.calculSATAVolum();
	//	CString strLastFileSize;
	//	strLastFileSize.Format(_T("%.2f"), dl);
	//	theApp.m_pMainDlg->m_formDlg1.m_SATAVolum.SetText(strLastFileSize);
	//	theApp.m_pMainDlg->m_formDlg2.m_SATAVolum.SetText(strLastFileSize);
	//}
}


//刷新数据上传界面
afx_msg LRESULT CFormDlg2::OnUpdateformdlg2Ui(WPARAM wParam, LPARAM lParam)
{
	byte *p = (byte *)wParam;
	UINT nLen = *((UINT *)lParam);
	UINT nHrrpCnt = (nLen - (3*4)) / 4;		//一维像点数

	UINT nAerAngel = *((UINT *)(p + 8));        //天线角度
	UINT nRFTemperature = *((UINT *)(p + 12));  //射频温度
	//UINT nSATASaveSpeed = *((UINT *)(p + 16));  //SATA存储速度
	UINT nSATAVolum = *((UINT *)(p + 20));      //SATA存储容量

	CString strAntennaAziAngle;
	CString strRFTemperature;
	CString strSATAVolum;
	CString strSATASaveSpeed;

	strAntennaAziAngle.Format(_T("%.2d"), nAerAngel);
	//m_AntennaAziAngle.SetText(strAntennaAziAngle);
	strRFTemperature.Format(_T("%.2d"), nRFTemperature);
	//m_RFTemperature.SetText(strAntennaAziAngle);
	strSATAVolum.Format(_T("%.2d"), nSATAVolum);
	m_SATAVolum.SetText(strSATAVolum);

	return 0;
}


//重读文件列表
void CFormDlg2::OnBnClickedButton9()
{
//	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
//	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
//	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
//	//wcscpy(gszSettingPath , szModulePath);
//	wcscat(szModulePath , _T("FileListInfo.txt"));
//
//	CString strModulePath;
//	strModulePath = szModulePath;
//	CFile file/*(strModulePath, CFile::modeRead)*/;
//
//	/////////////////////////////////////////  测试代码  ///////////////////////////////////////
//	if (file.Open(strModulePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
//	{
//		file.SeekToEnd();
//		FILELISTINFO *pFileListInfo = new FILELISTINFO; 
//		pFileListInfo->BeginAddress = 0x00000000aaaaaaaa;
//		pFileListInfo->EndAddress = 0x00000000bbbaaaaa;
//		//GetSystemTime((&pFileListInfo->systime));
//		GetLocalTime(&(pFileListInfo->systime));
//		file.Write(pFileListInfo, sizeof(FILELISTINFO));
//		delete pFileListInfo;
//		file.Close();
//	}
//
//	//清链表
//	POSITION pos = m_fileinfolist.GetHeadPosition(); 
//
//	while(pos != NULL)
//	{
//		FILELISTINFO *p = NULL;
//		p = (FILELISTINFO *)m_fileinfolist.GetNext(pos);
//		delete p;
//		//m_fileinfolist.RemoveAt(pos);
//	}
//	m_fileinfolist.RemoveAll();
//
//	//读取“文件列表信息”文件，数据如对，并更新显示
//	theApp.m_pMainDlg->m_filelist.DeleteAllItems();
//	if (file.Open(strModulePath, CFile::modeRead))
//	{
//		ULONGLONG uFileSize = file.GetLength();
//		ULONGLONG uCount = uFileSize / sizeof(FILELISTINFO);
//		for (int i=0; i<uCount; i++)
//		{
//			//读文件列表信息
//			FILELISTINFO *pFileListInfo = new FILELISTINFO; 
//			file.Read(pFileListInfo, sizeof(FILELISTINFO));
//			m_fileinfolist.AddTail(pFileListInfo);
//
//			//更新界面显示
//			CString strFileName;
//			strFileName.Format(_T("%.4d_%.2d_%.2d-%.2d_%.2d_%.2d.dat"),
//				pFileListInfo->systime.wYear, pFileListInfo->systime.wMonth, pFileListInfo->systime.wDay, 
//				pFileListInfo->systime.wHour, pFileListInfo->systime.wMinute, pFileListInfo->systime.wSecond);
//			
//			theApp.m_pMainDlg->m_filelist.InsertItem(i, strFileName);  //更新文件名;
//			ULONGLONG uEachFileSize = ((pFileListInfo->EndAddress) - (pFileListInfo->BeginAddress)) / (1024 * 1024);
//			CString strEachFileSize;
//			strEachFileSize.Format(_T("%d"), uEachFileSize);
//			theApp.m_pMainDlg->m_filelist.SetItemText(i, 1, strEachFileSize);  //更新文件大小
//		}
//		file.Close();
//	}


	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("FileListInfo.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file/*(strModulePath, CFile::modeRead)*/;

	//清链表
	POSITION pos = m_fileinfolist.GetHeadPosition(); 

	while(pos != NULL)
	{
		FILELISTINFO *p = NULL;
		p = (FILELISTINFO *)m_fileinfolist.GetNext(pos);
		delete p;
		//m_fileinfolist.RemoveAt(pos);
	}
	m_fileinfolist.RemoveAll();
	
	int n = m_fileinfolist.GetSize();
	n = m_fileinfolist.GetCount();

	//读取“文件列表信息”文件，数据如对，并更新显示
	theApp.m_pMainDlg->m_filelist.DeleteAllItems();
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
			m_fileinfolist.AddTail(pFileListInfo);

			//更新界面显示
			CString strFileName;
			strFileName.Format(_T("%d_%.4d_%.2d_%.2d-%.2d_%.2d_%.2d.dat"), (i + 1),
				pFileListInfo->systime.wYear, pFileListInfo->systime.wMonth, pFileListInfo->systime.wDay, 
				pFileListInfo->systime.wHour, pFileListInfo->systime.wMinute, pFileListInfo->systime.wSecond);

			theApp.m_pMainDlg->m_filelist.InsertItem(i, strFileName);  //更新文件名;
			ULONGLONG uEachFileSize = ((pFileListInfo->EndAddress) - (pFileListInfo->BeginAddress)) / (1024 * 1024);
			CString strEachFileSize;
			strEachFileSize.Format(_T("%d"), uEachFileSize);
			theApp.m_pMainDlg->m_filelist.SetItemText(i, 1, strEachFileSize);  //更新文件大小
		}
		file.Close();
	}
}


//读取“文件列表信息”文件，数据如对，并更新显示
void CFormDlg2::InitFileListCtrl()
{
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("FileListInfo.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file/*(strModulePath, CFile::modeRead)*/;

	//清链表
	POSITION pos = m_fileinfolist.GetHeadPosition(); 

	while(pos != NULL)
	{
		FILELISTINFO *p = NULL;
		p = (FILELISTINFO *)m_fileinfolist.GetNext(pos);
		delete p;
		//m_fileinfolist.RemoveAt(pos);
	}
	m_fileinfolist.RemoveAll();
	vector<FILELISTINFO*> vFileInfo;
	//读取“文件列表信息”文件，数据如对，并更新显示
	theApp.m_pMainDlg->m_filelist.DeleteAllItems();
	if (file.Open(strModulePath, CFile::modeRead))
	{
		ULONGLONG uFileSize = file.GetLength();
		ULONGLONG uCount = uFileSize / sizeof(FILELISTINFO);	//获取上一次采集的文件个数
		for (int i=0; i<uCount; i++)
		{
			//读文件列表信息
			FILELISTINFO *pFileListInfo = new FILELISTINFO; 
			file.Read(pFileListInfo, sizeof(FILELISTINFO));
			m_fileinfolist.AddTail(pFileListInfo);
			vFileInfo.push_back(pFileListInfo);
			//更新界面显示
			CString strFileName;
			strFileName.Format(_T("%d_%.4d_%.2d_%.2d-%.2d_%.2d_%.2d.dat"), (i + 1),
				pFileListInfo->systime.wYear, pFileListInfo->systime.wMonth, pFileListInfo->systime.wDay, 
				pFileListInfo->systime.wHour, pFileListInfo->systime.wMinute, pFileListInfo->systime.wSecond);

			theApp.m_pMainDlg->m_filelist.InsertItem(i, strFileName);  //更新文件名;
			ULONGLONG uEachFileSize = ((pFileListInfo->EndAddress) - (pFileListInfo->BeginAddress)) / (1024 * 1024);
			CString strEachFileSize;
			strEachFileSize.Format(_T("%d"), uEachFileSize);
			theApp.m_pMainDlg->m_filelist.SetItemText(i, 1, strEachFileSize);  //更新文件大小
		}
		file.Close();
	}
}


void CFormDlg2::OnBnClickedButton10()
{
	g_bWritingFile = false;
}


void CFormDlg2::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	//IFFT_tchart1();
	CDialogEx::OnTimer(nIDEvent);
}


//void CFormDlg2::Draw(float *p, UINT nLen, UINT nSeriesCnt, CSeries series)
//{
//	//获取曲线的数量
//	long SeriesCount = m_chart1.get_SeriesCount();
//
//	//断言曲线数量为4
//	ASSERT(SeriesCount == 4);
//
//	
//	COleSafeArray XValues, YValues;
//
//	//定义数据长度
//	UINT N = nLen / 8;
//	DWORD rgElements[] = {N};
//
//	//申请数据内存空间
//	XValues.Create(VT_R8, 1, rgElements);
//	YValues.Create(VT_R8, 1, rgElements);
//
//	//赋值
//	//static int tt = 0;
//	if (nSeriesCnt == 4)
//	{
//		for (long j=0; j<N; j++)
//		{
//			double x = (double)j;
//			float real = p[j * 2];
//			float image = p[j * 2 + 1];
//			double z = powf(real, 2.0) + powf(image, 2.0);
//			z = sqrt(z)/16000;
//			//if (z == 0.0)
//			//{
//			//	z = 100;
//			//}
//			//long double zlog = 10 * log((long double)z);
//			//double z = real;
//			XValues.PutElement(&j, &x);
//			YValues.PutElement(&j, &z);
//		}
//		//绘制曲线
//		series.AddArray(N, YValues, XValues);
//		
//	}
//	else if (nSeriesCnt == 2)
//	{
//
//	}
//}


void CFormDlg2::IFFT_tchart1()
{
	memcpy(pHrrpBuf, pTemp, HRRPBUFFERSIZE);

	//m_criticalsection.Unlock();

	UINT *p32 = NULL;
	p32 = (UINT *)pHrrpBuf;
	UINT nDataType = *p32;			//解析数据头

	if (nDataType == 0x7c7c7c7c)
	{

		//PostMessage(WM_USER+444, (WPARAM)pHrrpBuf, HRRPBUFFERSIZE);

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
				memset(pTemp, 0, HRRPBUFFERSIZE);
				m_criticalsection.Unlock();
			}
			//CloseHandle(m_hFile);
			delete []pHrrpTemp;
			pHrrpTemp = NULL;
			pdlHrrptemp = NULL;
		}
	}
}


void CFormDlg2::IFFT_tchart2()
{
	memcpy(pHrrpBuf, pTemp, HRRPBUFFERSIZE);

	//m_criticalsection.Unlock();

	UINT *p32 = NULL;
	p32 = (UINT *)pHrrpBuf;
	UINT nDataType = *p32;			//解析数据头

	if (nDataType == 0x7c7c7c7c)
	{

		PostMessage(WM_USER+222, (WPARAM)pHrrpBuf, HRRPBUFFERSIZE);

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
				m_criticalsection.Lock();
				memset(pTemp, 0, HRRPBUFFERSIZE);
				m_criticalsection.Unlock();
			}
			//CloseHandle(m_hFile);
			delete []pHrrpTemp;
			pHrrpTemp = NULL;
			pdlHrrptemp = NULL;
		}
	}
}

afx_msg LRESULT CFormDlg2::OnUser444(WPARAM wParam, LPARAM lParam)
{
	float *p = (float*)wParam;

	CString str;

	////天线指向方位角
	//float fAntennaAziAngle = *(p + 3);
	//if (fAntennaAziAngle < -180.0 || fAntennaAziAngle > 180.0)
	//{
	//	return 0;
	//}
	//str.Format(_T("%.2f"), fAntennaAziAngle);
	//g_fAntennaAziAngle = fAntennaAziAngle;
	////m_AntennaAziAngle.SetText(str);

	////天线指向俯仰角
	//float fAntennaEleAngle = *(p + 4);
	//str.Format(_T("%.2f"), fAntennaEleAngle);
	//m_AntennaEleAngle.SetText( str);

	////射频模块温度
	//float fRFTemperature = *(p + 5);
	//str.Format(_T("%.2f"), fRFTemperature);
	//m_RFTemperature.SetText(str);

	////SATA上传速度
	//float fSATASaveSpeed = *(p + 6);
	//str.Format(_T("%.2f"), fSATASaveSpeed);
	//m_SATASaveSpeed.SetText(str);


	int a = 0;
	int b = 0;
	//str.Format(_T("%.2f"), g_dlNetSpeed);
	//m_SATATransSpeed.SetText(str);

	////SATA存储容量
	//ULONGLONG *q = (ULONGLONG*)wParam;
	//q += 4;
	//ULONGLONG ulSATAVolum = *q;
	//UINT uSATAVolum = ulSATAVolum /1024/1024/1024 ;
	//str.Format(_T("%d"), uSATAVolum);
	//m_SATAVolum.SetText(str);

	CString strNetSpeed;
	strNetSpeed.Format(_T("%.2f"), g_dlNetSpeed);
	m_SATATransSpeed.SetText(strNetSpeed);


	return 0;
}


afx_msg LRESULT CFormDlg2::OnUser778(WPARAM wParam, LPARAM lParam)
{
	BOOL bShowWindow = *((BOOL*)wParam);

	((CButton *)GetDlgItem(IDC_BUTTON8))->EnableWindow(bShowWindow);

	if (bShowWindow)
	{
		GetDlgItem(IDC_BUTTON9)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	}
	
	return 0;
}

afx_msg LRESULT CFormDlg2::OnUser892(WPARAM wParam, LPARAM lParam)
{
	SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON8, BN_CLICKED), NULL);	// 点击开始上传
	OutputDebugString(_T("点击开始上传！！！！~~~~"));
	return 0;
}

afx_msg LRESULT CFormDlg2::OnUser893(WPARAM wParam, LPARAM lParam)
{
	SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BUTTON5, BN_CLICKED), NULL);	// 点击擦除
	OutputDebugString(_T("点击擦除！！！！~~~~"));
	return 0;
}


double CFormDlg2::calculDiskVolum()
{
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("FilePath.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file(strModulePath, CFile::modeRead);
	CArchive ar(&file,CArchive::load);
	//m_szSavePath = _T("d:\\");
	CString strAr;
	ar >> strAr;
	m_szSavePath = strAr;
	theApp.m_pMainDlg->strFileSavePath = strAr;

	__int64 i64FreeBytesToCaller = 0;
	__int64 i64TotalBytes = 0;
	__int64 i64FreeBytes = 0;
	BOOL bReturn = GetDiskFreeSpaceEx( m_szSavePath,(PULARGE_INTEGER)&i64FreeBytesToCaller, (PULARGE_INTEGER)&i64TotalBytes, (PULARGE_INTEGER)&i64FreeBytes );
	double dLeftSize = i64FreeBytes / 1024.0 / 1024.0 / 1024.0;

	return dLeftSize;
}
