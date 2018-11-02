#/bin/bash

g++ msg.h epoller.h epoller.cc server.h server.cc -o server -lpthread
g++ msg.h client.h client.cc -o client -lpthread
