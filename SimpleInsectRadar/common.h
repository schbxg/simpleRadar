////////////////////////////////////////////////////////////////
// 文件 - common.h
// 类别 - 标准库 > 公共函数
// 版本 - 1.0
// 备注 - 源码
//
// 孙铎
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
//获取文件大小（支持大于4GB文件）
LONGLONG GetFileSize(LPCTSTR lpFileName);


//宽字符转多字节
bool WideCharToMultiByte(PCWSTR pWideCharStr, PSTR pMultiByteStr, int cbMultiByte);


//获取exe文件路径
void GetExePath(CString &str);


//读取ini文件中特定段名特定键名下的字符串
void ReadIni(CString strPath, CString tSecName, CString tKeyName, CString &strOut);


//字符串转成以十六进制显示的字符串
int strToHex(char *ch, char *hex);


//服务于上一个函数, value: 0~255
char valueToHexCh(const int value);


//逆转字符串中的所有字符
bool StringReverseW(PWSTR pWideCharStr, DWORD cchLength);
bool StringReverseA(PSTR pMultiByteStr, DWORD cchLength);


/************************************************************************/
/* 
	StartTick和EndTick是一对记时函数。单位是秒。
	使用方法：
	__int64 t1=StartTick();
	...
	DOUBLE t2=EndTick(t1);
	t2就是中间过程所用时间。
*/
/************************************************************************/
__int64 StartTick();
double EndTick(__int64 QPart1);

//删除指定路径下的所有文件
BOOL DeleteAll(CString dirName);

//创建目录
int CreateFolder(CString strDir);

#endif
