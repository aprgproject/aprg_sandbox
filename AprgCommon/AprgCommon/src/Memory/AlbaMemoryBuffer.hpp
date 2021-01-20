#pragma once

#include <string>
#include <vector>

namespace alba
{

class AlbaMemoryBuffer
{
public:
    AlbaMemoryBuffer();
    AlbaMemoryBuffer(void const* bufferPointer, unsigned int const size);
    operator bool() const;
    bool hasContent() const;
    unsigned int getSize() const;    void* getBufferPointer();
    void const* getConstantBufferPointer() const;
    void clear();
    void clearAndSetNewData(void* bufferPointer, unsigned int const size);
    void resize(unsigned int const size);
    void resize(unsigned int const size, unsigned int const initialValue);
    void* addDataAndReturnBeginOfAdditionalData(unsigned int const size);
    void addData(void const* bufferPointer, unsigned int const size);
    std::string getDisplayableString() const;

private:    std::vector<unsigned char> m_buffer;
};

}//namespace alba