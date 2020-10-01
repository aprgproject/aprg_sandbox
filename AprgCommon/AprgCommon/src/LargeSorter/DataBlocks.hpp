#pragma once

#include <algorithm>
#include <functional>
#include <LargeSorter/AlbaLargeSorterConfiguration.hpp>
#include <LargeSorter/AlbaLargeSorterCache.hpp>
#include <LargeSorter/AlbaLargeSorterTypes.hpp>
#include <LargeSorter/DataBlock.hpp>
#include <sstream>

namespace alba{

template <typename ObjectToSort>
class DataBlocks{
    typedef AlbaLargeSorterBlockType<ObjectToSort> BlockType;
    typedef AlbaLargeSorterBlockContainer<ObjectToSort> BlockContainer;
    typedef AlbaLargeSorterBlockIterator<ObjectToSort> BlockIterator;
    typedef AlbaLargeSorterCache<BlockIterator> BlockCache;

public:
    DataBlocks(
            AlbaLargeSorterConfiguration const& configuration,
            BlockCache & memoryCache,
            BlockCache & fileStreamOpenedCache)
        : m_configuration(configuration)
        , m_memoryCache(memoryCache)
        , m_fileStreamOpenedCache(fileStreamOpenedCache)
        , m_numberOfBlocks(0)
    {
        initializeDataBlocks();
    }
    bool isEmpty() const
    {
        for(BlockType const& block : m_blocks)
        {
            if(block.getNumberOfObjects() != 0)
            {
                return false;
            }
        }
        return true;
    }
    BlockIterator getNearestBlockIterator(ObjectToSort const& objectToSort)
    {
        if(isLessThanOrEqual(m_mainIterator->getLowestObject(), objectToSort))
        {
            while((m_mainIterator != m_blocks.end()) && isLessThanOrEqual(m_mainIterator->getLowestObject(), objectToSort))
            {
                m_mainIterator++;
            }
            m_mainIterator--;
        }
        else if(objectToSort < m_mainIterator->getLowestObject())
        {
            while((m_mainIterator != m_blocks.begin()) && (objectToSort < m_mainIterator->getLowestObject()))
            {
                m_mainIterator--;
            }
        }
        return m_mainIterator;
    }
    void moveMainInteratorToStart()
    {
        m_mainIterator = m_blocks.begin();
    }
    void createNewBlockBeforeThisIterator(BlockIterator const& iteratorAfterNewBlock, DataBlockType const blockType)
    {
        std::stringstream ss;
        ss << m_configuration.m_directoryForBlocks << R"(\BLOCK_)" << m_numberOfBlocks << ".txt";
        m_blocks.emplace(iteratorAfterNewBlock, blockType, m_numberOfBlocks, ss.str());
        BlockIterator newBlockIterator(iteratorAfterNewBlock);
        newBlockIterator--;
        m_numberOfBlocks++;
    }
    void deleteBlock(BlockIterator const& iteratorOfBlockToErase)
    {
        bool const isMainIteratorDeleted = m_mainIterator==iteratorOfBlockToErase;
        m_memoryCache.deleteBlock(iteratorOfBlockToErase->getBlockId());
        m_fileStreamOpenedCache.deleteBlock(iteratorOfBlockToErase->getBlockId());
        BlockIterator newIterator= m_blocks.erase(iteratorOfBlockToErase);
        if(isMainIteratorDeleted) { m_mainIterator = newIterator; }
    }
    void addObjectToBlock(BlockIterator const& iteratorOfBlock, ObjectToSort const& objectToSort)
    {
        iteratorOfBlock->add(objectToSort);
        updateCaches(iteratorOfBlock);
    }
    void addObjectToBlockAtTheStart(BlockIterator const& iteratorOfBlock, ObjectToSort const& objectToSort)
    {
        iteratorOfBlock->addAtTheStart(objectToSort);
        updateCaches(iteratorOfBlock);
    }
    void sortThenDoFunctionThenReleaseAllObjects(std::function<void(ObjectToSort const&)> doFunctionForAllObjects)
    {
        for(BlockType& block : m_blocks)
        {
            block.sortThenDoFunctionThenRelease(doFunctionForAllObjects);
        }
        releaseAllBlocks();
        initializeDataBlocks();
    }
    void releaseAllBlocks()
    {
        m_blocks.clear();
        m_memoryCache.clear();
        m_fileStreamOpenedCache.clear();
        m_numberOfBlocks = 0;
    }
    void initializeDataBlocks()
    {
        createNewBlockBeforeThisIterator(m_blocks.begin(), DataBlockType::Memory);
        m_mainIterator = m_blocks.begin();
    }

private:
    void updateCaches(BlockIterator const& iteratorOfBlock)
    {
        switch(iteratorOfBlock->getBlockType())
        {
        case DataBlockType::File:
            m_fileStreamOpenedCache.addBlock(iteratorOfBlock->getBlockId(), iteratorOfBlock);
            break;
        case DataBlockType::Memory:
            m_memoryCache.addBlock(iteratorOfBlock->getBlockId(), iteratorOfBlock);
            break;
        case DataBlockType::Empty:
            break;
        }
    }
    inline bool isLessThanOrEqual(ObjectToSort const& firstTerm, ObjectToSort const& secondTerm)
    {
        return (firstTerm < secondTerm) || (firstTerm == secondTerm);
    }
    AlbaLargeSorterConfiguration const & m_configuration;
    BlockCache & m_memoryCache;
    BlockCache & m_fileStreamOpenedCache;
    unsigned int m_numberOfBlocks;
    BlockContainer m_blocks;
    BlockIterator m_mainIterator;
};

}//namespace alba
