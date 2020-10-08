#pragma once

#include <algorithm>
#include <LargeSorter/AlbaLargeSorterTypes.hpp>
#include <LargeSorter/DataBlock.hpp>
#include <deque>

namespace alba
{

template <typename BlockInformation>
class AlbaLargeSorterCache
{
public:
    struct BlockInformationPair
    {
        BlockInformationPair(unsigned int blockId, BlockInformation const& blockInformation)
            : m_blockId(blockId)
            , m_blockInformation(blockInformation)
        {}
        unsigned int m_blockId;
        BlockInformation m_blockInformation;
    };
    typedef std::deque<BlockInformationPair> BlocksInformationContainer;

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
        m_blocksInformationCache.erase(std::remove_if(m_blocksInformationCache.begin(), m_blocksInformationCache.end(), [blockId](BlockInformationPair const& blockInformation)
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
    BlocksInformationContainer & getContainerReference()
    {
        return m_blocksInformationCache;
    }
    void clear()
    {
        m_blocksInformationCache.clear();
    }

private:
     BlocksInformationContainer m_blocksInformationCache;
};

}
