////////////////////////////////////////////////////////////////
// 文件 - Sequence.h
// 类别 - 标准库 > 模板类
// 版本 - 1.1
//
// 毛冬
// V1.0 2013.01
// V1.1 2014.04
////////////////////////////////////////////////////////////////

#pragma once

//序列器，T=数据类型，ChannelCount=通道数量
template<typename T, size_t ChannelCount>
class CBaseSequence : public CObject
{
private:
	CCriticalSection m_CriticalSection;

protected:
	bool m_Enabled[ChannelCount];

public:
	CBaseSequence()
	{
		for (size_t i=0; i<ChannelCount; i++)
			ChannelEnable(i, true);
	}

	virtual ~CBaseSequence() {}

	//添加数据，输入数据首地址，返回添加的通道个数
	virtual size_t Push(T* pMem) = NULL;

	//获取数据，输入通道ID，返回数据首地址
	virtual T* Pop(size_t ChannelID = 0) = NULL;

	//判断序列是否为空，输入通道ID，空返回TRUE，非空返回FALSE
	virtual BOOL IsEmpty(size_t ChannelID = 0) = NULL;

	//获取序列个数，输入通道ID，返回序列个数
	virtual size_t Count(size_t ChannelID = 0) = NULL;

	//锁，成功返回TRUE，失败返回FALSE
	virtual BOOL Lock() { return m_CriticalSection.Lock(); }

	//解锁，成功返回TRUE，失败返回FALSE
	virtual BOOL Unlock() { return m_CriticalSection.Unlock(); }

	//通道使能，ChannelID=通道号，Enabled=使能标志
	virtual void ChannelEnable(size_t ChannelID = 0, bool Enabled = true)
	{
		ASSERT(ChannelID < ChannelCount);
		m_Enabled[ChannelID] = Enabled;
	}

	//判断通道是否使能，ChannelID=通道号，使能返回true，不使能返回false
	virtual bool IsChannelEnabled(size_t ChannelID = 0)
	{
		ASSERT(ChannelID < ChannelCount);
		return m_Enabled[ChannelID];
	}
};

//FIFO序列器
template<typename T, size_t ChannelCount>
class CFIFOSequence : public CBaseSequence<T, ChannelCount>
{
private:
	CList<T*> m_List[ChannelCount];

public:
	CFIFOSequence() {}
	virtual ~CFIFOSequence() {}

	virtual size_t Push(T* pMem)
	{
		ASSERT(pMem);

		size_t ReferenceCount = 0;

		for (size_t i=0; i<ChannelCount; i++)
		{
			if (m_Enabled[i])
			{
				m_List[i].AddTail(pMem);
				ReferenceCount++;
			}
		}

		return ReferenceCount;
	}

	virtual T* Pop(size_t ChannelID = 0)
	{
		ASSERT(ChannelID < ChannelCount);

		if (m_List[ChannelID].IsEmpty())
			return NULL;

		return m_List[ChannelID].RemoveHead();
	}

	virtual BOOL IsEmpty(size_t ChannelID = 0)
	{
		return m_List[ChannelID].IsEmpty();
	}

	virtual size_t Count(size_t ChannelID = 0)
	{
		return m_List[ChannelID].GetCount();
	}
};

//FILO序列器
template<typename T, size_t ChannelCount>
class CFILOSequence : public CBaseSequence<T, ChannelCount>
{
private:
	CList<T*> m_List[ChannelCount];

public:
	CFILOSequence() {}
	virtual ~CFILOSequence() {}

	virtual size_t Push(T* pMem)
	{
		ASSERT(pMem);

		size_t ReferenceCount = 0;

		for (size_t i=0; i<ChannelCount; i++)
		{
			if (m_Enabled[i])
			{
				m_List[i].AddHead(pMem);
				ReferenceCount++;
			}
		}

		return ReferenceCount;
	}

	virtual T* Pop(size_t ChannelID = 0)
	{
		ASSERT(ChannelID < ChannelCount);

		if (m_List[ChannelID].IsEmpty())
			return NULL;

		return m_List[ChannelID].RemoveHead();
	}

	virtual BOOL IsEmpty(size_t ChannelID = 0)
	{
		return m_List[ChannelID].IsEmpty();
	}

	virtual size_t Count(size_t ChannelID = 0)
	{
		return m_List[ChannelID].GetCount();
	}
};
