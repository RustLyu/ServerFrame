#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "Msg.h"
#include "Server.h"
#include "Epoller.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include "EventLoopThread.h"

static void* recvMessage(void* arg)
{
    int* sock_fd = (int*)arg;
    char buf[MAX_RECV_BUFFER_SIZE];
    for(;;)
    {
        int len = ::recv(*sock_fd, buf, MAX_RECV_BUFFER_SIZE, 0);
        if(len == 0)
        {
            std::cout << "client disconnect: " << *sock_fd << std::endl;
            close(*sock_fd);
            break;
        }
        else if(len > 0)
        {
            std::cout << "recv client msg" << std::endl;
            std::string str(buf);
            std::cout << str << std::endl;
        }
    }
}

//
Server::Server(std::string ip, int port)
{
    serverFd_ = socket(AF_INET, SOCK_STREAM, 0);
     //memset(&serverAddr_, 0, sizeof(serverAddr_));  
     //serverAddr_.sin_family = AF_INET;  
     //serverAddr_.sin_addr.s_addr = htonl(0);
     //serverAddr_.sin_port = htons(port);
     //bool bReuseaddr = true;
     //setsockopt(serverFd_,SOL_SOCKET ,SO_REUSEADDR,(const char*)&bReuseaddr,sizeof(bool));
     //if(bind(serverFd_, (struct sockaddr*)(&serverAddr_), sizeof(serverAddr_)) == -1)
     //{
     //    std::cout << "bind error" << std::endl;
     //}
     //if(listen(serverFd_, 100) == -1)
     //{
     //    std::cout << "listen error" << std::endl;
     //}
}

void Server::begin()
{
    memset(&serverAddr_, 0, sizeof(serverAddr_));  
    serverAddr_.sin_family = AF_INET;  
    serverAddr_.sin_addr.s_addr = htonl(0);
    serverAddr_.sin_port = htons(6066);
    bool bReuseaddr = true;
    setsockopt(serverFd_,SOL_SOCKET ,SO_REUSEADDR,(const char*)&bReuseaddr,sizeof(bool));
    if(bind(serverFd_, (struct sockaddr*)(&serverAddr_), sizeof(serverAddr_)) == -1)
    {
        std::cout << "bind error" << std::endl;
    }
    if(listen(serverFd_, 100) == -1)
    {
        std::cout << "listen error" << std::endl;
    }
    std::cout << "liten success" << std::endl;

}

void Server::run()
{
    std::cout << "run...." << std::endl;
    for(;;)
    {
        std::cout << "wait...." << std::endl;
        clientFd_ = 0;// = accept(server_fd, (struct sockaddr*)(&clientAddr), NULL);
        if((clientFd_ = accept(serverFd_, (struct sockaddr*)NULL, NULL)) == -1)
        {  
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);  
            continue;  
        }  
        std::cout << "new client come in:" << clientFd_ << std::endl;
        // char buf[4096];
        RequestLoginCmd_CS msg;
        char lsk[] = "looksmart";
        memcpy(msg.name, lsk, sizeof(lsk));
        msg.time = 20181017;
        // memcpy(buf,&msg,sizeof(msg));

        // int len_send = send(client_fd, buf, sizeof(msg),0);  
        sendToMe(msg, clientFd_);
        {
            pthread_t tid;
            if(pthread_create(&tid, NULL, recvMessage, (void* )&clientFd_) == -1)
            {
                std::cout << "create pthread errot" << std::endl;
            }
            pthread_detach(tid);
        }
    }
}

void Server::messageCallFunc(int sock_fd)
{
    // int* sock_fd = (int*)arg;
    char buf[MAX_RECV_BUFFER_SIZE];
    for(;;)
    {
        int len = ::recv(sock_fd, buf, MAX_RECV_BUFFER_SIZE, 0);
        if(len == 0)
        {
            std::cout << "client disconnect: " << sock_fd << std::endl;
            close(sock_fd);
            break;
        }
        else if(len > 0)
        {
            std::cout << "recv client msg" << std::endl;
            std::string str(buf);
            std::cout << str << std::endl;
        }
    }
}

void Server::newConnectCallFunc(int sock_fd)
{
    // // TODO new TcpConnection
    // // int* sock_fd = (int*)arg;
    // std::cout << "new client come in:" << sock_fd << std::endl;
    // // char buf[4096];
    // RequestLoginCmd_CS msg;
    // char lsk[] = "looksmart";
    // memcpy(msg.name, lsk, sizeof(lsk));
    // msg.time = 20181017;

    // sendToMe(msg, sock_fd);
    // EventLoop* ioLoop = new EventLoop();//threadPool_->getNextLoop();
    EventLoopThread* loop_ = new EventLoopThread();
    EventLoop* ioLoop = loop_->startLoop();
    //char buf[64];
    // string connName = name_ + buf;

    // FIXME poll with zero timeout to double confirm the new connection
    //   // FIXME use make_shared if necessary
    std::cout << "recv  fd: " << sock_fd << std::endl;
    //TcpConnectionPtr conn(new TcpConnection(sock_fd, ioLoop));
    TcpConnection* conn = new TcpConnection(sock_fd, ioLoop);
    conn->setConnectCallBack(connectCb_);
    conn->setReadCallBack(msgCb_);
    conn->setWriteCallBack(writeMsgCb_);
    conn->setCloseCallback(
            boost::bind(&Server::removeConnection, this, _1)); // FIXME: unsafe
    // ioLoop->loop();
    // ioLoop->runInLoop(boost::bind(&TcpConnection::connectEstablished, conn));
}

void Server::removeConnection(int sockfd)
{
    close(sockfd);
}

Server::~Server()
{
    close(serverFd_);
}

static void* creatServerInstance(void* args)
{
    Server* server = new Server("*", 6066);
    std::cout << "start...." << std::endl;
    EventLoopThread* loop_ = new EventLoopThread();
    EventLoop* eloop = loop_->startLoop();
    std::cout << "start loop...." << std::endl;
    std::cout << server->getSocketFd() << std::endl;
    Acceptor* accept_ = new Acceptor(eloop, server->getSocketFd());
    accept_->setNewConnectCallBack(boost::bind(&Server::newConnectCallFunc, server, _1));
    server->begin();
    for(;;)
    {}
    //Channel* acceptC_ = new Channel(loop_, server->getSocketFd());
    //acceptC_->update();
    //Epoller* poller = new Epoller(loop);
    //poller->add(server->getSocketFd(), EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLHUP);
    //poller->setNewConnectCallBack(boost::bind(&Server::newConnectCallFunc, server, _1));
    //poller->setMessageCallBack(boost::bind(&Server::messageCallFunc, server, _1));
    // server->run();
    // loop_->loop();
}

int main()
{
    pthread_t tid;
    if(pthread_create(&tid, NULL, creatServerInstance, NULL) == -1)
    {
        std::cout << "creat pthread error";
        return -1;
    }
    if(pthread_join(tid, NULL))
    {
        std::cout << "pthread not exit";
        return -2;
    }
}
