#include"lock.h"

DataLock::DataLock()
{
    pthread_mutex_init(&m_mutex, NULL);
    pthread_cond_init(&m_cond, NULL);
}

DataLock::~DataLock()
{
    pthread_mutex_destroy(&m_mutex);
    pthread_cond_destroy(&m_cond);
}

int DataLock::Lock()
{
    return pthread_mutex_lock(&m_mutex);
}

int DataLock::Unlock()
{
    return pthread_mutex_unlock(&m_mutex);
}

int DataLock::Wait()
{
    return pthread_cond_wait(&m_cond, &m_mutex);
}

int DataLock::TimedWait(int second)
{
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += second;
    return pthread_cond_timedwait(&m_cond, &m_mutex, &abstime);
}

int DataLock::Signal()
{
    return pthread_cond_signal(&m_cond);
}

int DataLock::Broadcast()
{
    return pthread_cond_broadcast(&m_cond);
}
