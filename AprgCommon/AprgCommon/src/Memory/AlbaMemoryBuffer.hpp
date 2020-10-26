#pragma once

namespace alba
{

class AlbaMemoryBuffer
{
public:
    AlbaMemoryBuffer();
    AlbaMemoryBuffer(AlbaMemoryBuffer const& memoryBuffer);
    ~AlbaMemoryBuffer();
    operator bool() const;
    bool hasContent() const;
    unsigned int getSize() const;
    void* getBufferPointer();
    void reAllocateBuffer(unsigned int size);
    void releaseBufferIfNeeded();
    void setNewBuffer(void* bufferPointer, unsigned int size);

private:
    bool m_hasContent;
    unsigned int m_size;
    void* m_bufferPointer;
};

}//namespace alba
