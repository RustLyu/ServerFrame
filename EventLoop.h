#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

// #include "Epoller.h"
class Epoller;
class Channel;
class EventLoop
{
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void updateChannel(Channel* channel);
private:
    Epoller* poller_;
};

#endif
