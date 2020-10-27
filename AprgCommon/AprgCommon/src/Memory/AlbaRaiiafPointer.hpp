#pragma once

#include <functional>
#include <iostream>

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
        if(m_hasContent)
        {
            std::cout<<"AlbaRaiiafPointer::~AlbaRaiiafPointer | Possible memory leak. AlbaRaiiafPointer has still some content."<<std::endl;
        }
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
        if(m_hasContent)
        {
            std::cout<<"AlbaRaiiafPointer::setAndAllocateNewContent | AlbaRaiiafPointer has still some content cannot be replaced"<<std::endl;
        }
        else
        {
            m_hasContent = true;
            m_voidPointer = new Type(reference);
        }
    }

private:
    bool m_hasContent;
    void* m_voidPointer;
};

}//namespace alba
