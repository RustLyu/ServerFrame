#ifndef TIMER_H
#define TIMER_H

#include <boost/function.hpp>
#include "thread.h"

typedef boost::function<void ()> TimerCALLBACK;

// get now time (msec)
int64_t getCurrentTime()
{    
    struct timeval tv;    
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;    
} 

class Timer
{
public:
    Timer(double timestamp);
    ~Timer();
    bool start();
    bool stop();
    void setCallBack(TimerCALLBACK call)
    {
        call_ = call;
    }
private:
    void loop();
private:
    double timestamp_;
    TimerCALLBACK call_;
    Thread* thread_;
};

#endif
