
// SimpleInsectRadar.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "SimpleInsectRadarDlg.h"
//#include "TCPClient.h"
// CSimpleInsectRadarApp:
// �йش����ʵ�֣������ SimpleInsectRadar.cpp
//

class CSimpleInsectRadarApp : public CWinApp
{
public:
	CSimpleInsectRadarApp();

// ��д
public:
	virtual BOOL InitInstance();
	CSimpleInsectRadarDlg *m_pMainDlg;

	

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CSimpleInsectRadarApp theApp;