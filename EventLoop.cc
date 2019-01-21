#include <iostream>
#include "EventLoop.h"
#include "Epoller.h"
#include "Channel.h"

EventLoop::EventLoop()
{
    quit_ = false;
    poller_ = new Epoller(this);
}

EventLoop::~EventLoop()
{
    delete poller_;
}

void EventLoop::loop()
{
    while(!quit_)
    {
        // std::cout << "index: " << a_ << std::endl;
        ChannelList event;
        poller_->poller(&event);
        for(auto it : event)        
        {
            it->handlEvent();
        }
    }
}

void EventLoop::add2Loop(Channel* channel)
{
    poller_->add2Loop(channel);
}

void EventLoop::update(Channel* channel)
{
    poller_->update(channel);
}
