/*
 * ThreadMutex.h
 *
 *  Created on: 2016Äê1ÔÂ7ÈÕ
 *      Author: zhiteng.he
 */

#ifndef THREADMUTEX_H_
#define THREADMUTEX_H_

#include <pthread.h>

class ThreadMutex {
public:
    ThreadMutex();
    ~ThreadMutex();
    void Lock();
    void Unlock();
    pthread_mutex_t* GetMutexPtr();

private:
    pthread_mutex_t m_lock;
    volatile bool is_locked;
};

#endif /* THREADMUTEX_H_ */
