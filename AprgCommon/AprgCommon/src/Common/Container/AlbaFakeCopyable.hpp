#pragma once

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

    ObjectType const& getObject()
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

} // namespace alba
