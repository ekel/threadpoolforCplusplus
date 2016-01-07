/*
 * ThreadMutex.cpp
 *
 *  Created on: 2016Äê1ÔÂ7ÈÕ
 *      Author: zhiteng.he
 */

#include "ThreadMutex.h"

ThreadMutex::ThreadMutex() {
    // TODO Auto-generated constructor stub
    pthread_mutex_init(&m_lock, NULL);
    is_locked = false;

}

ThreadMutex::~ThreadMutex() {
    // TODO Auto-generated destructor stub
    while(is_locked);
    Unlock();
    pthread_mutex_destroy(&m_lock);
}

void ThreadMutex::Lock()
{
    pthread_mutex_lock(&m_lock);
    is_locked = true;
}

void ThreadMutex::Unlock()
{
    pthread_mutex_unlock(&m_lock);
    is_locked = false;
}

pthread_mutex_t *ThreadMutex::GetMutexPtr()
{
    return &m_lock;
}
