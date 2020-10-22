#include <AlbaMemoryBuffer.hpp>

namespace alba
{

AlbaMemoryBuffer::AlbaMemoryBuffer()
    : m_hasContent(0)
    , m_size(0)
    , m_bufferPointer(nullptr)
{}

AlbaMemoryBuffer::AlbaMemoryBuffer(AlbaMemoryBuffer const& memoryBuffer)
    : m_hasContent(0)
    , m_size(0)
    , m_bufferPointer(nullptr)
{
    setNewBuffer(memoryBuffer.m_bufferPointer, memoryBuffer.m_size);
}

AlbaMemoryBuffer::~AlbaMemoryBuffer()
{
    releaseBufferIfNeeded();
}

AlbaMemoryBuffer::operator bool() const
{
    return m_hasContent;
}

unsigned int AlbaMemoryBuffer::getSize() const
{
    return m_size;
}

void* AlbaMemoryBuffer::getBufferPointer()
{
    return m_bufferPointer;
}

void AlbaMemoryBuffer::reAllocateBuffer(unsigned int size)
{
     releaseBufferIfNeeded();
     m_hasContent = true;
     m_size = size;
     m_bufferPointer = malloc(size);
}

void AlbaMemoryBuffer::releaseBufferIfNeeded()
{
    if(m_hasContent)
    {
        free(m_bufferPointer);
    }
    m_hasContent = false;
    m_size = 0;
    m_bufferPointer = nullptr;
}

void AlbaMemoryBuffer::setNewBuffer(void* bufferPointer, unsigned int size)
{
    reAllocateBuffer(size);
    memcpy(m_bufferPointer, bufferPointer, size);
}


}//namespace alba
