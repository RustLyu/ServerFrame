#include <iostream>
#include "Channel.h"
#include "EventLoop.h"

Channel::Channel(EventLoop* loop, int fd)
{
    loop_ = loop;
    fd_ = fd;
}

Channel::~Channel()
{
}

void Channel::handlEvent()
{
    switch(op_)
    {
        case EPOLLIN:
            {
                std::cout << "has msg to read" << std::endl;
                readCB_(fd_);
            }
            break;
        case EPOLLOUT:
            {
                std::cout << "has msg to write" << std::endl;
                writeCB_(fd_);
            }
            break;
        case EPOLLERR:
            {
                std::cout << "error invoke" << std::endl;
            }
            break;
        default:
            break;
    }
}

void Channel::update()
{
    loop_->updateChannel(this);
}
