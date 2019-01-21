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
    void add2Loop(Channel* channel);
    void update(Channel* channel);
private:
    Epoller* poller_;
    int a_;
};

#endif
