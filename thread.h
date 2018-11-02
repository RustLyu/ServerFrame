#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <map>
#include <boost/function.h>

// typedef CALLBACK void*()
typedef boost::function<void()> CALLBACK;

class Thread
{
public:
    Thread(CALLBACK call, void* args)
    {
        call_ = call;
        pthread_create(tid_, NULL, call_, (void*)arg);
    }

    ~Thread()
    {
        pthread_exit(tid_);
    }

    int join()
    {
        if(pthread_join(tid_, NULL) == 0)
        {
            return 0;
        }
        else
        {
            std::cout << "thread start error: " << tid_ <<std::endl;
        }
    }

    static pthread_t CreatThread(CALLBACK call, void* args)
    {
        Thread* thread = new Thread(call, args); 
        threadMap[thread.tid_] = thread;
        return thread.tid_;
    }
    
    // remove thread from map and delete this object 
    static bool DeleteThread(pthread_t tid)
    {
        // TODO if not exist
        delete threadMap[tid];
        return true;
    }

    pthread_t getTid()
    {
        return tid_;
    }

    static std::map<pthread_t, Thread*> threadMap;
private:
    pthread_t tid_;
    CALLBACK call_;

};

class ThreadPool
{
};

#endif
