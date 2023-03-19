#pragma once

#include <ostream>

namespace alba
{

template <class ObjectType>
class AlbaFakeCopyable
{
public:

    // rule of five or six

    AlbaFakeCopyable() = default;

    AlbaFakeCopyable(ObjectType const& object)
        : m_object(object)
    {}

    AlbaFakeCopyable(AlbaFakeCopyable const&) // copy constructor calls default constructor
        : m_object()
    {}

    AlbaFakeCopyable & operator=(AlbaFakeCopyable const&)  // copy assignment calls default constructor
    {}

    AlbaFakeCopyable(AlbaFakeCopyable &&) = default;
    AlbaFakeCopyable & operator= (AlbaFakeCopyable &&) = default;

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
