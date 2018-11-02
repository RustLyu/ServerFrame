#include "TcpConnection.h"

TcpConnection::TcpConnection(int fd, EventLoop* loop)
    :loop_(loop),
    fd_(fd),
    channel_(new Channel(loop, fd))
{
    // loop_ = loop;
    // fd_ = fd;
    // channel_ = new Channel(loop_, fd_);
    channel_->setReadCallBack(boost::bind(&TcpConnection::handRead, this, _1));
    channel_->setWriteCallBack(boost::bind(&TcpConnection::handWrite, this, _1));
}

TcpConnection::~TcpConnection()
{
}

void TcpConnection::handRead(int fd)
{
    // read msg from buffer 
    // call func
    msgCb_(fd);
}

void TcpConnection::handWrite(int fd)
{
    // write msg 2 buffer
    // call
    writeMsgCb_(fd);
}
