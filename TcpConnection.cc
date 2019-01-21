#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

#include "TcpConnection.h"
#include "Log.h"

TcpConnection::TcpConnection(int fd, EventLoop* loop)
    :loop_(loop),
    fd_(fd),
    channel_(new Channel(loop, fd))
{
    channel_->setReadCallBack(boost::bind(&TcpConnection::handRead, this, _1));
    channel_->setWriteCallBack(boost::bind(&TcpConnection::handWrite, this, _1));
    channel_->enableRead();
}

TcpConnection::~TcpConnection()
{
    std::cout << "close fd:" << fd_ << std::endl;
    LOG("Close client fd:" + fd_);
    close(fd_);
}

void TcpConnection::handRead(int fd)
{
    // read msg from buffer 
    // call func
    LOG("TcpConnection msg read");
    char buf[1024];
    {
        int len = ::recv(fd, buf, 1024, 0);
        if(len > 0)
        {
            //std::cout << buf << std::endl;
            LOG(buf);
        }
        else
   {
            channel_->disableAll();
            LOG("Disconnect");
        }
    }
    // msgCb_(fd);
}

void TcpConnection::handWrite(int fd)
{
    // write msg 2 buffer
    // call
    LOG("TcpConnection msg write");
    // writeMsgCb_(fd);
}
