#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include "Epoller.h"


Epoller::Epoller(EventLoop* loop)
{
    ownerloop_ = loop;
    size_ = 10240;
    epollFd_ = epoll_create(size_);
    if(epollFd_ == -1)
    {
        std::cout << "create epoll failed!" << std::endl;
    }
}

Epoller::~Epoller()
{
    close(epollFd_);
}

void Epoller::updateChannel(Channel* channel)
{
    epoll_event ev;
    ev.data.fd = channel->getFd();
    ev.data.ptr = channel;
    ev.events = channel->getOp();//op->getOp();
    if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1) 
    {
        std::cout << "epoll_ctl: ADD FD: " << ev.data.fd <<  std::endl;
    }
}

void Epoller::enableRead(Channel* channel)
{
}

int Epoller::update(Channel* channel)
{
    epoll_event ev;
    ev.data.fd = channel->getFd();
    ev.data.ptr = channel;
    ev.events = channel->getOp();
    if (epoll_ctl(epollFd_, EPOLL_CTL_MOD, ev.data.fd, &ev) == -1) 
    {
        std::cout << "epoll_ctl: MODIFY FD: " << ev.data.fd <<  std::endl;
        return -1;
    }
    return 0;
}

void Epoller::poller(ChannelList* polllist)
{
    int timeout = 5;
    int count = epoll_wait(epollFd_, events_, EPOLL_FD_MAX, timeout);
}

void Epoller::fillActiveEvent()
{
}

// void Epoller::loop(int timeout)
// {
//     for(;;)
//     {
//         int count = epoll_wait(epollFd_, events_, EPOLL_FD_MAX, timeout);
//         for(int index = 0; index < count; ++index)
//         {
//             std::cout << "EPOLL EVENT INVOKE" << std::endl;
//             epoll_event ev = events_[index];
//             int fd = ev.data.fd;
//             switch(ev.events)
//             {
//                 case EPOLLIN:
//                     {
//                         std::cout << "EPOLLIN INVOKE" << std::endl;
//                         // new connect come in
//                         if(fd == serverFd_)
//                         { 
//                             int clientFd_ = 0;
//                             sockaddr_in client;
//                             //int clinetFd = accept(serverFD_, (sockaddr*)NULL, sizeof(sockaddr), 0);
//                             if((clientFd_ = accept(serverFd_, (struct sockaddr*)NULL, NULL)) == -1)
//                             {  
//                                 printf("accept socket error: %s(errno: %d)",strerror(errno),errno);  
//                                 continue;  
//                             } 
//                             newConnectCb_(clientFd_); 
//                             std::cout << "new client come in" << std::endl;
//                             add(fd, EPOLLIN);
//                         }
//                         // new msg come in
//                         else
//                         {
//                             msgCb_(fd);
//                         }
//                     }
//                     break;
//                 case EPOLLOUT:
//                     {
//                         std::cout << "EPOLLOUT INVOKE" << std::endl;
//                     }
//                     break;
//                 case EPOLLERR:
//                     {
//                         std::cout << "EPOLLERR INVOKE" << std::endl;
//                     }
//                     break;
//                 default:
//                     std::cout << "EPOLLE default INVOKE" << std::endl;
//                     break;
//             }
//         }
//     }
//     //return 0;
// }
