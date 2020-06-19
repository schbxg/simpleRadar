#include "stdafx.h"
#include "CommonFun.h"

CommonFun::CommonFun()
{}
CommonFun::~CommonFun()
{}

void CommonFun::BroseAllFiles(CString pathStr, CStringArray& arrStrFile, vector<CString> &vec)
{
	CString myDataPath,fdPath;
	myDataPath=pathStr + L"\\*.*";
	CString strTmp;

	CFileFind find;
	BOOL bf = find.FindFile(myDataPath);
	while(bf)
	{                        
		bf = find.FindNextFile();
		if(!find.IsDots())
		{
			fdPath=find.GetFilePath();
			if (find.IsDirectory())
			{
				//如果是文件夹，递归，继续往下找                        
				BroseAllFiles(fdPath, arrStrFile, vec);
			}
			else
			{
				//如果是文件,判断是否是*.txt
				strTmp=fdPath.Right(4);
				strTmp.MakeLower();
				/*vecStr.push_back(strTmp);*/
				if ( strTmp==".txt" )
				{
					arrStrFile.Add(fdPath);
					vec.push_back(fdPath);
				}
			}
		}
	}
	find.Close();
}

CString CommonFun::ComFunGetSystemTime(int type)// type:年_月_日 type为3
{
	SYSTEMTIME curSystemTime;
	GetLocalTime(&curSystemTime);
	CString strTime;
	if(type == 3)
	{
		strTime.Format(L"%4d_%02d_%02d", 
			curSystemTime.wYear, curSystemTime.wMonth, curSystemTime.wDay, 
			curSystemTime.wHour);
	}
	else if(7 == type)
	{
		strTime.Format(L"%4d_%02d_%02d_%02d_%02d_%02d_%03d", 
			curSystemTime.wYear, curSystemTime.wMonth, curSystemTime.wDay, 
			curSystemTime.wHour, curSystemTime.wMinute, curSystemTime.wSecond, curSystemTime.wMilliseconds);
	}	
	
	return strTime;
}

void CommonFun::CreateFilePath(CString filePath)
{
	if(!PathIsDirectory(filePath))
	{
		CreateDirectory(filePath, 0); // 不存在路径就创建
		//theApp.m_pMainDlg->PrintMessage("Create trackFilePath Directory");
	}
}