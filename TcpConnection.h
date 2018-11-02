#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <boost/scoped_ptr.hpp>

#include "Channel.h"
#include "EventLoop.h"
#include "CallBack.h"

class TcpConnection
{
public:
    TcpConnection(int fd, EventLoop* loop);
    ~TcpConnection();
    void setReadCallBack(MessageCallBack& cb)
    { msgCb_ = cb; }
    void setWriteCallBack(WriteMessageCallBack& cb)
    { writeMsgCb_ = cb; }
    void setnewConnectCallBack(NewConnectCallBack& cb)
    { newConnectCb_ = cb; }
    void handRead(int fd);
    void handWrite(int fd);
private:
    int fd_;
    boost::scoped_ptr<Channel> channel_;
    EventLoop* loop_;
    MessageCallBack msgCb_;
    WriteMessageCallBack writeMsgCb_;
    NewConnectCallBack newConnectCb_;
};

#endif
