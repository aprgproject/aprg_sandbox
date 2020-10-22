#pragma once

#include <windows.h>

namespace alba
{

class AlbaMemoryBuffer
{
public:
    AlbaMemoryBuffer();
    AlbaMemoryBuffer(AlbaMemoryBuffer const& memoryBuffer);
    ~AlbaMemoryBuffer();
    operator bool() const;
    unsigned int getSize() const;
    void* getBufferPointer();
    void reAllocateBuffer(unsigned int size);
    void releaseBufferIfNeeded();
    void setBuffer(void* bufferPointer, unsigned int size);

private:
    bool m_hasContent;
    unsigned int m_size;
    void* m_bufferPointer;
};

}//namespace alba
