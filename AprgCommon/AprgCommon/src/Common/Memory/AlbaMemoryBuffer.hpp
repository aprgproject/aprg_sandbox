#pragma once

#include <Common/Types/AlbaTypeHelper.hpp>

#include <cstdint>
#include <cstring>
#include <ostream>
#include <vector>

namespace alba {

class AlbaMemoryBuffer {
public:
    using ByteType = uint8_t;
    using BufferContainer = std::vector<uint8_t>;

    AlbaMemoryBuffer() = default;    AlbaMemoryBuffer(void const* sourcePointer, size_t const size);

    // rule of zero

    explicit operator bool() const;  // not explicit
    ByteType operator[](size_t const index) const;
    ByteType& operator[](size_t const index);
    // If a class has a subscript operator, it usually should define two versions:
    // one that returns a plain reference and the other that is a const member and returns a reference to const.

    bool hasContent() const;
    size_t getSize() const;
    void const* getConstantBufferPointer() const;
    void* getBufferPointer();
    void clear();
    void clearAndSetNewData(void* sourcePointer, size_t const size);
    void resize(size_t const size);
    void resize(size_t const size, uint8_t const initialValue);
    void* resizeWithAdditionalSizeAndReturnBeginOfAdditionalData(size_t const size);
    void addData(void const* sourcePointer, size_t const size);

    template <typename ObjectType>
    void saveObject(ObjectType const& object) {
        // Herb Sutter: Dont xray objects. Me: It has standard layout so it can be xray-ed.
        static_assert(typeHelper::hasStandardLayout<ObjectType>(), "ObjectType needs to have standard layout.");
        size_t objectSize = sizeof(object);
        resize(objectSize);
        void const* sourcePointer = static_cast<void const*>(&object);
        void* destinationVoidPointer = getBufferPointer();
        memcpy(destinationVoidPointer, sourcePointer, objectSize);
    }

    template <typename ObjectType>
    ObjectType retrieveObjectAsConstReference() const {
        // Herb Sutter: Dont xray objects. Me: It has standard layout so it can be xray-ed.
        static_assert(typeHelper::hasStandardLayout<ObjectType>(), "ObjectType needs to have standard layout.");
        return *reinterpret_cast<ObjectType const*>(getConstantBufferPointer());
    }

    template <typename ObjectType>
    ObjectType& retrieveObjectAsReference() {
        // Herb Sutter: Dont xray objects. Me: It has standard layout so it can be xray-ed.
        static_assert(typeHelper::hasStandardLayout<ObjectType>(), "ObjectType needs to have standard layout.");
        return *reinterpret_cast<ObjectType*>(getBufferPointer());
    }

private:
    friend std::ostream& operator<<(std::ostream& out, AlbaMemoryBuffer const& memoryBuffer);

    BufferContainer m_buffer;
};

}  // namespace alba
