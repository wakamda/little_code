#ifndef _LOCK_H_
#define _LOCK_H_

#include <pthread.h>

class DataLock
{
public:
    DataLock();
    ~DataLock();

    int Lock();

    int Unlock();

    int Wait();

    int TimedWait(int second);

    int Signal();

    int Broadcast();

private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};

#endif
