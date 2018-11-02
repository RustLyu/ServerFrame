#include "EventLoop.h"
#include "Epoller.h"
#include "Channel.h"

EventLoop::EventLoop()
{
    poller_ = new Epoller(this);
}

EventLoop::~EventLoop()
{}

void EventLoop::loop()
{
    for(;;)
    {
        ChannelList event;
        poller_->poller(&event);
        for(auto it : event)        
        {
            // Channel* channel = static_cast<Channel*>(it.data.ptr);
            it->handlEvent();
        }
    }
}

void EventLoop::updateChannel(Channel* channel)
{
    poller_->enableRead(channel);
}
