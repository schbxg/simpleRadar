////////////////////////////////////////////////////////////////
// 文件 - Buffer.h
// 类别 - 标准库 > 模板类
// 版本 - 1.1
//
// 毛冬
// V1.0 2013.01
// V1.1 2014.04
////////////////////////////////////////////////////////////////

#pragma once

//缓存，T=数据类型，Width=数据宽度（sizeof(T)），Deepth=数据深度（Width*sizeof(T)），ChannelCount=通道数量，CAllocator=分配器，CSequence=序列器
template<typename T, size_t Width, size_t Deepth, size_t ChannelCount,
	template<typename, size_t, size_t> class CAllocator,
	template<typename, size_t> class CSequence>
class CBaseBuffer : public CObject
{
private:
	CEvent *m_pEvent[ChannelCount];

protected:
	CAllocator<T, Width, Deepth> m_Allocator;
	CSequence<T, ChannelCount> m_Sequence;
	CMap<T*, T*&, size_t, size_t&> m_Map;

public:
	CBaseBuffer()
	{
		for (size_t i=0; i<ChannelCount; i++)
			m_pEvent[i] = new CEvent(FALSE, TRUE);
	}

	virtual ~CBaseBuffer()
	{
		for (size_t i=0; i<ChannelCount; i++)
			delete m_pEvent[i];
	}

	//申请内存，输入等待时长（毫秒），返回内存首地址
	virtual T* Alloc(DWORD dwTimeout = 0) = NULL;

	//释放内存，输入已申请内存首地址，成功返回TRUE，失败返回FALSE
	virtual BOOL Free(T* pMem) = NULL;

	//添加数据，输入数据首地址
	virtual VOID Push(T* pMem)
	{
		m_Sequence.Lock();

		m_Map[pMem] = m_Sequence.Push(pMem);

		for (size_t i=0; i<ChannelCount; i++)
			if (m_Sequence.IsChannelEnabled(i))
				m_pEvent[i]->SetEvent();

		m_Sequence.Unlock();
	}

	//获取数据，ChannelID=通道ID，dwTimeout=等待时长（毫秒），返回数据首地址
	virtual T* Pop(size_t ChannelID = 0, DWORD dwTimeout = 0)
	{
		T* pMem = NULL;

		if (m_pEvent[ChannelID]->Lock(dwTimeout))
		{
			m_Sequence.Lock();

			pMem = m_Sequence.Pop(ChannelID);

			if (m_Sequence.IsEmpty(ChannelID))
				m_pEvent[ChannelID]->ResetEvent();

			m_Sequence.Unlock();
		}

		return pMem;
	}

	//通道使能，ChannelID=通道号，Enabled=使能标志
	virtual void ChannelEnable(size_t ChannelID = 0, bool Enabled = true)
	{
		m_Sequence.Lock();
		m_Sequence.ChannelEnable(ChannelID, Enabled);
		m_Sequence.Unlock();
	}

	//判断通道是否使能，ChannelID=通道号，使能返回true，不使能返回false
	virtual bool IsChannelEnabled(size_t ChannelID = 0)
	{
		bool bEnabled = false;
		m_Sequence.Lock();
		bEnabled = m_Sequence.IsChannelEnabled(ChannelID);
		m_Sequence.Unlock();
		return bEnabled;
	}

	//判断序列是否为空，输入通道ID，空返回TRUE，非空返回FALSE
	virtual BOOL IsEmpty(size_t ChannelID = 0)
	{
		BOOL bEmpty = FALSE;
		m_Sequence.Lock();
		bEmpty = m_Sequence.IsEmpty(ChannelID);
		m_Sequence.Unlock();
		return bEmpty;
	}

	//获取序列个数，输入通道ID，返回序列个数
	virtual size_t Count(size_t ChannelID = 0)
	{
		size_t nCount = 0;
		m_Sequence.Lock();
		nCount = m_Sequence.Count(ChannelID);
		m_Sequence.Unlock();
		return nCount;
	}
};

//静态缓存
template<typename T, size_t Width, size_t Deepth, size_t ChannelCount,
	template<typename, size_t> class CSequence,
	template<typename, size_t, size_t> class CAllocator>
class CStaticBuffer : public CBaseBuffer<T, Width, Deepth, ChannelCount, CAllocator, CSequence>
{
protected:
	T* m_Allocs[Deepth];

public:
	CStaticBuffer()
	{
		for (size_t i=0; i<Deepth; i++)
			m_Allocs[i] = m_Allocator.Alloc();
	}

	virtual ~CStaticBuffer()
	{
		for (size_t i=0; i<Deepth; i++)
			m_Allocator.Free(m_Allocs[i]);
	}
};

//动态缓存
template<typename T, size_t Width, size_t Deepth, size_t ChannelCount,
	template<typename, size_t> class CSequence,
	template<typename, size_t, size_t> class CAllocator>
class CDynamicBuffer : public CBaseBuffer<T, Width, Deepth, ChannelCount, CAllocator, CSequence>
{
private:
	CEvent m_Event;
	size_t m_Deepth;

public:
	CDynamicBuffer() : m_Event(TRUE, TRUE) { m_Deepth = 0; }

	virtual ~CDynamicBuffer() {}

	virtual T* Alloc(DWORD dwTimeout = 0)
	{
		T* pMem = NULL;

		if (m_Event.Lock(dwTimeout))
		{
			m_Allocator.Lock();

			if (m_Deepth < Deepth)
			{
				pMem = m_Allocator.Alloc();

				if (pMem)
				{
					m_Deepth++;
					if (m_Deepth >= Deepth)
						m_Event.ResetEvent();
				}
			}

			m_Allocator.Unlock();
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
				m_Allocator.Lock();
				bOK = m_Allocator.Free(pMem);
				m_Deepth--;
				m_Event.SetEvent();
				m_Allocator.Unlock();

				m_Map.RemoveKey(pMem);
			}
		}

		m_Sequence.Unlock();

		return bOK;
	}
};
