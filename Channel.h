#ifndef CHANNEL_H
#define CHANNEL_H

#include <sys/epoll.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>


typedef boost::function<void (int)> ReadCallBack;
typedef boost::function<void (int)> WriteCallBack;

class EventLoop;
// manage epoll invoke event
class Channel
{
public:
    Channel(EventLoop* loop, int fd);
    ~Channel();
    void handlEvent();
    void enableRead(Channel* channel)
    {op_ |= EPOLLIN; update();};
    void update();
    void setReadCallBack(const ReadCallBack& cb)
    {readCB_ = cb;}
    void setWriteCallBack(const WriteCallBack& cb)
    {writeCB_ = cb;}
    int getFd()
    {return fd_;}
    int getOp()
    {return op_;}
private:
    int fd_;
    EventLoop* loop_;
    ReadCallBack readCB_;
    WriteCallBack writeCB_;
    int op_;
};

#endif
