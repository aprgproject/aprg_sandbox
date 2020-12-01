#include "AlbaMemoryBuffer.hpp"

#include <Container/AlbaContainerHelper.hpp>

#include <memory>

using namespace std;

namespace alba
{

AlbaMemoryBuffer::AlbaMemoryBuffer()
{}

AlbaMemoryBuffer::AlbaMemoryBuffer(void* bufferPointer, unsigned int size)
{
    addData(bufferPointer, size);
}

AlbaMemoryBuffer::operator bool() const
{
    return hasContent();
}

bool AlbaMemoryBuffer::hasContent() const
{
    return m_buffer.size()>0;
}

unsigned int AlbaMemoryBuffer::getSize() const
{
    return m_buffer.size();
}

void* AlbaMemoryBuffer::getBufferPointer()
{
    return m_buffer.begin().base();
}

void const* AlbaMemoryBuffer::getConstantBufferPointer() const
{
    return m_buffer.begin().base();
}

void AlbaMemoryBuffer::clear()
{
    m_buffer.clear();
}

void AlbaMemoryBuffer::clearAndSetNewData(void* bufferPointer, unsigned int size)
{
    clear();
    addData(bufferPointer, size);
}

void AlbaMemoryBuffer::resize(unsigned int size)
{
    m_buffer.resize(size);
}

void* AlbaMemoryBuffer::addDataAndReturnBeginOfAdditionalData(unsigned int additionalSize)
{
    unsigned int oldSize = getSize();
    m_buffer.resize(oldSize+additionalSize);
    return m_buffer.begin().base()+oldSize;
}

void AlbaMemoryBuffer::addData(void* bufferPointer, unsigned int additionalSize)
{
    unsigned char* bufferPointerByteType = (unsigned char*)bufferPointer;
    for(unsigned int i=0; i<additionalSize; i++)
    {
        m_buffer.emplace_back(bufferPointerByteType[i]);
    }
}
string AlbaMemoryBuffer::getDisplayableString() const
{
    return containerHelper::getStringFromContentsOfContainerWithNumberFormat(m_buffer, ", ");
}


}//namespace alba
