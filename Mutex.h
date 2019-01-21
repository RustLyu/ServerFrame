#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex
{
    public:
        Mutex()
        {
            pthread_mutex_init(&lock_, NULL);
        }
        ~Mutex()
        {
            pthread_mutex_destroy(&lock_);
        }

        pthread_mutex_t* getMutex()
        {
            return & lock_;
        }
    private:
        pthread_mutex_t lock_;
};

class MutexLockGuide
{
    public:
        MutexLockGuide(Mutex& mutex):
            mutex_(mutex)
        {
            pthread_mutex_lock(mutex_.getMutex());
        }
        ~MutexLockGuide()
        {
            pthread_mutex_unlock(mutex_.getMutex());
        }
    private:
        Mutex mutex_;
};

#endif // MUTEX_H
