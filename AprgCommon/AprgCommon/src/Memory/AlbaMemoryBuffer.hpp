#pragma once

#include <cstring>
#include <string>
#include <vector>
namespace alba
{
class AlbaMemoryBuffer
{
public:
    AlbaMemoryBuffer();
    AlbaMemoryBuffer(void const* sourcePointer, unsigned int const size);
    operator bool() const;
    bool hasContent() const;
    unsigned int getSize() const;
    void* getBufferPointer();
    void const* getConstantBufferPointer() const;
    void clear();
    void clearAndSetNewData(void* sourcePointer, unsigned int const size);
    void resize(unsigned int const size);
    void resize(unsigned int const size, unsigned int const initialValue);
    void* resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(unsigned int const size);
    void addData(void const* bufferPointer, unsigned int const size);
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

private:    std::vector<unsigned char> m_buffer;};

}//namespace alba