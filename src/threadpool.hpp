#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <deque>
#include <set>
#include <iostream>
#include "task.hpp"
#include "thread.hpp"

using namespace std;

typedef void *HANDLE;
const int STARTED = 0;
const int STOPPED = 1;

class CThreadPool
{
public:
	CThreadPool();
	CThreadPool(int poolSize);
	~CThreadPool();
	int Init();
	int Destroy();
	void* ExecuteThread();
	int AddTask(CTask* task);


private:
	int m_poolSize;
	unsigned int m_threadID;
	HANDLE m_handle;
	CRITICAL_SECTION m_csThreadPoolLock;
	CRITICAL_SECTION m_csTasksLock;
	//set<CThread *> m_threadPool;
	set<HANDLE> m_threadPool;
	set<HANDLE>::iterator m_threadPoolIter;
	deque<CTask *> m_tasks;
	volatile int m_poolState;
};

#endif