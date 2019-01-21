#ifndef CONDITION_H
#define CONDITION_H

#include <pthread.h>
#include "Mutex.h"

class Condition
{
    public:
    Condition()
    {
        pthread_cond_init(&cond_, NULL);
    }
    ~Condition()
    {
        pthread_cond_destroy(&cond_);
    }
    void signal()
    {
        MutexLockGuide lock(lock_);   
        pthread_cond_signal(&cond_);
    }

    void wait()
    {
        pthread_cond_wait(&cond_, lock_.getMutex());
    }
    private:
    pthread_cond_t cond_;
    Mutex lock_;
};

#endif // CONDITION_H
