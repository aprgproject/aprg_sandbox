#pragma once

namespace alba{

template<typename TypeIterator>
TypeIterator getMovedIterator(TypeIterator currentIterator, int index)
{
    while(index>0)
    {
        currentIterator++;
        index--;
    }
    while(index<0)
    {
        currentIterator--;
        index++;
    }
    return currentIterator;
}

}//namespace alba
