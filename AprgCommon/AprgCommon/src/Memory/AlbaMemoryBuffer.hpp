#pragma once

#include <string>
#include <vector>

namespace alba
{

class AlbaMemoryBuffer
{
public:
    AlbaMemoryBuffer();
    AlbaMemoryBuffer(void* bufferPointer, unsigned int size);
    operator bool() const;
    bool hasContent() const;
    unsigned int getSize() const;
    void* getBufferPointer();
    void const* getConstantBufferPointer() const;
    void clear();
    void clearAndSetNewData(void* bufferPointer, unsigned int size);
    void* addDataForWritingOutside(unsigned int size);
    void addData(void* bufferPointer, unsigned int size);
    std::string getDisplayableString() const;

private:
    std::vector<unsigned char> m_buffer;
    void* m_bufferPointer;
};

}//namespace alba
