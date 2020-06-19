////////////////////////////////////////////////////////////////
// �ļ� - Sequence.h
// ��� - ��׼�� > ģ����
// �汾 - 1.1
//
// ë��
// V1.0 2013.01
// V1.1 2014.04
////////////////////////////////////////////////////////////////

#pragma once

//��������T=�������ͣ�ChannelCount=ͨ������
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

	//������ݣ����������׵�ַ��������ӵ�ͨ������
	virtual size_t Push(T* pMem) = NULL;

	//��ȡ���ݣ�����ͨ��ID�����������׵�ַ
	virtual T* Pop(size_t ChannelID = 0) = NULL;

	//�ж������Ƿ�Ϊ�գ�����ͨ��ID���շ���TRUE���ǿշ���FALSE
	virtual BOOL IsEmpty(size_t ChannelID = 0) = NULL;

	//��ȡ���и���������ͨ��ID���������и���
	virtual size_t Count(size_t ChannelID = 0) = NULL;

	//�����ɹ�����TRUE��ʧ�ܷ���FALSE
	virtual BOOL Lock() { return m_CriticalSection.Lock(); }

	//�������ɹ�����TRUE��ʧ�ܷ���FALSE
	virtual BOOL Unlock() { return m_CriticalSection.Unlock(); }

	//ͨ��ʹ�ܣ�ChannelID=ͨ���ţ�Enabled=ʹ�ܱ�־
	virtual void ChannelEnable(size_t ChannelID = 0, bool Enabled = true)
	{
		ASSERT(ChannelID < ChannelCount);
		m_Enabled[ChannelID] = Enabled;
	}

	//�ж�ͨ���Ƿ�ʹ�ܣ�ChannelID=ͨ���ţ�ʹ�ܷ���true����ʹ�ܷ���false
	virtual bool IsChannelEnabled(size_t ChannelID = 0)
	{
		ASSERT(ChannelID < ChannelCount);
		return m_Enabled[ChannelID];
	}
};

//FIFO������
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

//FILO������
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
