#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <map>

#include "Msg.h"
#include "EventLoop.h"
#include "Channel.h"
#include "CallBack.h"

union test
{
    int m;
    char msg[4];
};

template<typename T>
void sendToMe(T &t, int dst_fd)
{
    PMsg msg;
    msg.cmd = t.cmd;
    msg.size = sizeof(msg);
    memcpy(msg.ptr, &t, sizeof(t));
    char buf[MAX_RECV_BUFFER_SIZE];
    char bufSend[MAX_RECV_BUFFER_SIZE];
    // TODO 缓冲区放不下? buf.size >= (sizeof(msg) + 5)
    memcpy(buf, &msg, sizeof(msg));
    if((sizeof(msg) + 5) < MAX_RECV_BUFFER_SIZE)
    {
        // char* cmd = itoa(msg.size);
        char cmd[5];
        test t1;
        t1.m = 276;
        // itoa(msg.size, cmd, 4);
        sscanf(cmd, "%d", &msg.size);
        for(int i = 0; i < 4; ++i)
        {
            std::cout << t1.msg[i] << std::endl;
        }
        strcpy(bufSend, buf);
        strcpy(bufSend, cmd);
    }
    int len = send(dst_fd, buf, sizeof(msg), 0);
    std::cout << "send success length: " << len << std::endl;
}

class Server
{
    public:
        Server(std::string ip, int port);
        ~Server();
        void run();
        int getSocketFd()
        {
            return serverFd_;
        }
        void setReadCallBack(MessageCallBack& cb)
        { 
            msgCb_ = cb; 
        }
        void setWriteCallBack(WriteMessageCallBack& cb)
        {
            writeMsgCb_ = cb; 
        }
        void setConnectCallBack(NewConnectCallBack& cb)
        {
            connectCb_ = cb; 
        }
        void messageCallFunc(int args);
        void newConnectCallFunc(int args);
    public: 
        void begin();
    private:
        void removeConnection(int sockfd);
    private:
        int serverFd_, clientFd_;
        sockaddr_in serverAddr_, clientAddr_;
        std::map<int, int> userMap_;
        Channel* channel_;
        EventLoop* loop_;
        MessageCallBack msgCb_;
        WriteMessageCallBack writeMsgCb_;
        NewConnectCallBack connectCb_;
};

#endif
