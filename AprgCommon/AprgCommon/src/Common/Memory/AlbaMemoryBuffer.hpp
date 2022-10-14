#pragma once

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace alba
{

class AlbaMemoryBuffer
{
public:

    AlbaMemoryBuffer() = default;
    AlbaMemoryBuffer(void const* sourcePointer, unsigned int const size);

    operator bool() const;
    bool hasContent() const;
    unsigned int getSize() const;    void* getBufferPointer();
    void const* getConstantBufferPointer() const;
    void clear();
    void clearAndSetNewData(void* sourcePointer, unsigned int const size);    void resize(unsigned int const size);
    void resize(unsigned int const size, unsigned char const initialValue);
    void* resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(unsigned int const size);
    void addData(void const* sourcePointer, unsigned int const size);
    std::string getDisplayableString() const;
    template <typename ObjectType> void saveObject(ObjectType const& object)
    {
        unsigned int objectSize = sizeof(object);
        resize(objectSize);
        void const* sourcePointer = static_cast<void const*>(&object);
        void * destinationVoidPointer = getBufferPointer();
        memcpy(destinationVoidPointer, sourcePointer, objectSize);
    }
    template <typename ObjectType> ObjectType& retrieveObject()
    {
        return *reinterpret_cast<ObjectType *>(getBufferPointer());
    }

private:
    std::vector<uint8_t> m_buffer;
};

}//namespace alba
