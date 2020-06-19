// ParaConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimpleInsectRadar.h"
#include "ParaConfig.h"
#include "afxdialogex.h"


// CParaConfig �Ի���

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
	DDX_Text(pDX, IDC_EDIT16, m_edit_12);	// ���ʲɼ�ʱ��
	DDX_Text(pDX, IDC_EDIT17, m_dlMinLength_Cali);
	DDX_Text(pDX, IDC_EDIT18, m_dlMinLength_Orien);
	DDX_Text(pDX, IDC_EDIT19, m_dlMinLength_Den);
	DDX_Control(pDX, IDC_COMBO_WORKINGMODES, m_comboxWorkingModes);	// ����ģʽ
	DDX_Control(pDX, IDC_COMBO_MINITIME1, m_minitime);
	DDX_Text(pDX, IDC_EDIT_INIAZIMUTH, m_iniAzimuth);
	DDX_Control(pDX, IDC_COMBO_ATTENU, m_comboxAttenu);	// ˥����Ϊ�Զ���У׼ģʽ
	DDX_Control(pDX, IDC_COMBO_MAINWAVPLUWID, m_mainWavPlusWid);	// ��-��������
	DDX_Control(pDX, IDC_COMBO_MAININITSAMPDIST, m_mainInitSapDist);	// ��-��ʼ��������
	DDX_Control(pDX, IDC_COMBO_DPTWAVPLUWID, m_dptWavPlusWid);	// ��-��������
	DDX_Control(pDX, IDC_COMBO_DPTINITSAMPDIST2, m_dptInitSampDist);	// ��-��ʼ��������
	DDX_Control(pDX, IDC_COMBO_WORKMODE, m_combox_workMode);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_dateTimePickerStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STOP, m_dateTimePickerStop);
	DDX_Text(pDX, IDC_EDIT_DISTDETECT, m_edit_distDetect);	// �����ⵥԪ��
	DDX_Text(pDX, IDC_EDIT_DOPPLERDETECT, m_edit_dopplerDetect);	// �����ռ�ⵥԪ��
	DDX_Control(pDX, IDC_COMBO_AUTOCALI, m_autoCali);	// �Զ���У׼ʹ��
	DDX_Control(pDX, IDC_COMBO_AUTOCALIMODE, m_comboxAutoCaliMode);	// �Զ���У׼ģʽ
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


// CParaConfig ��Ϣ�������

//CString dataTimerPickerStartPlayAr;
BOOL CParaConfig::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//MessageBox(_T("OnInitDialog"));
	InitFilePath_jiaozhun();

	//����ģʽ
	m_combox1.InsertString(0, _T("����ͬʱȫ����"));
	m_combox1.InsertString(1, _T("�����ʱȫ����"));
	m_combox1.InsertString(2, _T("Զ��ͬʱȫ����"));
	m_combox1.InsertString(3, _T("Զ���ʱȫ����"));

	//�������ģʽ
	m_combox2.InsertString(0, _T("���������"));
	m_combox2.InsertString(1, _T("��֡�����������"));
	m_combox2.InsertString(2, _T("˫֡�����������"));
	m_combox2.InsertString(3, _T("˫֡֡��������"));
	m_combox17.InsertString(0, _T("���������"));
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


	//Զ�ನ������
	m_comboxPlusWidth.InsertString(0, _T("0.4s"));
	m_comboxPlusWidth.InsertString(1, _T("1us"));
	m_comboxPlusWidth.InsertString(2, _T("2us"));
	m_comboxPlusWidth.InsertString(3, _T("3us"));
	m_comboxPlusWidth.InsertString(4, _T("4us"));
	m_comboxPlusWidth.InsertString(5, _T("5us"));

	// ������-��������
	m_mainWavPlusWid.InsertString(0, _T("0.4s"));
	m_mainWavPlusWid.InsertString(1, _T("1us"));
	m_mainWavPlusWid.InsertString(2, _T("2us"));
	m_mainWavPlusWid.InsertString(3, _T("3us"));
	m_mainWavPlusWid.InsertString(4, _T("4us"));
	m_mainWavPlusWid.InsertString(5, _T("5us"));

	// ��-��������
	m_dptWavPlusWid.InsertString(0, _T("0.4s"));
	m_dptWavPlusWid.InsertString(1, _T("1us"));
	m_dptWavPlusWid.InsertString(2, _T("2us"));
	m_dptWavPlusWid.InsertString(3, _T("3us"));
	m_dptWavPlusWid.InsertString(4, _T("4us"));
	m_dptWavPlusWid.InsertString(5, _T("5us"));

	((CComboBox*)GetDlgItem(IDC_COMBO16))->InsertString(0, _T("0.1us"));
	((CComboBox*)GetDlgItem(IDC_COMBO16))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO16))->ShowWindow(FALSE);

	// ������
	((CComboBox*)GetDlgItem(IDC_COMBO_MWAVPLUWID))->InsertString(0, _T("0.1us"));
	((CComboBox*)GetDlgItem(IDC_COMBO_MWAVPLUWID))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_MWAVPLUWID))->ShowWindow(FALSE);
	// ������
	((CComboBox*)GetDlgItem(IDC_COMBO_DWAVPLUWID))->InsertString(0, _T("0.1us"));
	((CComboBox*)GetDlgItem(IDC_COMBO_DWAVPLUWID))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_DWAVPLUWID))->ShowWindow(FALSE);
	

	//��Ϣ�ϴ�����
	for (int i=0; i<10; i++)
	{
		CString str;
		str.Format(_T("%d֡�ϴ�һ��"), (i+1)*100);
		m_combox4.InsertString(i, str);
	}

	//��ʼ��������
	for (int i=0; i<56; i++)
	{
		CString str;
		str.Format(_T("%dm"), i*15);
		m_comboxSimpleRage.InsertString(i, str);
	}

	// ��-��ʼ��������
	for (int i=0; i<56; i++)
	{
		CString str;
		str.Format(_T("%dm"), i*15);
		m_mainInitSapDist.InsertString(i, str);
	}

	// ��-��ʼ��������
	for (int i=0; i<56; i++)
	{
		CString str;
		str.Format(_T("%dm"), i*15);
		m_dptInitSampDist.InsertString(i, str);
	}

	//����������
	m_combox5.InsertString(0, _T("256"));
	m_combox5.InsertString(1, _T("512"));
	m_combox5.InsertString(2, _T("1024"));
	m_combox5.InsertString(3, _T("2048"));

	//ʵʱ�����ϴ�����
	m_combox6.InsertString(0, _T("256"));
	m_combox6.InsertString(1, _T("512"));
	m_combox6.InsertString(2, _T("1024"));
	m_combox6.InsertString(3, _T("2048"));
	m_combox6.InsertString(4, _T("4096"));
	m_combox6.InsertString(5, _T("8192"));
	m_combox6.InsertString(6, _T("16384"));

	//AGC������1��2
	UINT AGC[7] = {0, 1, 2, 4, 8, 16, 31};
	for (int i=0; i<7; i++)
	{
		CString str;
		str.Format(_T("%d"), AGC[i]);
		m_combox7.InsertString(i, str);
		m_combox9.InsertString(i, str);
	}
	
	
	//У׼ͨ��ʹ��
	m_combox8.InsertString(0, _T("��"));
	m_combox8.InsertString(1, _T("��"));
	
	//У׼ͨ������
	m_combox10.InsertString(0, _T("000(����)"));
	m_combox10.InsertString(1, _T("001(����1)"));
	m_combox10.InsertString(2, _T("010(����2)"));
	m_combox10.InsertString(3, _T("011(����1)"));
	m_combox10.InsertString(4, _T("100(����2)"));
	m_combox10.InsertString(5, _T("101(����1��2)"));
	m_combox10.InsertString(6, _T("110(����1��2)"));
	m_combox10.InsertString(7, _T("111(��У׼)"));


	//������Ƶ����
	m_combox13.InsertString(0, _T("10"));
	m_combox13.InsertString(1, _T("20"));
	m_combox13.InsertString(2, _T("30"));
	m_combox13.InsertString(3, _T("40"));
	m_combox14.InsertString(0, _T("40"));
	m_combox14.SetCurSel(0);

	//��ƵԤ��ʱ��
	m_combox24.InsertString(0, _T("15us"));
	m_combox24.InsertString(1, _T("30us"));
	m_combox24.InsertString(2, _T("40us"));
	m_combox24.InsertString(3, _T("50us"));
	m_combox24.InsertString(4, _T("60us"));
	m_combox24.InsertString(5, _T("70us"));

	//����ת��ģʽ
	m_combox15.InsertString(0, _T("����״̬"));
	m_combox15.InsertString(1, _T("�Լ�ģʽ"));
	m_combox15.InsertString(2, _T("��λģʽ"));
	m_combox15.InsertString(3, _T("��ֱ����ɨ��ģʽ"));
	m_combox15.InsertString(4, _T("��λһάɨ��ģʽ"));
	m_combox15.InsertString(5, _T("����һάɨ��ģʽ"));
	m_combox15.InsertString(6, _T("������άɨ��ģʽ"));
	m_combox15.InsertString(7, _T("���̶�άɨ��ģʽ"));
	m_combox15.InsertString(8, _T("�߶ȸ���ģʽ-1"));
	m_combox15.InsertString(9, _T("�߶ȸ���ģʽ-2"));
	m_combox15.InsertString(10, _T("�߶ȸ���ģʽ-3"));

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
	

	//ģʽѡ��
	m_combox18.InsertString(0, _T("����ģʽ"));
	m_combox18.InsertString(1, _T("У׼ģʽ"));
	m_combox18.SetCurSel(0);

	// ����ģʽ
	m_comboxWorkingModes.InsertString(0, _T("һά������ɼ�ģʽ"));
	m_comboxWorkingModes.InsertString(1, _T("��ֱģʽ-��һ����"));
	m_comboxWorkingModes.InsertString(2, _T("ɨ��ģʽ"));
	m_comboxWorkingModes.InsertString(3, _T("��ֱģʽ-��������"));
	m_comboxWorkingModes.SetCurSel(1);

	// ���ݲɼ���Сʱ����
	m_minitime.InsertString(0, _T("������"));
	for(int i = 1; i < 12; ++i)
	{
		CString ss;
		ss.Format(_T("%d"), 10 + (i-1)*5);
		m_minitime.InsertString(i, ss);
	}
	m_minitime.SetCurSel(0);

	// ˥��
	m_comboxAttenu.InsertString(0,_T("00001"));
	m_comboxAttenu.InsertString(1,_T("00010"));
	m_comboxAttenu.InsertString(2,_T("00100"));
	m_comboxAttenu.InsertString(3,_T("01000"));
	m_comboxAttenu.InsertString(4,_T("10000"));
	m_comboxAttenu.InsertString(5,_T("00000"));
	m_comboxAttenu.SetCurSel(5);

	// �������ģʽ-��ʱ
	m_combox_workMode.InsertString(0, _T("����ģʽ"));
	m_combox_workMode.InsertString(1, _T("��ʱģʽ"));
	m_combox_workMode.SetCurSel(0);

	// ʱ���ʼ��
	CTime tTime(0, 0, 0);
	m_dateTimePickerStart.SetTime(&tTime);
	m_dateTimePickerStop.SetTime(&tTime);

	// �Զ���У׼ʹ��
	m_autoCali.InsertString(0, _T("��"));
	m_autoCali.InsertString(1, _T("��"));
	m_autoCali.SetCurSel(0);

	// �Զ���У׼ģʽ
	m_comboxAutoCaliMode.InsertString(0, _T("��ͨ��ͬʱ"));
	m_comboxAutoCaliMode.InsertString(1, _T("��ͨ����ʱ"));
	m_comboxAutoCaliMode.SetCurSel(0);


	// ת��ʹ��
	m_combox_zhuancun.InsertString(0, _T("��"));
	m_combox_zhuancun.InsertString(1, _T("��"));
	m_combox_zhuancun.SetCurSel(0);

	// ת��ʱ��
	m_combox_zhuanCunTime.InsertString(0, _T("1h"));
	m_combox_zhuanCunTime.InsertString(1, _T("2h"));
	m_combox_zhuanCunTime.InsertString(2, _T("3h"));
	m_combox_zhuanCunTime.InsertString(3, _T("4h"));
	m_combox_zhuanCunTime.InsertString(4, _T("5h"));
	m_combox_zhuanCunTime.InsertString(5, _T("6h"));
	m_combox_zhuanCunTime.InsertString(6, _T("7h"));
	m_combox_zhuanCunTime.InsertString(7, _T("8h"));
	m_combox_zhuanCunTime.SetCurSel(0);

	// ���ͨ��
	m_combox_detectionChannel.InsertString(0, _T("HH"));
	m_combox_detectionChannel.InsertString(1, _T("HV"));
	m_combox_detectionChannel.InsertString(2, _T("VH"));
	m_combox_detectionChannel.InsertString(3, _T("VV"));
	m_combox_detectionChannel.SetCurSel(0);

	// �ط�ʹ��
	m_comboxEnablePlayBack.InsertString(0, _T("��"));
	m_comboxEnablePlayBack.InsertString(1, _T("��"));
	m_comboxEnablePlayBack.SetCurSel(0);

	// ��ɨģʽʹ��
	m_comboxSlowScan.InsertString(0, _T("��"));
	m_comboxSlowScan.InsertString(1, _T("��"));
	m_comboxSlowScan.SetCurSel(0);


	// ���л�, �Ѳ�����Ϣд��txt
	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
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

	// ����������
	ar >> tt;
	m_mainWavPlusWid.SetCurSel(tt);

	// ����������
	ar >> tt;
	m_dptWavPlusWid.SetCurSel(tt);

	ar >> tt;
	m_combox4.SetCurSel(tt);

	ar >> tt;
	m_comboxSimpleRage.SetCurSel(tt);

	// ��-��ʼ��������
	ar >> tt;
	m_mainInitSapDist.SetCurSel(tt);
	// ��-��ʼ��������
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

		m_combox17.ShowWindow(TRUE);		//������붼��
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
	case 8:		//�߶ȸ���ģʽ-1
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
	case 9:		//�߶ȸ���ģʽ-2
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
	case 10:	//�߶ȸ���ģʽ-3
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

	// �ŷ�����
	ar >> m_AziStart;	// ��λ��ʼ�Ƕ�
	ar >> m_AziEnd;		// ��λ��ֹ�Ƕ�
	ar >> m_AziSpeed;	// ��λɨ��Ƕ�
	ar >> m_wbNum;		// ��λ��תȦ��
	ar >> m_EleStart;	// ������ʼ�Ƕ�
	ar >> m_EleEnd;		// ������ֹ�Ƕ�
	ar >> m_EleSpeed;	// ����ɨ���ٶ�

	// ����ģʽ
	ar >> tt;
	m_comboxWorkingModes.SetCurSel(tt);

	// �����ϴ�ѡ�������״̬
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

	//ʵʱ�ɼ�����
	ar >> m_iniAzimuth; // �ɼ���ʼ��λ��
	ar >> tt;
	m_minitime.SetCurSel(tt); // �ɼ���Сʱ����

	
	ar >> m_edit_distDetect;	// �����ⵥԪ��
	ar >> m_edit_dopplerDetect;	// �����ռ�ⵥԪ��

	// �������ģʽ-��ʱģʽ
	ar >> tt;
	m_combox_workMode.SetCurSel(tt);

	// ʱ�����л�
	/*ar >> tTime;
	m_dateTimePickerStart.SetTime(&tTime);

	ar >> tTime;
	m_dateTimePickerStop.SetTime(&tTime);*/

	// �Զ�У׼ʹ��
	ar >> tt;
	m_autoCali.SetCurSel(tt);

	// �Զ�У׼ģʽ
	ar >> tt;
	m_comboxAutoCaliMode.SetCurSel(tt);

	// Track·�����л�
	ar >> m_editPlayBackTrackPath;

	// Track�ļ��ط�ʱ����
	ar >> m_editPlayBackTimerInterval;
	// ʱ��ؼ�����ʼ�ط�ʱ��
	/*ar >> dataTimerPickerStartPlayAr;
	SetDlgItemText(IDC_DATETIMEPICKER_STARTPLAYBACK, dataTimerPickerStartPlayAr);*/

	// ��ɨģʽʹ��
	ar >> tt;
	m_comboxSlowScan.SetCurSel(tt);

	UpdateData(false);

	CString strstr;
	/*m_combox1.*/GetDlgItemText(IDC_COMBO1, strstr);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//ȷ����ť
bool b_isOkBtnParaConfig = false;
UINT tempnPara_7 = 0;	// ��ֱ����ģʽ-��������ʼ�������룬����ģʽ-��ʼ��������
UINT tempDptInitSampDist = 0; // ��ֱ����ģʽ-��������ʼ��������
float tempnPara_48 = 0.0;
RadarPara tempRadarPara;
extern RadarPara ToDspParaConfig;
extern int verticalOrSlowScanCount;
void CParaConfig::OnBnClickedButton1()
{
	if ((g_iIsTcpConnect != 0) && (m_comboxEnablePlayBack.GetCurSel() == 0))
	{
		MessageBox(_T("�����쳣���޷���DSP�·����ò���"), NULL, MB_ICONWARNING);
		//return;
	}
	if (g_bflag_enable == false)	//��ʼ������˱�־λfalse�����Ե��ȷ����
	{
		CDialogEx::OnOK();
		return;
	}

	DeleteFiles(_T("ToDspParaConfig.txt"));
	DeleteFiles(_T("ToOwnParaConfig.txt"));
	DeleteFiles(_T("ToMatlabParaConfig.txt"));

	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , _T("ParaConfig.txt"));

	CString strModulePath;
	strModulePath = szModulePath;
	CFile file(strModulePath, CFile::modeWrite);
	CArchive ar(&file,CArchive::store);

	

	UpdateData(TRUE);
	//�����������л�
	ar << m_combox1.GetCurSel();
	ar << m_combox2.GetCurSel();
	ar << m_combox3.GetCurSel();
	ar << m_comboxPlusWidth.GetCurSel();
	ar << m_mainWavPlusWid.GetCurSel();	// ��-��������
	ar << m_dptWavPlusWid.GetCurSel();	// ��-��������
	ar << m_combox4.GetCurSel();
	ar << m_comboxSimpleRage.GetCurSel();
	ar << m_mainInitSapDist.GetCurSel();	// ��-��ʼ��������
	ar << m_dptInitSampDist.GetCurSel();	// ��-��ʼ��������
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

	// �ŷ�����
	ar << m_AziStart;	// ��λ��ʼ�Ƕ�
	ar << m_AziEnd;		// ��λ��ֹ�Ƕ�
	ar << m_AziSpeed;	// ��λɨ��Ƕ�
	ar << m_wbNum;		// ��λ��תȦ��
	ar << m_EleStart;	// ������ʼ�Ƕ�
	ar << m_EleEnd;		// ������ֹ�Ƕ�
	ar << m_EleSpeed;	// ����ɨ���ٶ�

	// ����ģʽ
	ar << m_comboxWorkingModes.GetCurSel();
	

	//ʵʱ�ɼ�����
	ar << m_iniAzimuth; // �ɼ���ʼ��λ��
	ar << m_minitime.GetCurSel(); // �ɼ���Сʱ����

	ar << m_edit_distDetect;	// �����ⵥԪ��
	ar << m_edit_dopplerDetect;	// �����ռ�ⵥԪ��

	// ����ģʽ-��ʱ����
	ar << m_combox_workMode.GetCurSel();

	// ʱ�������л�-start
	/*CTime cTimett;
	m_dateTimePickerStart.GetTime(cTimett);
	ar << cTimett;*/

	// ʱ�������л�-stop
	/*m_dateTimePickerStop.GetTime(cTimett);
	ar << cTimett;*/

	// �Զ�У׼ʹ��
	ar << m_autoCali.GetCurSel();

	// �Զ�У׼ģʽ
	ar << m_comboxAutoCaliMode.GetCurSel();

	// Track·�����л�
	ar << m_editPlayBackTrackPath;
	// �ط��ļ����ʱ��
	ar << m_editPlayBackTimerInterval;

	// ��ɨģʽʹ��
	ar << m_comboxSlowScan.GetCurSel();
	
	// ʱ��ؼ����л�
	/*GetDlgItemText(IDC_DATETIMEPICKER_STARTPLAYBACK, dataTimerPickerStartPlayAr);
	ar << dataTimerPickerStartPlayAr;*/

	if((m_combox8.GetCurSel() == 0 && (m_combox10.GetCurSel() == 1 || m_combox10.GetCurSel() == 2 || m_combox10.GetCurSel() == 4 || m_combox10.GetCurSel() == 7) && m_comboxAttenu.GetCurSel() != 5))	// ��
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
		MessageBox(_T("������ѡ��У׼ͨ��ʹ�ܡ�У׼ͨ�����ƻ�˥����"), NULL, MB_ICONERROR);
		return;
	}

	// �Զ����ղ�����ֵ�����޶�-���ݲ��������������޶�
	if(m_combox5.GetCurSel() == 0)
	{
		if(m_edit_dopplerDetect > 16 || m_edit_dopplerDetect < 2)
		{
			MessageBox(_T("�����ռ�ⵥԪ��������Ч��Χ�ڣ����������룡"));
			return;
		}
	}
	else if(m_combox5.GetCurSel() == 1)
	{
		if(m_edit_dopplerDetect > 8 || m_edit_dopplerDetect < 2)
		{
			MessageBox(_T("�����ռ�ⵥԪ��������Ч��Χ�ڣ����������룡"));
			return;
		}
	}
	else if(m_combox5.GetCurSel() == 2)
	{
		if(m_edit_dopplerDetect > 4 || m_edit_dopplerDetect < 2)
		{
			MessageBox(_T("�����ռ�ⵥԪ��������Ч��Χ�ڣ����������룡"));
			return;
		}
	}
	else if(m_combox5.GetCurSel() == 3)
	{
		if(!(m_edit_dopplerDetect == 2))
		{
			MessageBox(_T("�����ռ�ⵥԪ��������Ч��Χ�ڣ����������룡"));
			return;
		}
	}
	
	if (MinMaxFloat() != 0)
		return;
	

	//�ռ��������ò���
	GetData(m_radarPara);
	tempRadarPara = m_radarPara;
	//������matlab��������
	//if (!ConfigMatlabPara())
		//return;
	GetData_ToMatlab(toMatlabPara);

	if (m_combox18.GetCurSel() == 0)
	{
		if ((!PathFileExists(toMatlabPara.s2)) && m_comboxEnablePlayBack.GetCurSel() == 0)
		{
			MessageBox(_T("�����ļ������ڣ�������ѡ��"), NULL, MB_ICONERROR);
			return;
		}
	}
	else
	{
		if ((!PathFileExists(toMatlabPara.s1)) && m_comboxEnablePlayBack.GetCurSel() == 0)
		{
			MessageBox(_T("У׼·�������ڣ�������ѡ��"), NULL, MB_ICONERROR);
			return;
		}
	}

	TCHAR szOwnModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szOwnModulePath, MAX_PATH);   //���ϵͳ·��
	(_tcsrchr(szOwnModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szOwnModulePath , _T("ToOwnParaConfig.txt"));

	CString strOwnModulePath;
	strOwnModulePath = szOwnModulePath;
	CFile ownFile(strOwnModulePath, CFile::modeCreate | CFile::modeWrite);
	CArchive arOwn(&ownFile,CArchive::store);


	// ����ɼ���ֹ��λ�Ƕ�
	m_radarPara.nPara_endAzimuth = m_iniAzimuth + m_radarPara.nPara_20 * m_radarPara.nPara_48;
	arOwn << m_radarPara.nPara_endAzimuth;

	if((m_comboxWorkingModes.GetCurSel() == 2) && (m_combox15.GetCurSel() == 4 || m_combox15.GetCurSel() == 6 || m_combox15.GetCurSel() == 7))
	{
		if(!((m_iniAzimuth - m_radarPara.nPara_18 >= m_radarPara.nPara_20 * m_radarPara.nPara_20 / 60 + 5) &&
			(m_radarPara.nPara_19 - m_radarPara.nPara_endAzimuth >= m_radarPara.nPara_20 * m_radarPara.nPara_20 / 60 + 5)) )
		{
			MessageBox(_T("����������ɨ��ǶȻ�ɨ���ٶ�"), NULL, MB_ICONERROR);
			return;
		}
	}


	// �Զ���У׼ʹ��
	g_autoCali = m_autoCali.GetCurSel();
	arOwn << g_autoCali;
	// �Զ���У׼ģʽ
	g_autoCaliMode = m_comboxAutoCaliMode.GetCurSel();
	arOwn << g_autoCaliMode;
	// ת��ʹ��
	g_zhuanCun = m_combox_zhuancun.GetCurSel();
	arOwn << g_zhuanCun;
	// ת��ʱ��
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

	// ��ɨʹ��
	g_slowScan = m_comboxSlowScan.GetCurSel();
	//g_zhuanCunTime = m_combox_zhuanCunTime.GetCurSel();


	// ��У׼ģʽ�����
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
		strMessage = _T("��ǰΪ") + strMode + _T("���Ƿ������");
		if (MessageBox(strMessage, NULL, MB_YESNO) == IDYES)
		{
			if(g_autoCali == 1)	// �Զ���У׼ģʽ
			{
				m_radarPara.nPara_7 = 0;	// ��ʼ��������Ϊ0
				m_radarPara.nPara_dptInitSampDist = 0;	// ����ģʽ�¸�������ʼ��������
			}
			if(g_autoCali == 1 && g_autoCaliMode == 1)
			{
				m_radarPara.nPara_detectionChannel = 0; // ��У׼ģʽ���ֶ�������Ƚ��з���һУ׼��HHͨ��
			}
			
			// ���·���Radar�������л�
			ArRadarParaConfig(m_radarPara);
			verticalOrSlowScanCount =0; // �ֶ���γ�ʼ��Ϊ0
			int tt = 0;
			tt = g_tcpClient.Send((byte *)(&m_radarPara), sizeof(m_radarPara));
			//GetData_ToMatlab(toMatlabPara);
			CString str;
			str.Format(_T("%d"),tt);
			//theApp.m_pMainDlg->PrintMessage(str);

			if (tt == sizeof(m_radarPara))
			{
				::SendMessage(theApp.m_pMainDlg->m_hWnd, WM_USER+400, NULL, NULL);
				//theApp.m_pMainDlg->PrintMessage(L"�ֶ�SEND��");

				//GetData_ToMatlab(toMatlabPara);
			}
			b_isOkBtnParaConfig = true;
			
		}
		else
			return;
	}
	else
	{
		// ��ȡ����-ʱ��ؼ�����
		GetDateTimeFromCtrl();
	}

	// ���βɼ�ʱ�����ֵ����---1024*1024*1024/(����������*160+128)*PRT*40/�������ģʽ
	int temp_g_singleAcquistionTimeMax = (g_singleAcquistionTimeMax / 1000000);
	if(m_edit_12 > temp_g_singleAcquistionTimeMax)
	{
		MessageBox(_T("���βɼ�ʱ��ֵ���ù������������ã�"));
		return;
	}

	// ����ģʽ
	g_workMode = m_combox_workMode.GetCurSel();
	arOwn << g_workMode;

	arOwn << b_isOkBtnParaConfig;
	//theApp.m_pMainDlg->PrintMessage(_T("arOwn << b_isOkBtnParaConfig;"));

	// ��ȡ��ʼ����-ֹͣ�����ؼ�����
	CString strStart, strLStart, strMStart, strStop, strLStop, strMStop;
	GetDlgItemText(IDC_DATETIMEPICKER_START, strStart);
	GetDlgItemText(IDC_DATETIMEPICKER_STOP, strStop);
	int iindex = strStart.Find(_T(":"));
	strLStart = strStart.Left(iindex);
	strMStart = strStart.Mid(iindex+1,2);
	strLStop = strStop.Left(iindex);
	strMStop = strStop.Mid(iindex+1,2);

	// ����ת��
	setTimeInfo.iStartHour = _ttoi(strLStart);
	setTimeInfo.iStartMinute = _ttoi(strMStart);
	setTimeInfo.iStopHour = _ttoi(strLStop);
	setTimeInfo.iStopMinute = _ttoi(strMStop);

	if(g_trackFilePath.IsEmpty() && m_comboxEnablePlayBack.GetCurSel() == 1)
	{
		MessageBox(L"·��Ϊ�գ���ѡ����Ч�Ļط�·����");
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
	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	wcscat(szModulePath , LRFileName);

	DeleteFile(szModulePath);
}

UINT tempStartRan = 0;
void CParaConfig::ArRadarParaConfig(RadarPara radarConfig)
{
	// ���л�
	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
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

	// ��������
	ar << waveMode;
	ar << codeMode;
	ar << g_nDrawNodes;
	ar << g_nCoefficient;
	ar << g_nPara_7;
	ar << g_singleAcquistionTimeMax;
	ar << tempnPara_48; // ���βɼ�ʱ��
	ar << tempnPara_7; // ��ʼ��������
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
		MessageBox(L"�ط�Matlab�⺯����ʼ��ʧ�ܣ�");
		return 0;
	}
	else
	{
		theApp.m_pMainDlg->PrintMessage(L"MATLAB��ʼ����ɣ�");
		g_isSucessInitMatlabPlayBacklib = true;
	}
	return 0;
}

void CParaConfig::GetDateTimeFromCtrl()
{
	// ��ȡ���ڿؼ�����
	CString strStartDateTime,strStopDateTime;
	GetDlgItemText(IDC_DATETIMEPICKER_STARTPLAYBACKDATE,strStartDateTime);
	GetDlgItemText(IDC_DATETIMEPICKER_STOPPLAYBACKDATE,strStopDateTime);

	
	// ��ȡʱ��ؼ�����
	CString strStartPlayBackTime, strStopPlayBackTime;
	GetDlgItemText(IDC_DATETIMEPICKER_STARTPLAYBACK, strStartPlayBackTime);
	GetDlgItemText(IDC_DATETIMEPICKER_STOPPLAYBACK, strStopPlayBackTime);

	// ת��ʱ���
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

	// ȡTrackFile·��
	g_trackFilePath = m_editPlayBackTrackPath;
	// ȡʱ����
	g_playBackTimeInterval = m_editPlayBackTimerInterval * 1000; // ��
}




//ȡ����ť
void CParaConfig::OnBnClickedButton2()
{
	CDialogEx::OnCancel();
}


//�ռ��������������ҽ�DSPͨ�ŵĲ����������л�
//RadarPara tempRadarPara;
void CParaConfig::GetData(RadarPara &radarPara)
{
	UpdateData(TRUE);

	CString str;
	radarPara.nParaType = 0x94EF032B;
	radarPara.nParaTail = 0x94EF032C;
	
	radarPara.nLen = sizeof(radarPara) - 8;   
	
	radarPara.nPara_2 = m_combox1.GetCurSel();					//����ģʽ
	
	if (radarPara.nPara_2 == 0 || radarPara.nPara_2 == 2)
		waveMode = 0;
	else 
		waveMode = 1;
	//waveMode = (radarPara.nPara_2%2) ? 0 : 1;
	//int tempInterpulseCodingPattern = 0;// �������ģʽ-���㵥�βɼ�ʱ�����ֵ��
	if (m_combox1.GetCurSel() == 1 || m_combox1.GetCurSel() == 3)
	{
		radarPara.nPara_3 = m_combox17.GetCurSel();					//�������ģʽ
	}
	else	// ��ʱ
	{
		//tempInterpulseCodingPattern = 2;
		radarPara.nPara_3 = m_combox2.GetCurSel();					//�������ģʽ
	}
	
	//radarPara.nPara_3 = m_combox2.GetCurSel();					//�������ģʽ
	if (m_combox2.GetCurSel() == 2)
		codeMode = 2;		//˫֡�����������
	else if (m_combox2.GetCurSel() == 3)
	{
		codeMode = 3;		//˫֡����������
	}
	
	// 0����ͬʱȫ�ֻ���1�����ʱȫ�ֻ���2Զ��ͬʱȫ�ֻ���3Զ���ʱȫ�ֻ�
	if(m_comboxWorkingModes.GetCurSel() == 3)	// ��ֱģʽ-���沨��
	{
		// ������
		if (m_combox1.GetCurSel() == 0 || m_combox1.GetCurSel() == 1)
		{
			radarPara.nPara_4 = 5;									//��������
		}
		else
		{
			if (m_mainWavPlusWid.GetCurSel() == 0)
				radarPara.nPara_4 = 6;
			else
				radarPara.nPara_4 = m_mainWavPlusWid.GetCurSel()-1;      //��������
		}
		
		radarPara.nPara_7 = m_mainInitSapDist.GetCurSel();         //��ʼ��������
		
		tempnPara_7 = m_mainInitSapDist.GetCurSel();

		// ������
		if (m_combox1.GetCurSel() == 0 || m_combox1.GetCurSel() == 1)
		{
			radarPara.nPara_dptWavPlusWid = 5;									//��������
		}
		else	// ��ֱģʽ-��һ����
		{
			if (m_dptWavPlusWid.GetCurSel() == 0)
				radarPara.nPara_dptWavPlusWid = 6;
			else
				radarPara.nPara_dptWavPlusWid = m_dptWavPlusWid.GetCurSel()-1;      //��������
		}
		

		radarPara.nPara_dptInitSampDist = m_dptInitSampDist.GetCurSel();         //��ʼ��������
		

		tempDptInitSampDist = m_dptInitSampDist.GetCurSel();
	}
	else	// ����ģʽ
	{
		if (m_combox1.GetCurSel() == 0 || m_combox1.GetCurSel() == 1)
		{
			radarPara.nPara_4 = 5;									//��������
		}
		else
		{
			if (m_comboxPlusWidth.GetCurSel() == 0)
				radarPara.nPara_4 = 6;
			else
				radarPara.nPara_4 = m_comboxPlusWidth.GetCurSel()-1;      //��������
		}
		
		radarPara.nPara_7 = m_comboxSimpleRage.GetCurSel();         //��ʼ��������
		
		tempnPara_7 = m_comboxSimpleRage.GetCurSel();
	}
	

	//if (m_combox1.GetCurSel() == 0 || m_combox1.GetCurSel() == 1)
	//{
	//	radarPara.nPara_4 = 5;									//��������
	//}
	//else
	//{
	//	if (m_comboxPlusWidth.GetCurSel() == 0)
	//		radarPara.nPara_4 = 6;
	//	else
	//		radarPara.nPara_4 = m_comboxPlusWidth.GetCurSel()-1;      //��������
	//}
	
	radarPara.nPara_5 = m_combox3.GetCurSel();				    //PRT
	

	radarPara.nPara_6 = m_combox5.GetCurSel();                  //����������
	

	//radarPara.nPara_7 = m_comboxSimpleRage.GetCurSel();         //��ʼ��������
	radarPara.nPara_8 = m_combox6.GetCurSel();				    //ʵʱ�����ϴ�����
	

	m_combox6.GetLBText(m_combox6.GetCurSel(), str);
	g_nDrawNodes = _tstoi(str);
	
	radarPara.nPara_9 = m_combox4.GetCurSel();					//��Ϣ�ϴ�����
	


	//������Ƶ����
	if (m_combox1.GetCurSel() == 0 || m_combox1.GetCurSel() == 2)
	{
		radarPara.nPara_10 = 40;   //�������ģʽ����ͬʱȫ������������Ƶ������40
	}
	else
	{
		radarPara.nPara_10 = (m_combox13.GetCurSel() + 1) * 10;
	}
	

	
	
	radarPara.nPara_11 = m_combox7.GetCurSel();					//AGC������1
	

	m_combox7.GetLBText(m_combox7.GetCurSel(), str);
	radarPara.nPara_11 = _tstoi(str);
	

	radarPara.nPara_12 = m_combox9.GetCurSel();					//AGC������2
	m_combox9.GetLBText(m_combox9.GetCurSel(), str);
	radarPara.nPara_12 = _tstoi(str);
	

	radarPara.nPara_13 = m_combox8.GetCurSel();					//��׼ͨ��ʹ��
	

	radarPara.nPara_14 = m_combox10.GetCurSel();				//��׼ͨ������
	


	radarPara.nPara_15 = m_combox15.GetCurSel();				//����ת��ģʽ

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
	


	if (radarPara.nPara_15 == 8 || radarPara.nPara_15 == 9 || radarPara.nPara_15 == 10)//�߶���������ģʽ��
	{
		radarPara.nPara_16 = m_aziCircleCnt;					//��λ��תȦ��
	}
	else						//�Ǹ߶���������ģʽ��
	{
		radarPara.nPara_16 = m_wbNum;							//����������
	}
	
	//if (radarPara.nPara_15 != 8)//�Ǹ߶���������ģʽ��
	//{
	//	radarPara.nPara_17 = 6;
	//	radarPara.nPara_18 = m_AziStart;
	//	radarPara.nPara_19 = m_AziEnd;
	//	radarPara.nPara_20 = m_AziSpeed;
	//	radarPara.nPara_21 = m_EleStart;
	//	radarPara.nPara_22 = m_EleEnd;
	//	radarPara.nPara_23 = m_EleSpeed;
	//}
	//else						//�߶���������ģʽ��
	//{
		if (radarPara.nPara_15 == 8)			//�߶���������ģʽ��-1
		{
			radarPara.nPara_17 = 4;
			radarPara.nPara_18 = 1.0;
			radarPara.nPara_19 = 5.7;
			radarPara.nPara_20 = 34.1;
			radarPara.nPara_21 = 90.0;
		}
		else if (radarPara.nPara_15 == 9)		//�߶���������ģʽ��-2
		{
			radarPara.nPara_17 = 6;
			radarPara.nPara_18 = 1.0;
			radarPara.nPara_19 = 2.7;
			radarPara.nPara_20 = 7.1;
			radarPara.nPara_21 = 19.3;
			radarPara.nPara_22 = 61.9;
			radarPara.nPara_23 = 90.0;
		}
		else if (radarPara.nPara_15 == 10)		//�߶���������ģʽ��-3
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
		else if (radarPara.nPara_15 != 8)//�Ǹ߶���������ģʽ��
		{
			radarPara.nPara_17 = 6;
			radarPara.nPara_18 = m_AziStart;
			radarPara.nPara_19 = m_AziEnd;
			radarPara.nPara_20 = m_AziSpeed;
			radarPara.nPara_21 = m_EleStart;
			radarPara.nPara_22 = m_EleEnd;
			radarPara.nPara_23 = m_EleSpeed;
		}



		//��ini�ļ���ȡ������λ��Ϣ
		//TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
		//GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
		//(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
		//wcscat(szModulePath , _T("Ele.ini"));
		//CString strModulePath;
		//strModulePath = szModulePath;

		//CString tSecName(_T("������λ�����ļ�"));   //����
		//CString tKeyName(_T("��λ����"));           //����

		//CString strOut;
		//::GetPrivateProfileString(tSecName, tKeyName, _T("0"), strOut.GetBuffer(256), 256, strModulePath);
		//int nCount = _ttoi(strOut);                 //��λ����
		//radarPara.nPara_17 = nCount;
		//tKeyName = _T("��λ");
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


		radarPara.nPara_38 = m_edit_2;	//��ⵥԪ��


		radarPara.nPara_39 = m_edit_3;	//�ο���Ԫ��


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



		radarPara.nPara_workingModes = m_comboxWorkingModes.GetCurSel();	// ����ģʽ



		// ���ݲɼ���Сʱ����
		if(m_minitime.GetCurSel() == 0)
		{
			radarPara.nPara_miniinterval = 0;
		}
		else
		{
			m_minitime.GetLBText(m_minitime.GetCurSel(), str);
			radarPara.nPara_miniinterval = _ttoi(str);
		}



		// �ɼ���ʼ��λ�Ƕ�
		radarPara.nPara_iniAzimuth = m_iniAzimuth;



		// �ɼ���ֹ��λ�Ƕ�
		radarPara.nPara_endAzimuth = m_iniAzimuth + radarPara.nPara_20 * radarPara.nPara_48;




		// ��׼У׼ͨ��ʹ��
		if(g_autoCali == 0)
		{
			if((m_combox8.GetCurSel() == 0 && (m_combox10.GetCurSel() == 1 || m_combox10.GetCurSel() == 2 || m_combox10.GetCurSel() == 4 || m_combox10.GetCurSel() == 7) && m_comboxAttenu.GetCurSel() != 5))	// ��
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


		
		radarPara.nPara_detectionChannel = m_combox_detectionChannel.GetCurSel(); // У׼ͨ�����ã�

		
		

		// ���βɼ�ʱ�����ֵ1024*1024*1024/(����������*160+128)*PRT*40/�������ģʽ

		int tempSmpWndCount = 256 * pow((double)2, (double)radarPara.nPara_6);	// ����������
		int tempPRT = radarPara.nPara_5 * 5 + 25;

		g_singleAcquistionTimeMax = 1024*1024*1024/(tempSmpWndCount*160+128)*tempPRT*40/2;


		//if(m_edit_12 > 1024*1024*1024/(tempSmpWndCount*160+128)*tempPRT*40/2)

		//delete []p;
		//p = NULL;
	//}
		//tempRadarPara = m_radarPara;

		radarPara.nPara_distDetect = m_edit_distDetect;		// �����ⵥԪ��


		radarPara.nPara_dopplerDetect = m_edit_dopplerDetect;	// �����ռ�ⵥԪ��

		
	
}



void CParaConfig::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_combox1.GetCurSel() == 1 || m_combox1.GetCurSel() == 3)
	{
		m_combox13.ShowWindow(TRUE);
		m_combox14.ShowWindow(FALSE);

		m_combox17.ShowWindow(TRUE);		//������붼��
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//int data = GetDlgItemInt(IDC_EDIT11);
	UpdateData(TRUE);
	if(/*m_wbNum<0 ||*/ m_wbNum>255)
	{
		SetDlgItemTextA(this->m_hWnd, IDC_EDIT11,"255");
		MessageBox(_T("������������Χ������0~255��"));
	}

	//CString str;
	//GetDlgItemText(IDC_EDIT11, str);

}


//����ת��ģʽѡ��
void CParaConfig::OnCbnSelchangeCombo15()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	case 3:		//��ֱ����ɨ��
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
	case 8:		//�߶ȸ���ģʽ-1
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
	case 9:		//�߶ȸ���ģʽ-2
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
	case 10:	//�߶ȸ���ģʽ-3
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
	//if (m_combox18.GetCurSel() == 0)	//����ģʽ
	//{
	//	CFileDialog dlg(TRUE);
	//	if (dlg.DoModal() == IDOK)
	//	{
	//		m_szSavePath = dlg.GetPathName();
	//		UpdateData(FALSE);
	//	}
	//}
	//else								//У׼ģʽ
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
			MessageBox(_T("��·�������ڣ�������ѡ��"), /*NULL,*/ NULL, MB_ICONWARNING);
			return;
		}
	//}
	

	

	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
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
	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
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
	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
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
	//����ģʽѡ������Ӧ�ļ�·�����ж�
	CString strFilejiaozhun, s1, s2, s3, s4, s5(_T("_"));
	strFilejiaozhun = m_szSavePath;
	m_combox1.GetLBText(m_combox1.GetCurSel(), s1);	//���α���strFilejiaozhun = "D:\Զ���ʱȫ����_��֡�����������_4_0.mat"
	if (m_combox1.GetCurSel() == 1 || m_combox1.GetCurSel() == 3)
	{
		m_combox17.GetLBText(m_combox17.GetCurSel(), s2);	//�������
	}
	else
	{
		m_combox2.GetLBText(m_combox2.GetCurSel(), s2);	//�������
	}
	
	m_combox7.GetLBText(m_combox7.GetCurSel(), s3);	//AGC1
	m_combox9.GetLBText(m_combox9.GetCurSel(), s4);	//AGC2
	strFilejiaozhun += (s1 + s5 + s2 + s5 + s3 + s5 + s4 + _T(".mat"));
	if (m_combox18.GetCurSel() == 0)	//����ģʽ
	{
		if (!PathFileExists(strFilejiaozhun))
		{
			MessageBox(_T("�ļ������ڣ�������У׼��"));
			return false;
		}
		else
		{
			int i = 0;
		}

	}
	else if (m_combox18.GetCurSel() == 1)	//У׼ģʽ
	{
		if (PathFileExists(strFilejiaozhun))
		{
			if (MessageBox(L"����У׼�ļ��Ѵ��ڣ��Ƿ������", NULL, MB_YESNO) == IDYES)
				return true;
			return false;
		}
		
	}

	return true;
}


void CParaConfig::GetData_ToMatlab(TOMATLABPARA &Para)
{
	TCHAR szModulePath[MAX_PATH+1];			        	//ϵͳ����Ŀ¼
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //���ϵͳ·��
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

	//��ʼ��������
	int nlhs = theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_comboxSimpleRage.GetCurSel();
	theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_comboxSimpleRage.GetLBText(nlhs, s);
	Para.StartRan = nlhs * 15;
	ar << Para.StartRan;
	tempStartRan = Para.StartRan;

	//����������
	nlhs = theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_combox5.GetCurSel();
	theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_combox5.GetLBText(nlhs, s);
	Para.SampleNum = _ttoi(s);
	ar << Para.SampleNum;

	//PRT
	nlhs = theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_combox3.GetCurSel();
	theApp.m_pMainDlg->m_formDlg1.m_dlgParaConfig.m_combox3.GetLBText(nlhs, s);
	Para.PRT = _ttoi(s);
	ar << Para.PRT;

	//���α���
	Para.WaveForm = m_combox1.GetCurSel();
	ar << Para.WaveForm;

	//�������
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

	// ��������
	if(m_comboxPlusWidth.GetCurSel() == 0)
	{
		Para.fPulseWid = 0.4;
	}
	else
	{
		Para.fPulseWid = m_comboxPlusWidth.GetCurSel();
	}
	ar << Para.fPulseWid;
	// ���βɼ�ʱ��
	Para.SampleTime = m_edit_12;
	ar << Para.SampleTime;

	// ����ģʽ
	Para.workingMode = m_comboxWorkingModes.GetCurSel();
	ar << Para.workingMode;

	// ��λ��ʼ�ɼ��Ƕ�
	Para.fAzi_S = m_iniAzimuth;
	ar << Para.fAzi_S;

	// ��λ��ֹ�ɼ��Ƕ�
	Para.fAzi_E = m_radarPara.nPara_endAzimuth;
	ar << Para.fAzi_E;

	// ������ʼ�Ƕ�
	Para.fElv_D = m_EleStart;
	ar << Para.fElv_D;
	// ������ֹ�Ƕ�
	Para.fElv_H = m_EleEnd;
	ar << Para.fElv_H;
	Para.enableAutoCali = m_autoCali.GetCurSel();
	ar << Para.enableAutoCali;

	ar << tempStartRan;
}



void CParaConfig::OnCbnSelchangeCombo18()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


int CParaConfig::MinMaxFloat()
{
	if (m_AziStart < -200 || m_AziStart > 200)
	{
		MessageBox(_T("��ȷ�Ϸ�λ��ʼ�Ƕ���-200��200֮�䣡"), NULL, MB_ICONERROR);
		return -1;
	}
	if (m_AziEnd < -200 || m_AziEnd > 200)
	{
		MessageBox(_T("��ȷ�Ϸ�λ��ֹ�Ƕ���-200��200֮�䣡"), NULL, MB_ICONERROR);
		return -1;
	}
	if (m_AziSpeed  < 0 || m_AziSpeed > 60 )
	{
		MessageBox(_T("��ȷ�Ϸ�λɨ���ٶ���0��60֮�䣡"), NULL, MB_ICONERROR);
		return -1;
	}
	if (m_EleStart  < 0 || m_EleStart > 90 )
	{
		MessageBox(_T("��ȷ�ϸ�����ʼ�Ƕ���0��90֮�䣡"), NULL, MB_ICONERROR);
		return -1;
	}
	if (m_EleEnd  < 0 || m_EleEnd > 90)
	{
		MessageBox(_T("��ȷ�ϸ�����ֹ�Ƕ���0��90֮�䣡"), NULL, MB_ICONERROR);
		return -1;
	}
	if ( m_EleSpeed  < 0 || m_EleSpeed > 40 )
	{
		MessageBox(_T("��ȷ�ϸ���ɨ���ٶ���0��40֮�䣡"), NULL, MB_ICONERROR);
		return -1;
	}
	return 0;
}


void CParaConfig::OnCbnSelchangeComboWorkingmodes()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: ѡ��Ҫ�طŵ�Track����·��
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
