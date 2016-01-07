/*
 * ThreadPool.h
 *
 *  Created on: 2016Äê1ÔÂ7ÈÕ
 *      Author: zhiteng.he
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <vector>
#include <deque>
#include <pthread.h>
#include <errno.h>
#include <string.h>

#include "Task.h"
#include "ThreadMutex.h"
#include "GlobalVar.h"

using namespace std;
class ThreadPool {
public:
    ThreadPool();
    ThreadPool(int size);
    ~ThreadPool();
    int AddTask(Task *task);
    int Init();
    int Destroy();
    void * Execute();


private:
    int m_pool_size;
    volatile int m_pool_status;
    vector<pthread_t> m_threads;
    deque<Task *> m_tasks;
    ThreadMutex m_mutex;
    pthread_cond_t m_cond;

};

#endif /* THREADPOOL_H_ */
