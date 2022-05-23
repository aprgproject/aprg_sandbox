#pragma once

#include <Algorithm/Sort/LargeSorter/AlbaLargeSorterTypes.hpp>
#include <Algorithm/Sort/LargeSorter/DataBlock.hpp>

#include <algorithm>
#include <deque>

namespace alba
{

namespace algorithm
{

template <typename BlockInformation>
class DataBlockCache
{
public:
    struct BlockCacheEntry
    {
        BlockCacheEntry(unsigned int blockId, BlockInformation const& blockInformation)
            : m_blockId(blockId)
            , m_blockInformation(blockInformation)
        {}
        unsigned int m_blockId;
        BlockInformation m_blockInformation;
    };

    using BlockCacheContainer = std::deque<BlockCacheEntry>;

    void addBlock(unsigned const int blockId, BlockInformation const& iterator)
    {
        if(m_blocksInformationCache.empty() || m_blocksInformationCache.front().m_blockId != blockId)
        {
            deleteBlock(blockId);
            m_blocksInformationCache.emplace_front(blockId, iterator);
        }
    }
    void deleteBlock(unsigned const int blockId)
    {
        m_blocksInformationCache.erase(std::remove_if(m_blocksInformationCache.begin(), m_blocksInformationCache.end(), [blockId](BlockCacheEntry const& blockInformation)
        {
            return blockId == blockInformation.m_blockId;
        }), m_blocksInformationCache.end());
    }
    BlockInformation popTheEarliestAddedBlock()
    {
        if(!m_blocksInformationCache.empty())
        {
            BlockInformation lastAddedBlock(m_blocksInformationCache.back().m_blockInformation);
            m_blocksInformationCache.pop_back();
            return lastAddedBlock;
        }
        return BlockInformation();
    }
    BlockCacheContainer & getContainerReference()
    {
        return m_blocksInformationCache;
    }
    void clear()
    {
        m_blocksInformationCache.clear();
    }

private:
     BlockCacheContainer m_blocksInformationCache;
};

}

}
