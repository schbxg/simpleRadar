////////////////////////////////////////////////////////////////
// �ļ� - Buffer.h
// ��� - ��׼�� > ģ����
// �汾 - 1.1
//
// ë��
// V1.0 2013.01
// V1.1 2014.04
////////////////////////////////////////////////////////////////

#pragma once

//���棬T=�������ͣ�Width=���ݿ�ȣ�sizeof(T)����Deepth=������ȣ�Width*sizeof(T)����ChannelCount=ͨ��������CAllocator=��������CSequence=������
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

	//�����ڴ棬����ȴ�ʱ�������룩�������ڴ��׵�ַ
	virtual T* Alloc(DWORD dwTimeout = 0) = NULL;

	//�ͷ��ڴ棬�����������ڴ��׵�ַ���ɹ�����TRUE��ʧ�ܷ���FALSE
	virtual BOOL Free(T* pMem) = NULL;

	//������ݣ����������׵�ַ
	virtual VOID Push(T* pMem)
	{
		m_Sequence.Lock();

		m_Map[pMem] = m_Sequence.Push(pMem);

		for (size_t i=0; i<ChannelCount; i++)
			if (m_Sequence.IsChannelEnabled(i))
				m_pEvent[i]->SetEvent();

		m_Sequence.Unlock();
	}

	//��ȡ���ݣ�ChannelID=ͨ��ID��dwTimeout=�ȴ�ʱ�������룩�����������׵�ַ
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

	//ͨ��ʹ�ܣ�ChannelID=ͨ���ţ�Enabled=ʹ�ܱ�־
	virtual void ChannelEnable(size_t ChannelID = 0, bool Enabled = true)
	{
		m_Sequence.Lock();
		m_Sequence.ChannelEnable(ChannelID, Enabled);
		m_Sequence.Unlock();
	}

	//�ж�ͨ���Ƿ�ʹ�ܣ�ChannelID=ͨ���ţ�ʹ�ܷ���true����ʹ�ܷ���false
	virtual bool IsChannelEnabled(size_t ChannelID = 0)
	{
		bool bEnabled = false;
		m_Sequence.Lock();
		bEnabled = m_Sequence.IsChannelEnabled(ChannelID);
		m_Sequence.Unlock();
		return bEnabled;
	}

	//�ж������Ƿ�Ϊ�գ�����ͨ��ID���շ���TRUE���ǿշ���FALSE
	virtual BOOL IsEmpty(size_t ChannelID = 0)
	{
		BOOL bEmpty = FALSE;
		m_Sequence.Lock();
		bEmpty = m_Sequence.IsEmpty(ChannelID);
		m_Sequence.Unlock();
		return bEmpty;
	}

	//��ȡ���и���������ͨ��ID���������и���
	virtual size_t Count(size_t ChannelID = 0)
	{
		size_t nCount = 0;
		m_Sequence.Lock();
		nCount = m_Sequence.Count(ChannelID);
		m_Sequence.Unlock();
		return nCount;
	}
};

//��̬����
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

//��̬����
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
