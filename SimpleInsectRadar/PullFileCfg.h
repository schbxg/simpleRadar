#pragma once

#include "SimpleInsectRadarDlg.h"
// CPullFileCfg �Ի���

class CPullFileCfg : public CDialogEx
{
	DECLARE_DYNAMIC(CPullFileCfg)

public:
	CPullFileCfg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPullFileCfg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	ULONGLONG m_nNeedFileSize;
	virtual BOOL OnInitDialog();
	ULONGLONG m_startAddress;
};
