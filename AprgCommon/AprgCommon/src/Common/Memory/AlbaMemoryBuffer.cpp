#include "AlbaMemoryBuffer.hpp"

#include <Common/Container/AlbaContainerHelper.hpp>

#include <memory>

using namespace std;

namespace alba {

AlbaMemoryBuffer::AlbaMemoryBuffer(void const* sourcePointer, size_t const size) { addData(sourcePointer, size); }

AlbaMemoryBuffer::operator bool() const { return hasContent(); }

AlbaMemoryBuffer::ByteType AlbaMemoryBuffer::operator[](size_t const index) const { return m_buffer[index]; }

AlbaMemoryBuffer::ByteType& AlbaMemoryBuffer::operator[](size_t const index) { return m_buffer[index]; }

bool AlbaMemoryBuffer::hasContent() const { return !m_buffer.empty(); }

size_t AlbaMemoryBuffer::getSize() const { return m_buffer.size(); }
void const* AlbaMemoryBuffer::getConstantBufferPointer() const { return static_cast<void const*>(m_buffer.data()); }

void* AlbaMemoryBuffer::getBufferPointer() { return static_cast<void*>(m_buffer.data()); }

void AlbaMemoryBuffer::clear() { m_buffer.clear(); }

void AlbaMemoryBuffer::clearAndSetNewData(void* sourcePointer, size_t const size) {
    clear();
    addData(sourcePointer, size);
}

void AlbaMemoryBuffer::resize(size_t const size) { m_buffer.resize(size); }

void AlbaMemoryBuffer::resize(size_t size, uint8_t const initialValue) { m_buffer.resize(size, initialValue); }

void* AlbaMemoryBuffer::resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(size_t const additionalSize) {
    size_t oldSize = m_buffer.size();
    m_buffer.resize(oldSize + additionalSize);
    return begin(m_buffer).base() + oldSize;
}

void AlbaMemoryBuffer::addData(void const* sourcePointer, size_t const additionalSize) {
    void* destinationVoidPointer = resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(additionalSize);
    memcpy(destinationVoidPointer, sourcePointer, additionalSize);
}

std::ostream& operator<<(std::ostream& out, AlbaMemoryBuffer const& memoryBuffer) {
    containerHelper::saveContentsInDecimalAndHexadecimalFormat<uint8_t, std::vector, size_t>(
        out, memoryBuffer.m_buffer);
    return out;
}

}  // namespace alba
