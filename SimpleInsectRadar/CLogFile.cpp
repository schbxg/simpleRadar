#include "stdafx.h" 
#include "CLogFile.h"
//#include <afx.h>
	 
CLogFile::CLogFile() 
{
		    
}
 
CLogFile::~CLogFile() 
{

} 
//获取文件名称 
CString CLogFile::GetFileName() 
{ 
	CString sFileName;
	sFileName = CTime::GetCurrentTime().Format("%Y-%m-%d") + TEXT(".log"); 
	return sFileName; 
} 
 
//获取应用程序所在路径 
CString CLogFile::GetFilePath() 
{   
	
	TCHAR szModulePath[MAX_PATH+1];			        	//系统工作目录
	GetModuleFileName( NULL, szModulePath, MAX_PATH);   //获得系统路径
	(_tcsrchr(szModulePath, _T('\\')))[1] = 0;
	//wcscpy(gszSettingPath , szModulePath);
	//wcscat(szModulePath , _T("ParaConfig.txt"));

	CString strModulePath;
	strModulePath = szModulePath;

	//MessageBox((HWND)szModulePath, NULL, (LPCWSTR)MB_ICONWARNING);
	
	
	/*
	CString m_FilePath;   
	GetModuleFileName(NULL,m_FilePath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
		     
	m_FilePath.ReleaseBuffer();
		     
	int m_iPosIndex;
		     
	m_iPosIndex = m_FilePath.ReverseFind('\\'); 
		     
	//m_FilePath = m_FilePath.Left(m_iPosIndex) + TEXT("\\Log");
	//m_FilePath = "D:\\Work\\radar";
	MessageBox((HWND)m_FilePath);
	 */    
	return szModulePath; 
}
  
bool CLogFile::WriteLog(CString LogText) 
{ 
	try 
	{ 
		//CFile m_File; 
		CFile m_SFile; 
		CFileFind m_FileFind; 
		CString m_sErrorMessage; 
		CString m_sFileName = GetFileName(); 
		CString m_sFilePath = GetFilePath(); 
		CString m_sCurrentTime = CTime::GetCurrentTime().Format("%Y-%m-%d %X");

		//printf("%s\n", m_sFilePath);
					         
		if(!m_FileFind.FindFile(m_sFilePath)) 
		{ 
			CreateDirectory(m_sFilePath,NULL); 
		} 
				         
		m_SFile.Open(m_sFilePath + TEXT("\\") +m_sFileName,CFile::modeCreate |CFile::modeNoTruncate| CFile::modeReadWrite |CFile::shareDenyWrite); 
		/*{ 
			m_SFile.Open(m_sFilePath + TEXT("\\") + m_sFileName,CFile::modeCreate | CFile::modeReadWrite |CFile::shareDenyWrite| CFile::typeText); 
		}*/ 
						           
		m_SFile.SeekToEnd(); 
				        
		if(sizeof(TCHAR)==sizeof(WCHAR)) 
		{ 
			WORD wSignature = 0xFEFF; 
			m_SFile.Write(&wSignature, 2); 
		}        
				         
		//TCHAR* m_szMessage;					        
		//m_szMessage=m_sErrorMessage.GetBuffer();
					         
		m_sErrorMessage = TEXT("*******************") + m_sCurrentTime + TEXT("*******************")+TEXT("\r\n") ; 
		m_SFile.Write(m_sErrorMessage,m_sErrorMessage.GetLength()*sizeof(TCHAR));
				         
		//m_sErrorMessage = LogText ; 
		LogText+=TEXT("\r\n"); 
		m_SFile.Write(LogText,LogText.GetLength()*sizeof(TCHAR)); 
		//m_sErrorMessage = TEXT("*******************") + m_sCurrentTime + TEXT("*******************") ; 
		//m_SFile.Write(m_sErrorMessage,m_sErrorMessage.GetLength()*sizeof(TCHAR));
				         
		//m_SFile.Write(m_sErrorMessage.GetBuffer(),m_sErrorMessage.GetLength());   
					         
		m_SFile.Close(); 
	} 
	catch(CFileException fileException) 
	{ 
		return false; 
	}
		     
	return true; 
}