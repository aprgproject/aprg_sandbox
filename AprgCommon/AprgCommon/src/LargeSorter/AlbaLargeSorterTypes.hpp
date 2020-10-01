#pragma once

#include <LargeSorter/DataBlock.hpp>
#include <list>

namespace alba{

template <typename ObjectToSort> using AlbaLargeSorterBlockType = DataBlock<ObjectToSort>;
template <typename ObjectToSort> using AlbaLargeSorterBlockContainer = std::list<AlbaLargeSorterBlockType<ObjectToSort>>;template <typename ObjectToSort> using AlbaLargeSorterBlockIterator = typename AlbaLargeSorterBlockContainer<ObjectToSort>::iterator;

}
