#include <iostream>
#include "Channel.h"
#include "EventLoop.h"

Channel::Channel(EventLoop* loop, int fd)
{
    loop_ = loop;
    fd_ = fd;
    std::cout << "new Channel fd: " << fd << std::endl;
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
                std::cout << "Channel has msg to read:" << fd_ << std::endl;
                readCB_(fd_);
            }
            break;
        case EPOLLOUT:
            {
                std::cout << "has msg to write" << "||||"<< fd_ << std::endl;
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

void Channel::add2Loop()
{
    loop_->add2Loop(this);
}

void Channel::updateChannel()
{
    loop_->update(this);
}
