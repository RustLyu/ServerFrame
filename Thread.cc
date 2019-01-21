#include <pthread.h>
#include <map>
#include <boost/function.hpp>
#include <iostream>

#include "Thread.h"

struct ThreadData
{
    ThreadCB call_;
    ThreadData(const ThreadCB& call)
    {
        call_ = call;
    }

    void run()
    {
        call_();
    }
};

void* startThread(void* obj)
{
      ThreadData* data = static_cast<ThreadData*>(obj);
      data->run();
      delete data;
      return NULL;
}

Thread::Thread(ThreadCB call, void* args)
{
    call_ = call;
}

Thread:: ~Thread()
{
    pthread_join(tid_, NULL);
}

pthread_t Thread::getTid()
{
    return tid_;
}

void Thread::start()
{
    ThreadData* data = new ThreadData(call_);
    if(pthread_create(&tid_, NULL, startThread, data) != 0)
    {
        std::cout << "create thread error" << std::endl;
    }
    std::cout << "create thread OK" << std::endl;
}
