#include "AlbaMemoryBuffer.hpp"

#include <Common/Container/AlbaContainerHelper.hpp>

#include <memory>

using namespace std;

namespace alba
{

AlbaMemoryBuffer::AlbaMemoryBuffer(void const* sourcePointer, unsigned int const size)
{
    addData(sourcePointer, size);}

AlbaMemoryBuffer::operator bool() const
{    return hasContent();
}

bool AlbaMemoryBuffer::hasContent() const
{
    return !m_buffer.empty();
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

void AlbaMemoryBuffer::clearAndSetNewData(void* sourcePointer, unsigned int const size)
{
    clear();
    addData(sourcePointer, size);
}

void AlbaMemoryBuffer::resize(unsigned int const size)
{
    m_buffer.resize(size);
}

void AlbaMemoryBuffer::resize(unsigned int size, unsigned char const initialValue)
{
    m_buffer.resize(size, initialValue);
}

void* AlbaMemoryBuffer::resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(unsigned int const additionalSize)
{
    unsigned int oldSize = m_buffer.size();
    m_buffer.resize(oldSize+additionalSize);
    return m_buffer.begin().base()+oldSize;
}

void AlbaMemoryBuffer::addData(void const* sourcePointer, unsigned int const additionalSize)
{
    void* destinationVoidPointer = resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(additionalSize);
    memcpy(destinationVoidPointer, sourcePointer, additionalSize);
}

string AlbaMemoryBuffer::getDisplayableString() const
{
    return containerHelper::getStringFromContentsWithNumberFormat(m_buffer);
}


}//namespace alba
