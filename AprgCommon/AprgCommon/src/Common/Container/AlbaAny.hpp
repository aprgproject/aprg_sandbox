#pragma once

#include <Common/Types/AlbaTypeId.hpp>
#include <Common/Memory/AlbaMemoryBuffer.hpp>

#include <cassert>
#include <ostream>

namespace alba
{

//class [[deprecated("Use std::any instead! (needs c++17)")]] AlbaAny // lets remove [[deprecated]] to avoid unnecessary warnings
class AlbaAny
{
    // This requires copy constructor and default constructor on ContentType
public:

    AlbaAny()
        : m_savedMemory()
        , m_typeId(EMPTY_TYPE_ID)
    {}

    template <typename ContentType>
    AlbaAny(ContentType const& content) // copy constructor for other ContentType
        : m_savedMemory(std::addressof(content), sizeof(content))
        , m_typeId(GetTypeId<ContentType>())

    {}

    AlbaAny(AlbaAny const&) = default;
    AlbaAny(AlbaAny &&) = delete;
    AlbaAny& operator=(AlbaAny const&) = default;
    AlbaAny& operator=(AlbaAny && any) = delete;

    operator bool() const
    {
        return hasContent();
    }

    bool hasContent() const
    {
        return m_savedMemory.hasContent();
    }

    template <typename ContentType>
    ContentType getContentAs() const
    {
        assert(m_typeId == GetTypeId<ContentType>()); // not allowing any mistakes
        return m_savedMemory.retrieveObjectAsConstReference<ContentType>();
    }

    template <typename ContentType>
    ContentType& getContentReferenceAs()
    {
        assert(m_typeId == GetTypeId<ContentType>()); // not allowing any mistakes
        return m_savedMemory.retrieveObjectAsReference<ContentType>();
    }

    template <typename ContentType>
    void saveContent(ContentType const& content)
    {
        m_savedMemory.saveObject<ContentType>(content);
    }

    void clear()
    {
        m_savedMemory.clear();
    }

private:

    friend std::ostream & operator<<(std::ostream & out, AlbaAny const& any)
    {
        out << "hasContent: " << any.hasContent() << "\n";
        if(any.hasContent())
        {
            out << " savedMemory: " << any.m_savedMemory;        }
        return out;
    }
    AlbaMemoryBuffer m_savedMemory; // void* approach was disregarded because we need to remember the type (which leads to enable RTTI).
    TypeId m_typeId;
};

} // namespace alba
