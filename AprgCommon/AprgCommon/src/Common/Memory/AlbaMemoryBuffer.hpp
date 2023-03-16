#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>

#include <cstdint>
#include <cstring>
#include <ostream>
#include <vector>

namespace alba
{

class AlbaMemoryBuffer
{
public:

    AlbaMemoryBuffer() = default;
    AlbaMemoryBuffer(void const* sourcePointer, unsigned int const size);

    AlbaMemoryBuffer(AlbaMemoryBuffer const&) = default;
    AlbaMemoryBuffer(AlbaMemoryBuffer && buffer) = default;
    AlbaMemoryBuffer& operator=(AlbaMemoryBuffer const&) = default;
    AlbaMemoryBuffer& operator=(AlbaMemoryBuffer && any) = default;

    operator bool() const; // not explicit
    bool hasContent() const;
    unsigned int getSize() const;
    void const* getConstantBufferPointer() const;

    void* getBufferPointer();
    void clear();
    void clearAndSetNewData(void* sourcePointer, unsigned int const size);
    void resize(unsigned int const size);
    void resize(unsigned int const size, unsigned char const initialValue);
    void* resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(unsigned int const size);
    void addData(void const* sourcePointer, unsigned int const size);

    template <typename ObjectType> void saveObject(ObjectType const& object)
    {
        // lets not check if its POD because it works on other cases
        unsigned int objectSize = sizeof(object);
        resize(objectSize);
        void const* sourcePointer = static_cast<void const*>(&object);
        void * destinationVoidPointer = getBufferPointer();
        memcpy(destinationVoidPointer, sourcePointer, objectSize);
    }

    template <typename ObjectType> ObjectType retrieveObjectAsConstReference() const
    {
        // lets not check if its POD because it works on other cases
        return *reinterpret_cast<ObjectType const*>(getConstantBufferPointer());
    }

    template <typename ObjectType> ObjectType& retrieveObjectAsReference()
    {
        // lets not check if its POD because it works on other cases
        return *reinterpret_cast<ObjectType *>(getBufferPointer());
    }

private:

    friend std::ostream & operator<<(std::ostream & out, AlbaMemoryBuffer const& memoryBuffer);

    std::vector<uint8_t> m_buffer;
};

}//namespace alba
