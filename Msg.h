#ifndef MSG_H
#define MSG_H
#include <iostream>
#include <string.h>

#define MAX_CHAR_LENGTH 1024
#define MAX_BUFFER_SIZE 4096
#define MAX_RECV_BUFFER_SIZE 8192

#define bzero(v, s) memset(v, 0, s)

struct PMsg
{
    PMsg()
    {
        cmd = 0; // 消息头索引值
        size = 0; // 消息长度
        bzero(ptr, MAX_BUFFER_SIZE); // 消息内容
    }
    int cmd;
    int size;
    char ptr[MAX_BUFFER_SIZE];
};

struct LoginCmd
{
    int cmd;
};

#define REQUEST_LOGIN_CMD 1000
struct RequestLoginCmd_CS : public LoginCmd
{
    RequestLoginCmd_CS()
    {
        cmd = REQUEST_LOGIN_CMD;
        bzero(name, MAX_CHAR_LENGTH);
        time = 0;
    }

    char name[MAX_CHAR_LENGTH];
    int time;
};

#endif
