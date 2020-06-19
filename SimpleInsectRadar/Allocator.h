////////////////////////////////////////////////////////////////
// �ļ� - Allocator.h
// ��� - ��׼�� > ģ����
// �汾 - 1.1
//
// ë��
// V1.0 2013.01
// V1.1 2014.04
////////////////////////////////////////////////////////////////

#pragma once

#include "Heap.h"

//��������T=�������ͣ�Width=���ݿ�ȣ�sizeof(T)����Deepth=������ȣ�Width*sizeof(T)��
template<typename T, size_t Width, size_t Deepth>
class CBaseAllocator : public CObject
{
public:
	CBaseAllocator() {}
	virtual ~CBaseAllocator() {}

	//�����ڴ棬�����ڴ��׵�ַ
	virtual T* Alloc() = NULL;

	//�ͷ��ڴ棬�����������ڴ��׵�ַ���ɹ�����TRUE��ʧ�ܷ���FALSE
	virtual BOOL Free(T* pMem) = NULL;

	//�����ɹ�����TRUE��ʧ�ܷ���FALSE
	virtual BOOL Lock() = NULL;

	//�������ɹ�����TRUE��ʧ�ܷ���FALSE
	virtual BOOL Unlock() = NULL;
};

//�ѷ�������S�棩
template<typename T, size_t Width, size_t Deepth>
class CSHeapAllocator : public CBaseAllocator<T, Width, Deepth>
{
private:
	static CHeap s_Heap;

public:
	CSHeapAllocator() {}
	virtual ~CSHeapAllocator() {}

	virtual T* Alloc()
	{
		if (s_Heap.IsEmpty())
		{
			if (!s_Heap.Create(0, sizeof(T)*Width*Deepth, 0))
				return NULL;
		}
		return (T*)s_Heap.Alloc(0, sizeof(T)*Width*Deepth);
	}

	virtual BOOL Free(T* pMem)
	{
		if (s_Heap.Free(0, pMem))
		{
			if (s_Heap.IsEmpty())
				return s_Heap.Destroy();
			return TRUE;
		}
		return FALSE;
	}

	virtual BOOL Lock() { return s_Heap.Lock(); }

	virtual BOOL Unlock() { return s_Heap.Unlock(); }
};

template<typename T, size_t Width, size_t Deepth>
CHeap CSHeapAllocator<T, Width, Deepth>::s_Heap = CHeap();

//�ѷ�������D�棩
template<typename T, size_t Width, size_t Deepth>
class CDHeapAllocator : public CBaseAllocator<T, Width, Deepth>
{
private:
	CHeap m_Heap;

public:
	CDHeapAllocator() { m_Heap.Create(0, sizeof(T)*Width*Deepth, 0); }

	virtual ~CDHeapAllocator() { m_Heap.Destroy(); }

	virtual T* Alloc()
	{
		if (m_Heap.Count() < Deepth )
			return (T*)m_Heap.Alloc(0, sizeof(T)*Width);
		else
			return NULL;
	}

	virtual BOOL Free(T* pMem) { return m_Heap.Free(0, pMem); }

	virtual BOOL Lock() { return m_Heap.Lock(); }

	virtual BOOL Unlock() { return m_Heap.Unlock(); }
};

//�����ڴ������
template<typename T, size_t Width, size_t Deepth>
class CVirtualAllocator : public CBaseAllocator<T, Width, Deepth>
{
private:
	CCriticalSection m_CriticalSection;

public:
	CVirtualAllocator() {}
	virtual ~CVirtualAllocator() {}

	virtual T* Alloc() { return (T*)::VirtualAlloc(NULL, sizeof(T)*Width, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); }

	virtual BOOL Free(T* pMem) { return ::VirtualFree(pMem, 0, MEM_RELEASE); }

	virtual BOOL Lock() { return m_CriticalSection.Lock(); }

	virtual BOOL Unlock() { return m_CriticalSection.Unlock(); }
};
