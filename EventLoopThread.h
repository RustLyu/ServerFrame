#ifndef EVENT_LOOP_THREAD_H
#define EVENT_LOOP_THREAD_H

#include "Mutex.h"
#include "Condition.h"

class Thread;
class EventLoop;
class Mutex;

class EventLoopThread
{
    public:
        EventLoopThread();
        ~EventLoopThread();
        EventLoop* startLoop();
    private:
        void callFunc();
    private:
       Thread* thread_;
       EventLoop* loop_;
       Mutex mutex_;
       Condition cond_;
};

#endif // EVENT_LOOP_THREAD_H
