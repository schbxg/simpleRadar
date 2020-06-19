/************************************************************************/
/* 类说明：公共类，包含常用的公共函数                                     */
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
	// 获取文件夹下所有文件名+路径，可以递归子目录
	void BroseAllFiles(CString pathStr, CStringArray& arrStrFile, vector<CString> &vec);

	// 获取系统时间：年月日
	CString ComFunGetSystemTime(int type);

	// 如果路径下不存在某个文件夹就创建
	void CreateFilePath(CString filePath);

protected:
private:
};