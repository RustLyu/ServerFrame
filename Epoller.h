#ifndef EPOLLER_H
#define EPOLLER_H

#include <stdio.h>
#include <sys/epoll.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <vector>

#include "CallBack.h"
// #include "EventLoop.h"
// #include "Channel.h"

class EventLoop;
class Channel;

#define EPOLL_FD_MAX 10240


class Epoller
{
public:
    Epoller(EventLoop* loop);
    ~Epoller();
    void updateChannel(Channel* channel);
    int update(Channel* channel);
    // void loop(int timeout);
   //  void setMessageCallBack(const MessageCallBack& call)
   //  {msgCb_ = call;}
   //  void setNewConnectCallBack(const NewConnectCallBack& call)
   //  {newConnectCb_ = call;}
    void poller(ChannelList* polllist);
    void enableRead(Channel* channel);
    void fillActiveEvent();
private:
    int epollFd_;
    int size_;
    // int serverFd_;
    epoll_event events_[EPOLL_FD_MAX];
    EventLoop* ownerloop_;
    // MessageCallBack msgCb_;
    // NewConnectCallBack newConnectCb_;
};

#endif
