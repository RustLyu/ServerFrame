#include <iostream>
#include "EventLoop.h"
#include "Epoller.h"
#include "Channel.h"

int a = 0;
EventLoop::EventLoop()
{
    a += 1;
    a_ = a;
    poller_ = new Epoller(this);
}

EventLoop::~EventLoop()
{}

void EventLoop::loop()
{
    for(;;)
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
