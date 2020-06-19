// PullFileCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "SimpleInsectRadar.h"
#include "PullFileCfg.h"
#include "afxdialogex.h"


// CPullFileCfg 对话框

IMPLEMENT_DYNAMIC(CPullFileCfg, CDialogEx)

CPullFileCfg::CPullFileCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPullFileCfg::IDD, pParent)
	, m_nNeedFileSize(0)
	, m_startAddress(0)
{

}

CPullFileCfg::~CPullFileCfg()
{
}

void CPullFileCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nNeedFileSize);
	DDX_Text(pDX, IDC_EDIT_STARTADDR, m_startAddress);
}


BEGIN_MESSAGE_MAP(CPullFileCfg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPullFileCfg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPullFileCfg 消息处理程序


BOOL CPullFileCfg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯


	POSITION pos;		
	pos = theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.FindIndex(theApp.m_pMainDlg->m_fileSelectedArray.GetAt(0));
	FILELISTINFO *p = (FILELISTINFO *)theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetAt(pos);
	ULONGLONG ulFileSize = (p->EndAddress) - (p->BeginAddress);

	m_nNeedFileSize = ulFileSize / (ULONGLONG)(1024*1024);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


//确定
void CPullFileCfg::OnBnClickedOk()
{
	UpdateData(TRUE);

	int nSelectedItemCnt = theApp.m_pMainDlg->m_fileSelectedArray.GetSize();

	UINT nSelectItem = theApp.m_pMainDlg->m_fileSelectedArray.GetAt(0);

	//提取被选文件的文件信息
	for (int i=0; i<nSelectedItemCnt; i++)
	{
		POSITION pos;		
		pos = theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.FindIndex(theApp.m_pMainDlg->m_fileSelectedArray.GetAt(i));
		FILELISTINFO *p = (FILELISTINFO *)theApp.m_pMainDlg->m_formDlg2.m_fileinfolist.GetAt(pos);

		ULONGLONG ulFileSize = (p->EndAddress) - (p->BeginAddress);

		if (m_nNeedFileSize*1024*1024 > (ulFileSize - m_startAddress*1024*1024))
		{
			MessageBox(_T("所选范围过大，请重新选择！"), NULL, MB_ICONWARNING);
			return;
		}

		if (m_nNeedFileSize*1024*1024 > ulFileSize)
		{
			MessageBox(_T("所选范围过大，请重新选择！"), NULL, MB_ICONWARNING);
			return;
		}
	}

	//将所需的文件大小赋值给全局变量;
	g_singleFileSize = m_nNeedFileSize;
	g_startAddress = m_startAddress;

	//向主界面发消息，调用导数线程
	::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+777, NULL, NULL);

	BOOL bShowWindow = FALSE;
	::SendMessage(theApp.m_pMainDlg->m_formDlg2.m_hWnd, WM_USER+778, (WPARAM)&bShowWindow, NULL);

	CDialogEx::OnOK();
}



