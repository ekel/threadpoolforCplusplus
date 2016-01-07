//============================================================================
// Name        : threadpool.cpp
// Author      : hzt
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "ThreadPool.h"


using namespace std;
int main(int argc, char* argv[])
{
	ThreadPool *p = new ThreadPool();

	int ret = p->Init();
	if (ret == -1)
    {
        cerr << "Failed to initialize thread pool!" << endl;
        return 0;
    }

	for (int i = 0; i < 4; i++)
	{
	    Task *task = new Task();
	    p->AddTask(task);
	}

	sleep(2);

	p->Destroy();

	delete p;

	return 0;
}
