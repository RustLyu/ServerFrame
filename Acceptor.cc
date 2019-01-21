#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

#include "Acceptor.h"
#include "EventLoop.h"
#include "Channel.h"
#include "Log.h"


Acceptor::Acceptor(EventLoop* loop, int fd):
    loop_(loop),
    fd_(fd),
    channel_(new Channel(loop, fd))
{
    channel_->enableRead();
    channel_->setReadCallBack(boost::bind(&Acceptor::handleRead, this));
}

Acceptor::~Acceptor()
{
}

void Acceptor::handleRead()
{
    int clientFD = accept(fd_, (struct sockaddr*)NULL, NULL);
    if(clientFD > 0)
    {
        if(cb_)
        {
            //std::cout << "Acceptor new client " << clientFD << std::endl;
            LOG("Acceptor Recv new Client" + std::to_string(clientFD));
            cb_(clientFD);
        }
        else
        {
            close(clientFD);
        }
    }
    else
    {
        //std::cout << "error" << std::endl;
    }
}
