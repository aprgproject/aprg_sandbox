#pragma once

#include <list>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename ObjectToSort> class DataBlock;
template <typename ObjectToSort> using AlbaLargeSorterBlockType = DataBlock<ObjectToSort>;
template <typename ObjectToSort> using AlbaLargeSorterBlockContainer = std::list<AlbaLargeSorterBlockType<ObjectToSort>>;template <typename ObjectToSort> using AlbaLargeSorterBlockIterator = typename AlbaLargeSorterBlockContainer<ObjectToSort>::iterator;

template <typename BlockIterator> class DataBlockCache;
template <typename BlockIterator> using AlbaLargeSorterBlockCache = DataBlockCache<BlockIterator>;template <typename BlockIterator> using AlbaLargeSorterBlockCacheEntry = typename AlbaLargeSorterBlockCache<BlockIterator>::BlockCacheEntry;
template <typename BlockIterator> using AlbaLargeSorterBlockCacheContainer = typename AlbaLargeSorterBlockCache<BlockIterator>::BlockCacheContainer;

using Indexes = std::vector<unsigned int> ;

}

}