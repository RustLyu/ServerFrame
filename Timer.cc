#include <boost/bind.hpp>
#include <sys/time.h>
#include "timer.h"

Timer::Timer(double timestamp, TimerCALLBACK call)
{
    timestamp_ = timestamp;
    call_ = call;
    thread_ = Thread::CreatThread(boost::bind(&Timer::loop, nullptr));
}

Timer::~Timer()
{
    Thread::DeleteThread(thread_->getTid());
}

int Timer::start()
{
    if(thread_.join() != 0)
    {
    }
    return true;
}

int Timer::stop()
{
    if( thread_.stop() != 0)
    {
        std::cout << "timer stop error" << std::endl;
        return 1;
    }
    std::cout << "timer stop success" << std::endl;
    return 0;
}

void Timer::loop()
{
    int64_t now = getCurrentTime();
    int64_t last = now;
    for(;;)
    {
        now = getCurrentTime();
        if((now - last) >= timestamp_)
        {
            call_();
        }
        else
            continue;
        last = getCurrentTime();
        if((last - now) > timestamp_)
        {
            std::cout << "time out: " << last - now << std::endl;
        }
    }
}


