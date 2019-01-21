#include <iostream>
#include <thread>

#include "Log.h"
#include "EventLoopThread.h"
#include "Thread.h"
#include "EventLoop.h"


EventLoopThread::EventLoopThread()
{
    thread_ = new Thread(boost::bind(&EventLoopThread::callFunc, this), nullptr);
    loop_ = nullptr;
}

EventLoopThread::~EventLoopThread()
{}

EventLoop* EventLoopThread::startLoop()
{
    thread_->start();
    MutexLockGuide lock(mutex_);
    while(loop_ == nullptr)
    {
        //std::cout << "wait signal" << std::endl;
        std::thread::id tid = std::this_thread::get_id();
        cond_.wait();
    }

    // std::cout << "signal recv" << std::endl;
    return loop_;
}

void EventLoopThread::callFunc()
{
    EventLoop loop;
    {
        MutexLockGuide lock(mutex_);
        loop_ = &loop;
        cond_.signal();
        //loop_ = nullptr;
    }
    std::thread::id tid = std::this_thread::get_id();

    //std::cout << "start loop" << std::endl;
    LOG("new thread start loop");
    loop.loop();
    loop_ = nullptr;
}
