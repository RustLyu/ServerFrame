#include <iostream>
#include "Channel.h"
#include "EventLoop.h"
#include "Log.h"

Channel::Channel(EventLoop* loop, int fd)
{
    loop_ = loop;
    fd_ = fd;
    // std::cout << "new Channel fd: " << fd << std::endl;
    LOG("new Channel fd:" + std::to_string(fd));
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
                LOG("Channel has msg to read:" + std::to_string(fd_));
                readCB_(fd_);
            }
            break;
        case EPOLLOUT:
            {
                // LOG("has msg to write:" + fd_);
                writeCB_(fd_);
            }
            break;
        case EPOLLERR:
            {
                // std::cout << "error invoke" << std::endl;
                ERROR("EPOLL ERROR INVOKE");
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
