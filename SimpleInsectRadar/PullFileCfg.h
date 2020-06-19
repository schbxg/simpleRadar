#pragma once

#include "SimpleInsectRadarDlg.h"
// CPullFileCfg 对话框

class CPullFileCfg : public CDialogEx
{
	DECLARE_DYNAMIC(CPullFileCfg)

public:
	CPullFileCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPullFileCfg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	ULONGLONG m_nNeedFileSize;
	virtual BOOL OnInitDialog();
	ULONGLONG m_startAddress;
};
