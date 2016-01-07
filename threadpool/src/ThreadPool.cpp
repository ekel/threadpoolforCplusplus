/*
 * ThreadPool.cpp
 *
 *  Created on: 2016年1月7日
 *      Author: zhiteng.he
 */
#include <iostream>

#include "ThreadPool.h"
using namespace std;

extern "C"
void* start_thread(void* arg)
{
    ThreadPool *tp = (ThreadPool *)arg;
    tp->Execute();
    return NULL;
}


ThreadPool::ThreadPool()
:m_pool_size(POOL_SIZE)
{
    // TODO Auto-generated constructor stub
    pthread_cond_init(&m_cond, NULL);
    cout << "Constructed ThreadPool of size " << m_pool_size << endl;
}

ThreadPool::ThreadPool(int size)
:m_pool_size(size)
{
    pthread_cond_init(&m_cond, NULL);
    cout << "Constructed ThreadPool of size " << m_pool_size << endl;
}

ThreadPool::~ThreadPool()
{
    // TODO Auto-generated destructor stub
    if (m_pool_status != STOPED)
        Destroy();

    pthread_cond_destroy(&m_cond);
}

int ThreadPool::Init()
{
    m_pool_status = STARTED;
    int ret = -1;
    for (int i = 0; i < m_pool_size; i++)
    {
        pthread_t tid;
        ret = pthread_create(&tid, NULL, start_thread, (void *)this);
        if (ret != 0)
        {
            cout<<"create thread failed return code:"<<ret<<endl;
            return -1;
        }
        m_threads.push_back(tid);
    }
    cout<<m_pool_size<<" thread(s) created"<<endl;
    return 0;
}

int ThreadPool::AddTask(Task *task)
{
    m_mutex.Lock();
    m_tasks.push_back(task);
    pthread_cond_signal(&m_cond);
    m_mutex.Unlock();
    return 0;
}

void * ThreadPool::Execute()
{
    Task *task = NULL;
    cout << "Starting thread " << pthread_self() << endl;

    while(true)
    {
        // Try to pick a task
        cout <<"Locking thread: "<<pthread_self()<<endl;
        m_mutex.Lock();
        while (m_pool_status != STOPED && m_tasks.empty())
        {
            cout << "Unlocking and waiting... thread id: " << pthread_self() << endl;
            pthread_cond_wait(&m_cond, m_mutex.GetMutexPtr());
            cout << "get Signal and then locking: " << pthread_self() << endl;
        }

        // If the thread was woken up to notify process shutdown, return from here
        if (m_pool_status == STOPED)
        {
            m_mutex.Unlock();
            pthread_exit(NULL);
        }

        task = m_tasks.front();
        m_tasks.pop_front();
        m_mutex.Unlock();
        cout << "Unlocking thread id: " << pthread_self() << endl;

        if (task != NULL)
        {
            task->Run();
        }
        cout << "Unlocking: " << pthread_self() << endl;
        delete task;
    }
    return NULL;
}

int ThreadPool::Destroy()
{
    m_mutex.Lock();
    m_pool_status = STOPED;
    m_mutex.Unlock();

    cout << "Broadcasting STOP signal to all threads..." << endl;
    // 唤醒全部线程
    pthread_cond_broadcast(&m_cond);// notify all threads we are shutted down

    int ret = -1;
    for (int i = 0; i < m_pool_size; i++)
    {
        void* result;
        ret = pthread_join(m_threads[i], &result);
        cout << "pthread_join() returned " << ret << ": " << strerror(errno) << endl;
        pthread_cond_broadcast(&m_cond);
    }
    cout << m_pool_size << " threads exited from the thread pool" << endl;
    return 0;
}
