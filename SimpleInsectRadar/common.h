////////////////////////////////////////////////////////////////
// �ļ� - common.h
// ��� - ��׼�� > ��������
// �汾 - 1.0
// ��ע - Դ��
//
// ����
// V1.0 2016.12.29
// V1.1 
// V1.2 
////////////////////////////////////////////////////////////////


#ifndef __COMMON__
#define __COMMON__

#pragma once

#ifdef UNICODE
#define StringReverse StringReverseW
#else
#define StringReverse StringReverseA
#endif

#include <string>
using namespace std;
//��ȡ�ļ���С��֧�ִ���4GB�ļ���
LONGLONG GetFileSize(LPCTSTR lpFileName);


//���ַ�ת���ֽ�
bool WideCharToMultiByte(PCWSTR pWideCharStr, PSTR pMultiByteStr, int cbMultiByte);


//��ȡexe�ļ�·��
void GetExePath(CString &str);


//��ȡini�ļ����ض������ض������µ��ַ���
void ReadIni(CString strPath, CString tSecName, CString tKeyName, CString &strOut);


//�ַ���ת����ʮ��������ʾ���ַ���
int strToHex(char *ch, char *hex);


//��������һ������, value: 0~255
char valueToHexCh(const int value);


//��ת�ַ����е������ַ�
bool StringReverseW(PWSTR pWideCharStr, DWORD cchLength);
bool StringReverseA(PSTR pMultiByteStr, DWORD cchLength);


/************************************************************************/
/* 
	StartTick��EndTick��һ�Լ�ʱ��������λ���롣
	ʹ�÷�����
	__int64 t1=StartTick();
	...
	DOUBLE t2=EndTick(t1);
	t2�����м��������ʱ�䡣
*/
/************************************************************************/
__int64 StartTick();
double EndTick(__int64 QPart1);

//ɾ��ָ��·���µ������ļ�
BOOL DeleteAll(CString dirName);

//����Ŀ¼
int CreateFolder(CString strDir);

#endif
