#pragma once

#include <sstream>

namespace alba
{

template <class ObjectType>
class AlbaFakeCopyable
{
public:
    AlbaFakeCopyable()
        : m_object()
    {}

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
    ObjectType m_object;
};

template <typename ObjectType>
std::ostream & operator<<(std::ostream & out, AlbaFakeCopyable<ObjectType> const& object)
{
    out << object.getObject();
    return out;
}

} // namespace alba
