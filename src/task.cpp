#include "task.hpp"


CTask::CTask()
{
	InitializeCriticalSection(&m_csTasksLock);
}


CTask::~CTask()
{
	DeleteCriticalSection(&m_csTasksLock);
}

unsigned int CTask::GetTaskSize()
{
	return m_tasks.size();
}

void CTask::AddTask(CWork *task)
{
	if (NULL != task)
		m_tasks.push_back(task);
}

CWork * CTask::GetTask()
{
	CWork *task = NULL;
	EnterCriticalSection(&m_csTasksLock);
	if (!m_tasks.empty())
	{
		task = m_tasks.front();
		m_tasks.pop_front();
	}
	LeaveCriticalSection(&m_csTasksLock);
    return task;
}