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
        void enableRead()
        {
            op_ |= EPOLLIN;
            op_ |= EPOLLPRI;
            add2Loop();
        }
        void add2Loop();
        void updateChannel();
        void setReadCallBack(const ReadCallBack& cb)
        {
            readCB_ = cb;
        }
        void setWriteCallBack(const WriteCallBack& cb)
        {
            writeCB_ = cb;
        }
        int getFd()
        {
            return fd_;
        }
        int getOp()
        {
            return op_;
        }
        void setEvent(int event)
        {
            op_ = event;
        }
        void disableAll()
        {
            op_ = 0;
            updateChannel();
        }
    private:
        int fd_;
        EventLoop* loop_;
        ReadCallBack readCB_;
        WriteCallBack writeCB_;
        int op_;
};

#endif
