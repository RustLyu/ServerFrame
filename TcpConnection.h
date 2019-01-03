#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <boost/scoped_ptr.hpp>
#include <boost/any.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include "Channel.h"
#include "EventLoop.h"
#include "CallBack.h"

class TcpConnection:boost::noncopyable,
    public boost::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(int fd, EventLoop* loop);
    ~TcpConnection();
    void setReadCallBack(const MessageCallBack& cb)
    { 
        msgCb_ = cb; 
    }
    void setWriteCallBack(const WriteMessageCallBack& cb)
    {
        writeMsgCb_ = cb; 
    }
    void setConnectCallBack(const NewConnectCallBack& cb)
    {
        connectCb_ = cb; 
    }
    void setCloseCallback(const RemoveConnectCallBack& cb)
    {
        removecb_ = cb;
    }
    void handRead(int fd);
    void handWrite(int fd);
private:
    int fd_;
    boost::scoped_ptr<Channel> channel_;
    EventLoop* loop_;
    MessageCallBack msgCb_;
    WriteMessageCallBack writeMsgCb_;
    NewConnectCallBack connectCb_;
    RemoveConnectCallBack removecb_;
};

typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;

#endif
