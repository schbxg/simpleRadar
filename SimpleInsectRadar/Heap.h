////////////////////////////////////////////////////////////////
// 文件 - Heap.h
// 类别 - 标准库 > 自定义基类
// 版本 - 1.1
//
// 毛冬
// V1.0 2012.10
// V1.1 2014.04
////////////////////////////////////////////////////////////////

#pragma once

enum CHEAPVER
{
	CHV_SRC_1_0 = 10,
	CHV_LIB_1_0 = 10,
	CHV_SRC_1_1 = 11,
	CHV_LIB_1_1 = 11
};

class CHeap : public CObject
{
	DECLARE_SERIAL(CHeap);

private:
	DWORD m_flOptions;
	SIZE_T m_dwInitialSize;
	SIZE_T m_dwMaximumSize;

	HANDLE m_hHeap;
	SIZE_T m_nNumAllocesInHeap;

public:
	CHeap();
	CHeap(const CHeap& objectSrc);
	CHeap(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize);
	virtual ~CHeap();

	BOOL Create(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize);
	BOOL Destroy();

	LPVOID Alloc(DWORD dwFlags, SIZE_T dwBytes);
	BOOL Free(DWORD dwFlags, LPVOID lpMem);

	BOOL IsEmpty();
	SIZE_T Count();

	SIZE_T Size(DWORD dwFlags, LPCVOID lpMem);
	BOOL Validate(DWORD dwFlags, LPCVOID lpMem);
	SIZE_T Compact(DWORD dwFlags);

	BOOL Lock();
	BOOL Unlock();

	virtual void Serialize(CArchive& ar);
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
};
