/************************************************************************/
/* ��˵���������࣬�������õĹ�������                                     */
/************************************************************************/
#pragma once
#include <afx.h>
#include <vector>

using namespace std;

class CommonFun
{
public:
	CommonFun();
	~CommonFun();

public:
	// ��ȡ�ļ����������ļ���+·�������Եݹ���Ŀ¼
	void BroseAllFiles(CString pathStr, CStringArray& arrStrFile, vector<CString> &vec);

	// ��ȡϵͳʱ�䣺������
	CString ComFunGetSystemTime(int type);

	// ���·���²�����ĳ���ļ��оʹ���
	void CreateFilePath(CString filePath);

protected:
private:
};