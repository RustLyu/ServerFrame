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
    void setQuit(bool status)
    { quit_ = status; }
private:
    Epoller* poller_;
    bool quit_;
};

#endif
