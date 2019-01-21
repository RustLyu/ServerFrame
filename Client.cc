#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "Msg.h"
#include "Client.h"

Client::Client()
{
    my_fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server_sock, 0, sizeof(server_sock));  
    server_sock.sin_family = AF_INET;  
    server_sock.sin_port = htons(6066);
}

void Client::run()
{
    char buf[MAX_RECV_BUFFER_SIZE];
    memset(buf, 0 , MAX_RECV_BUFFER_SIZE);
    std::cout << "try connect server" << std::endl;;
    int ret = 0;
    if(ret = connect(my_fd, (struct sockaddr*)(&server_sock), sizeof(server_sock)) != -1)
    {
        std::cout << "connect server success" << std::endl;
        std::string kk = "1111111111222222222222222";
        int sendlen = send(my_fd, kk.c_str(), sizeof(kk), 0);
        std::cout << sendlen << std::endl;
        for(;;)
        {
            // TODO 消息拆包,合包
            int len = recv(my_fd, buf, MAX_RECV_BUFFER_SIZE, 0);
            if(len > 0)
            {
                // bool isMsg = xxx; // 根据缓冲区数据判断
                //while(isMsg)
                {
                    PMsg* msg = (PMsg*)buf;
                    std::cout << "cmd: " << msg->cmd << std::endl;
                    std::cout << "recv length: " << len << std::endl;
                    std::cout << "length: " << msg->size << std::endl;
                    if(msg->cmd == REQUEST_LOGIN_CMD)
                    {
                        RequestLoginCmd_CS* pUser = (RequestLoginCmd_CS*)(msg->ptr);
                        std::cout << pUser->name << std::endl;
                        std::cout << pUser->time << std::endl;
                        int len = send(my_fd, "hello world", sizeof("hello world"), 0);
                        std::cout << len << std::endl;
                    }
                    // isMsg = xxx  // 根据缓冲区判断
                }
            }
            else if(len == 0)
            {
                std::cout << "disconnect" << std::endl;
                return;
            }
        }
    }
    std::cout << ret << std::endl;
}

Client::~Client()
{
    close(my_fd);
}

static void* creatClientInstance(void *arg)
{
    Client* client = new Client();
    client->run();
}

int main()
{
    pthread_t tidp;

    if ((pthread_create(&tidp, NULL, creatClientInstance, NULL)) == -1)
    {
        std::cout << "create error!";
        return 1;
    }
    
    if (pthread_join(tidp, NULL))                  
    {
        std::cout << "thread is not exit...";
        return -2;
    }
}
