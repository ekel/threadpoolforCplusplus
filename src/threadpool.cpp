#include <process.h>
#include "threadpool.hpp"

const int DEFAULT_POOL_SIZE = 10;

//extern "C"
unsigned int __stdcall start_thread(void* arg)
{
  CThreadPool* tp = (CThreadPool*)arg;
  tp->ExecuteThread();
  return 0;
}

CThreadPool::CThreadPool()
	:m_poolSize(DEFAULT_POOL_SIZE), m_handle(NULL)
{
	InitializeCriticalSection(&m_csTasksLock);
	InitializeCriticalSection(&m_csThreadPoolLock);
	cout << "Constructed ThreadPool of size " << m_poolSize << endl;
}

CThreadPool::CThreadPool(int poolSize)
	:m_poolSize(poolSize), m_handle(NULL)
{
	InitializeCriticalSection(&m_csTasksLock);
	InitializeCriticalSection(&m_csThreadPoolLock);
	cout << "Constructed ThreadPool of size " << m_poolSize << endl;
}

CThreadPool::~CThreadPool()
{
	// Release resources
	DeleteCriticalSection(&m_csTasksLock);
	DeleteCriticalSection(&m_csThreadPoolLock);

	if (m_poolState != STOPPED) 
	{
		Destroy();
	}
}


int CThreadPool::Init()
{
	m_poolState = STARTED;
	for (int i = 0; i < m_poolSize; i++)
	{
		m_handle = (HANDLE)_beginthreadex(NULL, 0, start_thread, this, 0, &m_threadID);
		if (NULL == m_handle)
		{
			cerr<<"pthread_create() failed: " <<endl;
			return -1;
		}
		EnterCriticalSection(&m_csThreadPoolLock);
		m_threadPool.insert(m_handle);
		LeaveCriticalSection(&m_csThreadPoolLock);
	}
	cout << m_poolSize << " threads created by the thread pool" << endl;
	return 0;
}

int CThreadPool::AddTask(CTask* task)
{
	EnterCriticalSection(&m_csTasksLock);

	m_tasks.push_back(task);

	LeaveCriticalSection(&m_csTasksLock);
	
	return 0;

}


void* CThreadPool::ExecuteThread()
{
	CTask* task = NULL;
	cout << "Starting thread " << endl;

	while (true)
	{
		
		while ((m_poolState != STOPPED) && m_tasks.empty())
		{
			printf("--lock--\n");
		}
		EnterCriticalSection(&m_csTasksLock);
		// If the thread was woken up to notify process shutdown, return from here
		if (m_poolState == STOPPED) 
		{
			cout << "Unlocking and exiting: " << endl;
			LeaveCriticalSection(&m_csTasksLock);
			ExitThread(0);
		}

		if (!m_tasks.empty())
		{
			task = m_tasks.front();
			m_tasks.pop_front();
		}

		LeaveCriticalSection(&m_csTasksLock);
		// execute the task
		//(*task)();
		
		//delete task;
	}

	return NULL;
}


int CThreadPool::Destroy()
{
	EnterCriticalSection(&m_csTasksLock);
	m_poolState = STOPPED;
	LeaveCriticalSection(&m_csTasksLock);
	m_threadPoolIter = m_threadPool.begin();
	for (; m_threadPoolIter != m_threadPool.end(); m_threadPoolIter++)
	{

		::WaitForSingleObject(*m_threadPoolIter, INFINITE);
	}
	return 0;
}