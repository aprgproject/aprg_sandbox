#pragma once

#include <Common/Memory/AlbaMemoryBuffer.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>
#include <Common/Types/AlbaTypeId.hpp>

#include <cassert>
#include <ostream>

namespace alba {

// class [[deprecated("Use std::any instead! (needs c++17)")]] AlbaAny
// lets remove [[deprecated]] to avoid unnecessary warnings
class AlbaAny {
    // This requires copy constructor and default constructor on ContentType
public:
    AlbaAny() : m_savedMemory(), m_typeId(EMPTY_TYPE_ID) {}

    template <typename ContentType>
    AlbaAny(ContentType const& content)  // copy constructor for other ContentType
        : m_savedMemory(std::addressof(content), sizeof(content)), m_typeId(GetTypeId<ContentType>()) {
        // Herb Sutter: Dont xray objects. Me: It has standard layout so it can be xray-ed.
        static_assert(typeHelper::hasStandardLayout<ContentType>(), "ObjectType needs to have standard layout.");
    }

    // rule of zero

    explicit operator bool() const  // not explicit
    {
        return hasContent();
    }
    bool hasContent() const { return m_savedMemory.hasContent(); }

    template <typename ContentType>    ContentType getContentAs() const {
        assert(m_typeId == GetTypeId<ContentType>());  // not allowing any mistakes
        return m_savedMemory.retrieveObjectAsConstReference<ContentType>();
    }

    template <typename ContentType>
    ContentType& getContentReferenceAs() {
        assert(m_typeId == GetTypeId<ContentType>());  // not allowing any mistakes
        return m_savedMemory.retrieveObjectAsReference<ContentType>();
    }

    template <typename ContentType>
    void saveContent(ContentType const& content) {
        m_savedMemory.saveObject<ContentType>(content);
    }

    void clear() { m_savedMemory.clear(); }

private:
    friend std::ostream& operator<<(std::ostream& out, AlbaAny const& any) {
        out << "hasContent: " << any.hasContent() << "\n";
        if (any.hasContent()) {
            out << " savedMemory: " << any.m_savedMemory;
        }
        return out;
    }

    AlbaMemoryBuffer m_savedMemory;
    // void* approach was disregarded because we need to remember the type (no RTTI).
    TypeId m_typeId;
};

}  // namespace alba
