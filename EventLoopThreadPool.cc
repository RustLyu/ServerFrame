#include "EventLoopThreadPool.h"

EventLoopThreadPool::EventLoopThreadPool()
{
    useIndex_ = 0;
}

EventLoopThreadPool::~EventLoopThreadPool()
{}

void EventLoopThreadPool::start()
{
    for(int i = 0; i < threadNum_; ++i)
    {
        EventLoopThread* loop = new EventLoopThread();
        threadVec_.push_back(loop);
        loopVec_.push_back(loop->startLoop());
    }
}

EventLoop* EventLoopThreadPool::getNextLoop()
{
    if(useIndex_ >= threadNum_)
    {
        return nullptr;
    }
    EventLoop* loop = loopVec_[useIndex_];
    useIndex_ += 1;
    return loop;
}

