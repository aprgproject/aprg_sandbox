#pragma once

#include <functional>
#include <cassert>

namespace alba
{

//RAIIAF
//Request Aquisition Is In A Function
//anti RAII :(

class AlbaRaiiafPointer
{
public:
    AlbaRaiiafPointer()
        : m_hasContent(0)
    {}

    ~AlbaRaiiafPointer()
    {
        assert(!m_hasContent);
    }

    template <typename Type> Type get()
    {
        return *((Type*)m_voidPointer);
    }

    template <typename Type> Type& getReference()
    {
        return *((Type*)m_voidPointer);
    }

    template <typename Type> void deAllocate()
    {
        if(m_hasContent)
        {
            delete((Type*)m_voidPointer);
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
