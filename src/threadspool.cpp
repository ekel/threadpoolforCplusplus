// threadspool.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include "stdafx.h"
#include "threadpool.hpp"

const int MAX_TASKS = 4;

int main(int argc, char** argv)
{
	CThreadPool tp(2);
	int ret = tp.Init();
	if (ret == -1) 
	{
		cerr << "Failed to initialize thread pool!" << endl;
		return 0;
	}

	for (int i = 0; i < MAX_TASKS; i++) 
	{
		
		CTask* t = new CTask();
		tp.AddTask(t);
	}

	tp.Destroy();
	return 0;
}

