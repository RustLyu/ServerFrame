#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Client
{
public:
    Client();
    ~Client();
    void run();
private:
    int my_fd;
    struct sockaddr_in my_sock, server_sock;
};

#endif
