#ifndef EVENTLOOP_THREAD_POOL_H
#define EVENTLOOP_THREAD_POOL_H

#include <vector>
#include <boost/noncopyable.hpp>
#include "EventLoopThread.h"

class EventLoopThreadPool:boost::noncopyable
{
    public:
        EventLoopThreadPool();
        ~EventLoopThreadPool();
        bool setThreadNum(int num)
        {
            if(num < 0)
            {
                return false;
            }
            threadNum_ = num;
        }
        void start();
        EventLoop* getNextLoop();
    private:
        int threadNum_;
        std::vector<EventLoopThread*> threadVec_;
        std::vector<EventLoop*> loopVec_;
        int useIndex_;
};

#endif // EVENTLOOP_THREAD_POOL_H
