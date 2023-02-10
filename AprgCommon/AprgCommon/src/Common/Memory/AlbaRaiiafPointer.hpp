#pragma once

#include <cassert>
#include <functional>

namespace alba
{

//RAIIAF
//Resource Aquisition Is In A Function
//anti RAII :(

class AlbaRaiiafPointer
{
public:
    AlbaRaiiafPointer()
        : m_hasContent(0)
        , m_voidPointer(nullptr)
    {}

    ~AlbaRaiiafPointer()
    {
        assert(!m_hasContent);
    }

    template <typename Type> Type get()
    {
        return *(static_cast<Type*>(m_voidPointer));
    }

    template <typename Type> Type& getReference()
    {
        return *(static_cast<Type*>(m_voidPointer));
    }

    template <typename Type> void deAllocate()
    {
        if(m_hasContent)
        {
            delete(static_cast<Type*>(m_voidPointer));
            m_hasContent = false;
        }
    }

    template <typename Type> void setAndAllocateNewContent(Type const& reference)
    {
        assert(!m_hasContent);
        m_hasContent = true;
        m_voidPointer = new Type(reference);
    }

private:
    bool m_hasContent;
    void* m_voidPointer;
};

}//namespace alba
