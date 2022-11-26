#pragma once

#include <ostream>

namespace alba
{

template <class ObjectType>
class AlbaFakeCopyable
{
public:

    AlbaFakeCopyable() = default;

    AlbaFakeCopyable(ObjectType const& object)
        : m_object(object)
    {}

    AlbaFakeCopyable(AlbaFakeCopyable const&) // copy constructor does nothing
        : m_object()
    {}

    ObjectType const& getObject() const
    {
        return m_object;
    }

    ObjectType & getObjectReference()
    {
        return m_object;
    }

private:

    friend std::ostream & operator<<(std::ostream & out, AlbaFakeCopyable<ObjectType> const& object)
    {
        out << object.m_object;
        return out;
    }

    ObjectType m_object;
};

} // namespace alba
