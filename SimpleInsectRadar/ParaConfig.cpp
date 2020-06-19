// ParaConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "SimpleInsectRadar.h"
#include "ParaConfig.h"
#include "afxdialogex.h"


// CParaConfig 对话框

IMPLEMENT_DYNAMIC(CParaConfig, CDialogEx)

CParaConfig::CParaConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(CParaConfig::IDD, pParent)
	, m_wbNum(10)
	, m_AziStart(-90)
	, m_AziEnd(90)
	, m_AziSpeed(1)
	, m_EleStart(0)
	, m_EleEnd(90)
	, m_EleSpeed(1)
	, m_aziCircleCnt(1)
	, m_szSavePath(_T(""))
	, m_edit_1(20)
	, m_edit_2(100)
	, m_edit_3(60)
	, m_edit_4(0)
	, m_edit_5(2)
	, m_edit_6(3)
	, m_edit_7(1)
	, m_edit_8(1)
	, m_edit_9(100)
	, m_edit_10(50)
	, m_RCS_ball(0)
	, m_edit_11(5)
	, m_edit_12(3)
	, m_dlMinLength_Cali(0)
	, m_dlMinLength_Orien(0)
	, m_dlMinLength_Den(0)
	, m_edit_distDetect(0)
	, m_edit_dopplerDetect(0)
	, m_editPlayBackTrackPath(_T(""))
	, m_editPlayBackTimerInterval(0)
{
	memset(&m_radarPara, 0, sizeof(m_radarPara));
	m_iniAzimuth = 0.0f;
}

CParaConfig::~CParaConfig()
{
}

void CParaConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combox1);
	DDX_Control(pDX, IDC_COMBO2, m_combox2);
	DDX_Control(pDX, IDC_COMBO3, m_combox3);
	DDX_Control(pDX, IDC_COMBO4, m_combox4);
	DDX_Control(pDX, IDC_COMBO5, m_combox5);
	DDX_Control(pDX, IDC_COMBO6, m_combox6);
	DDX_Control(pDX, IDC_COMBO7, m_combox7);
	DDX_Control(pDX, IDC_COMBO8, m_combox9);
	DDX_Control(pDX, IDC_COMBO9, m_combox8);
	DDX_Control(pDX, IDC_COMBO10, m_combox10);
	DDX_Control(pDX, IDC_COMBO11, m_comboxPlusWidth);
	DDX_Control(pDX, IDC_COMBO12, m_comboxSimpleRage);
	DDX_Control(pDX, IDC_COMBO13, m_combox13);
	DDX_Control(pDX, IDC_COMBO14, m_combox14);
	DDX_Control(pDX, IDC_COMBO15, m_combox15);
	DDX_Text(pDX, IDC_EDIT11, m_wbNum);
	DDX_Text(pDX, IDC_EDIT8, m_AziStart);
	DDX_Text(pDX, IDC_EDIT9, m_AziEnd);
	DDX_Text(pDX, IDC_EDIT10, m_AziSpeed);
	DDX_Text(pDX, IDC_EDIT5, m_EleStart);
	DDX_Text(pDX, IDC_EDIT6, m_EleEnd);
	DDX_Text(pDX, IDC_EDIT7, m_EleSpeed);
	DDX_Text(pDX, IDC_EDIT12, m_aziCircleCnt);
	//DDV_MinMaxFloat(pDX, m_AziStart, -200, 200);
	//DDV_MinMaxFloat(pDX, m_AziEnd, -200, 200);
	//DDV_MinMaxFloat(pDX, m_AziSpeed, 0, 60);
	//DDV_MinMaxFloat(pDX, m_EleStart, 0, 90);
	//DDV_MinMaxFloat(pDX, m_EleEnd, 0, 90);
	//DDV_MinMaxFloat(pDX, m_EleSpeed, 0, 40);
	DDX_Control(pDX, IDC_COMBO17, m_combox17);
	DDX_Control(pDX, IDC_COMBO18, m_combox18);
	DDX_Text(pDX, IDC_EDIT13, m_szSavePath);
	DDX_Text(pDX, IDC_EDIT15, m_edit_1);
	DDX_Control(pDX, IDC_COMBO19, m_combox19);
	DDX_Control(pDX, IDC_COMBO20, m_combox20);
	DDX_Control(pDX, IDC_COMBO21, m_combox21);
	DDX_Control(pDX, IDC_COMBO22, m_combox22);
	DDX_Control(pDX, IDC_COMBO23, m_combox23);
	DDX_Text(pDX, IDC_EDIT21, m_edit_2);
	DDX_Text(pDX, IDC_EDIT22, m_edit_3);
	DDX_Text(pDX, IDC_EDIT23, m_edit_4);
	DDX_Text(pDX, IDC_EDIT24, m_edit_5);
	DDX_Text(pDX, IDC_EDIT25, m_edit_6);
	DDX_Text(pDX, IDC_EDIT26, m_edit_7);
	DDX_Text(pDX, IDC_EDIT27, m_edit_8);
	DDX_Text(pDX, IDC_EDIT28, m_edit_9);
	DDX_Text(pDX, IDC_EDIT29, m_edit_10);
	DDX_Text(pDX, IDC_EDIT14, m_RCS_ball);
	DDX_Text(pDX, IDC_EDIT30, m_edit_11);
	DDX_Control(pDX, IDC_COMBO24, m_combox24);
	DDX_Text(pDX, IDC_EDIT16, m_edit_12);	// 单词采集时间
	DDX_Text(pDX, IDC_EDIT17, m_dlMinLength_Cali);
	DDX_Text(pDX, IDC_EDIT18, m_dlMinLength_Orien);
	DDX_Text(pDX, IDC_EDIT19, m_dlMinLength_Den);
	DDX_Control(pDX, IDC_COMBO_WORKINGMODES, m_comboxWorkingModes);	// 工作模式
	DDX_Control(pDX, IDC_COMBO_MINITIME1, m_minitime);
	DDX_Text(pDX, IDC_EDIT_INIAZIMUTH, m_iniAzimuth);
	DDX_Control(pDX, IDC_COMBO_ATTENU, m_comboxAttenu);	// 衰减变为自动内校准模式
	DDX_Control(pDX, IDC_COMBO_MAINWAVPLUWID, m_mainWavPlusWid);	// 主-波形脉宽
	DDX_Control(pDX, IDC_COMBO_MAININITSAMPDIST, m_mainInitSapDist);	// 主-起始采样距离
	DDX_Control(pDX, IDC_COMBO_DPTWAVPLUWID, m_dptWavPlusWid);	// 副-波形脉宽
	DDX_Control(pDX, IDC_COMBO_DPTINITSAMPDIST2, m_dptInitSampDist);	// 副-起始采样距离
	DDX_Control(pDX, IDC_COMBO_WORKMODE, m_combox_workMode);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_dateTimePickerStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STOP, m_dateTimePickerStop);
	DDX_Text(pDX, IDC_EDIT_DISTDETECT, m_edit_distDetect);	// 距离检测单元数
	DDX_Text(pDX, IDC_EDIT_DOPPLERDETECT, m_edit_dopplerDetect);	// 多普勒检测单元数
	DDX_Control(pDX, IDC_COMBO_AUTOCALI, m_autoCali);	// 自动内校准使能
	DDX_Control(pDX, IDC_COMBO_AUTOCALIMODE, m_comboxAutoCaliMode);	// 自动内校准模式
	DDX_Control(pDX, IDC_COMBO_ZHUANCUN, m_combox_zhuancun);
	DDX_Control(pDX, IDC_COMBO_ZHUANCUNTIME, m_combox_zhuanCunTime);
	DDX_Control(pDX, IDC_COMBO_DETECTIONCHANNEL, m_combox_detectionChannel);
	DDX_Control(pDX, IDC_COMBO_ENABLEPLAYBACK, m_comboxEnablePlayBack);
	DDX_Text(pDX, IDC_EDIT_PLAYBACKTRACKPATH, m_editPlayBackTrackPath);
	//  DDX_Control(pDX, IDC_DATETIMEPICKER_STARTPLAYBACK, m_dateTimePickerDtart);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STOPPLAYBACK, m_dateTimerPickerStopPlayBack);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTPLAYBACK, m_dateTimePickerStartPlayBack);
	DDX_Text(pDX, IDC_EDIT_TIMEINTERVAL, m_editPlayBackTimerInterval);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTPLAYBACKDATE, m_dateTimePickerStartPlayBackDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STOPPLAYBACKDATE2, m_dateTimePickerStopDate);
	DDX_Control(pDX, IDC_COMBO_SLOWSCAN, m_comboxSlowScan);
}


BEGIN_MESSAGE_MAP(CParaConfig, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CParaConfig::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CParaConfig::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CParaConfig::OnCbnSelchangeCombo1)
	ON_EN_UPDATE(IDC_EDIT11, &CParaConfig::OnEnUpdateEdit11)
	ON_CBN_SELCHANGE(IDC_COMBO15, &CParaConfig::OnCbnSelchangeCombo15)
	ON_BN_CLICKED(IDC_BUTTON12, &CParaConfig::OnBnClickedButton12)
	ON_CBN_SELCHANGE(IDC_COMBO18, &CParaConfig::OnCbnSelchangeCombo18)
	ON_CBN_SELCHANGE(IDC_COMBO_WORKINGMODES, &CParaConfig::OnCbnSelchangeComboWorkingmodes)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CParaConfig::OnCbnSelchangeCombo5)
	ON_BN_CLICKED(IDC_BUTTON_CHOSEPLAYBACKPATH, &CParaConfig::OnBnClickedButtonChoseplaybackpath)
END_MESSAGE_MAP()


// CParaConfig 消息处理程序

//CString dataTimerPickerStartPlayAr;
BOOL CParaConfig::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//MessageBox(_T("OnInitDialog"));
	InitFilePath_jiaozhun();

	//波形模式
	m_combox1.InsertString(0, _T("近距同时全极化"));
	m_combox1.InsertString(1, _T("近距分时全极化"));
	m_combox1.InsertString(2, _T("远距同时全极化"));
	m_combox1.InsertString(3, _T("远距分时全极化"));

	//脉间编码模式
	m_combox2.InsertString(0, _T("无脉间编码"));
	m_combox2.InsertString(1, _T("单帧脉间四相编码"));
	m_combox2.InsertString(2, _T("双帧脉间四相编码"));
	m_combox2.InsertString(3, _T("双帧帧间二相编码"));
	m_combox17.InsertString(0, _T("无脉间编码"));
	m_combox17.SetCurSel(0);

	//PRT
	m_combox3.InsertString(0, _T("25us"));
	m_combox3.InsertString(1, _T("30us"));
	m_combox3.InsertString(2, _T("35us"));
	m_combox3.InsertString(3, _T("40us"));
	m_combox3.InsertString(4, _T("50us"));
	m_combox3.InsertString(5, _T("60us"));
	m_combox3.InsertString(6, _T("70us"));
	m_combox3.InsertString(7, _T("80us"));


	//远距波形脉宽
	m_comboxPlusWidth.InsertString(0, _T("0.4s"));
	m_comboxPlusWidth.InsertString(1, _T("1us"));
	m_comboxPlusWidth.InsertString(2, _T("2us"));
	m_comboxPlusWidth.InsertString(3, _T("3us"));
	m_comboxPlusWidth.InsertString(4, _T("4us"));
	m_comboxPlusWidth.InsertString(5, _T("5us"));

	// 主波形-波形脉宽
	m_mainWavPlusWid.InsertString(0, _T("0.4s"));
	m_mainWavPlusWid.InsertString(1, _T("1us"));
	m_mainWavPlusWid.InsertString(2, _T("2us"));
	m_mainWavPlusWid.InsertString(3, _T("3us"));
	m_mainWavPlusWid.InsertString(4, _T("4us"));
	m_mainWavPlusWid.InsertString(5, _T("5us"));

	// 副-波形脉宽
	m_dptWavPlusWid.InsertString(0, _T("0.4s"));
	m_dptWavPlusWid.InsertString(1, _T("1us"));
	m_dptWavPlusWid.InsertString(2, _T("2us"));
	m_dptWavPlusWid.InsertString(3, _T("3us"));
	m_dptWavPlusWid.InsertString(4, _T("4us"));
	m_dptWavPlusWid.InsertString(5, _T("5us"));

	((CComboBox*)GetDlgItem(IDC_COMBO16))->InsertString(0, _T("0.1us"));
	((CComboBox*)GetDlgItem(IDC_COMBO16))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO16))->ShowWindow(FALSE);

	// 主波形
	((CComboBox*)GetDlgItem(IDC_COMBO_MWAVPLUWID))->InsertString(0, _T("0.1us"));
	((CComboBox*)GetDlgItem(IDC_COMBO_MWAVPLUWID))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_MWAVPLUWID))->ShowWindow(FALSE);
	// 副波形
	((CComboBox*)GetDlgItem(IDC_COMBO_DWAVPLUWID))->InsertString(0, _T("0.1us"));
	((CComboBox*)GetDlgItem(IDC_COMBO_DWAVPLUWID))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_DWAVPLUWID))->ShowWindow(FALSE);
	

	//信息上传周期
	for (int i=0; i<10; i++)
	{
		CString str;
		str.Format(_T("%d帧上传一次"), (i+1)*100);
		m_combox4.InsertString(i, str);
	}

	//起始采样距离
	for (int i=0; i<56; i++)
	{
		CString str;
		str.Format(_T("%dm"), i*15);
		m_comboxSimpleRage.InsertString(i, str);
	}

	// 主-起始采样距离
	for (int i=0; i<56; i++)
	{
		CString str;
		str.Format(_T("%dm"), i*15);
		m_mainInitSapDist.InsertString(i, str);
	}

	// 副-起始采样距离
	for (int i=0; i<56; i++)
	{
		CString str;
		str.Format(_T("%dm"), i*15);
		m_dptInitSampDist.InsertString(i, str);
	}

	//采样窗点数
	m_combox5.InsertString(0, _T("256"));
	m_combox5.InsertString(1, _T("512"));
	m_combox5.InsertString(2, _T("1024"));
	m_combox5.InsertString(3, _T("2048"));

	//实时成像上传点数
	m_combox6.InsertString(0, _T("256"));
	m_combox6.InsertString(1, _T("512"));
	m_combox6.InsertString(2, _T("1024"));
	m_combox6.InsertString(3, _T("2048"));
	m_combox6.InsertString(4, _T("4096"));
	m_combox6.InsertString(5, _T("8192"));
	m_combox6.InsertString(6, _T("16384"));

	//AGC控制码1和2
	UINT AGC[7] = {0, 1, 2, 4, 8, 16, 31};
	for (int i=0; i<7; i++)
	{
		CString str;
		str.Format(_T("%d"), AGC[i]);
		m_combox7.InsertString(i, str);
		m_combox9.InsertString(i, str);
	}
	
	
	//校准通道使能
	m_combox8.InsertString(0, _T("否"));
	m_combox8.InsertString(1, _T("是"));
	
	//校准通道控制
	m_combox10.InsertString(0, _T("000(正常)"));
	m_combox10.InsertString(1, _T("001(发射1)"));
	m_combox10.InsertString(2, _T("010(发射2)"));
	m_combox10.InsertString(3, _T("011(接收1)"));
	m_combox10.InsertString(4, _T("100(接收2)"));
	m_combox10.InsertString(5, _T("101(发射1和2)"));
	m_combox10.InsertString(6, _T("110(接收1和2)"));
	m_combox10.InsertString(7, _T("111(自校准)"));


	//处理跳频点数
	m_combox13.InsertString(0, _T("10"));
	m_combox13.InsertString(1, _T("20"));
	m_combox13.InsertString(2, _T("30"));
	m_combox13.InsertString(3, _T("40"));
	m_combox14.InsertString(0, _T("40"));
	m_combox14.SetCurSel(0);

	//调频预留时间
	m_combox24.InsertString(0, _T("15us"));
	m_combox24.InsertString(1, _T("30us"));
	m_combox24.InsertString(2, _T("40us"));
	m_combox24.InsertString(3, _T("50us"));
	m_combox24.InsertString(4, _T("60us"));
	m_combox24.InsertString(5, _T("70us"));

	//天线转动模式
	m_combox15.InsertString(0, _T("待机状态"));
	m_combox15.InsertString(1, _T("自检模式"));
	m_combox15.InsertString(2, _T("定位模式"));
	m_combox15.InsertString(3, _T("垂直对天扫描模式"));
	m_combox15.InsertString(4, _T("方位一维扫描模式"));
	m_combox15.InsertString(5, _T("俯仰一维扫描模式"));
	m_combox15.InsertString(6, _T("往返二维扫描模式"));
	m_combox15.InsertString(7, _T("单程二维扫描模式"));
	m_combox15.InsertString(8, _T("高度覆盖模式-1"));
	m_combox15.InsertString(9, _T("高度覆盖模式-2"));
	m_combox15.InsertString(10, _T("高度覆盖模式-3"));

	//CA-CFAR
	for (int i=0; i<11; i++)
	{
		CString ss;
		ss.Format(_T("%d"), i);
		m_combox19.InsertString(i, ss);
		m_combox20.InsertString(i, ss);
	}
	m_combox19.SetCurSel(2);
	m_combox20.SetCurSel(4);

	for (int i=0; i<11; i++)
	{
		CString ss;
		ss.Format(_T("%d"), i);
		m_combox21.InsertString(i, ss);
		m_combox22.InsertString(i, ss);
		m_combox23.InsertString(i, ss);
	}
	for (int i=0; i<10; i++)
	{
		CString ss;
		ss.Format(_T("-%d"), 10-i);
		m_combox21.InsertString(i, ss);
		m_combox22.InsertString(i, ss);
		m_combox23.InsertString(i, ss);
	}
	m_combox21.SetCurSel(10);
	m_combox22.SetCurSel(10);
	m_combox23.SetCurSel(10);
	

	//模式选择
	m_combox18.InsertString(0, _T("正常模式"));
	m_combox18.InsertString(1, _T("校准模式"));
	m_combox18.SetCurSel(0);

	// 工作模式
	m_comboxWorkingModes.InsertString(0, _T("一维距离象采集模式"));
	m_comboxWorkingModes.InsertString(1, _T("垂直模式-单一脉宽"));
	m_comboxWorkingModes.InsertString(2, _T("扫描模式"));
	m_comboxWorkingModes.InsertString(3, _T("垂直模式-交替脉宽"));
	m_comboxWorkingModes.SetCurSel(1);

	// 数据采集最小时间间隔
	m_minitime.InsertString(0, _T("不控制"));
	for(int i = 1; i < 12; ++i)
	{
		CString ss;
		ss.Format(_T("%d"), 10 + (i-1)*5);
		m_minitime.InsertString(i, ss);
	}
	m_minitime.SetCurSel(0);

	// 衰减
	m_comboxAttenu.InsertString(0,_T("00001"));
	m_comboxAttenu.InsertString(1,_T("00010"));
	m_comboxAttenu.InsertString(2,_T("00100"));
	m_comboxAttenu.InsertString(3,_T("01000"));
	m_comboxAttenu.InsertString(4,_T("10000"));
	m_comboxAttenu.InsertString(5,_T("00000"));
	m_comboxAttenu.SetCurSel(5);

	// 软件工作模式-定时
	m_combox_workMode.InsertString(0, _T("正常模式"));
	m_combox_workMode.InsertString(1, _T("定时模式"));
	m_combox_workMode.SetCurSel(0);

	// 时间初始化
	CTime tTime(0, 0, 0);
	m_dateTimePickerStart.SetTime(&tTime);
	m_dateTimePickerStop.SetTime(&tTime);

	// 自动内校准使能
	m_autoCali.InsertString(0, _T("否"));
	m_autoCali.InsertString(1, _T("是"));
	m_autoCali.SetCurSel(0);

	// 自动内校准模式
	m_comboxAutoCaliMode.InsertString(0, _T("两通道同时"));
	m_comboxAutoCaliMode.InsertString(1, _T("两通道分时"));
	m_comboxAutoCaliMode.SetCurSel(0);


	// 转存使能
	m_combox_zhuancun.InsertString(0, _T("否"));
	m_combox_zhuancun.InsertString(1, _T("是"));
	m_combox_zhuancun.SetCurSel(0);

	// 转存时间
	m_combox_zhuanCunTime.InsertString(0, _T("1h"));
	m_combox_zhuanCunTime.InsertString(1, _T("2h"));
	m_combox_zhuanCunTime.InsertString(2, _T("3h"));
	m_combox_zhuanCunTime.InsertString(3, _T("4h"));
	m_combox_zhuanCunTime.InsertString(4, _T("5h"));
	m_combox_zhuanCunTime.InsertString(5, _T("6h"));
	m_combox_zhuanCunTime.InsertString(6, _T("7h"));
	m_combox_zhuanCunTime.InsertString(7, _T("8h"));
	m_combox_zhuanCunTime.SetCurSel(0);

	// 检测通道
	m_combox_detectionChannel.InsertString(0, _T("HH"));
	m_combox_detectionChannel.InsertString(1, _T("HV"));
	m_combox_detectionChannel.InsertString(2, _T("VH"));
	m_combox_detectionChannel.InsertString(3, _T("VV"));
	m_combox_detectionChannel.SetCurSel(0);

	// 回放使能
	m_comboxEnablePlayBack.InsertString(0, _T("否"));
	m_comboxEnablePlayBack.InsertString(1, _T("是"));
	m_comboxEnablePlayBack.SetCurSel(0);

	// 慢扫模式使能
	m_comboxSlowScan.InsertString(0, _T("否"));
	m_comboxSlowScan.InsertString(1, _T("是"));
	m_comboxSlowScan.SetCurSel(0);


	// 串行化, 把参数信息写进txt
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("ParaConfig.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file(strModulePath, CFile::modeRead);
	CArchive ar(&file,CArchive::load);
	
	int tt = 0;
	ar >> tt;
	m_combox1.SetCurSel(tt);
	ar >> tt;
	m_combox2.SetCurSel(tt);
	ar >> tt;
	m_combox3.SetCurSel(tt);
	ar >> tt;
	m_comboxPlusWidth.SetCurSel(tt);

	// 主波形脉宽
	ar >> tt;
	m_mainWavPlusWid.SetCurSel(tt);

	// 副波形脉宽
	ar >> tt;
	m_dptWavPlusWid.SetCurSel(tt);

	ar >> tt;
	m_combox4.SetCurSel(tt);

	ar >> tt;
	m_comboxSimpleRage.SetCurSel(tt);

	// 主-起始采样距离
	ar >> tt;
	m_mainInitSapDist.SetCurSel(tt);
	// 副-起始采样距离
	ar >> tt;
	m_dptInitSampDist.SetCurSel(tt);

	ar >> tt;
	m_combox5.SetCurSel(tt);
	ar >> tt;
	m_combox6.SetCurSel(tt);
	ar >> tt;
	m_combox7.SetCurSel(tt);
	ar >> tt;
	m_combox8.SetCurSel(tt);
	ar >> tt;
	m_combox9.SetCurSel(tt);
	ar >> tt;
	m_combox10.SetCurSel(tt);
	ar >> tt;
	m_combox13.SetCurSel(tt);
	//ar >> tt;
	//m_combox17.SetCurSel(tt);
	ar >> tt;
	m_combox24.SetCurSel(tt);

	if (m_combox1.GetCurSel() == 1 || m_combox1.GetCurSel() == 3)
	{
		m_combox13.ShowWindow(TRUE);
		m_combox14.ShowWindow(FALSE);

		m_combox17.ShowWindow(TRUE);		//脉间编码都有
		m_combox2.ShowWindow(FALSE);
	}
	else
	{
		m_combox13.ShowWindow(FALSE);
		m_combox14.ShowWindow(TRUE);

		m_combox17.ShowWindow(FALSE);		
		m_combox2.ShowWindow(TRUE);
	}

	if (m_combox1.GetCurSel() == 0 || m_combox1.GetCurSel() == 1)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO11))->ShowWindow(FALSE);
		(CComboBox*)GetDlgItem(IDC_COMBO_MAINWAVPLUWID)->ShowWindow(FALSE);
		(CComboBox*)GetDlgItem(IDC_COMBO_DPTWAVPLUWID)->ShowWindow(FALSE);
		((CComboBox*)GetDlgItem(IDC_COMBO16))->ShowWindow(TRUE);
		((CComboBox*)GetDlgItem(IDC_COMBO_MWAVPLUWID))->ShowWindow(TRUE);
		((CComboBox*)GetDlgItem(IDC_COMBO_DWAVPLUWID))->ShowWindow(TRUE);
	}
	else
	{
		(CComboBox*)GetDlgItem(IDC_COMBO_MAINWAVPLUWID)->ShowWindow(TRUE);
		(CComboBox*)GetDlgItem(IDC_COMBO_DPTWAVPLUWID)->ShowWindow(TRUE);
		((CComboBox*)GetDlgItem(IDC_COMBO11))->ShowWindow(TRUE);
		((CComboBox*)GetDlgItem(IDC_COMBO16))->ShowWindow(FALSE);
		((CComboBox*)GetDlgItem(IDC_COMBO_MWAVPLUWID))->ShowWindow(FALSE);
		((CComboBox*)GetDlgItem(IDC_COMBO_DWAVPLUWID))->ShowWindow(FALSE);
	}
	
	ar >> tt;
	m_combox15.SetCurSel(tt);
	switch (tt)
	{
	case 0:
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 1:
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 2:
		GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 3:
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 4:
		GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 5:
		GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 6:
		GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 7:
		GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 8:		//高度覆盖模式-1
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(TRUE);
		break;
	case 9:		//高度覆盖模式-2
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(TRUE);
		break;
	case 10:	//高度覆盖模式-3
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(TRUE);
		break;
	}

	ar >> m_edit_1;
	ar >> tt;
	m_combox19.SetCurSel(tt);
	ar >> tt;
	m_combox20.SetCurSel(tt);
	ar >> tt;
	m_combox21.SetCurSel(tt);
	ar >> tt;
	m_combox22.SetCurSel(tt);
	ar >> tt;
	 m_combox23.SetCurSel(tt);
	ar >> m_edit_2;
	ar >> m_edit_3;
	ar >> m_edit_4;
	ar >> m_edit_11;

	ar >> m_edit_5;
	ar >> m_edit_6;
	ar >> m_edit_7;
	ar >> m_edit_8;
	ar >> m_edit_9;
	ar >> m_edit_10;
	ar >> tt;
	m_combox18.SetCurSel(tt);
	ar >> m_RCS_ball;

	ar >> m_edit_12;

	ar >> m_dlMinLength_Cali;
	ar >> m_dlMinLength_Orien;
	ar >> m_dlMinLength_Den;

	// 伺服参数
	ar >> m_AziStart;	// 方位起始角度
	ar >> m_AziEnd;		// 方位终止角度
	ar >> m_AziSpeed;	// 方位扫描角度
	ar >> m_wbNum;		// 方位旋转圈数
	ar >> m_EleStart;	// 俯仰起始角度
	ar >> m_EleEnd;		// 俯仰终止角度
	ar >> m_EleSpeed;	// 俯仰扫描速度

	// 工作模式
	ar >> tt;
	m_comboxWorkingModes.SetCurSel(tt);

	// 记忆上次选择参数的状态
	if(tt == 3)
	{
		GetDlgItem(IDC_COMBO16)->EnableWindow(FALSE);
		/*GetDlgItem(IDC_COMBO_MAINWAVPLUWID)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DPTWAVPLUWID)->EnableWindow(FALSE);*/

		GetDlgItem(IDC_COMBO_MWAVPLUWID)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DWAVPLUWID)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO11)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO12)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_MAINWAVPLUWID)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_MAININITSAMPDIST)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DPTWAVPLUWID)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DPTINITSAMPDIST2)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_MAINWAVPLUWID)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_MAININITSAMPDIST)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DPTWAVPLUWID)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DPTINITSAMPDIST2)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO11)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO12)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO16)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_MWAVPLUWID)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DWAVPLUWID)->EnableWindow(TRUE);
	}

	//实时采集参数
	ar >> m_iniAzimuth; // 采集起始方位角
	ar >> tt;
	m_minitime.SetCurSel(tt); // 采集最小时间间隔

	
	ar >> m_edit_distDetect;	// 距离检测单元数
	ar >> m_edit_dopplerDetect;	// 多普勒检测单元数

	// 软件工作模式-定时模式
	ar >> tt;
	m_combox_workMode.SetCurSel(tt);

	// 时间序列化
	/*ar >> tTime;
	m_dateTimePickerStart.SetTime(&tTime);

	ar >> tTime;
	m_dateTimePickerStop.SetTime(&tTime);*/

	// 自动校准使能
	ar >> tt;
	m_autoCali.SetCurSel(tt);

	// 自动校准模式
	ar >> tt;
	m_comboxAutoCaliMode.SetCurSel(tt);

	// Track路径序列化
	ar >> m_editPlayBackTrackPath;

	// Track文件回放时间间隔
	ar >> m_editPlayBackTimerInterval;
	// 时间控件，开始回放时间
	/*ar >> dataTimerPickerStartPlayAr;
	SetDlgItemText(IDC_DATETIMEPICKER_STARTPLAYBACK, dataTimerPickerStartPlayAr);*/

	// 慢扫模式使能
	ar >> tt;
	m_comboxSlowScan.SetCurSel(tt);

	UpdateData(false);

	CString strstr;
	/*m_combox1.*/GetDlgItemText(IDC_COMBO1, strstr);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//确定按钮
bool b_isOkBtnParaConfig = false;
UINT tempnPara_7 = 0;	// 垂直交替模式-主波形起始采样距离，其他模式-起始采样距离
UINT tempDptInitSampDist = 0; // 垂直交替模式-副波形起始采样距离
float tempnPara_48 = 0.0;
RadarPara tempRadarPara;
extern RadarPara ToDspParaConfig;
extern int verticalOrSlowScanCount;
void CParaConfig::OnBnClickedButton1()
{
	if ((g_iIsTcpConnect != 0) && (m_comboxEnablePlayBack.GetCurSel() == 0))
	{
		MessageBox(_T("网络异常，无法向DSP下发配置参数"), NULL, MB_ICONWARNING);
		//return;
	}
	if (g_bflag_enable == false)	//开始工作后此标志位false，忽略点击确定；
	{
		CDialogEx::OnOK();
		return;
	}

	DeleteFiles(_T("ToDspParaConfig.txt"));
	DeleteFiles(_T("ToOwnParaConfig.txt"));
	DeleteFiles(_T("ToMatlabParaConfig.txt"));

	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("ParaConfig.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file(strModulePath, CFile::modeWrite);
	CArchive ar(&file,CArchive::store);

	

	UpdateData(TRUE);
	//界面数据序列化
	ar << m_combox1.GetCurSel();
	ar << m_combox2.GetCurSel();
	ar << m_combox3.GetCurSel();
	ar << m_comboxPlusWidth.GetCurSel();
	ar << m_mainWavPlusWid.GetCurSel();	// 主-波形脉宽
	ar << m_dptWavPlusWid.GetCurSel();	// 副-波形脉宽
	ar << m_combox4.GetCurSel();
	ar << m_comboxSimpleRage.GetCurSel();
	ar << m_mainInitSapDist.GetCurSel();	// 主-起始采样距离
	ar << m_dptInitSampDist.GetCurSel();	// 副-起始采样距离
	ar << m_combox5.GetCurSel();
	ar << m_combox6.GetCurSel();
	ar << m_combox7.GetCurSel();
	ar << m_combox8.GetCurSel();
	ar << m_combox9.GetCurSel();
	ar << m_combox10.GetCurSel();
	ar << m_combox13.GetCurSel();
	ar << m_combox24.GetCurSel();

	ar << m_combox15.GetCurSel();
	//ar << m_combox17.GetCurSel();

	ar << m_edit_1;
	ar << m_combox19.GetCurSel();
	ar << m_combox20.GetCurSel();
	ar << m_combox21.GetCurSel();
	ar << m_combox22.GetCurSel();
	ar << m_combox23.GetCurSel();
	ar << m_edit_2;
	ar << m_edit_3;
	ar << m_edit_4;
	ar << m_edit_11;

	ar << m_edit_5;
	ar << m_edit_6;
	ar << m_edit_7;
	ar << m_edit_8;
	ar << m_edit_9;
	ar << m_edit_10;
	ar << m_combox18.GetCurSel();
	ar <<m_RCS_ball;

	ar << m_edit_12;

	ar << m_dlMinLength_Cali;
	ar << m_dlMinLength_Orien;
	ar << m_dlMinLength_Den;

	// 伺服参数
	ar << m_AziStart;	// 方位起始角度
	ar << m_AziEnd;		// 方位终止角度
	ar << m_AziSpeed;	// 方位扫描角度
	ar << m_wbNum;		// 方位旋转圈数
	ar << m_EleStart;	// 俯仰起始角度
	ar << m_EleEnd;		// 俯仰终止角度
	ar << m_EleSpeed;	// 俯仰扫描速度

	// 工作模式
	ar << m_comboxWorkingModes.GetCurSel();
	

	//实时采集参数
	ar << m_iniAzimuth; // 采集起始方位角
	ar << m_minitime.GetCurSel(); // 采集最小时间间隔

	ar << m_edit_distDetect;	// 距离检测单元数
	ar << m_edit_dopplerDetect;	// 多普勒检测单元数

	// 工作模式-定时功能
	ar << m_combox_workMode.GetCurSel();

	// 时间插件序列化-start
	/*CTime cTimett;
	m_dateTimePickerStart.GetTime(cTimett);
	ar << cTimett;*/

	// 时间插件序列化-stop
	/*m_dateTimePickerStop.GetTime(cTimett);
	ar << cTimett;*/

	// 自动校准使能
	ar << m_autoCali.GetCurSel();

	// 自动校准模式
	ar << m_comboxAutoCaliMode.GetCurSel();

	// Track路径序列化
	ar << m_editPlayBackTrackPath;
	// 回放文件间隔时间
	ar << m_editPlayBackTimerInterval;

	// 慢扫模式使能
	ar << m_comboxSlowScan.GetCurSel();
	
	// 时间控件序列化
	/*GetDlgItemText(IDC_DATETIMEPICKER_STARTPLAYBACK, dataTimerPickerStartPlayAr);
	ar << dataTimerPickerStartPlayAr;*/

	if((m_combox8.GetCurSel() == 0 && (m_combox10.GetCurSel() == 1 || m_combox10.GetCurSel() == 2 || m_combox10.GetCurSel() == 4 || m_combox10.GetCurSel() == 7) && m_comboxAttenu.GetCurSel() != 5))	// 是
	{
	}
	else if ((m_combox8.GetCurSel() == 1 && (m_combox10.GetCurSel() == 0 || m_combox10.GetCurSel() == 3 || m_combox10.GetCurSel() == 5 || m_combox10.GetCurSel() == 6) && m_comboxAttenu.GetCurSel() != 5))
	{	
	}
	else if(m_combox8.GetCurSel() == 0 && m_comboxAttenu.GetCurSel() == 5 && (m_combox10.GetCurSel() == 0 || m_combox10.GetCurSel() == 3 || m_combox10.GetCurSel() == 5 || m_combox10.GetCurSel() == 6))
	{}
	else if(m_combox8.GetCurSel() == 1 && m_comboxAttenu.GetCurSel() == 5 && (m_combox10.GetCurSel() == 1 || m_combox10.GetCurSel() == 2 || m_combox10.GetCurSel() == 4 || m_combox10.GetCurSel() == 7))
	{}
	else
	{
		MessageBox(_T("请重新选择校准通道使能、校准通道控制或衰减！"), NULL, MB_ICONERROR);
		return;
	}

	// 对多普勒参数极值进行限定-根据采样窗点数进行限定
	if(m_combox5.GetCurSel() == 0)
	{
		if(m_edit_dopplerDetect > 16 || m_edit_dopplerDetect < 2)
		{
			MessageBox(_T("多普勒检测单元数不在有效范围内，请重新输入！"));
			return;
		}
	}
	else if(m_combox5.GetCurSel() == 1)
	{
		if(m_edit_dopplerDetect > 8 || m_edit_dopplerDetect < 2)
		{
			MessageBox(_T("多普勒检测单元数不在有效范围内，请重新输入！"));
			return;
		}
	}
	else if(m_combox5.GetCurSel() == 2)
	{
		if(m_edit_dopplerDetect > 4 || m_edit_dopplerDetect < 2)
		{
			MessageBox(_T("多普勒检测单元数不在有效范围内，请重新输入！"));
			return;
		}
	}
	else if(m_combox5.GetCurSel() == 3)
	{
		if(!(m_edit_dopplerDetect == 2))
		{
			MessageBox(_T("多普勒检测单元数不在有效范围内，请重新输入！"));
			return;
		}
	}
	
	if (MinMaxFloat() != 0)
		return;
	

	//收集界面配置参数
	GetData(m_radarPara);
	tempRadarPara = m_radarPara;
	//配置与matlab交互参数
	//if (!ConfigMatlabPara())
		//return;
	GetData_ToMatlab(toMatlabPara);

	if (m_combox18.GetCurSel() == 0)
	{
		if ((!PathFileExists(toMatlabPara.s2)) && m_comboxEnablePlayBack.GetCurSel() == 0)
		{
			MessageBox(_T("极化文件不存在，请重新选择！"), NULL, MB_ICONERROR);
			return;
		}
	}
	else
	{
		if ((!PathFileExists(toMatlabPara.s1)) && m_comboxEnablePlayBack.GetCurSel() == 0)
		{
			MessageBox(_T("校准路径不存在，请重新选择！"), NULL, MB_ICONERROR);
			return;
		}
	}

	TCHAR szOwnModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szOwnModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szOwnModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szOwnModulePath , _T("ToOwnParaConfig.txt"));

	CString strOwnModulePath;
	strOwnModulePath = szOwnModulePath;
	CFile ownFile(strOwnModulePath, CFile::modeCreate | CFile::modeWrite);
	CArchive arOwn(&ownFile,CArchive::store);


	// 计算采集终止方位角度
	m_radarPara.nPara_endAzimuth = m_iniAzimuth + m_radarPara.nPara_20 * m_radarPara.nPara_48;
	arOwn << m_radarPara.nPara_endAzimuth;

	if((m_comboxWorkingModes.GetCurSel() == 2) && (m_combox15.GetCurSel() == 4 || m_combox15.GetCurSel() == 6 || m_combox15.GetCurSel() == 7))
	{
		if(!((m_iniAzimuth - m_radarPara.nPara_18 >= m_radarPara.nPara_20 * m_radarPara.nPara_20 / 60 + 5) &&
			(m_radarPara.nPara_19 - m_radarPara.nPara_endAzimuth >= m_radarPara.nPara_20 * m_radarPara.nPara_20 / 60 + 5)) )
		{
			MessageBox(_T("请重新配置扫描角度或扫描速度"), NULL, MB_ICONERROR);
			return;
		}
	}


	// 自动内校准使能
	g_autoCali = m_autoCali.GetCurSel();
	arOwn << g_autoCali;
	// 自动内校准模式
	g_autoCaliMode = m_comboxAutoCaliMode.GetCurSel();
	arOwn << g_autoCaliMode;
	// 转存使能
	g_zhuanCun = m_combox_zhuancun.GetCurSel();
	arOwn << g_zhuanCun;
	// 转存时间
	if(m_combox_zhuanCunTime.GetCurSel() == 0)
	{
		g_zhuanCunTime = 6;
	}
	else if(m_combox_zhuanCunTime.GetCurSel() == 1)
	{
		g_zhuanCunTime = 12;
	}
	else if(m_combox_zhuanCunTime.GetCurSel() == 2)
	{
		g_zhuanCunTime = 18;
	}
	else if(m_combox_zhuanCunTime.GetCurSel() == 3)
	{
		g_zhuanCunTime = 24;
	}
	else if(m_combox_zhuanCunTime.GetCurSel() == 4)
	{
		g_zhuanCunTime = 30;
	}
	else if(m_combox_zhuanCunTime.GetCurSel() == 5)
	{
		g_zhuanCunTime = 36;
	}
	else if(m_combox_zhuanCunTime.GetCurSel() == 6)
	{
		g_zhuanCunTime = 42;
	}
	else if(m_combox_zhuanCunTime.GetCurSel() == 7)
	{
		g_zhuanCunTime = 48;
	}
	arOwn << g_zhuanCunTime;

	// 慢扫使能
	g_slowScan = m_comboxSlowScan.GetCurSel();
	//g_zhuanCunTime = m_combox_zhuanCunTime.GetCurSel();


	// 内校准模式配参数
	if(g_autoCali == 1 && g_autoCaliMode == 0)
	{
		toMatlabPara.UintCaliType = 5;
		m_radarPara.nPara_13 = 0;
		m_radarPara.nPara_14 = 160;
	}
	else if(g_autoCali == 1 && g_autoCaliMode == 1)
	{
		toMatlabPara.UintCaliType = 1;
		m_radarPara.nPara_13 = 1;
		m_radarPara.nPara_14 = 32;
	}
	
	if(m_comboxEnablePlayBack.GetCurSel() == 0)
	{
		CString strMode, strMessage;
		m_combox18.GetLBText(m_combox18.GetCurSel(), strMode);
		strMessage = _T("当前为") + strMode + _T("，是否继续？");
		if (MessageBox(strMessage, NULL, MB_YESNO) == IDYES)
		{
			if(g_autoCali == 1)	// 自动内校准模式
			{
				m_radarPara.nPara_7 = 0;	// 起始采样距离为0
				m_radarPara.nPara_dptInitSampDist = 0;	// 交替模式下副波形起始采样距离
			}
			if(g_autoCali == 1 && g_autoCaliMode == 1)
			{
				m_radarPara.nPara_detectionChannel = 0; // 内校准模式下手动配参首先进行发射一校准，HH通道
			}
			
			// 将下发的Radar参数序列化
			ArRadarParaConfig(m_radarPara);
			verticalOrSlowScanCount =0; // 手动配参初始化为0
			int tt = 0;
			tt = g_tcpClient.Send((byte *)(&m_radarPara), sizeof(m_radarPara));
			//GetData_ToMatlab(toMatlabPara);
			CString str;
			str.Format(_T("%d"),tt);
			//theApp.m_pMainDlg->PrintMessage(str);

			if (tt == sizeof(m_radarPara))
			{
				::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+400, NULL, NULL);
				//theApp.m_pMainDlg->PrintMessage(L"手动SEND！");

				//GetData_ToMatlab(toMatlabPara);
			}
			b_isOkBtnParaConfig = true;
			
		}
		else
			return;
	}
	else
	{
		// 获取日期-时间控件内容
		GetDateTimeFromCtrl();
	}

	// 单次采集时间最大值限制---1024*1024*1024/(采样窗点数*160+128)*PRT*40/脉间编码模式
	int temp_g_singleAcquistionTimeMax = (g_singleAcquistionTimeMax / 1000000);
	if(m_edit_12 > temp_g_singleAcquistionTimeMax)
	{
		MessageBox(_T("单次采集时间值设置过大，请重新设置！"));
		return;
	}

	// 工作模式
	g_workMode = m_combox_workMode.GetCurSel();
	arOwn << g_workMode;

	arOwn << b_isOkBtnParaConfig;
	//theApp.m_pMainDlg->PrintMessage(_T("arOwn << b_isOkBtnParaConfig;"));

	// 获取开始工作-停止工作控件内容
	CString strStart, strLStart, strMStart, strStop, strLStop, strMStop;
	GetDlgItemText(IDC_DATETIMEPICKER_START, strStart);
	GetDlgItemText(IDC_DATETIMEPICKER_STOP, strStop);
	int iindex = strStart.Find(_T(":"));
	strLStart = strStart.Left(iindex);
	strMStart = strStart.Mid(iindex+1,2);
	strLStop = strStop.Left(iindex);
	strMStop = strStop.Mid(iindex+1,2);

	// 类型转换
	setTimeInfo.iStartHour = _ttoi(strLStart);
	setTimeInfo.iStartMinute = _ttoi(strMStart);
	setTimeInfo.iStopHour = _ttoi(strLStop);
	setTimeInfo.iStopMinute = _ttoi(strMStop);

	if(g_trackFilePath.IsEmpty() && m_comboxEnablePlayBack.GetCurSel() == 1)
	{
		MessageBox(L"路径为空，请选择有效的回放路径！");
		return;
	}
	if(m_comboxEnablePlayBack.GetCurSel() == 1 && !g_isSucessInitMatlabPlayBacklib)
	{
		AfxBeginThread(InitMatlabPlayBackLib, this);

	}

	CDialogEx::OnOK();
}

void CParaConfig::DeleteFiles(LPCTSTR LRFileName)
{
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , LRFileName);

	DeleteFile(szModulePath);
}

UINT tempStartRan = 0;
void CParaConfig::ArRadarParaConfig(RadarPara radarConfig)
{
	// 序列化
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("ToDspParaConfig.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file(strModulePath, CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file,CArchive::store);

	ar << radarConfig.nParaType;
	ar << radarConfig.nLen;
	ar << radarConfig.nPara_2;
	ar << radarConfig.nPara_3;
	ar << radarConfig.nPara_4;
	ar << radarConfig.nPara_5;
	ar << radarConfig.nPara_6;
	ar << radarConfig.nPara_7;
	ar << radarConfig.nPara_8;
	ar << radarConfig.nPara_9;
	ar << radarConfig.nPara_10;
	ar << radarConfig.nPara_11;
	ar << radarConfig.nPara_12;
	ar << radarConfig.nPara_13;
	ar << radarConfig.nPara_14;
	ar << radarConfig.nPara_15;
	ar << radarConfig.nPara_16;
	ar << radarConfig.nPara_17;
	ar << radarConfig.nNewAziSpeed;
	ar << radarConfig.nNewEleSpeed;
	ar << radarConfig.nPara_18;
	ar << radarConfig.nPara_19;
	ar << radarConfig.nPara_20;
	ar << radarConfig.nPara_21;
	ar << radarConfig.nPara_22;
	ar << radarConfig.nPara_23;
	ar << radarConfig.nPara_24;
	ar << radarConfig.reserve[0];
	ar << radarConfig.reserve[1];
	ar << radarConfig.reserve[2];
	ar << radarConfig.reserve[3];
	ar << radarConfig.reserve[4];
	ar << radarConfig.reserve[5];
	ar << radarConfig.reserve[6];
	ar << radarConfig.nPara_32;
	ar << radarConfig.nPara_33;
	ar << radarConfig.nPara_34;
	ar << radarConfig.nPara_35;
	ar << radarConfig.nPara_36;
	ar << radarConfig.nPara_37;
	ar << radarConfig.nPara_38;
	ar << radarConfig.nPara_39;
	ar << radarConfig.fPara_40;
	ar << radarConfig.nPara_47;
	ar << radarConfig.nPara_41;
	ar << radarConfig.nPara_42;
	ar << radarConfig.nPara_43;
	ar << radarConfig.nPara_44;
	ar << radarConfig.nPara_45;
	ar << radarConfig.nPara_46;
	ar << radarConfig.nPara_48;
	ar << radarConfig.nPara_workingModes;
	ar << radarConfig.nPara_miniinterval;
	ar << radarConfig.nPara_iniAzimuth;
	ar << radarConfig.nPara_endAzimuth;
	ar << radarConfig.nPara_dptWavPlusWid;
	ar << radarConfig.nPara_dptInitSampDist;
	ar << radarConfig.nPara_distDetect;
	ar << radarConfig.nPara_dopplerDetect;
	ar << radarConfig.nPara_detectionChannel;

	// 其他参数
	ar << waveMode;
	ar << codeMode;
	ar << g_nDrawNodes;
	ar << g_nCoefficient;
	ar << g_nPara_7;
	ar << g_singleAcquistionTimeMax;
	ar << tempnPara_48; // 单次采集时间
	ar << tempnPara_7; // 起始采样距离
	ar << tempStartRan;
	
}

UINT CParaConfig::InitMatlabPlayBackLib(LPVOID lpParam)
{
	return ((CParaConfig*) lpParam)->InitMatlabPlayBackLibProcess();
}

UINT CParaConfig::InitMatlabPlayBackLibProcess()
{
	if (!libfunc_Playback_VerticalLookingModeInitialize())
	{
		MessageBox(L"回放Matlab库函数初始化失败！");
		return 0;
	}
	else
	{
		theApp.m_pMainDlg->PrintMessage(L"MATLAB初始化完成！");
		g_isSucessInitMatlabPlayBacklib = true;
	}
	return 0;
}

void CParaConfig::GetDateTimeFromCtrl()
{
	// 获取日期控件内容
	CString strStartDateTime,strStopDateTime;
	GetDlgItemText(IDC_DATETIMEPICKER_STARTPLAYBACKDATE,strStartDateTime);
	GetDlgItemText(IDC_DATETIMEPICKER_STOPPLAYBACKDATE,strStopDateTime);

	
	// 获取时间控件内容
	CString strStartPlayBackTime, strStopPlayBackTime;
	GetDlgItemText(IDC_DATETIMEPICKER_STARTPLAYBACK, strStartPlayBackTime);
	GetDlgItemText(IDC_DATETIMEPICKER_STOPPLAYBACK, strStopPlayBackTime);

	// 转化时间戳
	CString strStartPlayBackDateTime, strStopPlayBackDateTime;
	strStartPlayBackDateTime = strStartDateTime + " " + strStartPlayBackTime;
	strStopPlayBackDateTime = strStopDateTime + " " + strStopPlayBackTime;

	USES_CONVERSION;
	char * ptrTempStartPlayBackDateTime = T2A(strStartPlayBackDateTime);   
	char * ptrTempStopPlayBackDateTime = T2A(strStopPlayBackDateTime);  
	sscanf_s(ptrTempStartPlayBackDateTime, "%d/%d/%d %d:%d:%d", &sStrartPlayBack.tm_year, &sStrartPlayBack.tm_mon, &sStrartPlayBack.tm_mday,
		&sStrartPlayBack.tm_hour, &sStrartPlayBack.tm_min, &sStrartPlayBack.tm_sec);
	sscanf_s(ptrTempStopPlayBackDateTime, "%d/%d/%d %d:%d:%d", &sStopPlayBack.tm_year, &sStopPlayBack.tm_mon, &sStopPlayBack.tm_mday,
		&sStopPlayBack.tm_hour, &sStopPlayBack.tm_min, &sStopPlayBack.tm_sec);
	
	sStrartPlayBack.tm_year -= 1900;
	sStrartPlayBack.tm_mon -= 1;
	sStopPlayBack.tm_year -= 1900;
	sStopPlayBack.tm_mon -= 1;

	// 取TrackFile路径
	g_trackFilePath = m_editPlayBackTrackPath;
	// 取时间间隔
	g_playBackTimeInterval = m_editPlayBackTimerInterval * 1000; // 秒
}




//取消按钮
void CParaConfig::OnBnClickedButton2()
{
	CDialogEx::OnCancel();
}


//收集界面参数并打包且将DSP通信的参数进行序列化
//RadarPara tempRadarPara;
void CParaConfig::GetData(RadarPara &radarPara)
{
	UpdateData(TRUE);

	CString str;
	radarPara.nParaType = 0x94EF032B;
	radarPara.nParaTail = 0x94EF032C;
	
	radarPara.nLen = sizeof(radarPara) - 8;   
	
	radarPara.nPara_2 = m_combox1.GetCurSel();					//波形模式
	
	if (radarPara.nPara_2 == 0 || radarPara.nPara_2 == 2)
		waveMode = 0;
	else 
		waveMode = 1;
	//waveMode = (radarPara.nPara_2%2) ? 0 : 1;
	//int tempInterpulseCodingPattern = 0;// 脉间编码模式-计算单次采集时间最大值用
	if (m_combox1.GetCurSel() == 1 || m_combox1.GetCurSel() == 3)
	{
		radarPara.nPara_3 = m_combox17.GetCurSel();					//脉间编码模式
	}
	else	// 分时
	{
		//tempInterpulseCodingPattern = 2;
		radarPara.nPara_3 = m_combox2.GetCurSel();					//脉间编码模式
	}
	
	//radarPara.nPara_3 = m_combox2.GetCurSel();					//脉间编码模式
	if (m_combox2.GetCurSel() == 2)
		codeMode = 2;		//双帧脉间四相编码
	else if (m_combox2.GetCurSel() == 3)
	{
		codeMode = 3;		//双帧脉间二相编码
	}
	
	// 0近距同时全局化，1近距分时全局化，2远距同时全局化，3远距分时全局化
	if(m_comboxWorkingModes.GetCurSel() == 3)	// 垂直模式-交替波形
	{
		// 主波形
		if (m_combox1.GetCurSel() == 0 || m_combox1.GetCurSel() == 1)
		{
			radarPara.nPara_4 = 5;									//波形脉宽
		}
		else
		{
			if (m_mainWavPlusWid.GetCurSel() == 0)
				radarPara.nPara_4 = 6;
			else
				radarPara.nPara_4 = m_mainWavPlusWid.GetCurSel()-1;      //波形脉宽
		}
		
		radarPara.nPara_7 = m_mainInitSapDist.GetCurSel();         //起始采样距离
		
		tempnPara_7 = m_mainInitSapDist.GetCurSel();

		// 副波形
		if (m_combox1.GetCurSel() == 0 || m_combox1.GetCurSel() == 1)
		{
			radarPara.nPara_dptWavPlusWid = 5;									//波形脉宽
		}
		else	// 垂直模式-单一波形
		{
			if (m_dptWavPlusWid.GetCurSel() == 0)
				radarPara.nPara_dptWavPlusWid = 6;
			else
				radarPara.nPara_dptWavPlusWid = m_dptWavPlusWid.GetCurSel()-1;      //波形脉宽
		}
		

		radarPara.nPara_dptInitSampDist = m_dptInitSampDist.GetCurSel();         //起始采样距离
		

		tempDptInitSampDist = m_dptInitSampDist.GetCurSel();
	}
	else	// 其他模式
	{
		if (m_combox1.GetCurSel() == 0 || m_combox1.GetCurSel() == 1)
		{
			radarPara.nPara_4 = 5;									//波形脉宽
		}
		else
		{
			if (m_comboxPlusWidth.GetCurSel() == 0)
				radarPara.nPara_4 = 6;
			else
				radarPara.nPara_4 = m_comboxPlusWidth.GetCurSel()-1;      //波形脉宽
		}
		
		radarPara.nPara_7 = m_comboxSimpleRage.GetCurSel();         //起始采样距离
		
		tempnPara_7 = m_comboxSimpleRage.GetCurSel();
	}
	

	//if (m_combox1.GetCurSel() == 0 || m_combox1.GetCurSel() == 1)
	//{
	//	radarPara.nPara_4 = 5;									//波形脉宽
	//}
	//else
	//{
	//	if (m_comboxPlusWidth.GetCurSel() == 0)
	//		radarPara.nPara_4 = 6;
	//	else
	//		radarPara.nPara_4 = m_comboxPlusWidth.GetCurSel()-1;      //波形脉宽
	//}
	
	radarPara.nPara_5 = m_combox3.GetCurSel();				    //PRT
	

	radarPara.nPara_6 = m_combox5.GetCurSel();                  //采样窗点数
	

	//radarPara.nPara_7 = m_comboxSimpleRage.GetCurSel();         //起始采样距离
	radarPara.nPara_8 = m_combox6.GetCurSel();				    //实时成像上传点数
	

	m_combox6.GetLBText(m_combox6.GetCurSel(), str);
	g_nDrawNodes = _tstoi(str);
	
	radarPara.nPara_9 = m_combox4.GetCurSel();					//信息上传周期
	


	//处理跳频点数
	if (m_combox1.GetCurSel() == 0 || m_combox1.GetCurSel() == 2)
	{
		radarPara.nPara_10 = 40;   //如果波形模式码是同时全极化，则处理跳频点数是40
	}
	else
	{
		radarPara.nPara_10 = (m_combox13.GetCurSel() + 1) * 10;
	}
	

	
	
	radarPara.nPara_11 = m_combox7.GetCurSel();					//AGC控制码1
	

	m_combox7.GetLBText(m_combox7.GetCurSel(), str);
	radarPara.nPara_11 = _tstoi(str);
	

	radarPara.nPara_12 = m_combox9.GetCurSel();					//AGC控制码2
	m_combox9.GetLBText(m_combox9.GetCurSel(), str);
	radarPara.nPara_12 = _tstoi(str);
	

	radarPara.nPara_13 = m_combox8.GetCurSel();					//标准通道使能
	

	radarPara.nPara_14 = m_combox10.GetCurSel();				//标准通道控制
	


	radarPara.nPara_15 = m_combox15.GetCurSel();				//天线转动模式

	int ntempPara_14 = 0;
	if(m_combox10.GetCurSel() == 0)
	{
		ntempPara_14 = 0;
	}
	else
	{
		ntempPara_14 = 32 * m_combox10.GetCurSel();
	}

	if(m_comboxAttenu.GetCurSel() != 5)
	{
		radarPara.nPara_14 = ntempPara_14 + pow((double)2, (double)m_comboxAttenu.GetCurSel());
	}
	else
	{
		radarPara.nPara_14 = ntempPara_14;
	}
	


	if (radarPara.nPara_15 == 8 || radarPara.nPara_15 == 9 || radarPara.nPara_15 == 10)//高度连续覆盖模式下
	{
		radarPara.nPara_16 = m_aziCircleCnt;					//方位旋转圈数
	}
	else						//非高度连续覆盖模式下
	{
		radarPara.nPara_16 = m_wbNum;							//俯仰波段数
	}
	
	//if (radarPara.nPara_15 != 8)//非高度连续覆盖模式下
	//{
	//	radarPara.nPara_17 = 6;
	//	radarPara.nPara_18 = m_AziStart;
	//	radarPara.nPara_19 = m_AziEnd;
	//	radarPara.nPara_20 = m_AziSpeed;
	//	radarPara.nPara_21 = m_EleStart;
	//	radarPara.nPara_22 = m_EleEnd;
	//	radarPara.nPara_23 = m_EleSpeed;
	//}
	//else						//高度连续覆盖模式下
	//{
		if (radarPara.nPara_15 == 8)			//高度连续覆盖模式下-1
		{
			radarPara.nPara_17 = 4;
			radarPara.nPara_18 = 1.0;
			radarPara.nPara_19 = 5.7;
			radarPara.nPara_20 = 34.1;
			radarPara.nPara_21 = 90.0;
		}
		else if (radarPara.nPara_15 == 9)		//高度连续覆盖模式下-2
		{
			radarPara.nPara_17 = 6;
			radarPara.nPara_18 = 1.0;
			radarPara.nPara_19 = 2.7;
			radarPara.nPara_20 = 7.1;
			radarPara.nPara_21 = 19.3;
			radarPara.nPara_22 = 61.9;
			radarPara.nPara_23 = 90.0;
		}
		else if (radarPara.nPara_15 == 10)		//高度连续覆盖模式下-3
		{
			radarPara.nPara_17 = 11;
			radarPara.nPara_18 = 1.0;
			radarPara.nPara_19 = 1.5;
			radarPara.nPara_20 = 2.3;
			radarPara.nPara_21 = 3.5;
			radarPara.nPara_22 = 5.4;
			radarPara.nPara_23 = 8.2;
			radarPara.reserve[0] = 12.6;
			radarPara.reserve[1] = 19.4;
			radarPara.reserve[2] = 30.5;
			radarPara.reserve[3] = 50.6;
			radarPara.reserve[4] = 90.0;
		}
		else if (radarPara.nPara_15 != 8)//非高度连续覆盖模式下
		{
			radarPara.nPara_17 = 6;
			radarPara.nPara_18 = m_AziStart;
			radarPara.nPara_19 = m_AziEnd;
			radarPara.nPara_20 = m_AziSpeed;
			radarPara.nPara_21 = m_EleStart;
			radarPara.nPara_22 = m_EleEnd;
			radarPara.nPara_23 = m_EleSpeed;
		}



		//从ini文件读取俯仰波位信息
		//TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
		//GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
		//(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
		//wcscat(szModulePath , _T("Ele.ini"));
		//CString strModulePath;
		//strModulePath = szModulePath;

		//CString tSecName(_T("俯仰波位配置文件"));   //段名
		//CString tKeyName(_T("波位个数"));           //键名

		//CString strOut;
		//::GetPrivateProfileString(tSecName, tKeyName, _T("0"), strOut.GetBuffer(256), 256, strModulePath);
		//int nCount = _ttoi(strOut);                 //波位个数
		//radarPara.nPara_17 = nCount;
		//tKeyName = _T("波位");
		//::GetPrivateProfileString(tSecName, tKeyName, _T("0"), strOut.GetBuffer(256), 256, strModulePath);
		//float *p = new float[nCount];
		//memset(p, 0, sizeof(float)*4);
		//strOut.ReleaseBuffer();
		//int j = strOut.GetLength();
		//for (int i=0; i<nCount; i++)
		//{
		//	CString str;
		//	str = strOut.Right(strOut.GetLength() - strOut.ReverseFind(',') - 1);
		//	float fAngle = _ttof(str);
		//	*(p + (nCount-1-i)) = fAngle;
		//	strOut = strOut.Left(strOut.ReverseFind(','));
		//}
		//memcpy(&(radarPara.nPara_18), p, nCount*4);

		radarPara.nNewAziSpeed = m_AziSpeed;


		radarPara.nNewEleSpeed = m_EleSpeed;


		m_combox24.GetLBText(m_combox24.GetCurSel(), str);
		radarPara.nPara_24 = _ttof(str);



		radarPara.nPara_32 = m_edit_1;


		radarPara.nPara_33 = m_combox19.GetCurSel();


		radarPara.nPara_34 = m_combox20.GetCurSel();


		m_combox21.GetLBText(m_combox21.GetCurSel(), str);
		radarPara.nPara_35 = _ttoi(str);


		m_combox22.GetLBText(m_combox22.GetCurSel(), str);
		radarPara.nPara_36 = _ttoi(str);


		m_combox23.GetLBText(m_combox23.GetCurSel(), str);
		radarPara.nPara_37 = _ttoi(str);


		radarPara.nPara_38 = m_edit_2;	//检测单元数


		radarPara.nPara_39 = m_edit_3;	//参考单元数


		radarPara.fPara_40 = m_edit_4;


		radarPara.nPara_41 = m_edit_5;


		radarPara.nPara_42 = m_edit_6;


		radarPara.nPara_43 = m_edit_7;


		radarPara.nPara_44 = m_edit_8;


		radarPara.nPara_45 = m_edit_9;


		radarPara.nPara_46 = m_edit_10;


		radarPara.nPara_47 = m_edit_11;



		radarPara.nPara_48 = m_edit_12;


		tempnPara_48 = m_edit_12;

		double temp = 0;
		double DrawNodes = g_nDrawNodes;
		temp = 256.0 * pow((double)2, (double)radarPara.nPara_6);
		g_nCoefficient = (temp / DrawNodes) * (15.0 / 16.0);

		//g_nCoefficient = ((radarPara.nPara_6 + 1)*256 / g_nDrawNodes) * (15 / 16);
		g_nPara_7 = radarPara.nPara_7 * 15;	



		radarPara.nPara_workingModes = m_comboxWorkingModes.GetCurSel();	// 工作模式



		// 数据采集最小时间间隔
		if(m_minitime.GetCurSel() == 0)
		{
			radarPara.nPara_miniinterval = 0;
		}
		else
		{
			m_minitime.GetLBText(m_minitime.GetCurSel(), str);
			radarPara.nPara_miniinterval = _ttoi(str);
		}



		// 采集起始方位角度
		radarPara.nPara_iniAzimuth = m_iniAzimuth;



		// 采集终止方位角度
		radarPara.nPara_endAzimuth = m_iniAzimuth + radarPara.nPara_20 * radarPara.nPara_48;




		// 标准校准通道使能
		if(g_autoCali == 0)
		{
			if((m_combox8.GetCurSel() == 0 && (m_combox10.GetCurSel() == 1 || m_combox10.GetCurSel() == 2 || m_combox10.GetCurSel() == 4 || m_combox10.GetCurSel() == 7) && m_comboxAttenu.GetCurSel() != 5))	// 是
			{
				radarPara.nPara_13 = m_combox8.GetCurSel();
			}
			else if ((m_combox8.GetCurSel() == 1 && (m_combox10.GetCurSel() == 0 || m_combox10.GetCurSel() == 3 || m_combox10.GetCurSel() == 5 || m_combox10.GetCurSel() == 6) && m_comboxAttenu.GetCurSel() != 5))
			{
				radarPara.nPara_13 = m_combox8.GetCurSel();
			}
			else if(m_combox8.GetCurSel() == 0 && m_comboxAttenu.GetCurSel() == 5 && (m_combox10.GetCurSel() == 0 || m_combox10.GetCurSel() == 3 || m_combox10.GetCurSel() == 5 || m_combox10.GetCurSel() == 6))
			{
				radarPara.nPara_13 = m_combox8.GetCurSel();
			}
			else if(m_combox8.GetCurSel() == 1 && m_comboxAttenu.GetCurSel() == 5 && (m_combox10.GetCurSel() == 2 || m_combox10.GetCurSel() == 4 || m_combox10.GetCurSel() == 7))
			{
				radarPara.nPara_13 = m_combox8.GetCurSel();
			}
		}


		
		radarPara.nPara_detectionChannel = m_combox_detectionChannel.GetCurSel(); // 校准通道配置；

		
		

		// 单次采集时间最大值1024*1024*1024/(采样窗点数*160+128)*PRT*40/脉间编码模式

		int tempSmpWndCount = 256 * pow((double)2, (double)radarPara.nPara_6);	// 采样窗点数
		int tempPRT = radarPara.nPara_5 * 5 + 25;

		g_singleAcquistionTimeMax = 1024*1024*1024/(tempSmpWndCount*160+128)*tempPRT*40/2;


		//if(m_edit_12 > 1024*1024*1024/(tempSmpWndCount*160+128)*tempPRT*40/2)

		//delete []p;
		//p = NULL;
	//}
		//tempRadarPara = m_radarPara;

		radarPara.nPara_distDetect = m_edit_distDetect;		// 距离检测单元数


		radarPara.nPara_dopplerDetect = m_edit_dopplerDetect;	// 多普勒检测单元数

		
	
}



void CParaConfig::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_combox1.GetCurSel() == 1 || m_combox1.GetCurSel() == 3)
	{
		m_combox13.ShowWindow(TRUE);
		m_combox14.ShowWindow(FALSE);

		m_combox17.ShowWindow(TRUE);		//脉间编码都有
		m_combox2.ShowWindow(FALSE);
	}
	else
	{
		m_combox13.ShowWindow(FALSE);
		m_combox14.ShowWindow(TRUE);

		m_combox17.ShowWindow(FALSE);		
		m_combox2.ShowWindow(TRUE);
	}

	if (m_combox1.GetCurSel() == 0 || m_combox1.GetCurSel() == 1)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO11))->ShowWindow(FALSE);
		((CComboBox*)GetDlgItem(IDC_COMBO_MAINWAVPLUWID))->ShowWindow(FALSE);
		((CComboBox*)GetDlgItem(IDC_COMBO_DPTWAVPLUWID))->ShowWindow(FALSE);
		((CComboBox*)GetDlgItem(IDC_COMBO16))->ShowWindow(TRUE);
		((CComboBox*)GetDlgItem(IDC_COMBO_DWAVPLUWID))->ShowWindow(TRUE);
		((CComboBox*)GetDlgItem(IDC_COMBO_MWAVPLUWID))->ShowWindow(TRUE);
	}
	else
	{
		((CComboBox*)GetDlgItem(IDC_COMBO11))->ShowWindow(TRUE);
		((CComboBox*)GetDlgItem(IDC_COMBO_MAINWAVPLUWID))->ShowWindow(TRUE);
		((CComboBox*)GetDlgItem(IDC_COMBO_DPTWAVPLUWID))->ShowWindow(TRUE);
		((CComboBox*)GetDlgItem(IDC_COMBO16))->ShowWindow(FALSE);
		((CComboBox*)GetDlgItem(IDC_COMBO_DWAVPLUWID))->ShowWindow(FALSE);
		((CComboBox*)GetDlgItem(IDC_COMBO_MWAVPLUWID))->ShowWindow(FALSE);
	}
}


void CParaConfig::OnEnUpdateEdit11()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//int data = GetDlgItemInt(IDC_EDIT11);
	UpdateData(TRUE);
	if(/*m_wbNum<0 ||*/ m_wbNum>255)
	{
		SetDlgItemTextA(this->m_hWnd, IDC_EDIT11,"255");
		MessageBox(_T("俯仰波段数范围必须在0~255！"));
	}

	//CString str;
	//GetDlgItemText(IDC_EDIT11, str);

}


//天线转动模式选择
void CParaConfig::OnCbnSelchangeCombo15()
{
	// TODO: 在此添加控件通知处理程序代码
	int tt = m_combox15.GetCurSel();

	switch (tt)
	{
	case 0:
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 1:
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 2:
		GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 3:		//垂直对天扫描
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		//GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		m_AziStart = -180;
		m_AziEnd = 180;
		UpdateData(FALSE);
		break;
	case 4:
		GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		//GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 5:
		GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		//GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 6:
		GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 7:
		GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(FALSE);
		break;
	case 8:		//高度覆盖模式-1
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(TRUE);
		break;
	case 9:		//高度覆盖模式-2
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(TRUE);
		break;
	case 10:	//高度覆盖模式-3
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(TRUE);
		break;
	}
}



void CParaConfig::OnBnClickedButton12()
{
	//if (m_combox18.GetCurSel() == 0)	//正常模式
	//{
	//	CFileDialog dlg(TRUE);
	//	if (dlg.DoModal() == IDOK)
	//	{
	//		m_szSavePath = dlg.GetPathName();
	//		UpdateData(FALSE);
	//	}
	//}
	//else								//校准模式
	//{
		BROWSEINFO stBrowseInfo;
		ITEMIDLIST *pStItemIdList;
		TCHAR acFilePath[100];
		memset( &stBrowseInfo, 0, sizeof(BROWSEINFO));
		stBrowseInfo.ulFlags = BIF_RETURNONLYFSDIRS;
		pStItemIdList = SHBrowseForFolder( &stBrowseInfo );
		SHGetPathFromIDList( pStItemIdList, acFilePath );
		CString strTemp;
		m_szSavePath.Format((_T("%s")), acFilePath );
		GetDlgItem(IDC_EDIT13)->SetWindowTextW(m_szSavePath);
		//UpdateData( FALSE );

		//SaveSetting();

		__int64 i64FreeBytesToCaller = 0;
		__int64 i64TotalBytes = 0;
		__int64 i64FreeBytes = 0;
		BOOL bReturn = GetDiskFreeSpaceEx( m_szSavePath, (PULARGE_INTEGER)&i64FreeBytesToCaller, (PULARGE_INTEGER)&i64TotalBytes, (PULARGE_INTEGER)&i64FreeBytes );
		if (m_szSavePath.IsEmpty())
			return;
		if (bReturn == 0)
		{
			MessageBox(_T("该路径不存在，请重新选择"), /*NULL,*/ NULL, MB_ICONWARNING);
			return;
		}
	//}
	

	

	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("FilePath_jiaozhun.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file(strModulePath, CFile::modeWrite);
	CArchive ar(&file,CArchive::store);
	theApp.m_pMainDlg->strFileSavePath = m_szSavePath;
	ar << m_szSavePath;
}


void CParaConfig::InitFilePath_jiaozhun()
{
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("FilePath_jiaozhun.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file(strModulePath, CFile::modeRead);
	CArchive ar(&file,CArchive::load);
	//m_szSavePath = _T("d:\\");
	CString strAr;
	ar >> strAr;
	m_szSavePath = strAr;
	theApp.m_pMainDlg->strFileSavePath_jiaozhun = strAr;

	UpdateData(FALSE);
}

void CParaConfig::SaveFilePath_jiaozhun()
{
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("FilePath_jiaozhun.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file(strModulePath, CFile::modeWrite);
	CArchive ar(&file,CArchive::store);

}


bool CParaConfig::ConfigMatlabPara()
{
	//根据模式选择，做相应文件路径的判断
	CString strFilejiaozhun, s1, s2, s3, s4, s5(_T("_"));
	strFilejiaozhun = m_szSavePath;
	m_combox1.GetLBText(m_combox1.GetCurSel(), s1);	//波形编码strFilejiaozhun = "D:\远距分时全极化_单帧脉间四相编码_4_0.mat"
	if (m_combox1.GetCurSel() == 1 || m_combox1.GetCurSel() == 3)
	{
		m_combox17.GetLBText(m_combox17.GetCurSel(), s2);	//脉间编码
	}
	else
	{
		m_combox2.GetLBText(m_combox2.GetCurSel(), s2);	//脉间编码
	}
	
	m_combox7.GetLBText(m_combox7.GetCurSel(), s3);	//AGC1
	m_combox9.GetLBText(m_combox9.GetCurSel(), s4);	//AGC2
	strFilejiaozhun += (s1 + s5 + s2 + s5 + s3 + s5 + s4 + _T(".mat"));
	if (m_combox18.GetCurSel() == 0)	//正常模式
	{
		if (!PathFileExists(strFilejiaozhun))
		{
			MessageBox(_T("文件不存在，请重新校准！"));
			return false;
		}
		else
		{
			int i = 0;
		}

	}
	else if (m_combox18.GetCurSel() == 1)	//校准模式
	{
		if (PathFileExists(strFilejiaozhun))
		{
			if (MessageBox(L"极化校准文件已存在，是否继续？", NULL, MB_YESNO) == IDYES)
				return true;
			return false;
		}
		
	}

	return true;
}


void CParaConfig::GetData_ToMatlab(TOMATLABPARA &Para)
{
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("ToMatlabParaConfig.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file(strModulePath, CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file,CArchive::store);

	Para.s1.Empty();
	Para.s2.Empty();
	//RCS_ball
	Para.RCS_ball = theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_RCS_ball;
	ar << Para.RCS_ball;
	CString s;

	//起始采样距离
	int nlhs = theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_comboxSimpleRage.GetCurSel();
	theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_comboxSimpleRage.GetLBText(nlhs, s);
	Para.StartRan = nlhs * 15;
	ar << Para.StartRan;
	tempStartRan = Para.StartRan;

	//采样窗点数
	nlhs = theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_combox5.GetCurSel();
	theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_combox5.GetLBText(nlhs, s);
	Para.SampleNum = _ttoi(s);
	ar << Para.SampleNum;

	//PRT
	nlhs = theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_combox3.GetCurSel();
	theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_combox3.GetLBText(nlhs, s);
	Para.PRT = _ttoi(s);
	ar << Para.PRT;

	//波形编码
	Para.WaveForm = m_combox1.GetCurSel();
	ar << Para.WaveForm;

	//脉间编码
	if (m_combox1.GetCurSel() == 1 || m_combox1.GetCurSel() == 3)
	{
		Para.CodeType = m_combox17.GetCurSel();
		Para.s1 = m_szSavePath + _T("\\");
		CString str, strTemp(_T("_")), strFinal(_T(".mat"));
		//m_combox1.GetLBText(m_combox1.GetCurSel(), str);
		Para.s2 += (m_szSavePath + _T("\\")/*+ str + strTemp*/);
		/*m_combox17.GetLBText(m_combox17.GetCurSel(), str);
		Para.s2 += (str + strTemp);
		m_combox7.GetLBText(m_combox7.GetCurSel(), str);
		Para.s2 += (str + strTemp);
		m_combox9.GetLBText(m_combox9.GetCurSel(), str);
		Para.s2 += (str + strFinal);*/
	}
	else
	{	
		Para.CodeType = m_combox2.GetCurSel();
		Para.s1 = m_szSavePath + _T("\\");
		CString str, strTemp(_T("_")), strFinal(_T(".mat"));
		//m_combox1.GetLBText(m_combox1.GetCurSel(), str);
		Para.s2 += (m_szSavePath + _T("\\")/*+ str + strTemp*/);
		/*m_combox2.GetLBText(m_combox2.GetCurSel(), str);
		Para.s2 += (str + strTemp);
		m_combox7.GetLBText(m_combox7.GetCurSel(), str);
		Para.s2 += (str + strTemp);
		m_combox9.GetLBText(m_combox9.GetCurSel(), str);
		Para.s2 += (str + strFinal);*/
	}
	ar << Para.CodeType;
	ar << Para.s1;
	ar << Para.s2;
	Para.mode = m_combox18.GetCurSel();
	ar << Para.mode;
	Para.dlMinLength_Cali = m_dlMinLength_Cali;
	ar << Para.dlMinLength_Cali;
	Para.dlMinLength_ParaEst = m_dlMinLength_Orien;
	ar << Para.dlMinLength_ParaEst;
	Para.dlMinLength_Den = m_dlMinLength_Den;
	ar << Para.dlMinLength_Den;

	// 波形脉宽
	if(m_comboxPlusWidth.GetCurSel() == 0)
	{
		Para.fPulseWid = 0.4;
	}
	else
	{
		Para.fPulseWid = m_comboxPlusWidth.GetCurSel();
	}
	ar << Para.fPulseWid;
	// 单次采集时间
	Para.SampleTime = m_edit_12;
	ar << Para.SampleTime;

	// 工作模式
	Para.workingMode = m_comboxWorkingModes.GetCurSel();
	ar << Para.workingMode;

	// 方位起始采集角度
	Para.fAzi_S = m_iniAzimuth;
	ar << Para.fAzi_S;

	// 方位终止采集角度
	Para.fAzi_E = m_radarPara.nPara_endAzimuth;
	ar << Para.fAzi_E;

	// 俯仰起始角度
	Para.fElv_D = m_EleStart;
	ar << Para.fElv_D;
	// 俯仰终止角度
	Para.fElv_H = m_EleEnd;
	ar << Para.fElv_H;
	Para.enableAutoCali = m_autoCali.GetCurSel();
	ar << Para.enableAutoCali;

	ar << tempStartRan;
}



void CParaConfig::OnCbnSelchangeCombo18()
{
	// TODO: 在此添加控件通知处理程序代码
}


int CParaConfig::MinMaxFloat()
{
	if (m_AziStart < -200 || m_AziStart > 200)
	{
		MessageBox(_T("请确认方位起始角度在-200与200之间！"), NULL, MB_ICONERROR);
		return -1;
	}
	if (m_AziEnd < -200 || m_AziEnd > 200)
	{
		MessageBox(_T("请确认方位终止角度在-200与200之间！"), NULL, MB_ICONERROR);
		return -1;
	}
	if (m_AziSpeed  < 0 || m_AziSpeed > 60 )
	{
		MessageBox(_T("请确认方位扫描速度在0与60之间！"), NULL, MB_ICONERROR);
		return -1;
	}
	if (m_EleStart  < 0 || m_EleStart > 90 )
	{
		MessageBox(_T("请确认俯仰起始角度在0与90之间！"), NULL, MB_ICONERROR);
		return -1;
	}
	if (m_EleEnd  < 0 || m_EleEnd > 90)
	{
		MessageBox(_T("请确认俯仰终止角度在0与90之间！"), NULL, MB_ICONERROR);
		return -1;
	}
	if ( m_EleSpeed  < 0 || m_EleSpeed > 40 )
	{
		MessageBox(_T("请确认俯仰扫描速度在0与40之间！"), NULL, MB_ICONERROR);
		return -1;
	}
	return 0;
}


void CParaConfig::OnCbnSelchangeComboWorkingmodes()
{
	// TODO: 在此添加控件通知处理程序代码
	int sequenceNumber = m_comboxWorkingModes.GetCurSel();

	if(sequenceNumber == 3)
	{
		GetDlgItem(IDC_COMBO16)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_MWAVPLUWID)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DWAVPLUWID)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO11)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO12)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_MAINWAVPLUWID)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_MAININITSAMPDIST)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DPTWAVPLUWID)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DPTINITSAMPDIST2)->EnableWindow(TRUE);
	}
	else
	{		
		GetDlgItem(IDC_COMBO_MAINWAVPLUWID)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_MAININITSAMPDIST)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DPTWAVPLUWID)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DPTINITSAMPDIST2)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO11)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO12)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO16)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_MWAVPLUWID)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DWAVPLUWID)->EnableWindow(TRUE);
	}

	if(sequenceNumber == 0)
	{
		m_combox5.SetCurSel(2);
		m_combox6.SetCurSel(5);
	}
}


void CParaConfig::OnCbnSelchangeCombo5()
{
	// TODO: 在此添加控件通知处理程序代码
	int sequenceNumber = m_combox5.GetCurSel();
	if(sequenceNumber == 2)
	{
		m_combox6.SetCurSel(5);
	}
	if(sequenceNumber == 3)
	{
		m_combox6.SetCurSel(6);
	}
}


void CParaConfig::OnBnClickedButtonChoseplaybackpath()
{
	// TODO: 选择要回放的Track数据路径
	BROWSEINFO stBrowseInfo;
	ITEMIDLIST *pStItemIdList;
	TCHAR acFilePath[100];
	memset( &stBrowseInfo, 0, sizeof(BROWSEINFO));
	stBrowseInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	pStItemIdList = SHBrowseForFolder( &stBrowseInfo );
	SHGetPathFromIDList( pStItemIdList, acFilePath );
	CString strTemp;
	m_editPlayBackTrackPath.Format((_T("%s")), acFilePath );
	GetDlgItem(IDC_EDIT_PLAYBACKTRACKPATH)->SetWindowTextW(m_editPlayBackTrackPath);
}
