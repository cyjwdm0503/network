/************************************************************************/
/* 
一写多读的队列
*/
/************************************************************************/

#ifndef LOCKQUEUE_H
#define LOCKQUEUE_H

#include "Mutex.h"
#include "MutexGuard.h"
#include "Semaphore.h"

template<typename T>
class CLockQueue
{
public:
	CLockQueue(int size);
	~CLockQueue();
	void AddValue(T& value);
	bool GetValue(T& value);
	bool TryGetValue(T& value);

protected:
	virtual void AddValueIn(T& value) =0;
	virtual bool GetValueIn(T& value) =0;
	virtual bool TryGetValueIn(T& value) =0;
private:
	CMutex m_mtx;
	CSemaphore m_sem;
	int m_avliableSize;
	int m_usedSize;

};




template<typename T>
bool CLockQueue<T>::GetValue( T& value )
{
	
	m_sem.Lock();
	m_mtx.Lock();
	m_avliableSize--;
	m_usedSize++;
	bool flag = GetValue(value);
	m_mtx.UnLock();

	
}

template<typename T>
bool CLockQueue<T>::TryGetValue( T& value )
{
	if(m_sem.TryLock() == false)
		return false;
	m_mtx.Lock();
	m_avliableSize--;
	m_usedSize++;
	bool flag = GetValue(value);
	m_mtx.UnLock();
}

template<typename T>
void CLockQueue<T>::AddValue( T& value )
{
	m_mtx.Lock();
	m_avliableSize++;
	m_usedSize--;
	bool flag =  AddValue(value);
	m_mtx.UnLock();
	m_sem.UnLock();
}

template<typename T>
CLockQueue<T>::~CLockQueue()
{
	;
}

template<typename T>
CLockQueue<T>::CLockQueue( int size ):m_avliableSize(size),m_usedSize(0),m_sem(size):
{
}

#endif 