#ifndef THREAD_H
#define THREAD_H

#include "CallBack.h"


class Thread
{
    public:
        Thread(ThreadCB call, void* args);
        ~Thread();
        pthread_t getTid();
        void start();
    private:
        pthread_t tid_;
    public:
        ThreadCB call_;
};


#endif
