// FormDlg3.cpp : 实现文件
//

#include "stdafx.h"
#include "SimpleInsectRadar.h"
#include "FormDlg3.h"
#include "afxdialogex.h"
#include "DSPF_sp_ifftSPxSP_cn.h"


// CFormDlg3 对话框

IMPLEMENT_DYNAMIC(CFormDlg3, CDialogEx)

CFormDlg3::CFormDlg3(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFormDlg3::IDD, pParent)
	//, m_chart3(0)
	//, m_chart4(0)
{

}

CFormDlg3::~CFormDlg3()
{
}

void CFormDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_TCHART1, m_chart3);
	//DDX_Control(pDX, IDC_TCHART2, m_chart4);
	DDX_Control(pDX, IDC_CUSTOM3, m_chart3);
	DDX_Control(pDX, IDC_CUSTOM4, m_chart4);

}


BEGIN_MESSAGE_MAP(CFormDlg3, CDialogEx)
	ON_MESSAGE(WM_USER+301, &CFormDlg3::OnOnupdateformdlg3UI)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK1, &CFormDlg3::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CFormDlg3::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CFormDlg3::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CFormDlg3::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CFormDlg3::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CFormDlg3::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CFormDlg3::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CFormDlg3::OnBnClickedCheck8)
END_MESSAGE_MAP()


// CFormDlg3 消息处理程序


BOOL CFormDlg3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	InitChartCtrl();

	return TRUE;  
}


afx_msg LRESULT CFormDlg3::OnOnupdateformdlg3UI(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

//extern int iChunZhiCount;
//extern RadarPara tempRadarPara;
void CFormDlg3::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if(toMatlabPara.workingMode == 3)
	//{

	//	if(iChunZhiCount % 2 == 0)
	//	{
	//		g_nPara_7 = tempRadarPara.nPara_dptInitSampDist * 15;// 副波形起始采样距离60
	//		//m_formDlg3.IFFT_tchart1();
	//	}
	//	else
	//	{
	//		g_nPara_7 = tempRadarPara.nPara_7 * 15; // 150
	//		//m_formDlg3.IFFT_tchart1();
	//	}
	//	/*iChunZhiCount++;
	//	CString str;
	//	str.Format(_T("%d"), g_nPara_7);
	//	PrintMessage(str);*/

	//}

	IFFT_tchart1();

	CDialogEx::OnTimer(nIDEvent);
}


void CFormDlg3::IFFT_tchart1()
{
	memcpy(pHrrpBuf, pTemp, HRRPBUFFERSIZE);

	//m_criticalsection.Unlock();

	UINT *p32 = NULL;
	p32 = (UINT *)pHrrpBuf;
	UINT nDataType = *p32;			//解析数据头

	if (nDataType == 0x7c7c7c7c)
	{

		//PostMessage(WM_USER+222, (WPARAM)pHrrpBuf, HRRPBUFFERSIZE);
		::PostMessage(theApp.m_pMainDlg->m_formDlg1.m_hWnd, WM_USER+222, (WPARAM)pHrrpBuf, HRRPBUFFERSIZE);
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
		pHrrpSrc = pHrrpBuf + 48 + 208 + 128/*36*/;									//指向一维像原始数据头
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
				for (int m=0; m<=31; m++)
				{
					if ((nEachChannelIFFTNodes & (1 << m)) == 0)
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
				Draw((float*)q1, nEachChannelIFFTBytes, nChannelCnt, m_pLineSeries[i]);			//送显画图

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
				for (int m=0; m<=31; m++)
				{
					if ((nEachChannelIFFTNodes & (1 << m)) == 0)
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
				//series[i] = (m_chart3.Series(i));
				//series[i].Clear();
				//Draw((float*)q, nEachChannelIFFTBytes, nChannelCnt, series[i]);			//送显画图

				
				Draw((float*)q, nEachChannelIFFTBytes, nChannelCnt, m_pLineSeries[i]);			//送显画图

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


void CFormDlg3::IFFT_tchart2()
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
		pHrrpSrc = pHrrpBuf + 48 + 208 + 128/*36*/;									//指向一维像原始数据头
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
				Draw((float*)q1, nEachChannelIFFTBytes, nChannelCnt, m_pLineSeries_capture[i]);			//送显画图

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
				for (int m=0; m<=31; m++)
				{
					if ((nEachChannelIFFTNodes & (1 << m)) == 0)
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
								
				//送显
				Draw((float*)q, nEachChannelIFFTBytes, nChannelCnt, m_pLineSeries_capture[i]);			//送显画图

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


void CFormDlg3::Draw(float *p, UINT nLen, UINT nSeriesCnt, CChartLineSerie *series)
{
	//double *pData = (double*)p;

	//获取曲线的数量
	//long SeriesCount = m_chart3.get_SeriesCount();

	//断言曲线数量为4
	//ASSERT(SeriesCount == 4);

	//获取曲线
	//CSeries m_Series[4];
	//m_Series[0] = (m_chart1.Series(0));
	//m_Series[1] = (m_chart1.Series(1));
	//m_Series[2] = (m_chart1.Series(2));
	//m_Series[3] = (m_chart1.Series(3));
	//CSeries m_Series0 = m_chart1.Series(0);
	//CSeries m_Series1 = m_chart1.Series(1);
	//CSeries m_Series2 = m_chart1.Series(2);
	//CSeries m_Series3 = m_chart1.Series(3);

	//清空曲线点
	//m_Series[0].Clear();
	//m_Series[1].Clear();
	//m_Series[2].Clear();
	//m_Series[3].Clear();

	//m_Series0.Clear();
	//m_Series1.Clear();
	//m_Series2.Clear();
	//m_Series3.Clear();

	//定义X轴和Y轴数据变量
	//COleSafeArray XValues, YValues;

	//定义数据长度
	//UINT N = nLen / 8;
	UINT N = g_nDrawNodes;


	DWORD rgElements[] = {N};

	//申请数据内存空间
	double *XValues = new double[N];
	double *YValues = new double[N];

	//XValues.Create(VT_R8, 1, rgElements);
	//YValues.Create(VT_R8, 1, rgElements);

	//赋值
	static int tt = 0;
	if (nSeriesCnt == 4)
	{
		for (long j=0; j<N; j++)
		{
			double x = (double)j;
			float real = p[j * 2];
			float image = p[j * 2 + 1];
			//double z = powf(real, 2.0) + powf(image, 2.0);
			//z = sqrt(z);
			//long double zlog = 10 * log((long double)z);
			//double z = real;
			//XValues.PutElement(&j, &x);
			//YValues.PutElement(&j, &z);
			//series.AddXY(x, z);
			XValues[j] = (double)((j - 1) * g_nCoefficient + g_nPara_7);
			double z = powf(real, 2.0) + powf(image, 2.0);
			YValues[j] = sqrt(z);
		}
		if (N == 16384)
		{
			tt++;
		}
		CString str;
		str.Format(_T("%d\r\n"), tt);
		//TRACE(str);
		//绘制曲线
		//series.AddArray(N, YValues, XValues);
		series->ClearSerie();
		series->SetPoints(XValues, YValues, N);
		//m_chart3.RefreshCtrl();
	}
	else if (nSeriesCnt == 2)
	{

	}
	int dd = 0;
	//绘制曲线
	//m_Series0.AddArray(N, YValues, XValues);
	//////////////////////////////////////////////////////
	//申请数据内存空间
	//XValues.Create(VT_R8, 1, rgElements);
	//YValues.Create(VT_R8, 1, rgElements);

	////赋值
	//for (long j=0; j<N; j++)
	//{
	//	double x = (double)j;
	//	//double y = pData[j];
	//	float y = p[j * 2];
	//	XValues.PutElement(&j, &x);
	//	YValues.PutElement(&j, &y);
	//}

	////绘制曲线
	//m_Series0.AddArray(N, YValues, XValues);


	//for (int i=0; i<nSeriesCnt; i++)
	//{
	//	//申请数据内存空间
	//	XValues.Create(VT_R8, 1, rgElements);
	//	YValues.Create(VT_R8, 1, rgElements);

	//	//赋值
	//	for (long j=0; j<N; j++)
	//	{
	//		double x = (double)j;
	//		//double y = pData[j];
	//		float y = p[j * 2 + i *(nLen / 4)];
	//		XValues.PutElement(&j, &x);
	//		YValues.PutElement(&j, &y);
	//	}

	//	//绘制曲线
	//	m_Series[i].AddArray(N, YValues, XValues); 
	//}


	//释放内存
	delete []XValues;
	delete []YValues;
	//delete[] p;
}


void CFormDlg3::InitChartCtrl()
{
	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK6))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK8))->SetCheck(1);



	CChartStandardAxis* pBottomAxis = m_chart3.CreateStandardAxis(CChartCtrl::BottomAxis);
	//pBottomAxis->SetMinMax(0, 1000);
	pBottomAxis->SetAutomatic(true);
	CChartStandardAxis* pLeftAxis = m_chart3.CreateStandardAxis(CChartCtrl::LeftAxis);
	//pLeftAxis->SetMinMax(0, 0);
	pLeftAxis->SetAutomatic(true);

	//for (int i=0; i<4; i++)
	//	m_pLineSeries[i] = m_chart3.CreateLineSerie();
	m_pLineSeries[0] = m_chart3.CreateLineSerie();
	m_pLineSeries[1] = m_chart3.CreateLineSerie();
	m_pLineSeries[3] = m_chart3.CreateLineSerie();
	m_pLineSeries[2] = m_chart3.CreateLineSerie();



	CChartStandardAxis* pBottomAxis_capture = m_chart4.CreateStandardAxis(CChartCtrl::BottomAxis);
	//pBottomAxis_capture->SetMinMax(0, 1000);
	pBottomAxis_capture->SetAutomatic(true);

	CChartStandardAxis* pLeftAxis_capture = m_chart4.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis_capture->SetAutomatic(true);

	//for (int i=0; i<4; i++)
	//	m_pLineSeries_capture[i] = m_chart4.CreateLineSerie();
	m_pLineSeries_capture[0] = m_chart4.CreateLineSerie();
	m_pLineSeries_capture[1] = m_chart4.CreateLineSerie();
	m_pLineSeries_capture[3] = m_chart4.CreateLineSerie();
	m_pLineSeries_capture[2] = m_chart4.CreateLineSerie();
}



void CFormDlg3::OnBnClickedCheck1()
{
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == 1)
		m_pLineSeries[0]->SetVisible(true);
	else
		m_pLineSeries[0]->SetVisible(false);
	m_chart3.RefreshCtrl();
}


void CFormDlg3::OnBnClickedCheck2()
{
	if (((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck() == 1)
		m_pLineSeries[2]->SetVisible(true);
	else
		m_pLineSeries[2]->SetVisible(false);
	m_chart3.RefreshCtrl();
}


void CFormDlg3::OnBnClickedCheck3()
{
	if (((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck() == 1)
		m_pLineSeries[1]->SetVisible(true);
	else
		m_pLineSeries[1]->SetVisible(false);
	m_chart3.RefreshCtrl();
}


void CFormDlg3::OnBnClickedCheck4()
{
	if (((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck() == 1)
		m_pLineSeries[3]->SetVisible(true);
	else
		m_pLineSeries[3]->SetVisible(false);
	m_chart3.RefreshCtrl();
}


void CFormDlg3::OnBnClickedCheck5()
{
	if (((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck() == 1)
		m_pLineSeries_capture[0]->SetVisible(true);
	else
		m_pLineSeries_capture[0]->SetVisible(false);
	m_chart4.RefreshCtrl();
}


void CFormDlg3::OnBnClickedCheck6()
{
	if (((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck() == 1)
		m_pLineSeries_capture[2]->SetVisible(true);
	else
		m_pLineSeries_capture[2]->SetVisible(false);
	m_chart4.RefreshCtrl();
}


void CFormDlg3::OnBnClickedCheck7()
{
	if (((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck() == 1)
		m_pLineSeries_capture[1]->SetVisible(true);
	else
		m_pLineSeries_capture[1]->SetVisible(false);
	m_chart4.RefreshCtrl();
}


void CFormDlg3::OnBnClickedCheck8()
{
	if (((CButton*)GetDlgItem(IDC_CHECK8))->GetCheck() == 1)
		m_pLineSeries_capture[3]->SetVisible(true);
	else
		m_pLineSeries_capture[3]->SetVisible(false);
	m_chart4.RefreshCtrl();
}
