////////////////////////////////////////////////////////////////
// ÎÄ¼þ - FIFO.h
// Àà±ð - ±ê×¼¿â > Ä£°åÀà
// °æ±¾ - 1.1
//
// Ã«¶¬
// V1.0 2013.01
// V1.1 2014.04
////////////////////////////////////////////////////////////////

#pragma once

#include "Allocator.h"
#include "Sequence.h"
#include "Buffer.h"

//¾²Ì¬FIFO
template<typename T, size_t Width, size_t Deepth, size_t ChannelCount,
	template<typename, size_t, size_t> class CAllocator,
	template<typename, size_t> class CSequence = CFIFOSequence>
class CStaticFIFO : public CStaticBuffer<T, Width, Deepth, ChannelCount, CSequence, CAllocator>
{
private:
	size_t m_Tail;
	size_t m_Deepth;
	CEvent m_Event;
	CCriticalSection m_CriticalSection;

public:
	CStaticFIFO() : m_Event(TRUE, TRUE)
	{
		m_Tail = 0;
		m_Deepth = 0;
	}

	virtual ~CStaticFIFO() {}

	virtual T* Alloc(DWORD dwTimeout = 0)
	{
		T* pMem = NULL;

		if (m_Event.Lock(dwTimeout))
		{
			m_CriticalSection.Lock();

			if (m_Deepth < Deepth)
			{
				pMem = m_Allocs[m_Tail];
				m_Tail = (m_Tail + 1) % Deepth;

				m_Deepth++;
				if (m_Deepth >= Deepth)
					m_Event.ResetEvent();
			}

			m_CriticalSection.Unlock();
		}

		return pMem;
	}

	virtual BOOL Free(T* pMem)
	{
		BOOL bOK = FALSE;

		m_Sequence.Lock();

		size_t p = 0;
		if (m_Map.Lookup(pMem, p))
		{
			bOK = TRUE;

			m_Map[pMem]--;

			if (m_Map[pMem] == 0)
			{
				m_CriticalSection.Lock();
				m_Deepth--;
				m_Event.SetEvent();
				m_CriticalSection.Unlock();
			}
		}

		m_Sequence.Unlock();

		return bOK;
	}
};

//¶¯Ì¬FIFO
template<typename T, size_t Width, size_t Deepth, size_t ChannelCount,
	template<typename, size_t, size_t> class CAllocator,
	template<typename, size_t> class CSequence = CFIFOSequence>
class CDynamicFIFO : public CDynamicBuffer<T, Width, Deepth, ChannelCount, CSequence, CAllocator> {};

//ÐéÄâ¾²Ì¬FIFO
template<typename T, size_t Width, size_t Deepth, size_t ChannelCount,
	template<typename, size_t, size_t> class CAllocator = CVirtualAllocator,
	template<typename, size_t> class CSequence = CFIFOSequence>
class CVSFIFO : public CStaticFIFO<T, Width, Deepth, ChannelCount, CAllocator, CSequence> {};

//ÐéÄâ¶¯Ì¬FIFO
template<typename T, size_t Width, size_t Deepth, size_t ChannelCount,
	template<typename, size_t, size_t> class CAllocator = CVirtualAllocator,
	template<typename, size_t> class CSequence = CFIFOSequence>
class CVDFIFO : public CDynamicFIFO<T, Width, Deepth, ChannelCount, CAllocator, CSequence> {};

//¶Ñ¾²Ì¬FIFO£¨D°æ£©
template<typename T, size_t Width, size_t Deepth, size_t ChannelCount,
	template<typename, size_t, size_t> class CAllocator = CDHeapAllocator,
	template<typename, size_t> class CSequence = CFIFOSequence>
class CHSFIFO : public CStaticFIFO<T, Width, Deepth, ChannelCount, CAllocator, CSequence> {};

//¶Ñ¶¯Ì¬FIFO£¨D°æ£©
template<typename T, size_t Width, size_t Deepth, size_t ChannelCount,
	template<typename, size_t, size_t> class CAllocator = CDHeapAllocator,
	template<typename, size_t> class CSequence = CFIFOSequence>
class CHDFIFO : public CDynamicFIFO<T, Width, Deepth, ChannelCount, CAllocator, CSequence> {};
