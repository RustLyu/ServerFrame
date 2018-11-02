#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <algorithm> 
#include <vector>

#include "msg.h"

/*------------------NOTICE-------------------------*/
/// COPY FROM MUDUO BY LVSHUIKU
/// SOURCE https://github.com/chenshuo/muduo
/// A buffer class modeled after org.jboss.netty.buffer.ChannelBuffer
///
/// @code
/// +-------------------+------------------+------------------+
/// | prependable bytes |  readable bytes  |  writable bytes  |
/// |                   |     (CONTENT)    |                  |
/// +-------------------+------------------+------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size

class Buffer
{
public:
    static size_t initPrepenLength = 8;
    static size_t initContentLength = 1024;

    Buffer()
    {
        buffer_(initPrepenLength + initContentLength);
        writeIndex_ = initPrepenLength;
        readIndex_ = initPrepenLength;
    }

    ~Buffer()
    {
    }
    
    char* beginWrite()
    {
        return &*buffer_.begin() + writeIndex_;
    }

    const char* beginWrite()
    {
        return &*buffer_.begin() + writeIndex_;
    }

    char* beginRead()
    {
        return &*buffer_.begin() + readIndex_;
    }

    const char* beginRead()
    {
        return &*buffer_.begin() + readIndex_;
    }
    
    void append(char* data, size_t len)
    {
        ensureSizeEnough(len);
        addWriteIndex(len);
        std::copy(data, data + len, beginWrite());
    }

    size_t readAble()
    {
        return writeIndex_ - readIndex_;
    }

    size_t writeAble()
    {
        return buffer_.size() - writeIndex_;
    }

    void ensureSizeEnough(void len)
    {   
        if (writeAble() < len)
        {
            makeSpace(len);
        }
    }

    size_t space()
    {
        return buffer_.size() - writeIndex_;
    }

    void pop(char* data, size_t len)
    {
        if(len > readAble())
        {
            return;
        }
        readIndex_ += len;
        addReadIndex(len);
        std::copy(beginWrite(), beginWrite() + len, data)
    }
    
    void addWriteIndex(size_t len)
    {
        writeIndex_ += len;
    }
   
    void addReadIndex(size_t len)
    {
        readIndex_ += len;
    }

    const size_t prependBytes()
    {
        return readIndex_;
    }
    
private:
    void makeSpace(size_t len)
    {
        if((prependBytes() + writeAble()) < len + initPrepenLength)
        {
            // TODO copy has assign bytes
            buffer_.resize(writeIndex_ + len);
        }
        else
        {
            std::copy(beginRead(), beginRead() + readAble(), &*buffer_.begin());
            readIndex_ = initPrepenLength;
            writeIndex_ = initPrepenLength + readAble();
        }
    }

private:
    std::vector<char> buffer_;
    int  readIndex_;
    int  writeIndex_;
};

#endif
