#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "CallBack.h"

class EventLoop;
class Channel;

class Acceptor
{
public:
    explicit Acceptor(EventLoop* loop, int fd);
    ~Acceptor();
    void setNewConnectCallBack(const NewConnectCallBack& cb)
    {
        cb_ = cb;
    }
private:
    void handleRead();
private:
    EventLoop* loop_;
    int fd_;
    Channel* channel_;
    NewConnectCallBack cb_;
};

#endif // ACCEPTOR_H
