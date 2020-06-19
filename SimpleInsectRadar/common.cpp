#include "stdafx.h"

#include "common.h"
#include <winbase.h>
#include <direct.h>

//��ȡ�ļ���С��֧�ִ���4GB�ļ���
LONGLONG GetFileSize(LPCTSTR lpFileName)
{
	HANDLE hFile = NULL;
	hFile = CreateFile(lpFileName, 0, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	LONGLONG temp = 0;

	if (hFile != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER filesize;
		if (GetFileSizeEx(hFile, &filesize))
			temp = filesize.QuadPart;
		else
			temp = 0xffffffffffffffff;
	}
	else
	{
		temp = 0xffffffffffffffff;
	}

	return temp;
}


//���ַ�ת���ֽ�
bool WideCharToMultiByte(PCWSTR pWideCharStr, PSTR pMultiByteStr, int cbMultiByte)
{
	int sizeMByte = WideCharToMultiByte(CP_OEMCP, 0, pWideCharStr, -1, NULL, 0, NULL, NULL);

	if (sizeMByte > cbMultiByte)
	{
		return false;
	}

	char *pBuffer = new char[sizeMByte];

	WideCharToMultiByte(CP_OEMCP, 0, pWideCharStr, -1, pBuffer, sizeMByte, NULL, NULL);

	memset(pMultiByteStr, 0, cbMultiByte*sizeof(char));
	strcpy(pMultiByteStr, pBuffer);

	delete[]pBuffer;
	pBuffer = NULL;

	return true;
}


//��ȡexe�ļ�·��
void GetExePath(CString &str)
{
	char dir_array[256];
	HINSTANCE hinst = NULL;
	//hinst = AfxGetApp()->m_hInstance;
	GetModuleFileNameA(hinst,dir_array,256);
	char dir1[256],dir2[256],dir3[256],dir4[256];
	_splitpath(dir_array,dir1,dir2,dir3,dir4);
	StrCatA(dir1,dir2);	 
	//StrCatA(dir1,"configFile.ini");
	str = dir1;
}


//��ȡini�ļ����ض������ض������µ��ַ���
void ReadIni(CString strPath, CString tSecName, CString tKeyName, CString &strOut)
{
	//::WritePrivateProfileString(tSecName, tKeyName1, L"e:\\TestData\\���ӻط�", configFilePath);
	::GetPrivateProfileString(tSecName, tKeyName, NULL/*_T("0")*/, strOut.GetBuffer(256), 256, strPath); 
	strOut.ReleaseBuffer();
}



char valueToHexCh(const int value)
{
	char result = '\0';

	if (value >=0 && value <= 9)
	{
		result = (char)(value + 48);	//48ΪASCII�����'0'�ַ�����ֵ
	}
	else if (value >= 10 && value <= 15)
	{
		result = (char)(value - 10 + 65);	//��ȥ10���ҳ��䴦��16���Ƶ�ƫ������65λASCII��'A'�ַ�����ֵ
	}

	return result;
}


//�ַ���ת����ʮ��������ʾ���ַ���
int strToHex(char *ch, char *hex)
{
	int high, low;
	int tmp = 0;

	if (ch == NULL || hex == NULL)
	{
		return -1;
	}

	if (strlen(ch) == 0)
	{
		return -2;
	}

	while(*ch)
	{
		tmp = (int)*ch;
		high = tmp >> 4;
		low = tmp & 15;
		*hex++ = valueToHexCh(high);	//��д���ֽ�
		*hex++ = valueToHexCh(low);		//��д���ֽ�
		*hex++ = ' ';
		ch++;
	}
	*hex = '\0';
	return 0;
}


//��ת�ַ����е������ַ�
bool StringReverseW(PWSTR pWideCharStr, DWORD cchLength)
{
	PWSTR pEndOfStr = pWideCharStr + wcsnlen_s(pWideCharStr, cchLength) - 1;

	wchar_t cCharT;

	while(pWideCharStr < pEndOfStr)
	{
		cCharT = *pWideCharStr;

		*pWideCharStr = *pEndOfStr;

		*pEndOfStr = cCharT;

		pWideCharStr++;
		pEndOfStr--;
	}

	return true;
}


bool StringReverseA(PSTR pMultiByteStr, DWORD cchLength)
{
	PWSTR  pWideCharStr;
	int	   nLenOfWideCharStr;
	bool   bOK = false;

	nLenOfWideCharStr = MultiByteToWideChar(CP_ACP, 0, 
		pMultiByteStr, cchLength,NULL, 0);

	pWideCharStr = (PWSTR)HeapAlloc(GetProcessHeap(), 0,
		nLenOfWideCharStr * sizeof(wchar_t));

	if (pWideCharStr == NULL)
		return bOK;

	MultiByteToWideChar(CP_ACP, 0, pMultiByteStr, cchLength,
		pWideCharStr, nLenOfWideCharStr);

	bOK = StringReverseW(pWideCharStr, cchLength);

	if (bOK)
	{
		WideCharToMultiByte(CP_ACP, 0, pWideCharStr, cchLength,
			pMultiByteStr, (int)strlen(pMultiByteStr), NULL, NULL);
	}

	HeapFree(GetProcessHeap(), 0, pWideCharStr);

	return bOK;
}


__int64 StartTick()
{
	LARGE_INTEGER litmp;
	QueryPerformanceCounter(&litmp);
	return litmp.QuadPart;	
}


double EndTick(__int64 QPart1)
{
	LARGE_INTEGER litmp1;
	QueryPerformanceCounter(&litmp1);

	LARGE_INTEGER litmp;
	QueryPerformanceFrequency(&litmp);
	double dfFreq=(double)litmp.QuadPart;//��ȡ����ʱ��Ƶ�ʣ���ʱʹ��;

	double dfdeltaTime;
	dfdeltaTime = (litmp1.QuadPart - QPart1) / dfFreq;

	return dfdeltaTime;
}


BOOL DeleteAll(CString dirName)
{
	CFileFind tempFind;
	CString foundFileName;
	CString tempFileFind = dirName + _T("*.*");

	BOOL IsFinded = tempFind.FindFile(tempFileFind);
	while(IsFinded)
	{
		IsFinded = tempFind.FindNextFile();
		if (!tempFind.IsDots())
		{
			foundFileName = tempFind.GetFileName();
			CString tempFileName = dirName + _T("\\") + foundFileName;
			DeleteFile(tempFileName);
		}
	}
	tempFind.Close();

	return TRUE;
}

int CreateFolder(CString strDir)
{
	if (!PathFileExists(strDir))
	{
		return _wmkdir(strDir);
	}
	return 0;


	if (!PathFileExists(strDir))
	{
		CString strTemp;
		CStringList list;

		while(1)
		{
			strTemp = strDir.Right(strDir.GetLength() - strDir.ReverseFind('\\') - 1);
			list.AddHead(strTemp);
			strDir = strDir.Left(strDir.ReverseFind('\\'));
			if (strDir.IsEmpty())
				break;
		}
		POSITION pos = list.GetHeadPosition();
		CString head, directory;
		while(pos != NULL)
		{
			strTemp = list.GetNext(pos);
			directory = directory + strTemp + _T("\\");
			_wmkdir(strDir);
		}
	}


	return 0;
}