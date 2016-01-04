#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <windows.h>
#include <list>
#include "work.hpp"
using namespace std;

class CTask
{
public:
	CTask();
	~CTask();
	/**
	  获取任务列表中的任务，若任务列表为空，返回NULL
	**/
	CWork * GetTask();
	void AddTask(CWork *);
	unsigned int GetTaskSize();
private:
	list<CWork *> m_tasks;
	CRITICAL_SECTION m_csTasksLock;
};

#endif